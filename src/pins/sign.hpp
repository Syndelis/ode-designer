#ifndef PINS_SIGN_HPP
#define PINS_SIGN_HPP

#include "echo.hpp"
#include "pin.hpp"

class SignPin : public EchoPin {
public:
    int selected = 0;

    SignPin(PinType type, Node *parent) : EchoPin(type, parent) {};

    ~SignPin() override = default;

    const char *getSign();

    void renderContent() override;
};

#endif