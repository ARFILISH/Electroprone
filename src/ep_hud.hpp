#ifndef EP_HUD_HPP
#define EP_HUD_HPP

#include <Godot.hpp>
#include <Control.hpp>

namespace godot {

class ElectricTimer;
class TextureProgress;
class Label;
class Player;
class Timer;

class HUD : public Control {
    GODOT_CLASS(HUD, Control);
protected:
    NodePath timer_path;
    NodePath player_path;
    ElectricTimer* electric_timer;
    TextureProgress* electric_progress_bar;
    Label* electric_text;
    Label* interaction_text;
    Label* hint_text;
    Timer* hint_hide_timer;
    Player* player;

public:
    static void _register_methods() {
        register_method("_ready", &HUD::_ready);
        register_method("_exit_tree", &HUD::_exit_tree);
        register_method("_physics_process", &HUD::_physics_process);
        register_method("show_hint", &HUD::show_hint);
        register_method("hide_hint", &HUD::hide_hint);
        register_method("timer_started", &HUD::timer_started);
        register_method("timer_stopped", &HUD::timer_stopped);
        register_property<HUD, NodePath>("timer_path", &HUD::timer_path, "");
        register_property<HUD, NodePath>("player_path", &HUD::player_path, "");
    }

    HUD() {}
    ~HUD() {}

    void _init() {}

    void show_hint(String text, float _hide_in_time = 0.f);
    void hide_hint();

protected:
    void _ready();
    void _exit_tree();
    void _physics_process(float delta);

    void timer_started(double p_time);
    void timer_stopped();
};

}

#endif /* EP_HUD_HPP */