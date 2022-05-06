#include "numeric.h"
#include <imgui.h>

void NumericPin::draw() {

    ImGui::PushItemWidth(100);
    ImGui::InputDouble("", &value);

}