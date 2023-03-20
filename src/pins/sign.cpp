#include "sign.hpp"
#include <imgui.h>
#include "../common/imgui_combo.hpp"

static const char *options[] = {"+", "-"};

const char *SignPin::getSign() {
    return options[selected];
}

void SignPin::renderContent() {

    ImGui::PushItemWidth(20);

    IMGUI_COMBO("##signcombo", options, selected, ImGuiComboFlags_NoArrowButton);

    ImGui::SameLine();

    EchoPin::renderContent();

}