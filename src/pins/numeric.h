#ifndef PINS_NUMERIC_H
#define PINS_NUMERIC_H

#include "base.h"

class NumericPin : public Pin {
public:
    double value;

    NumericPin() : Pin(), value(0) {};
    NumericPin(double startVal) : Pin(), value(startVal) {};
    
    virtual ~NumericPin() {};
    virtual void draw();
};

#endif