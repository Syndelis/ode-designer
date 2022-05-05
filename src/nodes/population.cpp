#include "population.h"
#include <imgui_node_editor.h>

namespace Editor = ax::NodeEditor;

Population::Population() {
}

Population::~Population() {
}

void Population::draw() {
    int uniqueId = 1;
    Editor::BeginNode(uniqueId++);
        ImGui::Text("Node A");
        Editor::BeginPin(uniqueId++, Editor::PinKind::Input);
            ImGui::Text("-> In");
        Editor::EndPin();
        ImGui::SameLine();
        Editor::BeginPin(uniqueId++, Editor::PinKind::Output);
            ImGui::Text("Out ->");
        Editor::EndPin();
    Editor::EndNode();
}