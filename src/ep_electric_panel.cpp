#include "ep_electric_panel.hpp"
#include "ep_gate.hpp"
#include <Tween.hpp>
#include <Timer.hpp>

using namespace godot;

void ElectricPanel::_ready() {
    main_gate = get_node<Gate>("MainGate");
    main_gate->connect("gate_opened", this, "complete");
    tween = get_node<Tween>("Tween");
    close_timer = get_node<Timer>("CloseTimer");
}

void ElectricPanel::_tree_exit() {
    if(!main_gate) return;
    main_gate->disconnect("gate_opened", this, "complete");
}

void ElectricPanel::show() {
    tween->interpolate_property(this, "rect_position", Vector2(0.f, 400.f), Vector2(0.f, 0.f), 0.3f);
    tween->interpolate_property(this, "rect_position", Color(1.f, 1.f, 1.f, 0.f), Color(1.f, 1.f, 1.f, 1.f), 0.3f);
    emit_signal("showed");
}

void ElectricPanel::hide() {
    tween->interpolate_property(this, "rect_position", Vector2(0.f, 0.f), Vector2(0.f, 400.f), 0.3f);
    tween->interpolate_property(this, "rect_position", Color(1.f, 1.f, 1.f, 1.f), Color(1.f, 1.f, 1.f, 0.f), 0.3f);
    close_timer->connect("timeout", this, "_queue_free");
    close_timer->start(0.3f);
    emit_signal("hidden");
}

void ElectricPanel::complete() {
    emit_signal("solved");
    hide();
}