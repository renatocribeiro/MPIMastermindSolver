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
    int _guess;
public:
    Guess();
    Guess(int guess_int);
    void display();
};


#endif //MASTERMIND_HYDRA_GUESS_H
