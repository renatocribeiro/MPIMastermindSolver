//
// Created by rena on 07.11.19.
//

#include "Guess.h"
#include <iostream>


Guess::Guess(int guess_int) {
    _guess = guess_int;
}

void Guess::display() {
    std::cout<<_guess<<std::endl;
}

bool Guess::is_valid() {
    return _guess != -1;
}