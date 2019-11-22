//
// Created by rena on 07.11.19.
//

#include "Gamemaster.h"
#include "Utils.h"
#include <iostream>

Gamemaster::Gamemaster(const int &size_secret, const int &nbr_colors, int chall_size){
    this->_generate_random_secret(size_secret, nbr_colors);
    _chall_size = chall_size;
}
Gamemaster::Gamemaster(Guess secret) {
    _secret = secret;
}

void Gamemaster::_generate_random_secret(int size_secret, int nbr_colors) {
    _secret = Guess(std::vector<int>(size_secret, 2));
    _secret.display_guess();std::cout<<std::endl;
}

Evaluation Gamemaster::evaluate(Guess guess){
    return evaluate_guess(_secret, guess);
}

Guess Gamemaster::pick_guess(std::vector<int> contiguous_guesses) {

    size_t i = 1;
    std::vector<int> picked_guess_int(_secret.size(), 9);
    int pos;
    bool found = false;
    while (!found and i < (_chall_size + 1)) {
        pos = i * _secret.size();
        if (contiguous_guesses[pos] != -2) {
            picked_guess_int = std::vector<int>(contiguous_guesses.begin() + pos,
                                                contiguous_guesses.begin() + pos + _secret.size());
            found = true;
        }
        i++;
    }

    return Guess(picked_guess_int);
}

bool Gamemaster::is_finished(Evaluation feedback) {
    return feedback.is_perfect(_secret.size());
}