#include "ep_panel_node.hpp"
#include <CanvasLayer.hpp>
#include <ResourceLoader.hpp>
#include "ep_electric_panel.hpp"

using namespace godot;

void PanelNode::_ready() {
    canvas = get_node<CanvasLayer>(canvas_path);
    pnl = nullptr;
}

void PanelNode::show() {
    if(pnl) return;
    if(!canvas) return;

    if(!(pnl = Object::cast_to<ElectricPanel>(panel_scene->instance()))) {
        pnl = nullptr;
        return;
    }

    canvas->add_child(pnl);
    pnl->connect("showed", this, "showed");
    pnl->connect("hidden", this, "hidden");
    pnl->connect("solved", this, "completed");
    pnl->show_panel();
}

void PanelNode::hide() {
    if(!pnl) return;

    pnl->hide_panel();
}

void PanelNode::showed() {
    emit_signal("showed");
}

void PanelNode::hidden() {
    pnl = nullptr;
    emit_signal("hidden");
}

void PanelNode::completed() {
    emit_signal("solved");
}