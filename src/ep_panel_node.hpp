#ifndef EP_PANEL_NODE_HPP
#define EP_PANEL_NODE_HPP

#include <Godot.hpp>
#include <Node.hpp>
#include <PackedScene.hpp>

namespace godot {

class CanvasLayer;
class ElectricPanel;

class PanelNode : public Node {
    GODOT_CLASS(PanelNode, Node);
public:
    NodePath canvas_path;
    Ref<PackedScene> panel_scene;

private:
    ElectricPanel* pnl;
    CanvasLayer* canvas;


public:
    static void _register_methods() {
        register_method("_ready", &PanelNode::_ready);
        register_method("show", &PanelNode::show);
        register_method("hide", &PanelNode::hide);
        register_method("showed", &PanelNode::showed);
        register_method("hidden", &PanelNode::hidden);
        register_method("completed", &PanelNode::completed);
        register_property<PanelNode, NodePath>("canvas_path", &PanelNode::canvas_path, "");
        register_property<PanelNode, Ref<PackedScene>>("panel_scene", &PanelNode::panel_scene, Ref<PackedScene>(), 
            GODOT_METHOD_RPC_MODE_DISABLED, GODOT_PROPERTY_USAGE_DEFAULT, GODOT_PROPERTY_HINT_RESOURCE_TYPE, "PackedScene");
        register_signal<PanelNode>("showed");
        register_signal<PanelNode>("hidden");
        register_signal<PanelNode>("solved");
    }

    PanelNode() {}
    ~PanelNode() {}

    void _init() {}

    void show();
    void hide();

protected:
    void _ready();
    void showed();
    void hidden();
    void completed();

};

}

#endif