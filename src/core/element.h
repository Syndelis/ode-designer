#ifndef ELEMENT_H
#define ELEMENT_H

#include <string>

typedef unsigned int ElementID;
static ElementID nextId = 1;

class Element {
public:
    ElementID id;

    static ElementID getNextId() { return nextId++; }

    Element(): id(nextId++) {}
    virtual ~Element() {}
    virtual void renderContent() {}
};

#endif