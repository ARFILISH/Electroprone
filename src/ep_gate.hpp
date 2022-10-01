#ifndef EP_GATE_HPP
#define EP_GATE_HPP

#include <Godot.hpp>
#include <Node.hpp>

namespace godot {

class Gate : public Node {
    GODOT_CLASS(Gate, Node);
public:
    int needed_number = 3;

private:
    int current_number = 0;

public:
    static void _register_methods() {
        register_method("add_number", &Gate::add_number);
        register_method("subtract_number", &Gate::subtract_number);
        register_property<Gate, int>("needed_number", &Gate::needed_number, 3);
        register_signal<Gate>("gate_opened");
        register_signal<Gate>("gate_closed");
    }

    Gate() {}
    ~Gate() {}

    void _init() {}

    void add_number();
    void subtract_number();
    void reset();
    void set_number(int num_to_set);

};

}

#endif /* EP_GATE_HPP */