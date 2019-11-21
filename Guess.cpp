//
// Created by rena on 07.11.19.
//

#include "Guess.h"
#include <iostream>

Guess::Guess(){
    _guess = std::vector<int>(1, -2);
}

Guess::Guess(const std::vector<int> guess_vect){
    _guess = guess_vect;
}

int Guess::size(){
    return _guess.size();
}

void Guess::erase(const size_t &idx){
    _guess.erase(_guess.begin() + idx);
}

void Guess::display_guess() {
    std::copy(_guess.begin(), _guess.end(),
              std::ostream_iterator<int>(std::cout, " "));
}

int &Guess::operator[](int idx){
    return _guess[idx];
}

Guess::operator std::set<int>() const {
    //return guess;
    std::set<int> res;
    for(int gues : _guess) res.insert(gues);
    return res;
}

Guess::operator std::vector<int>() const {
    return _guess;
}

