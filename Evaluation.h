//
// Created by rena on 17.11.19.
//

#ifndef MASTERMIND_HYDRA_EVALUATION_H
#define MASTERMIND_HYDRA_EVALUATION_H


struct Evaluation {
    int only_color = 0;
    int perfect = 0;
    bool operator==(const Evaluation& rhs);
    bool operator!=(const Evaluation& rhs);
    void display();
};



#endif //MASTERMIND_HYDRA_EVALUATION_H
