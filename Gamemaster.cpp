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
    _secret = rand()%((int) pow(nbr_colors, size_secret)-0 + 1) + 0;
}

bool Gamemaster::is_finished() {
    return false;
}

Guess Gamemaster::pick_guess(std::vector<Guess> guesses) {
    auto rng = std::default_random_engine {};
    std::shuffle(guesses.begin() + 1, guesses.end(), rng);
    Guess res;
    for(Guess g: guesses){
        if(g.is_valid()){
            return g;}
    }
    return res;
}

Evaluation Gamemaster::evaluate(Guess guess) {
    Evaluation res;
    evaluate_guess(res, _secret, guess, _size_secret);


    return res;
}