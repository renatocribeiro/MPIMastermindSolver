//
// Created by rena on 07.11.19.
//

#include "Challenger.h"

Challenger::Challenger(const int &challenger_id, const int &size_secret, const int &nbr_color, const type_guess local_partition[]) {
    _chall_id = challenger_id;
    _size_secret= size_secret;
    _nbr_colors = nbr_color;
    _from = local_partition[0];
    _end = local_partition[1];
    _guesses_left = std::vector<bool>(_end - _from, true);
    //_init_guesses(local_partition);

}

/*void Challenger::_init_guesses(const int local_partition[]) {
    for(size_t i = local_partition[0]; i<local_partition[1]; i++){
        _guesses.push_back(Guess(i));
    }
    _guesses_left = std::vector<bool>(_guesses.size(), true);
    //for(auto f: _guesses){f.display();}
}*/

void Challenger::generate_partitions(std::vector<type_guess > &partitions, int challengers_size, int total_guesses_left) {
    std::cout<<"oyo"<<total_guesses_left<<std::endl;
    type_guess partition_size = ceil(total_guesses_left / challengers_size);
    std::cout<<partition_size<<std::endl;

    std::vector<type_guess> local = std::vector<type_guess>(challengers_size, partition_size);
    type_guess off = total_guesses_left - (partition_size * challengers_size);
    local.at(challengers_size -1 ) = local.at(challengers_size - 1) + off;
    partitions = std::vector<type_guess>(challengers_size*2);
    type_guess previous = 0;
    for(size_t i = 0; i<challengers_size; i++){
        partitions[i*2] = previous;
        previous = partitions[i*2] + local[i];
        partitions[i*2+1] = previous;
    }
}

Guess Challenger::get_guess(){
    Guess res = Guess();
    for(size_t i = _from; i<_end; i++){
        //std::cout<<i<<"__"<<i-_from<<"__"<<_guesses_left[i-_from]<<std::endl;
        if (_guesses_left[i - _from] == true){
            //std::cout<<"_____"<<i<<"--"<<i-_from<<std::endl;
            //std::cout<<i<<std::endl;
            return Guess(i, _size_secret, _nbr_colors);
        }
    }

    return res;
}

void Challenger::filter_guesses(Guess last_guess, Evaluation last_evaluation) {
    for(size_t i = 0; i<_guesses_left.size(); i++){
        if(_guesses_left[i] == true){

            if(last_guess.evaluate(Guess(i + _from, _size_secret, _nbr_colors), _size_secret) != last_evaluation){
                _guesses_left[i] = false;
            }

/*            if(evaluate_guess(last_guess, Guess(i + _from, _size_secret), _size_secret) != last_evaluation){
                _guesses_left[i] = false;
            }*/
        }
        //std::cout<<Guess(i+_from, _size_secret).to_string()<<":::"<<_guesses_left[i]<<std::endl;
    }

}

void Challenger::display() {
    for(size_t i = 0; i<_guesses_left.size(); i++){
        std::cout<<i+_from<<"::"<<Guess(i+_from, _size_secret, _nbr_colors).to_string()<<"::"<<_guesses_left[i]<<std::endl;
    }
}