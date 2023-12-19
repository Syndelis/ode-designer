#ifndef NODES_NODE_HPP
#define NODES_NODE_HPP

#include <imnodes.h>
#include <iostream>
#include <map>
#include <odeir.hpp>
#include <string>
#include <vector>
#include <odeir.hpp>

#include "../common/pin_type.hpp"
#include "../core/element.hpp"

#include "../pins/pin.hpp"

class Pin;

class Node : public Element {
public:

    inline static std::map<ElementID, Node *> allNodes;
    std::string name;
    std::vector<Pin *> inputs;
    std::vector<Pin *> outputs;

    virtual inline unsigned int getColor() {
        return IM_COL32(127, 127, 127, 255);
    }

    virtual inline unsigned int getHighlitColor() {
        return IM_COL32(255, 255, 255, 255);
    }

    Node(char *name);
    ~Node() override;
    virtual void renderPins();
    virtual void process();
    virtual bool onPinLinked(Pin *thisPin, Node *otherNode);
    virtual void onPinUnlinked(Pin *thisPin, Node *otherNode);

    virtual Pin *getNextAvailablePin(PinType type) {
        switch (type) {
            case PinType::Input:
                return inputs[inputs.size() - 1];
                break;

            case PinType::Output:
                return outputs[outputs.size() - 1];
                break;
        }
    }

    virtual Model serializeInto(Model model);

    template <class T>
    T *pushInput() {
        inputs.push_back(new T(PinType::Input, this));
        return (T *)inputs.back();
    }

    template <class T>
    T *pushOutput() {
        outputs.push_back(new T(PinType::Output, this));
        return (T *)outputs.back();
    }
};

#endif