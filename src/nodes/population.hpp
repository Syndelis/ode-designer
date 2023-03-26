#ifndef NODES_POPULATION_H
#define NODES_POPULATION_H

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
};

#endif