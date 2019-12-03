//
// Created by rena on 07.11.19.
//

#include "Gamemaster.h"
#include "Utils.h"
#include <iostream>
#include <algorithm>
#include <random>


Gamemaster::Gamemaster(int size_secret, int nbr_colors, int nbr_challengers) {
    _size_secret = size_secret;
    type_guess tmp = (type_guess) (rand() % static_cast<type_guess>(pow(nbr_colors, size_secret) + 1));
    _secret = Guess(tmp, size_secret, nbr_colors);
    _nbr_challengers = nbr_challengers;
}

Guess Gamemaster::pick_guess(std::vector<Guess> guesses) {
    Guess res;
    for(size_t i = 0; i<_nbr_challengers; i++){
        if(guesses[i+1].is_valid()){
            return guesses[i+1];
        }
    }
    return res;
}

Evaluation Gamemaster::evaluate(Guess &guess) {
    return _secret.evaluate(guess, _size_secret);
}


Guess Gamemaster::get_secret() {
    return _secret;
}