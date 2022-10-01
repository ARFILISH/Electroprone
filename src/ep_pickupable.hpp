#ifndef EP_PICKUPABLE_HPP
#define EP_PICKUPABLE_HPP

#include <Godot.hpp>
#include "ep_interactable.hpp"

namespace godot {

class Pickupable : public Interactable {
    GODOT_CLASS(Pickupable, Interactable);
public:
    String id = "default_id";

public:
    static void _register_methods() {
        register_method("on_interacted", &Pickupable::on_interacted);
        register_method("can_interact", &Pickupable::can_interact);
        register_property<Pickupable, String>("id", &Pickupable::id, "default_id");
        register_signal<Pickupable>("picked_up");
    }

    Pickupable() {}
    ~Pickupable() {}

    void _init() {}
    virtual bool can_interact(Node* interacted) const override;
    
protected:
    virtual void on_interacted(Node* interacted) override;

};

}

#endif