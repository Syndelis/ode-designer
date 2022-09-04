#ifndef NODES_NODE_H
#define NODES_NODE_H

#include <imnodes.h>
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include "../core/element.h"
#include "../pins/pin.h"
#include "../common/pin_type.h"

class Pin;
class Node : public Element {
public:

    inline static std::map<unsigned int, Node*> allNodes;
    std::string name;
    std::vector<Pin*> inputs;
    std::vector<Pin*> outputs;

    virtual inline unsigned int getColor() { return IM_COL32(127, 127, 127, 255); }
    virtual inline unsigned int getHighlitColor() { return IM_COL32(255, 255, 255, 255); }

    Node(char *name);
    virtual ~Node();
    virtual void renderPins();
    virtual void process();
    virtual bool onPinLinked(Pin *thisPin, Node *otherNode);
    virtual void onPinUnlinked(Pin *thisPin, Node *otherNode);
    virtual Pin *getNextAvailablePin(PinType type) {
        if (type == PinType::Input)
            return inputs[inputs.size() - 1];

        else if (type == PinType::Output)
            return outputs[outputs.size() - 1];
    };

    template<class T> T *pushInput() {
        inputs.push_back(new T(PinType::Input, this));
        return (T *)inputs.back();
    }

    template<class T> T *pushOutput() {
        outputs.push_back(new T(PinType::Output, this));
        return (T *)outputs.back();
    }
};

#endif