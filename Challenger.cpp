//
// Created by rena on 07.11.19.
//

#include "Challenger.h"

Challenger::Challenger(const int &challenger_id, const int &size_secret, const int &nbr_color, Range range) {
    _chall_id = challenger_id;
    _size_secret= size_secret;
    _nbr_colors = nbr_color;
    _ranges.push_back(range);

}


void Challenger::generate_partitions(std::vector<Range > &partitions, int challengers_size, type_guess total_guesses_left) {
    type_guess partition_size = ceil(total_guesses_left / challengers_size);

    std::vector<type_guess> local = std::vector<type_guess>(challengers_size, partition_size);
    type_guess off = total_guesses_left - (partition_size * challengers_size);
    local.at(challengers_size -1 ) = local.at(challengers_size - 1) + off;
    std::vector<type_guess> tmp_partitions = std::vector<type_guess>(challengers_size*2);
    type_guess previous = 0;
    for(size_t i = 0; i<challengers_size; i++){
        Range tmp;
        tmp_partitions[i*2] = previous;
        tmp.from = previous;
        previous = tmp_partitions[i*2] + local[i];
        tmp_partitions[i*2+1] = previous;
        tmp.end = previous;
        partitions.push_back(tmp);
    }


}

bool Challenger::_is_plausible(Guess &guess) {
    //std::cout<<"chid"<<_chall_id<<" nbr of prev guesses: "<<_prev_guesses.size()<<std::endl;
    for(size_t i = 0; i<_prev_guesses.size(); i++){
        if(_prev_guesses[i].evaluate(guess, _size_secret) != _prev_evals[i]){
            return false;
        }
    }
    return true;
}

Guess Challenger::get_guess(){
    //std::cout<<"chid: "<<_chall_id<<" from: "<<_from<<"end: "<<_end<<std::endl;
    Guess res;
    if(_prev_guesses.size() < 1){
        //std::cout<<"chid: "<<_chall_id<<" prev empty, return: "<<_from<<std::endl;
        return Guess(_ranges[0].from, _size_secret, _nbr_colors);
    }else{
        //std::cout<<"chid: "<<_chall_id<<" not empty checking: from"<<_from<<", to: "<<_end<<std::endl;

        for(size_t r = 0; r<_ranges.size(); r++){
            for(type_guess i = _ranges[r].from; i<_ranges[r].end; i++) {
                Guess tmp_guess = Guess(i, _size_secret, _nbr_colors);
                bool pl = _is_plausible(tmp_guess);
                //std::cout<<tmp_guess.get_nbr()<<", "<<tmp_guess.to_string()<<"plausible: "<<pl<<std::endl;
                if(pl){
                    _ranges[r].from = i;
                    return tmp_guess;
                }
            }
            _ranges[r].from = _ranges[r].end;
        }


    }
    //std::cout<<"chid: "<<_chall_id<<", nbr: "<<res.to_string()<<std::endl;
    return res;
}

void Challenger::update(Guess &last_guess, Evaluation last_evaluation) {
    _prev_guesses.push_back(last_guess);
    _prev_evals.push_back(last_evaluation);

}

void Challenger::display() {
    for(size_t r = 0; r<_ranges.size(); r++) {
        for(size_t i = _ranges[r].from; i<_ranges[r].end; i++){
            std::cout<<"chid: "<<_chall_id<<", r: "<<r<<"nbr: "<<i<<std::endl;
        }
    }

}