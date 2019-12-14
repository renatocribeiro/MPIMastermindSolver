//
// Created by rena on 11.12.19.
//

#include <iostream>
#include "Range.h"

/**
 * Displays a range.
 */
void Range::display() {
    std::cout<<from<<"->"<<end<<std::endl;
}

/**
 * Constructs a Range object from given bounds.
 * @param new_from lower bound
 * @param new_end upper bound
 */
Range::Range(type_guess &new_from, type_guess &new_end) {
    from = new_from; end = new_end;
}

/**
 * Returns the difference between the upper and the lower bound.
 * @return size of the range
 */
type_guess Range::size() {
    return end-from;
}