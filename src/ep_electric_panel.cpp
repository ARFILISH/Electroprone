#include "ep_electric_panel.hpp"
#include "ep_gate.hpp"
#include <Tween.hpp>
#include <Timer.hpp>
#include <Input.hpp>
#include <AudioStreamPlayer.hpp>

using namespace godot;

void ElectricPanel::_ready() {
    main_gate = get_node<Gate>("MainGate");
    main_gate->connect("gate_opened", this, "complete");
    tween = get_node<Tween>("Tween");
    close_timer = get_node<Timer>("CloseTimer");
    sound_player = get_node<AudioStreamPlayer>("SoundPlayer");
}

void ElectricPanel::_input(const Ref<InputEvent> event) {
    Input* input = Input::get_singleton();

    if(input->is_action_just_pressed("ui_cancel")) hide_panel();
}

void ElectricPanel::show_panel() {
    tween->interpolate_property(this, "rect_position", get_position() + Vector2(0.f, 400.f), get_position(), anim_duration);
    tween->interpolate_property(this, "modulate", Color(1.f, 1.f, 1.f, 0.f), Color(1.f, 1.f, 1.f, 1.f), anim_duration);
    tween->start();
    if(sound_player) {
        sound_player->set_stream(show_sound);
        sound_player->play();
    }
    emit_signal("showed");
}

void ElectricPanel::hide_panel() {
    tween->interpolate_property(this, "rect_position", get_position(), get_position() + Vector2(0.f, 400.f), anim_duration);
    tween->interpolate_property(this, "modulate", Color(1.f, 1.f, 1.f, 1.f), Color(1.f, 1.f, 1.f, 0.f), anim_duration);
    tween->start();
    close_timer->start(anim_duration);
    if(!close_timer->is_connected("timeout", this, "queue_free")) close_timer->connect("timeout", this, "queue_free");
    if(sound_player) {
        sound_player->set_stream(hide_sound);
        sound_player->play();
    }
    emit_signal("hidden");
}

void ElectricPanel::complete() {
    emit_signal("solved");
    hide_panel();
}