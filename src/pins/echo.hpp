#ifndef PINS_ECHO_HPP
#define PINS_ECHO_HPP

#include "pin.hpp"

class EchoPin : public Pin {
public:

    EchoPin(PinType type, Node *parent) : Pin(type, parent) {};
    ~EchoPin() override = default;

    bool acceptsData() override { return true; }

    void renderContent() override;
};

#endif