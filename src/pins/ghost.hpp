#ifndef PINS_GHOST_H
#define PINS_GHOST_H

#include "pin.hpp"

class GhostPin : public Pin {
public:

    GhostPin(PinType type, Node *parent) : Pin(type, parent) {};
    ~GhostPin() override = default;

    void renderContent() override;
    void renderPinConnector() override;

};

#endif