#ifndef EP_BOOL_GATE_HPP
#define EP_BOOL_GATE_HPP

#include <Godot.hpp>
#include <Node.hpp>

namespace godot {

class BoolGate : public Node {
    GODOT_CLASS(BoolGate, Node);
private:
    bool opened = false;

public:
    static void _register_methods() {
        register_method("open", &BoolGate::open);
        register_method("close", &BoolGate::close);
        register_method("set_opened", &BoolGate::set_opened);
        register_property<BoolGate, bool>("opened", &BoolGate::opened, false);
        register_signal<BoolGate>("gate_opened");
        register_signal<BoolGate>("gate_closed");
    }

    BoolGate() {}
    ~BoolGate() {}

    void _init() {}

    void open();
    void close();
    void set_opened(bool value);

};

}

#endif /* EP_GATE_HPP */