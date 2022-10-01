#ifndef EP_SEQUENCE_HPP
#define EP_SEQUENCE_HPP

#include <Godot.hpp>
#include <Node.hpp>

namespace godot {

class Sequence : public Node {
    GODOT_CLASS(Sequence, Node);
private:
    int current_number = 0;

    int max_signals = 16;

public:
    static void _register_methods() {
        register_method("_init", &Sequence::_init);
        register_method("add_number", &Sequence::add_number);
        register_method("subtract_number", &Sequence::subtract_number);
        register_method("set_number", &Sequence::set_number);
        register_property<Sequence, int>("current_number", &Sequence::current_number, 0);
        for(int i = 0; i < 16; ++i) {
            const String name = "sequence_" + String::num_int64(i);
            register_signal<Sequence>(name);
        }
    }

    Sequence() {}
    ~Sequence() {}

    void _init();

    void add_number();
    void subtract_number();
    void set_number(int num_to_set);

};

}

#endif /* EPSEQUENCE_HPP */