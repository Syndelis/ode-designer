#ifndef ELEMENT_H
#define ELEMENT_H

#include <string>

using ElementID         = int;
static ElementID nextId = 1;

class Element {
public:
    ElementID id;

    static ElementID getNextId() { return nextId++; }

    Element() : id(nextId++) {}

    virtual ~Element() = default;

    virtual void renderContent() {}
};

#endif