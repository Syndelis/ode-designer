#ifndef PINS_BASE_H
#define PINS_BASE_H

#include <map>
#include <imnodes.h>
#include "../core/element.h"

enum class PinType : char {
    Input,
    Output
};

class Pin : public Element {
public:
    inline static std::map<unsigned int, Pin*> allPins;
    std::map<int, Pin*> linkedTo;
    PinType type;

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
                pin1->link(pin2);
                break;

            case PinType::Output:
                pin2->link(pin1);
                break;

        }
    }
    
    Pin(PinType type) : Element(), type(type) {
        allPins[id] = this;
    }

    void link(Pin *other) {
        linkedTo[getNextId()] = other;
    }

    void renderLinks() {
        for (auto &[linkId, dstPin] : linkedTo)
            ImNodes::Link(linkId, id, dstPin->id);
    }
};

#endif