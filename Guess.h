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
    std::vector<int> _guess;
public:
    Guess();
    Guess(const std::vector<int> guess_vect);
    int size();
    void erase(const size_t &idx);
    void display_guess();
    int &operator[](int idx);
    explicit operator std::set<int>() const;
    explicit operator std::vector<int>() const;

};


#endif //MASTERMIND_HYDRA_GUESS_H
