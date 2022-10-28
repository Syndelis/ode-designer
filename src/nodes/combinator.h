#ifndef NODES_COMBINATOR_H
#define NODES_COMBINATOR_H

#include "node.h"

class Combinator : public Node {
public:
    int selected;
    Pin *expression_pin;

    virtual inline unsigned int getColor() { return IM_COL32(0, 121, 140, 255); }
    virtual inline unsigned int getHighlitColor() { return IM_COL32(6, 214, 160, 255); }

    Combinator(char *name);
    virtual ~Combinator();
    virtual void renderContent();
    virtual bool onPinLinked(Pin *thisPin, Node *otherNode);
    virtual void onPinUnlinked(Pin *thisPin, Node *otherNode);

    void updateExpressionInBackground();

};

#endif