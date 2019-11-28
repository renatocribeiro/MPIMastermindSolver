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

    public:
        Gamemaster(){}
        bool is_finished();
        Guess pick_guess(std::vector<Guess> guesses);
};


#endif //MASTERMIND_HYDRA_GAMEMASTER_H
