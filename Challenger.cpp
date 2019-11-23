//
// Created by rena on 07.11.19.
//

#include "Challenger.h"

Challenger::Challenger(const int &challenger_id, const int &size_secret, const int &nbr_color) {
    _chall_id = challenger_id;
    _init_guesses(size_secret, nbr_color);
}

std::vector<std::string> Challenger::_to_base(int nbr, int base) {
    std::vector<std::string> guess = std::vector<std::string>(base, "0");
    for (int in = nbr, cnt = 0; in > 0; in /= base, cnt++) {
        int x = in % base;
        if ((x >= 0) and (x <= 9))
            guess[cnt] = ('0' + x);
        else
            guess[cnt] = ('A' + (x - 10));
    }
    return guess;
}

void Challenger::_init_guesses(int size_secret, int nbr_colors) {
    unsigned tot_guesses = pow(nbr_colors, size_secret);

    std::vector<std::string> guess;
    for (size_t i = 0; i < tot_guesses; i++) {
        guess = _to_base(i, size_secret);
        std::reverse(guess.begin(), guess.end());
        _guesses.push_back(Guess(guess));
    }

    _guesses_left = std::vector<bool>(_guesses.size(), true);
}

std::vector<int> Challenger::filter_guesses(Evaluation &last_evaluation, Guess &last_guess) {
    std::vector<int> to_pop;
    //for(size_t i=from;i<=end;i++){

    for(size_t i = _from; i < _end; i++){
        if(_guesses_left[i] == true) {
            if (evaluate_guess(_guesses[i], last_guess) != last_evaluation) to_pop.push_back(i);

        }
    }
    return to_pop;
}

void Challenger::update_guesses_left(const std::vector<int> &guesses_to_pop){
    for(auto idx: guesses_to_pop) _guesses_left[idx] = false;
}

Guess Challenger::get_guess(){
    Guess result = Guess(std::vector<int>(_guesses[0].size(), -2));
    for(int i = _from; i < _end; ++i){
        if (_guesses_left[i]) return _guesses[i];
    }
    return result;
}

void Challenger::display_guesses_left(){
    for(size_t i = 0; i < _guesses.size(); i++){
        _guesses[i].display_guess();
        std::cout << "  " << _guesses_left[i] << std::endl;
    }
}

void Challenger::set_from(int new_from){ _from = new_from;}
void Challenger::set_end(int new_end){ _end = new_end;}


void Challenger::display_from_end(){
    std::string tmp = "ch_id: ";
    tmp+= std::to_string(_chall_id);
    tmp += "from: ";
    tmp += std::to_string(_from);
    tmp += "end: ";
    tmp += std::to_string(_end);
    std::cout<<tmp<<std::endl;
}

void Challenger::find_new_end(int size_local_partition){
    int cnt = size_local_partition;
    size_t i = _from;
    while(i < _guesses.size() and cnt > 0){
        //std::cout<<"chdi: "<<ch_id<<"i: "<<i<<" cnt: "<<cnt<<std::endl;
        if(_guesses_left[i]){
            if(cnt == size_local_partition) _from = i;
            cnt--;
        }
        i++;
    }
    _end = i;
}

int Challenger::get_size(){return _guesses.size();}
int Challenger::get_end(){return _end;}

void Challenger::generate_partitions(std::vector<int> &partitions, int challengers_size, int nbr_guesses_left) {
    int partition_size = ceil(nbr_guesses_left/challengers_size);
    partitions = std::vector<int>(challengers_size, partition_size);

    int off = nbr_guesses_left - (partition_size * challengers_size);
    partitions.at(challengers_size -1 ) = partitions.at(challengers_size - 1) + off;

}
