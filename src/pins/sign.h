#ifndef PINS_SIGN_H
#define PINS_SIGN_H

#include "pin.h"
#include "echo.h"

class SignPin : public EchoPin {
public:
    int selected;

    SignPin(PinType type, Node *parent) : EchoPin(type, parent), selected(0) {};
    virtual ~SignPin() {};

    const char *getSign();

    virtual void renderContent();

};

#endif