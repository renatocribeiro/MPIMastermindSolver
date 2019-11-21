//
// Created by rena on 07.11.19.
//

#include "Challenger.h"

Challenger::Challenger(const int &challenger_id, const int &size_secret, const int &nbr_color,
                       const std::vector<Guess> &all_guesses, unsigned int def_from, unsigned int def_end) {
    _chall_id = challenger_id;
    _guesses = all_guesses;
    _guesses_left = std::vector<bool>(all_guesses.size(), true);
    _from = def_from;
    _end = def_end;

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
