//
// Created by rena on 07.11.19.
//

#include "Guess.h"
#include <iostream>
#include <algorithm>


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

Evaluation Guess::evaluate(Guess guess, int size_secret) {

    Evaluation res;
/*    std::vector<std::string> secret_conv = to_base(secret, size_secret);
    std::vector<std::string> guess_conv = conv(guess, size_secret);*/
    std::vector<std::string> secret_conv = this->conv();
    std::vector<std::string> guess_conv = guess.conv();


/*
    for(auto f: secret_conv){std::cout<<f<<"::";}std::cout<<std::endl;
    for(auto f: guess_conv){std::cout<<f<<"::";}std::cout<<std::endl;
*/



    for(unsigned int i = size_secret; i-- > 0;){
        if (secret_conv[i] == guess_conv[i]){
            secret_conv.erase(secret_conv.begin() + i);
            guess_conv.erase(guess_conv.begin() + i);
            res.perfect++;
        }
    }
    //for(auto f: secret_conv){std::cout<<f<<"::";}std::cout<<std::endl;


    std::set<std::string> secret_set(secret_conv.begin(), secret_conv.end());
    std::set<std::string> guess_set(guess_conv.begin(), guess_conv.end());
    std::set<std::string> secret_inter_guess;
    std::set_intersection(secret_set.begin(), secret_set.end(), guess_set.begin(), guess_set.end(), std::inserter(secret_inter_guess,secret_inter_guess.begin()));

    res.only_color = secret_inter_guess.size();
    return res;


}