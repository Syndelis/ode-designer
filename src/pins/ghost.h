#ifndef PINS_GHOST_H
#define PINS_GHOST_H

#include "pin.h"

class GhostPin : public Pin {
public:

    GhostPin(PinType type, Node *parent) : Pin(type, parent) {};
    virtual ~GhostPin() {};

    virtual void renderContent();
    virtual void renderPinConnector();

};

#endif