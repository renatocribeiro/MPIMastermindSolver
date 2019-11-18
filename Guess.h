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
    Guess(){
        guess = std::vector<int>(1, -2);
    }

    Guess(const std::vector<int> guess_vect){
        guess = guess_vect;
    }

    int size();
    void erase(const size_t &idx);
    void display_guess();
    int &operator[](int idx){return guess[idx];};
    operator std::set<int>() const {
        //return guess;
        std::set<int> res;
        for(int gues : guess) res.insert(gues);
        return res;
    }

    explicit operator std::vector<int>() const {
        return guess;
    }

};


#endif //MASTERMIND_HYDRA_GUESS_H
