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
    int _size_secret;
public:
    Guess(){};
    Guess(int guess_int, int size_secret);
    void display();
    bool is_valid();
    int get_nbr();
    std::vector<std::string> conv();
    std::string to_string();
};


#endif //MASTERMIND_HYDRA_GUESS_H
