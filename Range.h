//
// Created by rena on 11.12.19.
//

#ifndef MASTERMIND_HYDRA_RANGE_H
#define MASTERMIND_HYDRA_RANGE_H


#include "Utils.h"

struct Range {
    type_guess from;
    type_guess end;
    void display();
    Range(){};
    Range(type_guess &new_from, type_guess &new_end);
    //Range(type_guess new_from, type_guess new_end);
    type_guess size();

};


#endif //MASTERMIND_HYDRA_RANGE_H
