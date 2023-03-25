#ifndef NODES_INITIAL_H
#define NODES_INITIAL_H

#include "node.hpp"
#include <string>


class Variable : public Node {
public:

    virtual inline unsigned int getColor() { return IM_COL32(48, 99, 142, 255); }
    virtual inline unsigned int getHighlitColor() { return IM_COL32(17, 138, 178, 255); }

    float value;
    bool is_range = false;
    float range_min = 0;
    float range_max = 0;

    Variable(char *name);
    ~Variable() override = default;
    virtual void renderContent();

};

#endif