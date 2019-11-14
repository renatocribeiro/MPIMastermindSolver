#include <iostream>
#include <mpi.h>
#include "Gamemaster.h"
#include "Challenger.h"
#include "Guess.h"
#include <vector>
#include <cmath>

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
    MPI_Get_processor_name(processor_name, &len);


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
        std::cout<<"id:"<<id<<" from:"<<(id-1)*local_partition_size<<"to: "<<local_partition_size*id-1<<std::endl;

        evaluation last_eval = {2, 1};
        std::vector<int> tmp_last_guess = {0, 1, 2};
        Guess last_guess = Guess(tmp_last_guess);

        int from, end;
        from = (id-1)*local_partition_size;
        end = local_partition_size*id-1;



        ch.filter_guesses(from, end, last_eval, last_guess);
        //this is just a test. faut que local_partition_size soit mis a jour selon le nombre de guesses qui RESTENT encore.
        //from et end sont les indices dans le array all_guesses







    }

    //std::vector<Guess> gguess;
    //MPI_Scatter(all_guesses, 9, MPI_BYTE, gguess, 9, MPI_BYTE, 0,  MPI_COMM_WORLD);



    //printf("%d: before buf is %d\n", id, buf);
    //MPI_Bcast(&buf, 1, MPI_INT, gm_id, MPI_COMM_WORLD);
    //printf("%d: after buf is %d\n", id, buf);


    //std::cout<<"Hello world! I’m "<<id <<" of "<<nb_instance<<" on "<<processor_name;
    //std::cout<<std::endl;
    MPI_Finalize();
    return 0;
}