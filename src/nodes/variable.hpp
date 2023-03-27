#ifndef NODES_INITIAL_H
#define NODES_INITIAL_H

#include "node.hpp"

#include <string>

class Variable : public Node {
public:

    inline unsigned int getColor() override {
        return IM_COL32(48, 99, 142, 255);
    }

    inline unsigned int getHighlitColor() override {
        return IM_COL32(17, 138, 178, 255);
    }

    float value     = .0f;
    bool is_range   = false;
    float range_min = 0;
    float range_max = 0;

    Variable(char *name);
    ~Variable() override = default;
    void renderContent() override;
};

#endif