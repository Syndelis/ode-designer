#ifndef PINS_ECHO_H
#define PINS_ECHO_H

#include "pin.h"
#include "../nodes/node.h"

class EchoPin : public Pin {
public:

    EchoPin(PinType type, Element *parent) : Pin(type, parent) {
        inputData = &((Node *)parent)->name;
    };
    virtual ~EchoPin() {};

    virtual void renderContent();
};

#endif