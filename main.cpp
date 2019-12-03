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
    int size_secret;
    int nbr_colors;

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
        return 0;
    }


    //ARGUMENTS
    for(size_t i = 1 ; i<argc; i+=2){
        if((std::string) argv[i] == "c")
            nbr_colors = std::stoi(argv[i+1]);
        else if((std::string) argv[i] == "s")
            size_secret = std::stoi(argv[i+1]);

    }

    std::vector<Guess> gathered_guesses;

    //GAME MASTER BEGINS
    if (world_rank == gm_rank) {
        gm = Gamemaster(size_secret, nbr_colors, world_size);
        gathered_guesses = std::vector<Guess>(world_size);
        std::cout<<"Secret: "<<gm.get_secret().to_string()<<std::endl;
        status = -1;
    }
    MPI_Bcast(&status, 1, MPI_INT, 0, MPI_COMM_WORLD);

    //INIT GUESSES
    if (world_rank != 0 and status == -1){

        std::vector<type_guess> partitions;
        type_guess local_partition[2];
        if(challengers_rank == 0){
            Challenger::generate_partitions(partitions, challengers_size, pow(nbr_colors, size_secret));
        }


        MPI_Scatter(&partitions[0], 2, MPI_UNSIGNED_LONG_LONG, &local_partition[0], 2, MPI_UNSIGNED_LONG_LONG, 0, chall_comm);

        ch = Challenger(challengers_rank, size_secret, nbr_colors, local_partition);
    }


    bool finished = false;
    Guess tmp_guess;
    Evaluation tmp_eval;
    int cnt=0;
    while (!finished){
        cnt++;
        if(world_rank != 0){
            tmp_guess = ch.get_guess();
        }
        MPI_Gather(&tmp_guess, sizeof(Guess), MPI_BYTE, &gathered_guesses[0], sizeof(Guess), MPI_BYTE, 0, MPI_COMM_WORLD);


        if (world_rank == 0){
            tmp_guess = gm.pick_guess(gathered_guesses);
            std::cout<<"gm picked: "<<tmp_guess.get_nbr()<<"__"<<tmp_guess.to_string()<<std::endl;
            tmp_eval = gm.evaluate(tmp_guess);
        }


        MPI_Bcast(&tmp_eval, sizeof(Evaluation), MPI_BYTE, 0, MPI_COMM_WORLD);
        finished = tmp_eval.is_perfect(size_secret);

        if (!finished) {
            MPI_Bcast(&tmp_guess, sizeof(Guess), MPI_BYTE, 0, MPI_COMM_WORLD);
            if (world_rank != 0) {
                ch.filter_guesses(tmp_guess, tmp_eval);
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