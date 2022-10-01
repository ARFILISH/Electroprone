#include "ep_interactable.hpp"

using namespace godot;

void Interactable::interact() {
    if(interaction_count < max_interacts || max_interacts <= 0)
        emit_signal("interacted");
}