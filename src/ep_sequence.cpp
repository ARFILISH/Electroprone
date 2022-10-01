#include "ep_sequence.hpp"

using namespace godot;

void Sequence::_init() {
    current_number = Math::clamp(current_number, 0, max_signals - 1);
}

void Sequence::add_number() {
    set_number(current_number + 1);
}

void Sequence::subtract_number() {
    set_number(current_number - 1);
}

void Sequence::set_number(int num_to_set) {
    num_to_set = Math::clamp(num_to_set, 0, max_signals - 1);
    if(num_to_set == current_number) return;
    
    current_number = num_to_set;
    Godot::print(get_name() + ": current number is " + String::num_int64(current_number));
    String signal_name = "sequence_" + String::num_int64(current_number);
    emit_signal(signal_name);
}