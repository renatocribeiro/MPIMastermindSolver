//
// Created by rena on 07.11.19.
//
#include <vector>
#include <random>
#include "Guess.h"
#include "Evaluation.h"

#ifndef MASTERMIND_HYDRA_GAMEMASTER_H
#define MASTERMIND_HYDRA_GAMEMASTER_H


class Gamemaster {

    private:
        Guess _secret;
        int _chall_size;
        void _generate_random_secret(int size_secret, int nbr_colors);
    public:
        Gamemaster(){}
        Gamemaster(const int &size_secret, const int &nbr_colors, int chall_size);
        Gamemaster(Guess secret);
        Evaluation evaluate(Guess guess);
        Guess pick_guess(std::vector<int> contiguous_guesses);
        bool is_finished(Evaluation feedback);
};


#endif //MASTERMIND_HYDRA_GAMEMASTER_H
