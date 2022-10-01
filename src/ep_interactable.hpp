#ifndef EP_INTERACTABLE_HPP
#define EP_INTERACTABLE_HPP

#include <Godot.hpp>
#include <Area2D.hpp>

namespace godot {

class Interactable : public Area2D {
    GODOT_CLASS(Interactable, Area2D)
protected:
    int max_interacts = 0;
    String prompt = "Press Enter to interact";
    int interaction_count = 0;

public:
    static void _register_methods() {
        register_method("interact", &Interactable::interact);
        register_property<Interactable, int>("max_interacts", &Interactable::max_interacts, 0);
        register_property<Interactable, String>("prompt", &Interactable::prompt, String("Press Enter to interact"));
        register_signal<Interactable>("interacted");
    }

    Interactable() {}
    ~Interactable() {}

    void _init() {}

    void interact();
};

}

#endif /* EP_INTERACTABLE_HPP */