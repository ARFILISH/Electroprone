#ifndef EP_COUNT_EVENT
#define EP_COUNT_EVENT

#include <Godot.hpp>
#include <Node.hpp>

namespace godot {

class CountEvent : public Node {
    GODOT_CLASS(CountEvent, Node)
public:
    int max_count = 3;

private:
    int current_count = 0;

public:
    static void _register_methods() {
        register_method("activate", &CountEvent::activate);
        register_method("reset", &CountEvent::reset);
        register_property<CountEvent, int>("max_count", &CountEvent::max_count, 3);
        register_property<CountEvent, int>("current_count", &CountEvent::current_count, 0);
        register_signal<CountEvent>("activated");
    }

    CountEvent() {}
    ~CountEvent() {}

    void _init() {}

    void activate();
    void reset();
};

}

#endif