#include "ep_range_gate.hpp"

using namespace godot;

void RangeGate::set_value(float value) {
    if((current_value && value) >= min_value && (current_value && value) <= max_value) return;
    const float last_value = current_value;

    current_value = value;
    if((last_value >= min_value && last_value <= max_value) && !(current_value >= min_value && current_value <= max_value)) {
        emit_signal("gate_closed");
        return;
    }
    if(!(last_value >= min_value && last_value <= max_value) && (current_value >= min_value && current_value <= max_value)) {
        emit_signal("gate_opened");
        return;
    }
}