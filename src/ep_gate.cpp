#include "ep_gate.hpp"

using namespace godot;

void Gate::add_number() {
    set_number(current_number + 1);
}

void Gate::subtract_number() {
    set_number(current_number - 1);
}

void Gate::set_number(int num_to_set) {
    if(num_to_set == current_number) return;
    const int last_set_number = current_number;

    current_number = Math::clamp(num_to_set, 0, needed_number);
    if(last_set_number == needed_number && current_number < needed_number) {
        emit_signal("gate_closed");
        return;
    }
    if(last_set_number < needed_number && current_number >= needed_number) {
        emit_signal("gate_opened");
        return;
    }
    Godot::print(get_name() + ": current number is " + String::num_int64(current_number));
}