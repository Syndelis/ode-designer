#ifndef NODES_ASSIGNER_H
#define NODES_ASSIGNER_H

#include "node.hpp"

#include "../pins/pin.hpp"

class PopulationNotFoundException: std::exception {
public:
    std::string name;
    PopulationNotFoundException(std::string name): name(std::move(name)), std::exception() { }
};

class Assigner : public Node {
public:

    char* population = nullptr;

    inline unsigned int getColor() override {
        return IM_COL32(0x20, 0x40, 0xdd, 255);
    }

    inline unsigned int getHighlitColor() override {
        return IM_COL32(0x2f, 0x4f, 0xf0, 255);
    }

    Assigner(char* name);
    ~Assigner() override = default;
    void renderContent() override;
    bool onPinLinked(Pin *thisPin, Node *otherNode) override;
    void onPinUnlinked(Pin *thisPin, Node *otherNode) override;
};

#endif
