#include "population.h"
#include "../pins/numeric.h"
#include <imnodes.h>

Population::Population() : Node() {
    outputs.push_back(new NumericPin());
}

Population::~Population() {}

void Population::draw() {
    ImNodes::BeginNode(id);

    ImNodes::BeginNodeTitleBar();
    ImGui::TextUnformatted("simple node :)");
    ImNodes::EndNodeTitleBar();

    Node::draw();

    ImNodes::EndNode();
}