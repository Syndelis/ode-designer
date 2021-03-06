#ifndef NODES_NODE_H
#define NODES_NODE_H

#include <imnodes.h>
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include "../core/element.h"
#include "../pins/pin.h"

class Node : public Element {
public:

    inline static std::map<unsigned int, Node*> allNodes;
    std::string name;
    std::vector<Pin*> inputs;
    std::vector<Pin*> outputs;

    virtual inline unsigned int getColor() { return IM_COL32(127, 127, 127, 255); }
    virtual inline unsigned int getHighlitColor() { return IM_COL32(255, 255, 255, 255); }

    Node(char *name) : Element() {
        this->name = std::string(name);
        allNodes[id] = this;
    }

    virtual ~Node() {
        allNodes.erase(id);
    };
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

    virtual void process() {

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

    template<class T> T *pushInput() {
        inputs.push_back(new T(PinType::Input, (Element *)this));
        return (T *)inputs.back();
    }

    template<class T> T *pushOutput() {
        outputs.push_back(new T(PinType::Output, (Element *)this));
        return (T *)outputs.back();
    }
};

#endif