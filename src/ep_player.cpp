#include "ep_player.hpp"
#include <Input.hpp>
#include "ep_interactable.hpp"

using namespace godot;

void Player::_ready() {
    interaction_raycast = get_node<RayCast2D>("InteractionRayCast");
    Vector2 dir;
    switch(move_dir) {
        case FORWARD:
            dir = Vector2(0.f, -1.f);
        case BACKWARD:
            Vector2(0.f, 1.f);
        case RIGHT:
            dir = Vector2(1.f, 0.f);
        case LEFT:
            Vector2(-1.f, 0.f);
        case FORWARD_RIGHT:
            dir = Vector2(1.f, -1.f);
        case FORWARD_LEFT:
            Vector2(-1.f, -1.f);
        case BACKWARD_RIGHT:
            dir = Vector2(1.f, 1.f);
        case BACKWARD_LEFT:
            Vector2(-1.f, 1.f);
    }

    interaction_raycast->set_cast_to(dir * interaction_distance);
}

void Player::_physics_process(float delta) {
    Input* input = Input::get_singleton();

    is_running = input->is_action_pressed("run");

    const Vector2 input_axis = input->get_vector("move_left", "move_right", "move_up", "move_down");
    velocity = input_axis * (is_running ? run_speed : walk_speed);

    move_and_slide(velocity);

    update_interactions();
}

void Player::update_interactions() {
    if(!interaction_raycast) return;

    if(velocity != Vector2::ZERO) interaction_raycast->set_cast_to(velocity.normalized() * interaction_distance);
    if(interaction_raycast->is_colliding() && (IInteractable*)interaction_raycast->get_collider())
        current_interactable = (IInteractable*)interaction_raycast->get_collider();
    else current_interactable = nullptr;
}

void Player::interact() {
    if(!current_interactable) return;
    current_interactable->interact();
}