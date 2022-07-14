#include "numeric.h"
#include <imgui.h>

void NumericPin::renderContent() {

    ImGui::PushItemWidth(100);
    if (ImGui::InputFloat("", &value))
        outputData = std::to_string(value);

}