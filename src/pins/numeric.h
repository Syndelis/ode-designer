#ifndef PINS_NUMERIC_H
#define PINS_NUMERIC_H

#include "pin.h"

class NumericPin : public Pin {
public:
    float value;

    NumericPin(PinType type) : Pin(type), value(0) {};
    NumericPin(PinType type, float startVal) : Pin(type), value(startVal) {};
    
    virtual ~NumericPin() {};
    virtual void renderContent();
};

#endif