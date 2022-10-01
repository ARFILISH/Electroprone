#ifndef EP_ELECTIC_PANEL_HPP
#define EP_ELECTIC_PANEL_HPP

#include <Godot.hpp>
#include <Control.hpp>

namespace godot {

class Gate;
class Tween;
class Timer;

class ElectricPanel : public Control {
    GODOT_CLASS(ElectricPanel, Control)
private:
    Gate* main_gate;
    Tween* tween;
    Timer* close_timer;

public:
    static void _register_methods() {
        register_method("_ready", &ElectricPanel::_ready);
        register_method("_tree_exit", &ElectricPanel::_tree_exit);
        register_method("show", &ElectricPanel::show);
        register_method("hide", &ElectricPanel::hide);
        register_method("complete", &ElectricPanel::complete);

        register_signal<ElectricPanel>("solved");
        register_signal<ElectricPanel>("showed");
        register_signal<ElectricPanel>("hidden");
    }

    ElectricPanel() {}
    ~ElectricPanel() {}

    void _init() {}

    void show();
    void hide();

protected:
    void _ready();
    void _tree_exit();
    void complete();

};

}

#endif /* EP_ELECTIC_PANEL_HPP */