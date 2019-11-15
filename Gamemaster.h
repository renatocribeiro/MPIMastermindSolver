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
        Guess secret;

    public:
        Gamemaster(const int &size_secret){
            std::vector<int> guess_vect(size_secret);

            for(size_t i = 0; i<guess_vect.size(); i++){
                guess_vect[i] = i;
            }
            secret = Guess(guess_vect);
            std::cout<<"secret: ";
            secret.display_guess();
            std::cout<<std::endl;
        }

        Gamemaster(){}
};


#endif //MASTERMIND_HYDRA_GAMEMASTER_H
