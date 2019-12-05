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
    int _nbr_colors;
    type_guess _from;
    type_guess _end;
    std::vector<Guess> _prev_guesses;
    std::vector<Evaluation> _prev_evals;
    int _chall_id;
    bool _is_plausible(Guess &guess);
public:
    Challenger(const int &challenger_id, const int &size_secret, const int &nbr_color, const type_guess local_partition[]);
    Challenger(){}
    static void generate_partitions(std::vector<type_guess> &partitions, int challengers_size, type_guess total_guesses_left);
    Guess get_guess();
    void update(Guess &last_guess, Evaluation last_evaluation);
    void display();

};


#endif //MASTERMIND_HYDRA_CHALLENGER_H
