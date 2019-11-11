//
// Created by rena on 11.11.19.
//

struct evaluation {
    int only_color;
    int perfect;
    bool operator==(const evaluation& rhs) {return only_color == rhs.only_color and perfect == rhs.perfect;};
};



evaluation evaluate_guess(Guess &guess1, Guess &guess2){
    int only_color, perfect = 0;
    evaluation res;
    for (size_t i = 0; i<guess1.size(); i++){
        if(guess1[i] == guess2[i]) perfect++;
    }

    //evaluation tmp = {2, 1};
    return res;
};