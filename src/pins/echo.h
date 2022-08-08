#ifndef PINS_ECHO_H
#define PINS_ECHO_H

#include "pin.h"

class EchoPin : public Pin {
public:

    EchoPin(PinType type, Node *parent) : Pin(type, parent) {};
    virtual ~EchoPin() {};

    virtual void renderContent();
};

#endif