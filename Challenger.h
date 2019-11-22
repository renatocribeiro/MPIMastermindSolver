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
    unsigned int _chall_id, _from, _end;
    void _init_guesses(int size_secret, int nbr_colors);
public:
    Challenger(const int &challenger_id, const int &size_secret, const int &nbr_color);
    Challenger(){}

    std::vector<int> filter_guesses(Evaluation &last_evaluation, Guess &last_guess);
    void update_guesses_left(const std::vector<int> &to_pop);
    Guess get_guess();
    void display_guesses_left();
    void set_from(int new_from);
    void set_end(int new_end);
    void display_from_end();
    void find_new_end(int size_local_partition);
    int get_size();
    int get_end();
    static void generate_partitions(std::vector<int> &partitions, int challengers_size, int nbr_guesss_left);

};


#endif //MASTERMIND_HYDRA_CHALLENGER_H
