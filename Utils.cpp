//
// Created by rena on 18.11.19.
//

#include "Utils.h"
#include <iostream>
#include <algorithm>

Evaluation evaluate_guess(Guess secret, Guess guess, int size_secret){
    Evaluation res;
/*    std::vector<std::string> secret_conv = to_base(secret, size_secret);
    std::vector<std::string> guess_conv = conv(guess, size_secret);*/
    std::vector<std::string> secret_conv = secret.conv();
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

std::vector<std::string> to_base(Guess guess, int base){
    int nbr = guess.get_nbr();
        std::vector<std::string> res = std::vector<std::string>(base, "0");
        for (int in = nbr, cnt = 0; in > 0; in /= base, cnt++) {
            int x = in % base;
            if ((x >= 0) and (x <= 9))
                res[cnt] = ('0' + x);
            else
                res[cnt] = ('A' + (x - 10));
        }
        return res;
}

/*

Evaluation evaluate_guess(Guess secret, Guess guess2){
    Evaluation result;

    for(unsigned int i = secret.size(); i-- > 0;){
        if (secret[i] == guess2[i]){
            secret.erase(i);
            guess2.erase(i);
            result.perfect++;
        }
    }
    std::set<int> secret_set = (std::set<int>) secret;
    std::set<int> guess_set = (std::set<int>) guess2;
    std::set<int> secret_inter_guess;
    std::set_intersection(secret_set.begin(), secret_set.end(), guess_set.begin(), guess_set.end(), std::inserter(secret_inter_guess,secret_inter_guess.begin()));

    result.only_color = secret_inter_guess.size();



    */
/*
    std::cout<<":::"<<std::endl;
    std::cout<<std::endl;
    *//*

    return result;
};*/
