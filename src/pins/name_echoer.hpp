#ifndef PINS_NAME_ECHOER_HPP
#define PINS_NAME_ECHOER_HPP

#include "pin.hpp"

#include "../nodes/node.hpp"

class NameEchoerPin : public Pin {
public:

    NameEchoerPin(PinType type, Node *parent) : Pin(type, parent) {
        setData(parent->name);
    };

    ~NameEchoerPin() override = default;

    void renderContent() override {};
};

#endif