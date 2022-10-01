#ifndef EP_INTERACTABLE_HPP
#define EP_INTERACTABLE_HPP

#include <Godot.hpp>
#include <Area2D.hpp>

namespace godot {

class AudioStreamPlayer2D;

class Interactable : public Area2D {
    GODOT_CLASS(Interactable, Area2D)
public:
    Array needed_items {};
    bool consume_items = true;
    bool may_interact = true;
protected:
    int max_interacts = 0;
    String prompt = "Press Enter to interact";
    String failed_prompt = "";

    AudioStreamPlayer2D* sound_player;

    int interaction_count = 0;

public:
    static void _register_methods() {
        register_method("_init", &Interactable::_init);
        register_method("interact", &Interactable::interact);
        register_method("_ready", &Interactable::_ready);
        register_method("on_interacted", &Interactable::on_interacted);
        register_method("can_interact", &Interactable::can_interact);
        register_method("get_prompt", &Interactable::get_prompt);
        register_property<Interactable, Array>("needed_items", &Interactable::needed_items, {});
        register_property<Interactable, bool>("consume_items", &Interactable::consume_items, true);
        register_property<Interactable, bool>("may_interact", &Interactable::may_interact, true);
        register_property<Interactable, int>("max_interacts", &Interactable::max_interacts, 0);
        register_property<Interactable, String>("prompt", &Interactable::prompt, "Press Enter to interact");
        register_property<Interactable, String>("failed_prompt", &Interactable::failed_prompt, "");
        register_signal<Interactable>("interacted", GODOT_VARIANT_TYPE_INT, "_count_interacted");
        register_signal<Interactable>("interacted_no_args");
    }

    Interactable() {}
    ~Interactable() {}

    void _init();
    void interact(Node* interacted);
    void reset_interaction_count();
    virtual bool can_interact(Node* interacted) const;
    String get_prompt(Node* interacted) const { return can_interact(interacted) ? prompt : failed_prompt; }

protected:
    void _ready();
    virtual void on_interacted(Node* interacted) {}
};

}

#endif /* EP_INTERACTABLE_HPP */