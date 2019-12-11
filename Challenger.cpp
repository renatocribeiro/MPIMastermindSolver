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



void Challenger::generate_partitions(std::vector<type_guess> &local, int challengers_size, type_guess total_guesses_left) {
    type_guess partition_size = ceil(total_guesses_left / challengers_size);

    local = std::vector<type_guess> (challengers_size, partition_size);
    type_guess off = total_guesses_left - (partition_size * challengers_size);
    local.at(challengers_size -1 ) = local.at(challengers_size - 1) + off;
/*    partitions = std::vector<type_guess>(challengers_size*2);
    type_guess previous = 0;
    for(size_t i = 0; i<challengers_size; i++){
        partitions[i*2] = previous;
        previous = partitions[i*2] + local[i];
        partitions[i*2+1] = previous;
    }*/
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

void Challenger::get_ranges(std::vector<Range> & ranges) {
    ranges = std::move(_ranges);
}

void Challenger::generate_new_ranges(std::vector<Range> & new_ranges, std::vector<int> &new_range_distr, std::vector<Range> & old_ranges, int & challengers_size) {


    type_guess total = 0;
    for(auto f: old_ranges) total += f.end - f.from;

    std::vector<type_guess> local;
    Challenger::generate_partitions(local, challengers_size, total);

    new_range_distr = std::vector<int>(challengers_size, 0);
    Range current_range = old_ranges.back();
    old_ranges.pop_back();
    int current_partition;
    type_guess diff;
    for(size_t i = 0; i<local.size(); i++){
        current_partition = local[i];
        while(current_partition > 0){
            std::cout<<"i: "<<i<<" cpartion: "<<current_partition<<std::endl;
            if(current_range.size() > current_partition){
                std::cout<<">>>"<<"crangeize: "<<current_range.size()<<std::endl;
                diff = current_range.size() - current_partition;
                current_partition = diff;
                Range new_range;
                new_range.from = current_range.from;
                new_range.end = current_range.end - diff;
                new_ranges.push_back(new_range);
                current_range.from = current_range.end - diff;
            }
            else if(current_range.size() < current_partition){
                std::cout<<"<<<"<<"crangeize: "<<current_range.size()<<std::endl;
                current_partition -= current_range.size();
                new_ranges.push_back(current_range);
                current_range = old_ranges.back();
                old_ranges.pop_back();
            }
            else {
                std::cout<<"==="<<"crangeize: "<<current_range.size()<<std::endl;
                current_partition = 0;
                new_ranges.push_back(current_range);
                current_range = old_ranges.back();
                old_ranges.pop_back();
            }
            new_range_distr[i]++;
        }

    }



    //for(auto f: local){std::cout<<"___, "<<f<<std::endl;}

}

void Challenger::generate_new_ranges(std::vector<Range> & new_ranges, int challengers_size, type_guess total_guesses_left) {
    std::vector<type_guess> local;
    Challenger::generate_partitions(local, challengers_size, total_guesses_left);


    type_guess previous = 0;
    for(size_t i = 0; i<challengers_size; i++){
        type_guess tmp_from = previous;
        previous = tmp_from + local[i];
        type_guess tmp_end = previous;
        new_ranges.push_back(Range(tmp_from, tmp_end));
    }
}