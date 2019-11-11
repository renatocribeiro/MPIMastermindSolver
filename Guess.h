//
// Created by rena on 07.11.19.
//

#ifndef MASTERMIND_HYDRA_GUESS_H
#define MASTERMIND_HYDRA_GUESS_H

#include <vector>
#include <random>
#include <iterator>


class Guess {
private:
    std::vector<int> guess;
public:
    Guess(){}

    Guess(const std::vector<int> guess_vect){
        guess = guess_vect;
    }

    int size(){return guess.size();};
    int &operator[](int idx){return guess[idx];};
    void display_guess();
};


#endif //MASTERMIND_HYDRA_GUESS_H
