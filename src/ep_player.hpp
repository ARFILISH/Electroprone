#ifndef EP_PLAYER_HPP
#define EP_PLAYER_HPP

#include <Godot.hpp>
#include <KinematicBody2D.hpp>
#include <RayCast2D.hpp>
#include "ep_interactable.hpp"

namespace godot {

class AnimationPlayer;

enum MOVE_DIRECTION {
    FORWARD = 0,
    BACKWARD = 1,
    RIGHT = 2,
    LEFT = 3,
    FORWARD_RIGHT = 4,
    FORWARD_LEFT = 5,
    BACKWARD_RIGHT = 6,
    BACKWARD_LEFT = 7
};

class Player : public KinematicBody2D {
    GODOT_CLASS(Player, KinematicBody2D)
public:
    float walk_speed = 200.f;
    float run_speed = 450.f;
    float interaction_distance = 50.f;

protected:
    bool is_running = false;
    int move_dir = MOVE_DIRECTION::FORWARD;

    RayCast2D* interaction_raycast;
    AnimationPlayer* anim_player;
    Interactable* current_interactable = nullptr;

private:
    // YOU, who looks at source code of this game - use only strings in this array!
    Array inventory {};
    Vector2 velocity = Vector2::ZERO;
    bool input_enabled = true;

public:
    static void _register_methods() {
        register_method("_ready", &Player::_ready);
        register_method("_process", &Player::_process);
        register_method("_physics_process", &Player::_physics_process);
        register_method("update_interactions", &Player::update_interactions);
        register_method("update_animations", &Player::update_animations);
        register_method("interact", &Player::interact);
        register_method("enable_input", &Player::enable_input);
        register_method("disable_input", &Player::disable_input);
        register_method("add_item_to_inventory", &Player::add_item_to_inventory);
        register_method("add_items_to_inventory", &Player::add_items_to_inventory);
        register_method("remove_items_from_inventory", &Player::remove_items_from_inventory);
        register_method("inventory_has_items", &Player::inventory_has_items);
        register_method("inventory_has_items", &Player::inventory_has_items);
        register_method("get_prompt", &Player::get_prompt);
        register_property<Player, bool>("input_enabled", &Player::input_enabled, true);
        register_property<Player, float>("walk_speed", &Player::walk_speed, 200.f);
        register_property<Player, float>("run_speed", &Player::run_speed, 450.f);
        register_property<Player, float>("interaction_distance", &Player::interaction_distance, 50.f);
        register_property<Player, int>("move_dir", &Player::move_dir, MOVE_DIRECTION::FORWARD, 
            GODOT_METHOD_RPC_MODE_DISABLED, GODOT_PROPERTY_USAGE_DEFAULT,GODOT_PROPERTY_HINT_ENUM, 
            "Forward, Backward, Right, Left, Forward right, Forward left, Backward right, Backward left");
        register_property<Player, Array>("inventory", &Player::inventory, {});
    }

    Player() {}
    ~Player() {}

    void _init() {}
    void enable_input() { input_enabled = true;}
    void disable_input() { input_enabled = false; }
    bool add_item_to_inventory(String item);
    void add_items_to_inventory(Array items);
    void remove_items_from_inventory(Array items);
    bool inventory_has_items(Array items);
    String get_prompt() const { if(!current_interactable || !input_enabled) return ""; return current_interactable->get_prompt((Player*)this); };

protected:
    void _ready();
    void _process(float delta);
    void _physics_process(float delta);
    
    void update_interactions();
    void update_animations();
    void interact();
};

}

#endif /* PLAYER_H */