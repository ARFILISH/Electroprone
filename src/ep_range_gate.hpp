#ifndef EP_RANGE_GATE_HPP
#define EP_RANGE_GATE_HPP

#include <Godot.hpp>
#include <Node.hpp>

namespace godot {

class RangeGate : public Node {
    GODOT_CLASS(RangeGate, Node);
public:
    float min_value = 3.f;
    float max_value = 6.f;

private:
    float current_value = 0.f;

public:
    static void _register_methods() {
        register_method("set_value", &RangeGate::set_value);
        register_property<RangeGate, float>("min_value", &RangeGate::min_value, 3.f);
        register_property<RangeGate, float>("max_value", &RangeGate::max_value, 6.f);
        register_property<RangeGate, float>("current_value", &RangeGate::current_value, 0.f);
        register_signal<RangeGate>("gate_opened");
        register_signal<RangeGate>("gate_closed");
    }

    RangeGate() {}
    ~RangeGate() {}

    void _init() {}

    void set_value(float value);

};

}

#endif /* EP_RANGE_GATE_HPP */