#include <iostream>
#include <mpi.h>
#include "Gamemaster.h"
#include "Challenger.h"
#include "Guess.h"
#include <vector>
#include <cmath>
#include <random>

int main(int argc, char *argv[]) {
    int id, nb_instance, len;
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    const int gm_id = 0;
    int buf = -1;
    const int size_secret = 3;
    const int nbr_colors = 3;


    Gamemaster gm;
    Challenger ch;


    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &nb_instance);
    //MPI_Get_processor_name(processor_name, &len);

    MPI_Group world_group;
    MPI_Comm_group(MPI_COMM_WORLD, &world_group);
    int ranks[nb_instance-1];
    for (size_t i = 0; i<nb_instance-1;++i) ranks[i] = i+1;
    //for(auto f: ranks){std::cout<<f<<std::endl;}
    MPI_Group challengers_group;
    MPI_Group_incl(world_group, nb_instance - 1, ranks, &challengers_group);

    MPI_Comm challengers_comm;
    MPI_Comm_create_group(MPI_COMM_WORLD, challengers_group, 0, &challengers_comm);
    int challengers_rank, challengers_size;
    if(MPI_COMM_NULL  != challengers_comm) {
        MPI_Comm_rank(challengers_comm, &challengers_rank);
        MPI_Comm_size(challengers_comm, &challengers_size);
    }
    //std::cout<<"ch rank: "<<challengers_rank<<"id: "<<id<<std::endl;
/*    int in = 3;
    if (challengers_rank == 0){
        in = -1;
    }

    if (id != 0){
        std::cout<<"id: "<<id<<"ch_r: "<<challengers_rank<<"in: "<<in<<std::endl;
        MPI_Bcast(&in, 1, MPI_INT, 0, challengers_comm);
        std::cout<<"id: "<<id<<"ch_r: "<<challengers_rank<<"in: "<<in<<std::endl;
    }*/





    if (id == gm_id){
        gm = Gamemaster(size_secret);



    }
    else{
        int nbr_rows = (int) std::pow(nbr_colors, size_secret);
        //int all_guesses[nbr_rows][size_secret];
        std::vector<Guess> all_guesses;
        //this needs to be replaced to create the combinations of possible guesses dynamically
        for (size_t i=0; i<nbr_colors; i++){
            for (size_t j=0; j<nbr_colors; j++){
                for (size_t k=0; k<nbr_colors; k++){
                    std::vector<int> tmp;
                    tmp.push_back(i);
                    tmp.push_back(j);
                    tmp.push_back(k);
                    Guess tmp_guess = Guess(tmp);
                    all_guesses.push_back(tmp_guess);
                }
            }
        }
        //this needs to be replaced to create the combinations of possible guesses dynamically

        auto rng = std::default_random_engine {};
        std::shuffle(all_guesses.begin(), all_guesses.end(), rng);

        ch = Challenger(id, size_secret, nbr_colors, all_guesses);



        int partitions[nb_instance];
        int partition_size = (int) (nbr_rows / (nb_instance - 1));
        if(id == 1) {
            //std::cout<<partition_size<<std::endl;
            for (size_t i = 0; i < nb_instance; i++) {
                partitions[i] = partition_size;
                //std::cout << id << "__" << partitions[i] << std::endl;
            }
        }
        int local_partition_size;
        MPI_Scatter(partitions, 1, MPI_INT, &local_partition_size, 1, MPI_INT, 1, MPI_COMM_WORLD);
        //std::cout<<id<<"::"<<local_partition_size<<std::endl;
        //std::cout<<"id:"<<id<<" from:"<<(id-1)*local_partition_size<<"to: "<<local_partition_size*id-1<<std::endl;

        evaluation last_eval = {2, 1};
        std::vector<int> tmp_last_guess = {0, 1, 2};
        Guess last_guess = Guess(tmp_last_guess);

        int from, end;
        from = (id-1)*local_partition_size;
        end = local_partition_size*id-1;


        std::vector<int> to_pop;
        to_pop = ch.filter_guesses(from, end, last_eval, last_guess);
        for(auto f: to_pop){
            //std::cout<<challengers_rank<<":"<<f<<std::endl;
        }
        int size_seperate_pop = to_pop.size();

        //SHARE INDIVIDUAL TO_POP SIZES
        int local_to_pop[challengers_size];
        MPI_Allgather(&size_seperate_pop, 1, MPI_INT, &local_to_pop, 1, MPI_INT, challengers_comm);



        //CALC TOTAL GUESSES TO POP
        int total_to_pop = 0;
        for(auto elem: local_to_pop) total_to_pop+=elem;


        //SYNC ALL TO_POP IDXs AMONG ALL THE PROCESSES
        int displs[challengers_size], offset = 0;
        for(size_t i = 0; i<challengers_size; ++i){
            displs[i] = offset;
            offset += local_to_pop[i];
        }

        //int all_to_pop[total_to_pop];
        std::vector<int> all_to_pop(total_to_pop);
        MPI_Allgatherv(&to_pop[0], to_pop.size(), MPI_INT, &all_to_pop[0], local_to_pop, displs, MPI_INT, challengers_comm);

        //UPDATE THE CHALLENGER LIST OF AVAILABLE GUESS
        ch.update_guesses_left(all_to_pop);



        MPI_Group_free(&challengers_group);
        MPI_Comm_free(&challengers_comm);

    }


    MPI_Group_free(&world_group);
    MPI_Finalize();
    return 0;
}