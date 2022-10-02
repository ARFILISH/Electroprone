#include "ep_player.hpp"
#include <Input.hpp>
#include <AnimationPlayer.hpp>
#include <CanvasLayer.hpp>
#include <Popup.hpp>
#include <ResourceLoader.hpp>

using namespace godot;

void Player::_ready() {
    interaction_raycast = get_node<RayCast2D>("InteractionRayCast");
    anim_player = get_node<AnimationPlayer>("AnimationPlayer");
    Vector2 dir;
    switch(move_dir) {
        case FORWARD:
            dir = Vector2(0.f, -1.f);
            break;
        case BACKWARD:
            Vector2(0.f, 1.f);
            break;
        case RIGHT:
            dir = Vector2(1.f, 0.f);
            break;
        case LEFT:
            Vector2(-1.f, 0.f);
            break;
        case FORWARD_RIGHT:
            dir = Vector2(1.f, -1.f);
            break;
        case FORWARD_LEFT:
            Vector2(-1.f, -1.f);
            break;
        case BACKWARD_RIGHT:
            dir = Vector2(1.f, 1.f);
            break;
        case BACKWARD_LEFT:
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
    update_animations();
    if(input->is_action_just_pressed("interact"))
        interact();
}

void Player::update_interactions() {
    if(!(interaction_raycast && input_enabled)) return;

    if(velocity != Vector2::ZERO) interaction_raycast->set_cast_to(velocity.normalized() * interaction_distance);
    if(!(current_interactable = Object::cast_to<Interactable>(interaction_raycast->get_collider())))
        current_interactable = nullptr;
}

void Player::update_animations() {
    if(!anim_player) return;

    Vector2 vel_norm = velocity.normalized();
    
    if(velocity != Vector2::ZERO) {
        if(vel_norm == Vector2(1.f, 0.f)) move_dir = RIGHT;
        else if (vel_norm == Vector2(0.35f, 0.35f)) move_dir = BACKWARD_RIGHT;
        else if (vel_norm == Vector2(0.35f, -0.35f)) move_dir = FORWARD_RIGHT;
        else if (vel_norm == Vector2(-1.f, 0.f)) move_dir = LEFT;
        else if (vel_norm == Vector2(-0.35f, 0.35f)) move_dir = BACKWARD_LEFT;
        else if (vel_norm == Vector2(-0.35f, -0.35f)) move_dir = FORWARD_LEFT;
        else if (vel_norm == Vector2(0.f, 1.f)) move_dir = BACKWARD;
        else if (vel_norm == Vector2(0.f, -1.f)) move_dir = FORWARD;
    }

    String anim_direction;
    switch(move_dir) {
        case FORWARD:
            anim_direction = "forward";
            break;
        case BACKWARD:
            anim_direction = "backward";
            break;
        case RIGHT:
            anim_direction = "right";
            break;
        case LEFT:
            anim_direction = "left";
            break;
        case FORWARD_RIGHT:
        case BACKWARD_LEFT:
        case FORWARD_LEFT:
        case BACKWARD_RIGHT:
            break;
    }

    String anim_speed;
    if(velocity.length() <= walk_speed / 4) anim_speed = "idle_";
    else if(velocity.length() > walk_speed / 4 && velocity.length() <= (walk_speed + run_speed) / 2) anim_speed = "walk_";
    else anim_speed = "run_";

    anim_player->set_current_animation(anim_speed + anim_direction);
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
        if(inventory.has(items[i])) inventory.remove(inventory.find(items[i]));
    }
}

bool Player::inventory_has_items(Array items, bool exclusive) {
    for(int i = 0; i < items.size(); i++) {
        if(exclusive)
            if(inventory.has(items[i])) return true;
        
        if(!inventory.has(items[i])) return false;
    }
    return true;
}

void Player::game_over() {
    disable_input();
    CanvasLayer* canvas = CanvasLayer::_new();
    canvas->set_name("GameOverCanvas");
    canvas->set_layer(999);
    add_child(canvas);

    Popup* game_over = Object::cast_to<Popup>(game_over_scene->instance());
    if(!game_over) return;
    canvas->add_child(game_over);
    game_over->popup();
}