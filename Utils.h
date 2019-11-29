//
// Created by rena on 18.11.19.
//

#ifndef MASTERMIND_HYDRA_UTILS_H
#define MASTERMIND_HYDRA_UTILS_H

#include "Evaluation.h"
#include "Guess.h"

void evaluate_guess(Evaluation &eval, Guess secret, Guess guess, int size_secret);
std::vector<std::string> to_base(Guess guess, int base);

#endif //MASTERMIND_HYDRA_UTILS_H
