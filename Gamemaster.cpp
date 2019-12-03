//
// Created by rena on 07.11.19.
//

#include "Gamemaster.h"
#include "Utils.h"
#include <iostream>
#include <algorithm>
#include <random>


Gamemaster::Gamemaster(int size_secret, int nbr_colors) {
    _size_secret = size_secret;
    type_guess tmp = (type_guess) (rand() % static_cast<type_guess>(pow(nbr_colors, size_secret) + 1));
    _secret = Guess(tmp, size_secret, nbr_colors);
}

Guess Gamemaster::pick_guess(std::vector<Guess> guesses) {
    Guess res;
    for(Guess g: guesses){
        if(g.is_valid()){
            return g;
        }
    }
    return res;
}

Evaluation Gamemaster::evaluate(Guess guess) {
    return _secret.evaluate(guess, _size_secret);
}


Guess Gamemaster::get_secret() {
    return _secret;
}