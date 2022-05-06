#ifndef NODES_INITIAL_H
#define NODES_INITIAL_H

#include "base.h"
#include <string>


class Variable : public Node {
public:

    std::string name;
    float value;
    bool is_range = false;
    float range_min = 0;
    float range_max = 0;

    Variable(char *name);
    virtual ~Variable();
    virtual void draw();

};

#endif