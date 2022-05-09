#ifndef PINS_BASE_H
#define PINS_BASE_H

#include <map>
#include <imnodes.h>
#include "../core/element.h"

class Pin : public Element {
public:
    inline static std::map<unsigned int, Pin*> allPins;
    std::map<int, Pin*> linkedTo;

    static void unlink(int linkId) {
        for (auto &[id, pin] : allPins)
            if (pin->linkedTo.count(linkId)) {
                pin->linkedTo.erase(linkId);
                break;
            }
    }
    
    Pin() : Element() {
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