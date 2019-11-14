//
// Created by rena on 07.11.19.
//

#ifndef MASTERMIND_HYDRA_GUESS_H
#define MASTERMIND_HYDRA_GUESS_H

#include <vector>
#include <random>
#include <iterator>
#include <set>


class Guess {
private:
    std::vector<int> guess;
public:
    Guess(){}

    Guess(const std::vector<int> guess_vect){
        guess = guess_vect;
    }

    int size(){return guess.size();};
    void erase(const size_t &idx){guess.erase(guess.begin()+idx);};
    int &operator[](int idx){return guess[idx];};
    void display_guess();
    explicit operator std::set<int>() const {
        //return guess;
        std::set<int> res;
        for(int gues : guess) res.insert(gues);
        return res;
    }
};


#endif //MASTERMIND_HYDRA_GUESS_H
