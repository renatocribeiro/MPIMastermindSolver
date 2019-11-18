//
// Created by rena on 18.11.19.
//

#include "Utils.h"
#include <algorithm>

Evaluation evaluate_guess(Guess secret, Guess guess2){

    /*
    std::cout<<":::"<<std::endl;

    secret.display_guess();
    std::cout<<std::endl;

    guess2.display_guess();
    std::cout<<std::endl;
    */

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



    /*
    std::cout<<":::"<<std::endl;
    std::cout<<std::endl;
    */
    return result;
};