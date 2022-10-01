#include "ep_electric_timer.hpp"

using namespace godot;

void ElectricTimer::start(double p_time) {
    Timer::start(p_time);
    emit_signal("started", p_time);
}

void ElectricTimer::stop() {
    Timer::stop();
    emit_signal("stopped");
}