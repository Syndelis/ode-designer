#ifndef ELEMENT_H
#define ELEMENT_H

#include <string>

static int nextId = 1;

class Element {
public:
    int id;

    static int getNextId() { return nextId++; }

    Element(): id(nextId++) {}
    virtual ~Element() {}
    virtual void renderContent() {}
};

#endif