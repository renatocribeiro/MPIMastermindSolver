//
// Created by rena on 17.11.19.
//

#include "Evaluation.h"
#include <iostream>

/**
 * Displays the current evaluation.
 */
void Evaluation::display(){
    std::cout<<"p: "<<perfect<<", co: "<<only_color<<std::endl;
}

/**
 * Returns true of the current evaluation is perfect. A perfect evaluation means that the number of perfect pegs
 * is the same as a given length of the secret.
 * @param size_secret length of secret/guess
 * @return true if the evaluation is perfect, false otherwise.
 */
bool Evaluation::is_perfect(int size_secret) {
    return this->perfect==size_secret;
}

bool Evaluation::operator==(const Evaluation& other) {
    return only_color == other.only_color and perfect == other.perfect;
}

bool Evaluation::operator!=(const Evaluation& other) {
    return !(*this == other);
}



Evaluation& Evaluation::operator= (Evaluation&& v) {
    if (this != &v) {
        only_color = v.only_color; perfect = v.perfect;
    }
    return *this;
}

Evaluation::Evaluation(const Evaluation& v): only_color(v.only_color), perfect(v.perfect){}