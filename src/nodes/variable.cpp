#include "variable.h"
#include "../pins/numeric.h"
#include <imnodes.h>
#include <iostream>

Variable::Variable(char *name) : Node() {
    this->name = std::string(name);
    outputs.push_back(new NumericPin());
}

Variable::~Variable() {}

void Variable::draw() {
    ImNodes::BeginNode(id);

    ImNodes::BeginNodeTitleBar();
    ImGui::TextUnformatted(name.c_str());
    ImNodes::EndNodeTitleBar();

    Node::draw();

    if (ImGui::Checkbox("Range?", &is_range)) {

        range_min = 0;
        range_max = 0;

    }

    ImGui::BeginDisabled(!is_range);
    ImGui::DragFloat("##range_min", &range_min, 2.5f, -FLT_MAX, 0, "%.2f");
    ImGui::SameLine();
    ImGui::DragFloat("##range_max", &range_max, 2.5f, 0, FLT_MAX, "+%.2f");
    // ImGui::DragFloatRange2("", &range_min, &range_max, 5, 0, FLT_MAX, "-%.2f", "+%.2f");
    ImGui::EndDisabled();

    ImNodes::EndNode();
}