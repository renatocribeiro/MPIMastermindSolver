//
// Created by rena on 07.11.19.
//

#ifndef MASTERMIND_HYDRA_CHALLENGER_H
#define MASTERMIND_HYDRA_CHALLENGER_H

#include <vector>
#include <algorithm>
#include <iostream>
#include "Guess.h"
#include "Evaluation.h"
#include "Utils.h"

class Challenger {
private:
    std::vector<Guess> guesses;
    std::vector<bool> guesses_left;
    int ch_id, from, end;
public:
    Challenger(const int &challenger_id, const int &size_secret, const int &nbr_color, const std::vector<Guess> &all_guesses, unsigned int def_from, unsigned int def_end){
        ch_id = challenger_id;
        guesses = all_guesses;
        guesses_left = std::vector<bool>(all_guesses.size(), true);
        from = def_from;
        end = def_end;

    }
    Challenger(){}

    std::vector<int> filter_guesses(Evaluation &last_evaluation, Guess &last_guess);

    void update_guesses_left(std::vector<int> to_pop) {
        for(auto elem: to_pop) guesses_left[elem] = false;
    }
    int get_number_guesses_left(){
        int result = 0;
        for(auto f:guesses_left){
            if (f) result++;
        }
        return result;
    }

    Guess get_guess(){
        Guess result = Guess(std::vector<int>(guesses[0].size(), -2));
        for(int i = from; i<end;++i){
            if (guesses_left[i]) return guesses[i];
        }

        return result;
    }
    void display_guesses_left(){
        for(size_t i = 0; i<guesses.size();i++){
            if(guesses_left[i]){
                //std::cout<<guesses[i]
                guesses[i].display_guess();
                std::cout<<"  "<<guesses_left[i]<<std::endl;
            }
        }
    }

    void set_from_end(int ffrom, int eend){
        from = ffrom; end = eend;
    }

    void display_from_end(){
       std::string tmp = "ch_id: ";
       tmp+= std::to_string(ch_id);
       tmp += "from: ";
       tmp += std::to_string(from);
       tmp += "end: ";
       tmp += std::to_string(end);
       std::cout<<tmp<<std::endl;
    }

    int get_size(){return guesses.size();}

};


#endif //MASTERMIND_HYDRA_CHALLENGER_H
