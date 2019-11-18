//
// Created by rena on 17.11.19.
//

#include "Evaluation.h"
#include <iostream>


bool Evaluation::operator==(const Evaluation& rhs) {return only_color == rhs.only_color and perfect == rhs.perfect;};
bool Evaluation::operator!=(const Evaluation& rhs) {return !(*this==rhs);};
void Evaluation::display(){std::cout<<"p: "<<perfect<<", co: "<<only_color<<std::endl;};