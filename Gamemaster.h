//
// Created by rena on 07.11.19.
//
#include "Guess.h"
#include <vector>
#include <random>

#ifndef MASTERMIND_HYDRA_GAMEMASTER_H
#define MASTERMIND_HYDRA_GAMEMASTER_H


class Gamemaster {

    private:
        Guess * secret;

    public:
        Gamemaster(const int &size_secret){
            std::vector<int> guess_vect(size_secret);

            for(size_t i = 0; i<guess_vect.size(); i++){
                guess_vect[i] = i;
            }
            secret = new Guess(guess_vect);

            //secret->display_guess();
        }

        Gamemaster(){}
};


#endif //MASTERMIND_HYDRA_GAMEMASTER_H
