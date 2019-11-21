//
// Created by rena on 07.11.19.
//

#include "Gamemaster.h"
#include "Utils.h"

Gamemaster::Gamemaster(const int &size_secret){
    //TODO:create random secret
    std::vector<int> guess_vect(size_secret);

    for(size_t i = 0; i<guess_vect.size(); i++){
        guess_vect[i] = i;
    }
    _secret = Guess(guess_vect);
    //secret.display_guess();
}

Evaluation Gamemaster::evaluate(std::vector<int> guess){
    return evaluate_guess(_secret, guess);
}