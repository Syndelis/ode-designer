#include "numeric.h"
#include <imgui.h>

void NumericPin::renderContent() {

    ImGui::PushItemWidth(100);
    ImGui::InputFloat("", &value);

}