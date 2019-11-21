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

    public:
        Gamemaster(const int &size_secret);
        Gamemaster(){}
        Evaluation evaluate(std::vector<int> guess);
};


#endif //MASTERMIND_HYDRA_GAMEMASTER_H
