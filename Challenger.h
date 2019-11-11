//
// Created by rena on 07.11.19.
//

#ifndef MASTERMIND_HYDRA_CHALLENGER_H
#define MASTERMIND_HYDRA_CHALLENGER_H

#include <vector>
#include <algorithm>
#include "utils.cpp"

class Challenger {
private:
    std::vector<Guess> guesses;
    std::vector<bool> guesses_left;
    int id;
public:
    Challenger(const int &challenger_id, const int &size_secret, const int &nbr_color, const std::vector<Guess> &all_guesses){
        id = challenger_id;
        guesses = all_guesses;
        guesses_left = std::vector<bool>(all_guesses.size(), true);

    }
    Challenger(){}

    void filter_guesses(const int &from, const int &end, const evaluation &last_evaluation, Guess &last_guess) {
        for(size_t i=from;i<=end;i++){
            /*
            std::cout<<id<<"___";
            guesses[i].display_guess();
            std::cout<<std::endl;
            */
            if(evaluate_guess(guesses[i], last_guess) == last_evaluation){
                std::cout<<"ok"<<std::endl;

            }

        }

    }
};


#endif //MASTERMIND_HYDRA_CHALLENGER_H
