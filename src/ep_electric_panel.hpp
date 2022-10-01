#ifndef EP_ELECTIC_PANEL_HPP
#define EP_ELECTIC_PANEL_HPP

#include <Godot.hpp>
#include <Control.hpp>
#include <InputEvent.hpp>

namespace godot {

class Gate;
class Tween;
class Timer;

class ElectricPanel : public Control {
    GODOT_CLASS(ElectricPanel, Control)
private:
    bool input_enabled = true;
    Gate* main_gate;
    Tween* tween;
    Timer* close_timer;

public:

    static void _register_methods() {
        register_method("_ready", &ElectricPanel::_ready);
        register_method("_tree_exit", &ElectricPanel::_exit_tree);
        register_method("show", &ElectricPanel::show);
        register_method("hide", &ElectricPanel::hide);
        register_method("_input", &ElectricPanel::_input);
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
    void _input(const Ref<InputEvent> event);
    void _exit_tree();
    void complete();

};

}

#endif /* EP_ELECTIC_PANEL_HPP */