//
// Created by rena on 07.11.19.
//

#include "Guess.h"
#include <iostream>
#include <algorithm>


Guess::Guess(type_guess guess_int, int size_secret, int nbr_colors) {
    _guess = guess_int;
    _size_secret = size_secret;
    _nbr_colors = nbr_colors;
    _empty = false;
}

void Guess::display() {
    std::cout<<_guess<<std::endl;
}

bool Guess::is_valid() {
    return !_empty;
}

int Guess::get_nbr() {
    return _guess;
}

std::vector<std::string> Guess::conv() {

        type_guess nbr = get_nbr();
        std::cout<<"conv: "<<nbr<<std::endl;
        std::vector<std::string> res = std::vector<std::string>(_nbr_colors, "0");
        for (type_guess in = nbr, cnt = 0; in > 0; in /= _nbr_colors, cnt++) {
            std::cout<<"in: "<<in<<std::endl;
            int x = in % _nbr_colors;
            if ((x >= 0) and (x <= 9))
                res[cnt] = ('0' + x);
            else
                res[cnt] = ('A' + (x - 10));
        }
        std::cout<<"conv2"<<std::endl;
        return res;

}

std::string Guess::to_string() {
    std::vector<std::string> converted = conv();
    return std::accumulate(converted.begin(), converted.end(), std::string(""));
}

Evaluation Guess::evaluate(Guess guess, int size_secret) {
    std::cout<<"guess::eval: "<<guess.get_nbr()<<std::endl;
    std::cout<<"this: "<<this->get_nbr()<<std::endl;
    Evaluation res;
    std::vector<std::string> secret_conv = this->conv();
    std::vector<std::string> guess_conv = guess.conv();
    std::cout<<"ah: "<<std::endl;

    for(type_guess i = size_secret; i-- > 0;){
        std::cout<<"i: "<<i<<std::endl;
        if (secret_conv[i] == guess_conv[i]){
            secret_conv.erase(secret_conv.begin() + i);
            guess_conv.erase(guess_conv.begin() + i);
            res.perfect++;
        }
    }
    std::cout<<"eval::perfect: "<<res.perfect<<std::endl;

    std::set<std::string> secret_set(secret_conv.begin(), secret_conv.end());
    std::set<std::string> guess_set(guess_conv.begin(), guess_conv.end());
    std::set<std::string> secret_inter_guess;
    std::set_intersection(secret_set.begin(), secret_set.end(), guess_set.begin(), guess_set.end(), std::inserter(secret_inter_guess,secret_inter_guess.begin()));

    res.only_color = secret_inter_guess.size();
    std::cout<<"eval::co: "<<res.only_color<<std::endl;
    return res;


}