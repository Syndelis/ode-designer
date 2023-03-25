#ifndef PINS_ECHO_H
#define PINS_ECHO_H

#include "pin.hpp"

class EchoPin : public Pin {
public:

    EchoPin(PinType type, Node *parent) : Pin(type, parent) {};
    ~EchoPin() override = default;

    virtual bool acceptsData() { return true; }

    virtual void renderContent();
};

#endif