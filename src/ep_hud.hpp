#ifndef EP_HUD_HPP
#define EP_HUD_HPP

#include <Godot.hpp>
#include <Control.hpp>

namespace godot {

class ElectricTimer;
class TextureProgress;
class Label;
class Player;

class HUD : public Control {
    GODOT_CLASS(HUD, Control);
protected:
    NodePath timer_path;
    ElectricTimer* electric_timer;
    TextureProgress* electric_progress_bar;
    Label* electric_text;
    Label* interaction_text;
    Player* player;

public:
    static void _register_methods() {
        register_method("_ready", &HUD::_ready);
        register_method("_exit_tree", &HUD::_exit_tree);
        register_method("_process", &HUD::_process);
        register_method("timer_started", &HUD::timer_started);
        register_method("timer_stopped", &HUD::timer_stopped);
        register_property<HUD, NodePath>("timer_path", &HUD::timer_path, "");
    }

    HUD() {}
    ~HUD() {}

    void _init() {}

protected:
    void _ready();
    void _exit_tree();
    void _process(float delta);

    void timer_started(double p_time);
    void timer_stopped();
};

}

#endif /* EP_HUD_HPP */