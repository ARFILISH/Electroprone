#ifndef EP_INTERACTABLE_HPP
#define EP_INTERACTABLE_HPP

#include <Godot.hpp>
#include <Area2D.hpp>

namespace godot {

class AudioStreamPlayer2D;

class Interactable : public Area2D {
    GODOT_CLASS(Interactable, Area2D)
protected:
    int max_interacts = 0;
    String prompt = "Press Enter to interact";

    AudioStreamPlayer2D* sound_player;

private:
    int interaction_count = 0;

public:
    static void _register_methods() {
        register_method("_init", &Interactable::_init);
        register_method("interact", &Interactable::interact);
        register_method("_ready", &Interactable::_ready);
        register_method("get_prompt", &Interactable::get_prompt);
        register_property<Interactable, int>("max_interacts", &Interactable::max_interacts, 0);
        register_property<Interactable, String>("prompt", &Interactable::prompt, String("Press Enter to interact"));
        register_signal<Interactable>("interacted", GODOT_VARIANT_TYPE_INT, "_count_interacted");
        register_signal<Interactable>("interacted_no_args");
    }

    Interactable() {}
    ~Interactable() {}

    void _init();
    void interact();
    void reset_interaction_count();
    String get_prompt() const { return prompt; }

protected:
    void _ready();
};

}

#endif /* EP_INTERACTABLE_HPP */