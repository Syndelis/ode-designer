#ifndef PINS_NAME_ECHOER_H
#define PINS_NAME_ECHOER_H

#include "pin.h"

class NameEchoerPin : public Pin {
public:

    NameEchoerPin(PinType type, Node *parent) : Pin(type, parent) {
        setData(parent->name);
    };
    virtual ~NameEchoerPin() {};

    virtual void renderContent() {};

};

#endif