//
// Created by rena on 17.11.19.
//

#ifndef MASTERMIND_HYDRA_EVALUATION_H
#define MASTERMIND_HYDRA_EVALUATION_H


struct Evaluation {
    int only_color = 0;
    int perfect = 0;
    bool operator==(const Evaluation& other);
    bool operator!=(const Evaluation& other);
    void display();
    bool is_perfect(int size_secret);
};



#endif //MASTERMIND_HYDRA_EVALUATION_H
