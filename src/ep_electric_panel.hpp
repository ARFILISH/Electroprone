#ifndef EP_ELECTIC_PANEL_HPP
#define EP_ELECTIC_PANEL_HPP

#include <Godot.hpp>
#include <Control.hpp>
#include <InputEvent.hpp>
#include <AudioStream.hpp>

namespace godot {

class Gate;
class Tween;
class Timer;
class AudioStreamPlayer;

class ElectricPanel : public Control {
    GODOT_CLASS(ElectricPanel, Control)
public:
    float anim_duration = 0.1f;
    Ref<AudioStream> show_sound;
    Ref<AudioStream> hide_sound;
private:
    bool input_enabled = true;
    Gate* main_gate;
    Tween* tween;
    Timer* close_timer;
    AudioStreamPlayer* sound_player;

public:
    static void _register_methods() {
        register_method("_ready", &ElectricPanel::_ready);
        register_method("show_panel", &ElectricPanel::show_panel);
        register_method("hide_panel", &ElectricPanel::hide_panel);
        register_method("_input", &ElectricPanel::_input);
        register_method("complete", &ElectricPanel::complete);
        register_property<ElectricPanel, float>("anim_duration", &ElectricPanel::anim_duration, 0.3f);
        register_property<ElectricPanel, Ref<AudioStream>>("show_sound", &ElectricPanel::show_sound, Ref<AudioStream>(), 
            GODOT_METHOD_RPC_MODE_DISABLED, GODOT_PROPERTY_USAGE_DEFAULT, GODOT_PROPERTY_HINT_RESOURCE_TYPE, "AudioStream");
        register_property<ElectricPanel, Ref<AudioStream>>("hide_sound", &ElectricPanel::hide_sound, Ref<AudioStream>(), 
            GODOT_METHOD_RPC_MODE_DISABLED, GODOT_PROPERTY_USAGE_DEFAULT, GODOT_PROPERTY_HINT_RESOURCE_TYPE, "AudioStream");
        register_signal<ElectricPanel>("solved");
        register_signal<ElectricPanel>("showed");
        register_signal<ElectricPanel>("hidden");
    }

    ElectricPanel() {}
    ~ElectricPanel() {}

    void _init() {}

    void show_panel();
    void hide_panel();

protected:
    void _ready();
    void _input(const Ref<InputEvent> event);
    void complete();

};

}

#endif /* EP_ELECTIC_PANEL_HPP */