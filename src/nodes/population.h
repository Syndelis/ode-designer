#ifndef NODES_POPULATION_H
#define NODES_POPULATION_H

#include "../pins/pin.h"
#include "node.h"

class Population : public Node {
public:

    Pin *name_echoer;

    virtual inline unsigned int getColor() { return IM_COL32(209, 73, 91, 255); }
    virtual inline unsigned int getHighlitColor() { return IM_COL32(239, 71, 111, 255); }

    Population(char *name);
    virtual ~Population();
    virtual void renderContent();
    virtual bool onPinLinked(Pin *thisPin, Node *otherNode);
    virtual void onPinUnlinked(Pin *thisPin, Node *otherNode);

    // Variable
    float value;

};

#endif
