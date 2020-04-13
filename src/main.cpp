#include <iostream>
#include <mpi.h>
#include <vector>
#include <cmath>
#include <string>

#include "Guess.h"
#include "Challenger.h"
#include "Gamemaster.h"
#include "Range.h"


int main(int argc, char *argv[]) {
    int world_rank, world_size, status;
    MPI_Comm chall_comm;
    MPI_Group chall_group;
    MPI_Group world_group;


    const int gm_rank = 0;
    int size_secret;
    int nbr_colors;
    bool regen = false;
    int hardcoded_secret = -1;

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

    if(world_size < 2){
        printf("You need more than 1 node to run this program.");
        return 0;
    }


    //ARGUMENTS
    for(size_t i = 1 ; i<argc; i+=2){
        if((std::string) argv[i] == "c")
            nbr_colors = std::stoi(argv[i+1]);
        else if((std::string) argv[i] == "s")
            size_secret = std::stoi(argv[i+1]);
        else if((std::string) argv[i] == "r")
            regen = std::stoi(argv[i+1]);
        else if((std::string) argv[i] == "h")
            hardcoded_secret = std::stoi(argv[i+1]);
    }

    std::vector<Guess> gathered_guesses;

    //GAME MASTER BEGINS
    if (world_rank == gm_rank) {
        printf("Welcome to Master Mind solver.\n");
        printf("Solving for a secret of size %u with %u different colors.\n"
               "Re-generation of ranges is %s and you chose a %s secret.\n\n\n",
                size_secret, nbr_colors, (regen) ? "ON" : "OFF", (hardcoded_secret == -1) ? "random" : "fixed");
        gm = Gamemaster(size_secret, nbr_colors, world_size, hardcoded_secret);
        gathered_guesses = std::vector<Guess>(world_size);
        //std::cout<<"Secret: "<<gm.get_secret().get_nbr()<<"->"<<gm.get_secret().to_string()<<std::endl;
        printf("[Gamemaster picks the secret number %llu, represented as %s.]\n\n",
                gm.get_secret().get_nbr(),
                gm.get_secret().to_string().c_str());
        status = -1;
    }

    MPI_Bcast(&status, 1, MPI_INT, 0, MPI_COMM_WORLD);

    //INIT GUESSES
    if (world_rank != 0 and status == -1){

        std::vector<Range> new_ranges;
        Range local_range;
        auto tot = pow(nbr_colors, size_secret);
        if(challengers_rank == 0){
            Challenger::generate_new_ranges(new_ranges, challengers_size, tot);
        }

        MPI_Scatter(&new_ranges[0], sizeof(Range), MPI_BYTE, &local_range, sizeof(Range), MPI_BYTE, 0, chall_comm);
        ch = Challenger(challengers_rank, size_secret, nbr_colors, local_range);
    }



    bool finished = false;
    Guess tmp_guess;
    Evaluation tmp_eval;
    int cnt = 0;

    //MAIN LOOP
    while (!finished){
        if(world_rank == 0) printf("\n-----Round %u-----\n", ++cnt);

        //ALL PLAUSIBLE GUESSES ARE COMPUTED AND GATHERED IN THE GAMEMASTER
        if(world_rank != 0){
            tmp_guess = ch.get_guess();
            if(tmp_guess.is_valid()){
                printf("Challenger %u proposes guess %llu -> %s\n",
                       challengers_rank,
                       tmp_guess.get_nbr(),
                       tmp_guess.to_string().c_str());
            }else{
                printf("Challenger %u didn't find a guess.\n",
                        challengers_rank);
            }

        }
        MPI_Gather(&tmp_guess, sizeof(Guess), MPI_BYTE, &gathered_guesses[0], sizeof(Guess), MPI_BYTE, 0, MPI_COMM_WORLD);


        //GAMEMASTER PICKS A GUESS AT RANDOM AND SENDS IT BACK ALONG WITH THE EVALUATION
        if (world_rank == 0){
            tmp_guess = gm.pick_guess(gathered_guesses);

            tmp_eval = gm.evaluate(tmp_guess);
            if(tmp_eval.is_perfect(size_secret)){
                printf("\n\nCongratulations! You found the secret in %u rounds.\n", cnt);

            }else{
                printf("Gamemaster picks guess %s. He says there are %u perfect and %u color only pegs.\n",
                       tmp_guess.to_string().c_str(),
                       tmp_eval.perfect,
                       tmp_eval.only_color);
            }

        }


        MPI_Bcast(&tmp_eval, sizeof(Evaluation), MPI_BYTE, 0, MPI_COMM_WORLD);
        finished = tmp_eval.is_perfect(size_secret);

        //UPDATES IF NOT FINISHED
        if (!finished) {
            MPI_Bcast(&tmp_guess, sizeof(Guess), MPI_BYTE, 0, MPI_COMM_WORLD);
            if (world_rank != 0) {

                //UPDATES THE CHALLENGERS LIST OF FAILED GUESSES AND EVALUATIONS
                ch.update(tmp_guess, tmp_eval);


                //RANGES RE-GENERATION
                if (regen){
                    std::vector<Range> local_ranges;
                    ch.get_ranges(local_ranges);

                    //CHALL'S ROOT GATHERS THE NUMBER OF RANGES EACH CHALL WILL BE SENDING
                    unsigned int local_size = local_ranges.size();
                    int recv_counts[challengers_size];
                    int displs[challengers_size];
                    MPI_Gather(&local_size, 1, MPI_INT, &recv_counts[0], 1, MPI_INT, 0, chall_comm);
                    int total_size = 0;
                    std::vector<Range> all_ranges;

                    //CHALL'S ROOT GATHERS ALL THE RANGES
                    if(challengers_rank == 0){

                        displs[0] = 0;
                        for(size_t i = 0; i<challengers_size; i++){
                            total_size += recv_counts[i];
                            recv_counts[i] *= sizeof(Range);
                            if(i>0)displs[i] = displs[i-1] + recv_counts[i-1];
                        }
                        all_ranges = std::vector<Range>(total_size);
                    }

                    MPI_Gatherv(&local_ranges[0], sizeof(Range)*local_size, MPI_BYTE, &all_ranges[0], recv_counts, displs, MPI_BYTE, 0, chall_comm);
                    std::vector<Range> new_ranges;
                    std::vector<int> new_range_distr(challengers_size);

                    //CHALL'S ROOT BALANCES THE RANGES
                    if(challengers_rank == 0){
                        Challenger::generate_new_ranges(new_ranges, new_range_distr, all_ranges, challengers_size);
                    }



                    //CHALL'S ROOT SCATTTERS THE NUMBER OF RANGES IT WILL BE SENDING TO EACH CHALLENGER
                    int local_distr;
                    MPI_Scatter(&new_range_distr[0], 1, MPI_INT, &local_distr, 1, MPI_INT, 0, chall_comm);

                    if(challengers_rank == 0){
                        displs[0] = 0;
                        for(size_t i = 0; i<challengers_size; i++){
                            new_range_distr[i] *= sizeof(Range);
                            if(i>0)displs[i] = displs[i-1] + new_range_distr[i-1];
                        }
                    }


                    //CHALL'S ROOT SENDS THE ACTUAL RANGES TO EACH CHALLENGER
                    std::vector<Range> new_ranges_local(local_distr);
                    MPI_Scatterv(&new_ranges[0], &new_range_distr[0], displs, MPI_BYTE, &new_ranges_local[0], sizeof(Range)*local_distr, MPI_BYTE, 0, chall_comm);

                    //CHALLS SET THE NEWLY GENERATED RANGES
                    ch.set_ranges(new_ranges_local);
                }


            }



        }



    }


    if(world_rank != gm_rank){
        MPI_Group_free(&chall_group);
        MPI_Comm_free(&chall_comm);
    }

    MPI_Group_free(&world_group);
    MPI_Finalize();
    return 0;
}