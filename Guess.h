//
// Created by rena on 07.11.19.
//

#ifndef MASTERMIND_HYDRA_GUESS_H
#define MASTERMIND_HYDRA_GUESS_H

#include <vector>
#include <random>
#include <iterator>
#include <set>
#include "Evaluation.h"
#include "Utils.h"


class Guess {
private:
    type_guess _guess;
    bool _empty = true;
    int _nbr_colors;
    int _size_secret;
public:
    Guess(){};
    Guess(type_guess guess_int, int size_secret, int nbr_colors);
    void display();
    bool is_valid();
    type_guess get_nbr();
    std::vector<std::string> conv();
    std::string to_string();
    Evaluation evaluate(Guess &guess, int size_secret);
    Guess& operator= (Guess&&);
    Guess (const Guess&);
};


#endif //MASTERMIND_HYDRA_GUESS_H
