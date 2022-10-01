#include <Godot.hpp>

#include "ep_player.hpp"
#include "ep_interactable.hpp"
#include "ep_gate.hpp"
#include "ep_sequence.hpp"
#include "ep_hud.hpp"
#include "ep_electric_timer.hpp"
#include "ep_pickupable.hpp"
#include "ep_bool_gate.hpp"
#include "ep_electric_panel.hpp"
#include "ep_panel_node.hpp"

using namespace godot;

extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options *o) {
    Godot::gdnative_init(o);
}

extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options *o) {
    Godot::gdnative_terminate(o);
}

extern "C" void GDN_EXPORT godot_nativescript_init(void *handle) {
    Godot::nativescript_init(handle);

    register_class<Player>();
    register_class<Interactable>();
    register_class<Gate>();
    register_class<Sequence>();
    register_class<HUD>();
    register_class<ElectricTimer>();
    register_class<Pickupable>();
    register_class<BoolGate>();
    register_class<ElectricPanel>();
    register_class<PanelNode>();
}