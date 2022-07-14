#ifndef PINS_NUMERIC_H
#define PINS_NUMERIC_H

#include "pin.h"

class NumericPin : public Pin {
public:
    float value;

    NumericPin(PinType type, Element *parent, float startVal=0) : Pin(type, parent), value(startVal) {};
    virtual ~NumericPin() {};

    virtual void renderContent();
};

#endif