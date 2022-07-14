#ifndef PINS_PIN_H
#define PINS_PIN_H

#include <map>
#include <imnodes.h>
#include "../core/element.h"
#include <iostream>
#include <stdio.h>

enum class PinType : char {
    Input,
    Output
};

class Pin : public Element {
public:
    inline static std::map<unsigned int, Pin*> allPins;
    std::map<int, Pin*> linkedTo;
    PinType type;
    Element *parent;
    std::string outputData, *inputData;

    static void unlink(int linkId) {
        for (auto &[id, pin] : allPins)
            if (pin->linkedTo.count(linkId)) {
                pin->linkedTo.erase(linkId);
                break;
            }
    }

    static void linkTogether(int linkId1, int linkId2) {
        Pin *pin1 = allPins[linkId1];
        Pin *pin2 = allPins[linkId2];
        
        switch (pin1->type) {

            case PinType::Input:
                pin2->link(pin1);
                break;

            case PinType::Output:
                pin1->link(pin2);
                break;

        }
    }
    
    Pin(PinType type, Element *parent) : Element(), type(type), parent(parent) {
        allPins[id] = this;
    }

    virtual ~Pin() {
        allPins.erase(id);
    }

    void link(Pin *other) {
        linkedTo[getNextId()] = other;
        other->inputData = &outputData;
    }

    void renderLinks() {
        for (auto &[linkId, dstPin] : linkedTo)
            ImNodes::Link(linkId, id, dstPin->id);
    }
};

#endif