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
    int _size_secret;
    int _nbr_challengers;

    public:
        Gamemaster(){}
        Gamemaster(int size_secret, int nbr_colors, int nbr_challengers);
        Guess pick_guess(std::vector<Guess> guesses);
        Evaluation evaluate(Guess &guess);
        Guess get_secret();
};


#endif //MASTERMIND_HYDRA_GAMEMASTER_H
