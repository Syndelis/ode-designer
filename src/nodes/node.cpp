#include "node.hpp"

#include <imnodes.h>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "../core/element.hpp"

#include "../pins/pin.hpp"

Node::Node(char *name) : Element() {
    this->name   = std::string(name);
    allNodes[id] = this;
}

Node::~Node() { allNodes.erase(id); }

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
    return thisPin->canLink;
}

void Node::onPinUnlinked(Pin *thisPin, Node *otherNode) {}

Model Node::serializeInto(Model model) {
    // This method should never be executed, as all subclasses must override it.
    // However, there appears to be a bug in the compiler that causes it to
    // complain about this method not being implemented, even though it is
    // implemented in the subclasses. This is a workaround.

    // Introducing a static_assert to guarantee it's never called doesn't work,
<<<<<<< HEAD
    // as the compiler seems to be adamant that it is, in fact, being called.    
=======
    // as the compiler seems to be adamant that it is, in fact, being called.
>>>>>>> 40e1569e6eea3a2bbbf4c62fd5086e008ac2209f

    return model;
}
