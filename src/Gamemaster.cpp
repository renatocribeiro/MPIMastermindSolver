//
// Created by rena on 07.11.19.
//

#include "Gamemaster.h"
#include "Utils.h"
#include <algorithm>
#include <random>

/**
 * Constructs a Gamemaster instance with a given length of secret, number of colors,
 * number of challengers and eventually a fixed secret. If no fixed secret is given, one will be randomly created.
 * @param size_secret length of secret
 * @param nbr_colors number of colors in secret
 * @param nbr_challengers number of challengers in game
 * @param hardcoded_secret optional fixed secret passed as argument when the program is executed
 */
Gamemaster::Gamemaster(int size_secret, int nbr_colors, int nbr_challengers, int &hardcoded_secret) {
    _size_secret = size_secret;
    type_guess tmp;
    if (hardcoded_secret != -1){
        tmp = hardcoded_secret;
    }else {
        srand(time(0));
         tmp = (type_guess) (rand() % static_cast<type_guess>(pow(nbr_colors, size_secret) + 1));
    }
    _secret = Guess(tmp, size_secret, nbr_colors);


    _nbr_challengers = nbr_challengers;
}

/**
 * Picks a random valid guess from a vector of guesses previously gathered from the challengers.
 * @param guesses vector of gathered guesses
 * @return random valid guess
 */
Guess Gamemaster::pick_guess(std::vector<Guess> guesses) {
    Guess res;
    srand(time(0));
    std::random_shuffle(guesses.begin() + 1, guesses.end());
    for(size_t i = 0; i<_nbr_challengers; i++){
        if(guesses[i+1].is_valid()){
            return guesses[i+1];
        }
    }
    return res;
}

/**
 * Returns the evaluation of the secret against another guess.
 * @param guess other guess
 * @return evaluation of secret and other guess
 */
Evaluation Gamemaster::evaluate(Guess &guess) {
    return _secret.evaluate(guess, _size_secret);
}


/**
 * Returns the gamemaster's secret.
 * @return secret/guess integer
 */
Guess Gamemaster::get_secret() {
    return _secret;
}