//
// Created by rena on 07.11.19.
//

#include "Guess.h"
#include <iostream>



void Guess::display_guess() {
    std::copy(guess.begin(), guess.end(),
              std::ostream_iterator<int>(std::cout, " "));
}

int Guess::size(){return guess.size();};
void Guess::erase(const size_t &idx){guess.erase(guess.begin()+idx);};

