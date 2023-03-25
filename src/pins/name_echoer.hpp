#ifndef PINS_NAME_ECHOER_H
#define PINS_NAME_ECHOER_H

#include "pin.hpp"

class NameEchoerPin : public Pin {
public:

    NameEchoerPin(PinType type, Node *parent) : Pin(type, parent) {
        setData(parent->name);
    };
    ~NameEchoerPin() override = default;

    virtual void renderContent() {};

};

#endif