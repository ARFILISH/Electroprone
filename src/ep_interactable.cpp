#include "ep_interactable.hpp"
#include <AudioStreamPlayer2D.hpp>
#include "ep_player.hpp"

using namespace godot;

void Interactable::_init() {
    max_interacts = Math::max(0, max_interacts);
    interaction_count = Math::clamp(interaction_count, 0, max_interacts);
}

void Interactable::_ready() {
    sound_player = get_node<AudioStreamPlayer2D>("SoundPlayer");
}

void Interactable::interact(Node* interacted) {
    if(interaction_count < max_interacts || max_interacts <= 0) {
        Player* plr = Object::cast_to<Player>(interacted);
        if(!plr) return;
        if(consume_items) plr->remove_items_from_inventory(needed_items);
        interaction_count++;
        emit_signal("interacted", interaction_count);
        emit_signal("interacted_no_args");
        on_interacted(interacted);
        if(!sound_player);
        sound_player->play();
    }
}

void Interactable::reset_interaction_count() {
    interaction_count = 0;
}

bool Interactable::can_interact(Node* interacted) const {
    if(!may_interact) return false;
    if(!this) return false;
    Player* plr = Object::cast_to<Player>(interacted);
    if(!plr) return false;
    if(needed_items.empty() || plr->inventory_has_items(needed_items)) return true;
}