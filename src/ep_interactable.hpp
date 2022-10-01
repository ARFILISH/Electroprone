#include <string>

class IInteractable {
public:
    virtual ~IInteractable();
    virtual void interact();
    virtual std::string get_prompt() const { return "Press Enter to interact."; };
};