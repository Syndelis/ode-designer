#include "sign.h"
#include <imgui.h>

static const char *options[] = {"+", "-"};

const char *SignPin::getSign() {
    return options[selected];
}

void SignPin::renderContent() {

    ImGui::PushItemWidth(20);

    if (
        ImGui::BeginCombo(
            "##signcombo", options[selected],
            ImGuiComboFlags_NoArrowButton)
    ) {
        for (int n = 0; n < IM_ARRAYSIZE(options); n++) {
            bool is_selected = (selected == n);
            if (ImGui::Selectable(options[n], is_selected))
                selected = n;

            if (is_selected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }

    ImGui::SameLine();

    EchoPin::renderContent();

}