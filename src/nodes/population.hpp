#ifndef NODES_POPULATION_HPP
#define NODES_POPULATION_HPP

#include "node.hpp"

#include "../pins/pin.hpp"

class Population : public Node {
public:

    Pin *name_echoer;

    inline unsigned int getColor() override {
        return IM_COL32(209, 73, 91, 255);
    }

    inline unsigned int getHighlitColor() override {
        return IM_COL32(239, 71, 111, 255);
    }

    Population(char *name);
    ~Population() override = default;
    void renderContent() override;
    bool onPinLinked(Pin *thisPin, Node *otherNode) override;
    void onPinUnlinked(Pin *thisPin, Node *otherNode) override;

    Model serializeInto(Model model) override;
<<<<<<< HEAD

=======
>>>>>>> 40e1569e6eea3a2bbbf4c62fd5086e008ac2209f
};

#endif