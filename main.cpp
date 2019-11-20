#include <iostream>
#include <mpi.h>
#include <vector>
#include <cmath>
#include <string>


//#include "Utils.h"
#include "Guess.h"
#include "Challenger.h"

#include "Gamemaster.h"
//#include "Evaluation.h"
//#include "utils.cpp"



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
    int ranks[nb_instance - 1];
    for (size_t i = 0; i < nb_instance - 1; ++i) ranks[i] = i + 1;
    //for(auto f: ranks){std::cout<<f<<std::endl;}
    MPI_Group challengers_group;
    MPI_Group_incl(world_group, nb_instance - 1, ranks, &challengers_group);

    MPI_Comm challengers_comm;
    MPI_Comm_create_group(MPI_COMM_WORLD, challengers_group, 0, &challengers_comm);
    int challengers_rank, challengers_size;
    if (MPI_COMM_NULL != challengers_comm) {
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




    int msg;
    if (id == gm_id) {
        gm = Gamemaster(size_secret);
        msg = -1;
    }
    MPI_Bcast(&msg, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int nbr_guesses_left, partition_size, local_partition_size, from, end;
    //CREATE POSSIBLE GUESSES AND INIT CHALLENGERS.
    std::vector<int> partitions;
    if (id != gm_id and msg == -1) {
        std::cout << "lets start" << std::endl;

        //int all_guesses[nbr_guesses_left][size_secret];
        std::vector<Guess> all_guesses;
        //this needs to be replaced to create the combinations of possible guesses dynamically
        for (size_t i = 0; i < nbr_colors; i++) {
            for (size_t j = 0; j < nbr_colors; j++) {
                for (size_t k = 0; k < nbr_colors; k++) {
                    std::vector<int> tmp;
                    tmp.push_back(i);
                    tmp.push_back(j);
                    tmp.push_back(k);
                    Guess tmp_guess = Guess(tmp);
                    all_guesses.push_back(tmp_guess);
                }
            }
        }



        if(challengers_rank == 0){
            nbr_guesses_left = all_guesses.size();

            partition_size = ceil(nbr_guesses_left/challengers_size);
            partitions = std::vector<int>(challengers_size, partition_size);

            int off = nbr_guesses_left - (partition_size * challengers_size);
            partitions.at(challengers_size -1 ) = partitions.at(challengers_size - 1) + off;

        }
        MPI_Scatter(&partitions[0], 1, MPI_INT, &local_partition_size, 1, MPI_INT, 0, challengers_comm);

        from = challengers_rank * local_partition_size;
        end = local_partition_size * (challengers_rank + 1);

        ch = Challenger(challengers_rank, size_secret, nbr_colors, all_guesses, from, end);
        //ch.display_from_end();


/*        //JUST TO DEBUG
        if(id == 1){
            for(size_t i = 0; i<all_guesses.size();i++){
                std::cout<<i<<":: ";
                all_guesses[i].display_guess();
                std::cout<<std::endl;
            }
        }
        //JUST TO DEBUG*/

    }



    bool finished = false;
    bool noguess = false;
    while(!finished){


        Guess new_guess;
        std::vector<int> new_guess_int(size_secret, -2);


        if (id != gm_id) {

            new_guess = ch.get_guess();
            new_guess_int = (std::vector<int>) new_guess;

            std::cout<<"a] id: "<<id<<"picked guess by ch: ";
            new_guess.display_guess();
            std::cout<<std::endl;

        }
        if (noguess) break;
        std::cout<<"b] id: "<<id<<" - break"<<std::endl;
        //break;


        //GATHERS ALL PROPOSITIONS IN GAMEMASTER
        int size_all_guesses;
        std::vector<int> gathered_guesses;
        if (id == gm_id) {
            size_all_guesses = size_secret * nb_instance;
            gathered_guesses = std::vector<int>(size_all_guesses);
        }
        MPI_Gather(&new_guess_int[0], size_secret, MPI_INT,
                   &gathered_guesses[0], size_secret, MPI_INT,
                   0, MPI_COMM_WORLD);

        if(id == 0) {
            std::string tmp = "c] id: ";
            tmp += std::to_string(id);
            tmp += " - ";
            for (auto f: gathered_guesses)tmp += std::to_string(f);
            std::cout << tmp << std::endl;
        }

        std::cout<<"d] id: "<<id<<" - break"<<std::endl;


        std::vector<int> picked_guess_int(size_secret, 9);
        int pos;
        Evaluation feedback;
        if (id == gm_id) {
            //PICK FIRST GUESS
            size_t i = 0;
            bool found = false;
            while (!found and i < nb_instance) {
                pos = i * size_secret;
                if (gathered_guesses[pos] != -2) {
                    picked_guess_int = std::vector<int>(gathered_guesses.begin() + pos,
                                                        gathered_guesses.begin() + pos + size_secret);
                    found = true;
                }
                i++;
            }

            //EVALUATES PICKED GUESS
            feedback = gm.evaluate(picked_guess_int);
            if (feedback.is_perfect(size_secret)) {
                finished = true;
                break;
            }
        }
        if(id == 0){
            std::string tmp2 = "e] id: ";
            tmp2 += std::to_string(id); tmp2 += " - picked guess by gm: ";
            for(auto f: picked_guess_int)tmp2+= std::to_string(f);
            std::cout<<tmp2<<std::endl;
        }



        //SEND PICKED GUESS BACK TO ALL THE CHALLENGERS SO THEY CAN FILTER THE FOLLOWING GUESSES
        MPI_Bcast(&picked_guess_int[0], size_secret, MPI_INT, gm_id, MPI_COMM_WORLD);
        Guess picked_guess = Guess(picked_guess_int);

        std::string tmp3 = "f] id: ";
        tmp3 += std::to_string(id); tmp3 += " - bcast chosen guess from gm: ";
        for(auto f: picked_guess_int)tmp3+= std::to_string(f);
        std::cout<<tmp3<<std::endl;




        if (id != gm_id) {

            //FILTERS THE ACTUAL GUESSES AND RETURNS THE IDX OF THE GUESSES THAT ARENT PART OF THE SOLUTION ANYMORE

            std::vector<int> to_pop;
            to_pop = ch.filter_guesses(feedback, picked_guess);
            int size_seperate_pop = to_pop.size();

            //SHARE INDIVIDUAL TO_POP SIZES
            int local_to_pop[challengers_size];
            MPI_Allgather(&size_seperate_pop, 1, MPI_INT, &local_to_pop, 1, MPI_INT, challengers_comm);



            //CALC TOTAL GUESSES TO POP
            int total_to_pop = 0;
            for (auto elem: local_to_pop) total_to_pop += elem;


            //SYNC ALL TO_POP IDXs AMONG ALL THE PROCESSES
            int displs[challengers_size], offset = 0;
            for (size_t i = 0; i < challengers_size; ++i) {
                displs[i] = offset;
                offset += local_to_pop[i];
            }

            //int all_to_pop[total_to_pop];
            std::vector<int> all_to_pop(total_to_pop);
            MPI_Allgatherv(&to_pop[0], to_pop.size(), MPI_INT, &all_to_pop[0], local_to_pop, displs, MPI_INT,
                           challengers_comm);

            //UPDATE THE CHALLENGER LIST OF AVAILABLE GUESS
            ch.update_guesses_left(all_to_pop);


            //SCATTER NEW PARTITIONS
            if (challengers_rank == 0){
                int nbr_guesses_left = ch.get_size() - total_to_pop;

                partition_size = ceil(nbr_guesses_left / challengers_size);
                partitions = std::vector<int>(challengers_size, partition_size);
                int off = nbr_guesses_left - (partition_size * challengers_size);
                partitions.at(challengers_size - 1) = partitions.at(challengers_size - 1) + off;

            }
            MPI_Scatter(&partitions[0], 1, MPI_INT, &local_partition_size, 1, MPI_INT, 0, challengers_comm);

            //DEFINE NEW FROM-END IN A SINGLE FILE
            int tmp_from = 0;
            int tmp_end;
            for(size_t i = 0; i<challengers_size; i++){
                if(challengers_rank == i){
                    if(challengers_rank == 0){
                        //ch.display_guesses_left();
                        ch.set_from(tmp_from);
                        ch.find_new_end(local_partition_size);
                        tmp_end = ch.get_end();
                        MPI_Send(&tmp_end, 1, MPI_INT, i+1, i, challengers_comm);
                        //std::cout<<"ch_id: "<<challengers_rank<<" sent: "<<tmp_end<<std::endl;
                        //ch.display_from_end();

                    } else if(challengers_rank == (challengers_size - 1)){ //mid
                        MPI_Recv(&tmp_from, 1, MPI_INT, i-1, i-1, challengers_comm, MPI_STATUS_IGNORE);
                        ch.set_from(tmp_from);
                        ch.find_new_end(local_partition_size);
                        //ch.display_from_end();


                    } else{ //end
                        MPI_Recv(&tmp_from, 1, MPI_INT, i-1, i-1, challengers_comm, MPI_STATUS_IGNORE);
                        //std::cout<<"ch_id: "<<challengers_rank<<" received: "<<tmp_from<<std::endl;
                        ch.set_from(tmp_from);
                        ch.find_new_end(local_partition_size);
                        tmp_end = ch.get_end();
                        //ch.display_from_end();
                        MPI_Send(&tmp_end, 1, MPI_INT, i+1, i, challengers_comm);
                        //std::cout<<"ch_id: "<<challengers_rank<<" new end: "<<tmp_end<<std::endl;

                    }

                }

            }
        }
        break;
    }

    if(id != gm_id){
        MPI_Group_free(&challengers_group);
        MPI_Comm_free(&challengers_comm);
    }


    MPI_Group_free(&world_group);
    MPI_Finalize();
    return 0;
}