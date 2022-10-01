#ifndef EP_ELECTRIC_TIMER_HPP
#define EP_ELECTRIC_TIMER_HPP

#include <Godot.hpp>
#include <Timer.hpp>

namespace godot {

class ElectricTimer : public Timer {
    GODOT_CLASS(ElectricTimer, Timer);
public:

public:
    static void _register_methods() {
        register_method("start", &ElectricTimer::start);
        register_method("stop", &ElectricTimer::stop);
        register_signal<ElectricTimer>("started", GODOT_VARIANT_TYPE_REAL, "p_time");
        register_signal<ElectricTimer>("stopped");
    }

    ElectricTimer() {}
    ~ElectricTimer() {}

    void _init() {}
    void start(double p_time);
    void stop();

};

}

#endif /* EP_ELECTRIC_TIMER_HPP */