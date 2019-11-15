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

    std::vector<int> filter_guesses(const int &from, const int &end, evaluation &last_evaluation, Guess &last_guess) {
        std::vector<int> to_pop;
        for(size_t i=from;i<=end;i++){
            if(evaluate_guess(guesses[i], last_guess) != last_evaluation) to_pop.push_back(i);
        }
        return to_pop;
    }

    void update_guesses_left(std::vector<int> to_pop) {
        for(auto guess: to_pop) std::cout<<guess<<std::endl;
    }
};


#endif //MASTERMIND_HYDRA_CHALLENGER_H
