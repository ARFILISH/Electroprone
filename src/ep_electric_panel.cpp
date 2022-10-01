#include "ep_electric_panel.hpp"
#include "ep_gate.hpp"
#include <Tween.hpp>
#include <Timer.hpp>
#include <Input.hpp>

using namespace godot;

void ElectricPanel::_ready() {
    main_gate = get_node<Gate>("MainGate");
    main_gate->connect("gate_opened", this, "complete");
    tween = get_node<Tween>("Tween");
    close_timer = get_node<Timer>("CloseTimer");
    close_timer->connect("timeout", this, "queue_free");
}

void ElectricPanel::_input(const Ref<InputEvent> event) {
    Input* input = Input::get_singleton();

    if(input->is_action_just_pressed("ui_cancel")) hide();
}

void ElectricPanel::_exit_tree() {
    if(main_gate)
        main_gate->disconnect("gate_opened", this, "complete");
    if(close_timer && close_timer->is_connected("timeout", this, "queue_free"))
        close_timer->disconnect("timeout", this, "queue_free");
    Godot::print("die");
}

void ElectricPanel::show() {
    tween->interpolate_property(this, "rect_position", get_position() + Vector2(0.f, 400.f), get_position(), 0.1f);
    tween->interpolate_property(this, "modulate", Color(1.f, 1.f, 1.f, 0.f), Color(1.f, 1.f, 1.f, 1.f), 0.1f);
    tween->start();
    emit_signal("showed");
}

void ElectricPanel::hide() {
    tween->interpolate_property(this, "rect_position", get_position(), get_position() + Vector2(0.f, 400.f), 0.1f);
    tween->interpolate_property(this, "modulate", Color(1.f, 1.f, 1.f, 1.f), Color(1.f, 1.f, 1.f, 0.f), 0.1f);
    tween->start();
    close_timer->start(0.3f);
    emit_signal("hidden");
}

void ElectricPanel::complete() {
    Godot::print("HAHAHA");
    emit_signal("solved");
    hide();
}