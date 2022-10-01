#include "ep_bool_gate.hpp"

using namespace godot;

void BoolGate::open() {
    set_opened(true);
}

void BoolGate::close() {
    set_opened(false);
}

void BoolGate::set_opened(bool value) {
    if(value == opened) return;
    opened = value;

    emit_signal(value ? "gate_opened" : "gate_closed"); 
}