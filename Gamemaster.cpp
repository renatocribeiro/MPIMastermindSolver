//
// Created by rena on 07.11.19.
//

#include "Gamemaster.h"
#include "Utils.h"

Gamemaster::Gamemaster(const int &size_secret, const int &nbr_colors){
    this->_generate_random_secret(size_secret, nbr_colors);
}
Gamemaster::Gamemaster(Guess secret) {
    _secret = secret;
}

void Gamemaster::_generate_random_secret(int size_secret, int nbr_colors) {
    _secret = Guess(std::vector<int>(size_secret, 1));
}

Evaluation Gamemaster::evaluate(std::vector<int> guess){
    return evaluate_guess(_secret, guess);
}