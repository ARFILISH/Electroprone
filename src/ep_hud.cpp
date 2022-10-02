#include "ep_hud.hpp"
#include "ep_electric_timer.hpp"
#include <TextureProgress.hpp>
#include <Label.hpp>
#include "ep_player.hpp"

using namespace godot;

void HUD::_ready() {
    electric_progress_bar = get_node<TextureProgress>("ElectricProgressBar");
    electric_text = get_node<Label>("ElectricProgressBar/ElectricLabel");
    interaction_text = get_node<Label>("PromptLabel");
    Node* timer_node = get_node_or_null(timer_path);
    if(electric_timer = Object::cast_to<ElectricTimer>(timer_node)) {
        if(electric_timer->get_time_left() <= 0.f) electric_progress_bar->set_visible(false);
        electric_timer->connect("started", this, "timer_started");
        electric_timer->connect("stopped", this, "timer_stopped");
        electric_timer->connect("timeout", this, "timer_stopped");
    }
    else electric_progress_bar->set_visible(false);
    hint_text = get_node<Label>("HintLabel");
    hint_text->set_text("");
    hint_text->set_visible(false);
    hint_hide_timer = get_node<Timer>("HintLabel/HideTimer");

    if(has_node(player_path)) player = get_node<Player>(player_path);
}

void HUD::_physics_process(float delta) {
    if(electric_timer) {
        electric_progress_bar->set_value(electric_progress_bar->get_max() / electric_timer->get_wait_time() * electric_timer->get_time_left());
        electric_text->set_text(String::num_int64((int)Math::round(electric_timer->get_time_left())) + " seconds left");
    }
    if(!player) return;
    interaction_text->set_visible(player->get_prompt() != "");
    interaction_text->set_text(player->get_prompt());
}

void HUD::_exit_tree() {
    if(!electric_timer) return;
    electric_timer->disconnect("started", this, "timer_started");
    electric_timer->disconnect("stopped", this, "timer_stopped");
    electric_timer->disconnect("timeout", this, "timer_stopped");
}

void HUD::show_hint(String text, float _hide_in_time) {
    if(text == "") return;
    hint_text->set_visible(true);
    hint_text->set_text(text);
    if(_hide_in_time > 0.f) {
        hint_hide_timer->start(_hide_in_time);
    }
}

void HUD::hide_hint() {
    hint_text->set_visible(false);
    hint_text->set_text("");
}

void HUD::timer_started(double p_time) {
    electric_progress_bar->set_visible(true);
}

void HUD::timer_stopped() {
    electric_progress_bar->set_visible(false);
}