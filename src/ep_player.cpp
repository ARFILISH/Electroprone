#include "ep_player.hpp"
#include <Input.hpp>

using namespace godot;

void Player::_ready() {
    interaction_raycast = get_node<RayCast2D>("InteractionRayCast");
    Vector2 dir;
    switch(move_dir) {
        case 0:
            dir = Vector2(0.f, -1.f);
            break;
        case 1:
            Vector2(0.f, 1.f);
            break;
        case 2:
            dir = Vector2(1.f, 0.f);
            break;
        case 3:
            Vector2(-1.f, 0.f);
            break;
        case 4:
            dir = Vector2(1.f, -1.f);
            break;
        case 5:
            Vector2(-1.f, -1.f);
            break;
        case 6:
            dir = Vector2(1.f, 1.f);
            break;
        case 7:
            Vector2(-1.f, 1.f);
            break;
    }

    interaction_raycast->set_cast_to(dir.normalized() * interaction_distance);
}

void Player::_process(float delta) {
    update_interactions();
}

void Player::_physics_process(float delta) {
    if(!input_enabled) return;

    Input* input = Input::get_singleton();

    is_running = input->is_action_pressed("run");

    const Vector2 input_axis = input->get_vector("move_left", "move_right", "move_up", "move_down");
    velocity = input_axis * (is_running ? run_speed : walk_speed);

    move_and_slide(velocity);
    if(input->is_action_just_pressed("interact"))
        interact();
}

void Player::update_interactions() {
    if(!(interaction_raycast && input_enabled)) return;

    if(velocity != Vector2::ZERO) interaction_raycast->set_cast_to(velocity.normalized() * interaction_distance);
    if(!(current_interactable = Object::cast_to<Interactable>(interaction_raycast->get_collider())))
        current_interactable = nullptr;
}

void Player::interact() {
    if(!(input_enabled && current_interactable && current_interactable->can_interact(this))) return;
    current_interactable->interact(this);
}

bool Player::add_item_to_inventory(String item) {
    if(inventory.has(item)) return false;
    inventory.append(item);
    return true;
}

void Player::add_items_to_inventory(Array items) {
    for(int i = 0; i < items.size(); i++) {
        add_item_to_inventory(items[i]);
    }
}

void Player::remove_items_from_inventory(Array items) {
    for(int i = 0; i < items.size(); i++) {
        if(inventory.has(items[i])) inventory.remove(i);
    }
}

bool Player::inventory_has_items(Array items) {
    for(int i = 0; i < items.size(); i++) {
        if(!inventory.has(items[i])) return false;
    }
    return true;
}