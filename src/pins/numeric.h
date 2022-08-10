#ifndef PINS_NUMERIC_H
#define PINS_NUMERIC_H

#include "pin.h"

class NumericPin : public Pin {
public:
    float value;

    NumericPin(PinType type, Node *parent, float startVal=0) : Pin(type, parent), value(startVal) {
        data = value;
    };
    virtual ~NumericPin() {};

    virtual void renderContent();
};

#endif