#ifndef NODES_BASE_H
#define NODES_BASE_H

#include <imnodes.h>
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include "../core/element.h"
#include "../pins/base.h"

class Node : public Element {
public:

    std::string name;
    std::vector<Pin*> inputs;
    std::vector<Pin*> outputs;

    virtual inline unsigned int getColor() { return IM_COL32(127, 127, 127, 255); }
    virtual inline unsigned int getHighlitColor() { return IM_COL32(255, 255, 255, 255); }

    Node(char *name) : Element() {
        this->name = std::string(name);
    }

    virtual ~Node() {};
    virtual void renderPins() {

        for (auto &input : inputs) {
            ImNodes::BeginInputAttribute(input->id);
            input->renderContent();
            ImNodes::EndInputAttribute();
        }

        for (auto &output : outputs) {
            ImNodes::BeginOutputAttribute(output->id);
            output->renderContent();
            ImNodes::EndOutputAttribute();
        }

    };
    
    virtual void process(std::map<Pin*, Pin*> &links) {

        unsigned int highlitColor = getHighlitColor();

        ImNodes::PushColorStyle(ImNodesCol_TitleBar, getColor());
        ImNodes::PushColorStyle(ImNodesCol_TitleBarHovered, highlitColor);
        ImNodes::PushColorStyle(ImNodesCol_TitleBarSelected, highlitColor);
        ImNodes::BeginNode(id);

        ImNodes::BeginNodeTitleBar();
        ImGui::TextUnformatted(name.c_str());
        ImNodes::EndNodeTitleBar();

        renderPins();
        renderContent();

        ImNodes::EndNode();
        ImNodes::PopColorStyle();
        ImNodes::PopColorStyle();
        ImNodes::PopColorStyle();

    }
};

#endif