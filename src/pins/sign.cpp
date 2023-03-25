#include "sign.hpp"
#include <imgui.h>
#include "../common/imgui_combo.hpp"

static const char *options[] = {"+", "-"};

const char *SignPin::getSign() {
    return options[selected];  // NOLINT(cppcoreguidelines-pro-bounds-constant-array-index)
}

void SignPin::renderContent() {

    ImGui::PushItemWidth(20);

    IMGUI_COMBO("##signcombo", options, selected, ImGuiComboFlags_NoArrowButton);  // NOLINT(cppcoreguidelines-pro-bounds-constant-array-index)

    ImGui::SameLine();

    EchoPin::renderContent();

}