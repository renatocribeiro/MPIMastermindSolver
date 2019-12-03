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

bool Gamemaster::is_finished() {
    return false;
}

Guess Gamemaster::pick_guess(std::vector<Guess> guesses) {
    /*std::cout<<"gm: ";
    for(auto f: guesses){
        std::cout<<f.get_nbr()<<":::";
    }std::cout<<std::endl;*/

    //auto rng = std::default_random_engine {};
    //std::shuffle(guesses.begin() + 1, guesses.end(), rng);
    Guess res;
    for(Guess g: guesses){
        //g.display();
        if(g.is_valid()){
            return g;
        }
    }
    return res;
}

Evaluation Gamemaster::evaluate(Guess guess) {
    std::cout<<"gm.eval: "<<guess.get_nbr()<<std::endl;
    return _secret.evaluate(guess, _size_secret);
    //return evaluate_guess(_secret, guess, _size_secret);
}