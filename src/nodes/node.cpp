#include "node.h"
#include <imnodes.h>
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include "../core/element.h"
#include "../pins/pin.h"

Node::Node(char *name) : Element() {
    this->name = std::string(name);
    allNodes[id] = this;
}

Node::~Node() {
    allNodes.erase(id);
}

void Node::renderPins() {

    for (auto &input : inputs) {
        input->renderPinConnector();
    }

    for (auto &output : outputs) {
        output->renderPinConnector();
    }

}

void Node::process() {

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
}

bool Node::onPinLinked(Pin *thisPin, Node *otherNode) {
    return true;
}

void Node::onPinUnlinked(Pin *thisPin, Node *otherNode) {}