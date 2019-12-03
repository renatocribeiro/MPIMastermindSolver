//
// Created by rena on 17.11.19.
//

#include "Evaluation.h"
#include <iostream>

void Evaluation::display(){
    std::cout<<"p: "<<perfect<<", co: "<<only_color<<std::endl;
}


bool Evaluation::operator==(const Evaluation& other) {
    return only_color == other.only_color and perfect == other.perfect;
}

bool Evaluation::operator!=(const Evaluation& other) {
    return !(*this == other);
}

bool Evaluation::is_perfect(int size_secret) {
    return this->perfect==size_secret;
}

Evaluation& Evaluation::operator= (Evaluation&& v) {
    if (this != &v) {
        only_color = v.only_color; perfect = v.perfect;
    }
    return *this;
}

Evaluation::Evaluation(const Evaluation& v): only_color(v.only_color), perfect(v.perfect){}