#ifndef PINS_BASE_H
#define PINS_BASE_H

#include <map>
#include "../core/element.h"

class Pin : public Element {
public:
    inline static std::map<unsigned int, Pin*> allPins;
    std::map<Pin*, int> linkedTo;
    
    Pin() : Element() {
        allPins[id] = this;
    }

    void link(Pin *other) {

        linkedTo[other] = getNextId();
        
    }
};

#endif