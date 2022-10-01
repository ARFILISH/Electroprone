#include "ep_interactable.hpp"
#include <AudioStreamPlayer2D.hpp>

using namespace godot;

void Interactable::_init() {
    max_interacts = Math::max(0, max_interacts);
    interaction_count = Math::clamp(interaction_count, 0, max_interacts);
}

void Interactable::_ready() {
    sound_player = get_node<AudioStreamPlayer2D>("SoundPlayer");
}

void Interactable::interact() {
    if(interaction_count < max_interacts || max_interacts <= 0) {
        interaction_count++;
        emit_signal("interacted", interaction_count);
        emit_signal("interacted_no_args");
        if(!sound_player) return;
        sound_player->play();
    }
}

void Interactable::reset_interaction_count() {
    interaction_count = 0;
}