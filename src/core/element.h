#ifndef ELEMENT_H
#define ELEMENT_H

static int nextId = 1;

class Element {
public:
    int id;
    Element(): id(nextId++) {}
    virtual ~Element() {}
    virtual void renderContent() {}
};

#endif