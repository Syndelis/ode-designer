#ifndef NODES_COMBINATOR_H
#define NODES_COMBINATOR_H

#include "node.hpp"

class Combinator : public Node {
public:
    int selected;
    Pin *expression_pin;

    inline unsigned int getColor() override {
        return IM_COL32(0, 121, 140, 255);
    }

    inline unsigned int getHighlitColor() override {
        return IM_COL32(6, 214, 160, 255);
    }

    Combinator(char *name);
    ~Combinator() override = default;
    void renderContent() override;
    bool onPinLinked(Pin *thisPin, Node *otherNode) override;
    void onPinUnlinked(Pin *thisPin, Node *otherNode) override;

    void updateExpressionInBackground();
};

#endif