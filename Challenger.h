//
// Created by rena on 07.11.19.
//

#ifndef MASTERMIND_HYDRA_CHALLENGER_H
#define MASTERMIND_HYDRA_CHALLENGER_H

#include <vector>
#include <algorithm>
#include <iostream>
#include "Guess.h"
#include "Evaluation.h"
#include "Utils.h"

class Challenger {
private:
    std::vector<Guess> _guesses;
    std::vector<bool> _guesses_left;
    int _size_secret;
    unsigned int _from = -1;
    unsigned int _end = -1;
    int _chall_id;
    //void _init_guesses(const int local_partition[]);
public:
    Challenger(const int &challenger_id, const int &size_secret, const int &nbr_color, const int local_partition[]);
    Challenger(){}
    static void generate_partitions(std::vector<int> &partitions, int challengers_size, int total_guesses_left);
    Guess get_guess();
    void filter_guesses(Guess last_guess, Evaluation last_evaluation);
    void display();

};


#endif //MASTERMIND_HYDRA_CHALLENGER_H
