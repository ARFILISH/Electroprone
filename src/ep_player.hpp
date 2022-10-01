#ifndef EP_PLAYER_HPP
#define EP_PLAYER_HPP

#include <Godot.hpp>
#include <KinematicBody2D.hpp>
#include <RayCast2D.hpp>
#include "ep_interactable.hpp"

namespace godot {

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
    Interactable* current_interactable = nullptr;

private:
    Vector2 velocity = Vector2::ZERO;

public:
    static void _register_methods() {
        register_method("_ready", &Player::_ready);
        register_method("_physics_process", &Player::_physics_process);
        register_method("update_interactions", &Player::update_interactions);
        register_method("interact", &Player::interact);
        register_property<Player, float>("walk_speed", &Player::walk_speed, 200.f);
        register_property<Player, float>("run_speed", &Player::run_speed, 450.f);
        register_property<Player, float>("interaction_distance", &Player::interaction_distance, 50.f);
        register_property<Player, int>("move_dir", &Player::move_dir, MOVE_DIRECTION::FORWARD, 
            GODOT_METHOD_RPC_MODE_DISABLED, GODOT_PROPERTY_USAGE_DEFAULT,GODOT_PROPERTY_HINT_ENUM, 
            "Forward, Backward, Right, Left, Forward right, Forward left, Backward right, Backward left");
    }

    Player() {}
    ~Player() {}

    void _init() {}

protected:
    void _ready();
    void _physics_process(float delta);
    
    void update_interactions();
    void interact();
};

}

#endif /* PLAYER_H */