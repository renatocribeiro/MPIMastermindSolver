//
// Created by rena on 07.11.19.
//

#include "Challenger.h"

std::vector<int> Challenger::filter_guesses(Evaluation &last_evaluation, Guess &last_guess) {
    std::vector<int> to_pop;
    //for(size_t i=from;i<=end;i++){

    for(size_t i = from; i<end; i++){
        if(guesses_left[i] == true) {
            if (evaluate_guess(guesses[i], last_guess) != last_evaluation) to_pop.push_back(i);

        }
    }
    return to_pop;
}