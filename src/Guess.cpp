//
// Created by rena on 07.11.19.
//

#include "Guess.h"
#include <iostream>
#include <algorithm>

/**
 * Constructs a Guess object from a given integer, secret size and number of colors.
 * @param guess_int integer representing a guess
 * @param size_secret length of the secret
 * @param nbr_colors number of colors in use
 */
Guess::Guess(type_guess guess_int, int size_secret, int nbr_colors) {
    _guess = guess_int;
    _size_secret = size_secret;
    _nbr_colors = nbr_colors;
    _empty = false;
}

/**
 * Returns the validity of the guess
 * @return true if the guess is valis, false otherwise.
 */
bool Guess::is_valid() {
    return !_empty;
}

/**
 * Returns the guess integer representation.
 * @return guess integer
 */
type_guess Guess::get_nbr() {
    return _guess;
}

/**
 * Converts a guess in base 10 to a guess in base 'nbr_colors' and returns it as an array of symbols.
 * @return vector of strings
 */
std::vector<std::string> Guess::conv() {

    type_guess nbr = get_nbr();
    std::vector<std::string> res = std::vector<std::string>(_size_secret, "0");
    for (type_guess in = nbr, cnt = 0; in > 0; in /= _nbr_colors, cnt++) {
        int x = in % _nbr_colors;
        if ((x >= 0) and (x <= 9))
            res[cnt] = ('0' + x);
        else
            res[cnt] = ('A' + (x - 10));
    }
    return res;

}

/**
 * Convert the guess to an array of symbols and then converts it into a string,
 * @return string of symbols
 */
std::string Guess::to_string() {
    if (is_valid()){
        std::vector<std::string> converted = conv();
        return std::accumulate(converted.begin(), converted.end(), std::string(""));
    }else{
        return "-1";
    }

}

/**
 * Evaluates two guesses and returns the corresponding evaluation.
 * @param guess other guess against this guess will be evaluated
 * @param size_secret length of the guess
 * @return evaluation containing the number of perfect and color-only pegs.
 */
Evaluation Guess::evaluate(Guess &guess, int size_secret) {
    Evaluation res;
    std::vector<std::string> secret_conv = this->conv();
    std::vector<std::string> guess_conv = guess.conv();

    //counts perfect pegs and pops them
    for(type_guess i = size_secret; i-- > 0;){
        if (secret_conv[i] == guess_conv[i]){
            secret_conv.erase(secret_conv.begin() + i);
            guess_conv.erase(guess_conv.begin() + i);
            res.perfect++;
        }
    }

    //intersection of sets created from the remaining pegs
    std::set<std::string> secret_set(secret_conv.begin(), secret_conv.end());
    std::set<std::string> guess_set(guess_conv.begin(), guess_conv.end());
    std::set<std::string> secret_inter_guess;
    std::set_intersection(secret_set.begin(), secret_set.end(), guess_set.begin(), guess_set.end(), std::inserter(secret_inter_guess,secret_inter_guess.begin()));

    res.only_color = secret_inter_guess.size();
    return res;


}

Guess& Guess::operator= (Guess&& v) {
    if (this != &v) {
        _guess = v._guess; _empty = v._empty;
        _nbr_colors = v._nbr_colors; _size_secret = v._size_secret;
    }
    return *this;
}

Guess::Guess(const Guess& v): _guess(v._guess), _empty(v._empty), _nbr_colors(v._nbr_colors), _size_secret(v._size_secret){}