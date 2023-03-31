#ifndef NODES_POPULATION_H
#define NODES_POPULATION_H

#include "node.hpp"
#include <exception>
#include <utility>

#include "../pins/pin.hpp"

class PopulationExistsException: std::exception {
public:
    std::string name;
    PopulationExistsException(std::string name): name(std::move(name)), std::exception() { }
};

class Population : public Node {
public:
    static inline std::unordered_map<std::string, Population*> allPopulations;

    static Population* getByName(const std::string& name);

    Pin *name_echoer;
    float value;

    inline unsigned int getColor() override {
        return IM_COL32(209, 73, 91, 255);
    }

    inline unsigned int getHighlitColor() override {
        return IM_COL32(239, 71, 111, 255);
    }

    Population(char *name);
    ~Population() override;
    void renderContent() override;
    bool onPinLinked(Pin *thisPin, Node *otherNode) override;
    void onPinUnlinked(Pin *thisPin, Node *otherNode) override;
};

#endif
