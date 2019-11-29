//
// Created by rena on 07.11.19.
//

#include "Guess.h"
#include <iostream>


Guess::Guess(int guess_int, int size_secret) {
    _guess = guess_int;
    _size_secret = size_secret;
}

void Guess::display() {
    std::cout<<_guess<<std::endl;
}

bool Guess::is_valid() {
    return _guess != -1;
}

int Guess::get_nbr() {
    return _guess;
}

std::vector<std::string> Guess::conv() {
        int nbr = get_nbr();
        std::vector<std::string> res = std::vector<std::string>(_size_secret, "0");
        for (int in = nbr, cnt = 0; in > 0; in /= _size_secret, cnt++) {
            int x = in % _size_secret;
            if ((x >= 0) and (x <= 9))
                res[cnt] = ('0' + x);
            else
                res[cnt] = ('A' + (x - 10));
        }
        return res;

}

std::string Guess::to_string() {
    std::vector<std::string> converted = conv();
    return std::accumulate(converted.begin(), converted.end(), std::string(""));
}