#include "ep_count_event.hpp"

using namespace godot;

void CountEvent::activate() {
    if(current_count < max_count) {
        emit_signal("activated");
        current_count++;
    }
}

void CountEvent::reset() {
    current_count = 0;
}