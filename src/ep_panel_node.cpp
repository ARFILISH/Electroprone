#include "ep_panel_node.hpp"
#include <CanvasLayer.hpp>
#include <ResourceLoader.hpp>
#include "ep_electric_panel.hpp"

using namespace godot;

void PanelNode::_ready() {
    canvas = get_node<CanvasLayer>(canvas_path);
}

void PanelNode::show() {
    if(!canvas) return;
    pnl = Object::cast_to<ElectricPanel>(panel_scene->instance());
    if(!pnl) return;

    canvas->add_child(pnl);
    pnl->connect("showed", this, "showed");
    pnl->connect("hidden", this, "hidden");
    pnl->connect("solved", this, "completed");
    pnl->show();
}

void PanelNode::hide() {
    if(!pnl) return;

    pnl->hide();
}

void PanelNode::showed() {
    if(!pnl) return;
    emit_signal("showed");
}

void PanelNode::hidden() {
    if(!pnl) return;
    if(pnl->is_connected("showed", this, "showed")) pnl->disconnect("showed", this, "showed");
    if(pnl->is_connected("hidden", this, "hidden")) pnl->disconnect("hidden", this, "hidden");
    if(pnl->is_connected("solved", this, "completed")) pnl->disconnect("solved", this, "completed");
    emit_signal("hidden");
}

void PanelNode::completed() {
    emit_signal("solved");
}