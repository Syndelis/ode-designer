#ifndef NODES_BASE_H
#define NODES_BASE_H

#include <imnodes.h>
#include <vector>
#include "../core/element.h"
#include "../pins/base.h"

class Node : public Element {
public:
    std::vector<Pin*> inputs;
    std::vector<Pin*> outputs;

    using Element::Element;
    virtual ~Node() {};
    virtual void draw() {
        // This method will only draw the pins,
        // so you can override it to draw the node itself

        for (auto &input : inputs) {
            ImNodes::BeginInputAttribute(input->id);
            input->draw();
            ImNodes::EndInputAttribute();
        }

        for (auto &output : outputs) {
            ImNodes::BeginOutputAttribute(output->id);
            output->draw();
            ImNodes::EndOutputAttribute();
        }

    };
};

#endif