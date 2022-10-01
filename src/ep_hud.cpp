#include "ep_hud.hpp"
#include "ep_electric_timer.hpp"
#include <TextureProgress.hpp>
#include <Label.hpp>

using namespace godot;

void HUD::_ready() {
    if(has_node(timer_path))
        electric_timer = get_node<ElectricTimer>(timer_path);

    electric_progress_bar = get_node<TextureProgress>("ElectricProgressBar");
    electric_text = get_node<Label>("ElectricProgressBar/ElectricLabel");

    if(!electric_timer || electric_timer->get_time_left() <= 0.f) electric_progress_bar->set_visible(false);
    if(!electric_timer) return;
    electric_timer->connect("started", this, "timer_started");
    electric_timer->connect("stopped", this, "timer_stopped");
}

void HUD::_process(float delta) {
    if(electric_timer && electric_timer->get_time_left() > 0.f) {
        electric_progress_bar->set_value(electric_progress_bar->get_max() / electric_timer->get_wait_time() * electric_timer->get_time_left());
        electric_text->set_text(String::num_int64((int)Math::round(electric_timer->get_time_left())) + " seconds left");
    }
}

void HUD::_exit_tree() {
    if(!electric_timer) return;
    electric_timer->disconnect("started", this, "timer_started");
    electric_timer->disconnect("stopped", this, "timer_stopped");
}

void HUD::timer_started(double p_time) {
    electric_progress_bar->set_visible(true);
}

void HUD::timer_stopped() {
    electric_progress_bar->set_visible(false);
}