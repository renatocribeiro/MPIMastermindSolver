#include <iostream>
#include <mpi.h>
#include <vector>
#include <cmath>
#include <string>

#include "Guess.h"
#include "Challenger.h"
#include "Gamemaster.h"


int main(int argc, char *argv[]) {
    int world_rank, world_size, status;
    MPI_Comm chall_comm;
    MPI_Group chall_group;
    MPI_Group world_group;


    const int gm_rank = 0;
    const int size_secret = 5;
    const int nbr_colors = 10;

    Gamemaster gm;
    Challenger ch;

    //INIT MPI
    MPI_Init(&argc, &argv);
    if(MPI_COMM_WORLD != MPI_COMM_NULL){
        MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
        MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    }


    //CREATES CHALLENGER GROUP
    MPI_Comm_group(MPI_COMM_WORLD, &world_group);
    int ranks[world_size - 1];
    for (size_t i = 0; i < world_size - 1; ++i) ranks[i] = i + 1;
    MPI_Group_incl(world_group, world_size - 1, ranks, &chall_group);

    MPI_Comm_create_group(MPI_COMM_WORLD, chall_group, 0, &chall_comm);
    int challengers_rank, challengers_size;
    if (chall_comm != MPI_COMM_NULL) {
        MPI_Comm_rank(chall_comm, &challengers_rank);
        MPI_Comm_size(chall_comm, &challengers_size);
    }

    //GAME MASTER BEGINS
    if (world_rank == gm_rank) {
        gm = Gamemaster(size_secret, nbr_colors, world_size - 1);
        status = -1;
    }
    MPI_Bcast(&status, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int partition_size, local_partition_size, from, end;
    //CREATE POSSIBLE GUESSES AND INIT CHALLENGERS.
    std::vector<int> partitions;
    if (world_rank != gm_rank and status == -1) {
        std::cout << "lets start" << std::endl;

        if(challengers_rank == 0)
            Challenger::generate_partitions(partitions, challengers_size, (int) pow(nbr_colors, size_secret));

        MPI_Scatter(&partitions[0], 1, MPI_INT, &local_partition_size, 1, MPI_INT, 0, chall_comm);

        from = challengers_rank * local_partition_size;

        ch = Challenger(challengers_rank, size_secret, nbr_colors);
        ch.set_from(from);
        ch.set_end(from + local_partition_size);

    }



    bool finished = false;
    bool noguess = false;
    int total_guesses_popped = 0;
    int cnt = 0;
    while(!finished){

        if (world_rank == gm_rank) {
            cnt++;
        }


        Guess new_guess;
        std::vector<int> new_guess_int(size_secret, -2);


        if (world_rank != gm_rank) {

            new_guess = ch.get_guess();
            new_guess_int = (std::vector<int>) new_guess;

        }



        //GATHERS ALL PROPOSITIONS IN GAMEMASTER
        int size_all_guesses;
        std::vector<int> gathered_guesses;
        if (world_rank == gm_rank) {
            size_all_guesses = size_secret * world_size;
            gathered_guesses = std::vector<int>(size_all_guesses);
        }
        MPI_Gather(&new_guess_int[0], size_secret, MPI_INT,
                   &gathered_guesses[0], size_secret, MPI_INT,
                   0, MPI_COMM_WORLD);


        std::vector<int> tmp_gss_prep = std::vector<int>(size_secret, -2);
        int pos;
        Evaluation feedback;
        Guess tmp_gss;
        std::vector<int> tmp_feed = std::vector<int>(2);
        if (world_rank == gm_rank) {
            //PICK FIRST GUESS
            tmp_gss = gm.pick_guess(gathered_guesses);
            tmp_gss.display_guess();std::cout<<std::endl;
            feedback = gm.evaluate(tmp_gss);
            finished = gm.is_finished(feedback);
            tmp_feed[0] = feedback.only_color; tmp_feed[1] = feedback.perfect;
            tmp_gss_prep = (std::vector<int>) tmp_gss;



        }
        if(world_rank == 1){
            //ch.display_guesses_left();
        }

        MPI_Bcast(&finished, 1, MPI_CXX_BOOL, 0, MPI_COMM_WORLD);
        if(finished){
            break;
        }



        //SEND FEEDBACK AND PICKED GUESS BACK TO CHALLENGERS
        MPI_Bcast(&tmp_feed[0], 2, MPI_INT, gm_rank, MPI_COMM_WORLD);
        MPI_Bcast(&tmp_gss_prep[0], size_secret, MPI_INT, gm_rank, MPI_COMM_WORLD);


        if (world_rank != gm_rank) {
            tmp_gss = Guess(tmp_gss_prep);
            feedback.only_color = tmp_feed[0];
            feedback.perfect = tmp_feed[1];


            //FILTERS THE ACTUAL GUESSES AND RETURNS THE IDX OF THE GUESSES THAT ARENT PART OF THE SOLUTION ANYMORE
            std::vector<int> to_pop;
            to_pop = ch.filter_guesses(feedback, tmp_gss);
            total_guesses_popped += to_pop.size();
            int size_seperate_pop = to_pop.size();
            //std::cout<<"sizeserperate: "<<size_seperate_pop<<std::endl;

            //SHARE INDIVIDUAL TO_POP SIZES
            int local_to_pop[challengers_size];
            MPI_Allgather(&size_seperate_pop, 1, MPI_INT, &local_to_pop, 1, MPI_INT, chall_comm);

            //std::cout<<"ff] world_rank: "<<world_rank<<" local partition size: "<<local_partition_size<<std::endl;

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
                           chall_comm);

            //UPDATE THE CHALLENGER LIST OF AVAILABLE GUESS
            ch.update_guesses_left(all_to_pop);


            //SCATTER NEW PARTITIONS
            if (challengers_rank == 0)
                Challenger::generate_partitions(partitions, challengers_size, ch.get_size() - total_to_pop);

            MPI_Scatter(&partitions[0], 1, MPI_INT, &local_partition_size, 1, MPI_INT, 0, chall_comm);

            //std::cout << "g] world_rank: " << world_rank << " local partition size: " << local_partition_size << std::endl;
            //DEFINE NEW FROM-END IN A SINGLE QUEUE
            int tmp_from = 0;
            int tmp_end;
            //std::cout<<"total so far popped: "<<total_guesses_popped<<std::endl;
            for(size_t i = 0; i<challengers_size; i++){
                if(challengers_rank == i){
                    if(challengers_rank == 0){
                        ch.set_from(tmp_from);
                        ch.find_new_end(local_partition_size);
                        tmp_end = ch.get_end();
                        MPI_Send(&tmp_end, 1, MPI_INT, i+1, i, chall_comm);


                    } else if(challengers_rank == (challengers_size - 1)){
                        MPI_Recv(&tmp_from, 1, MPI_INT, i-1, i-1, chall_comm, MPI_STATUS_IGNORE);
                        ch.set_from(tmp_from);
                        ch.find_new_end(local_partition_size);


                    } else{
                        MPI_Recv(&tmp_from, 1, MPI_INT, i-1, i-1, chall_comm, MPI_STATUS_IGNORE);
                        ch.set_from(tmp_from);
                        ch.find_new_end(local_partition_size);
                        tmp_end = ch.get_end();
                        MPI_Send(&tmp_end, 1, MPI_INT, i+1, i, chall_comm);

                    }

                }

            }
        }
    }

    if(world_rank != gm_rank){
        MPI_Group_free(&chall_group);
        MPI_Comm_free(&chall_comm);
    }

    if(world_rank == gm_rank) std::cout<<"cnt: "<<cnt<<std::endl;

    MPI_Group_free(&world_group);
    MPI_Finalize();
    return 0;
}