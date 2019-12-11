//
// Created by rena on 11.12.19.
//

#include <iostream>
#include "Range.h"


void Range::display() {
    std::cout<<from<<"->"<<end<<std::endl;
}

Range::Range(type_guess &new_from, type_guess &new_end) {
    from = new_from; end = new_end;
}
/*

Range::Range(type_guess new_from, type_guess new_end) {
    from = new_from; end = new_end;
}*/

type_guess Range::size() {
    return end-from;
}