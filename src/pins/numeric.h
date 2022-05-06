#ifndef PINS_NUMERIC_H
#define PINS_NUMERIC_H

#include "base.h"

class NumericPin : public Pin {
public:
    float value;

    NumericPin() : Pin(), value(0) {};
    NumericPin(float startVal) : Pin(), value(startVal) {};
    
    virtual ~NumericPin() {};
    virtual void renderContent();
};

#endif