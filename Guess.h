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
    int _guess = -1;
public:
    Guess(){};
    Guess(int guess_int);
    void display();
    bool is_valid();
};


#endif //MASTERMIND_HYDRA_GUESS_H
