#include "ep_gate.hpp"

using namespace godot;

void Gate::_init() {
    needed_number = Math::max(1, needed_number);
    current_number = Math::clamp(current_number, 0, needed_number);
}

void Gate::add_number() {
    set_number(current_number + 1);
}

void Gate::subtract_number() {
    set_number(current_number - 1);
}

void Gate::set_number(int num_to_set) {
    num_to_set = Math::clamp(num_to_set, 0, needed_number);
    if(num_to_set == current_number) return;
    const int last_set_number = current_number;
    
    current_number = num_to_set;

    Godot::print(get_name() + ": number set to " + String::num_int64(current_number));

    if(last_set_number == needed_number && current_number < needed_number) {
        emit_signal("gate_closed");
        Godot::print(get_name() + ": gate was closed");
        return;
    }
    if(last_set_number < needed_number && current_number >= needed_number) {
        emit_signal("gate_opened");
        Godot::print(get_name() + ": gate was opened");
        return;
    }
}