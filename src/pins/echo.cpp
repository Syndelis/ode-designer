#include "echo.h"
#include <imgui.h>
void EchoPin::renderContent() {

    ImGui::PushItemWidth(100);
    ImGui::Text("%s", inputData->c_str());

}