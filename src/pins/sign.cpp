#include "sign.hpp"

#include <imgui.h>

#include "../common/imgui_combo.hpp"

static const char *options[] = { "+", "-" };

const char *SignPin::getSign() {
    /*
     * SAFETY: `selected` is populated solely via ImGui using `options` as the
     * source of truth. Therefore, it is guaranteed to be within its bounds.
     */
    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-constant-array-index)
    return options[selected];
}

void SignPin::renderContent() {

    ImGui::PushItemWidth(20);

    // SAFETY: Read previous comment.
    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-constant-array-index)
    IMGUI_COMBO(
        "##signcombo", options, selected, ImGuiComboFlags_NoArrowButton
    );

    ImGui::SameLine();

    EchoPin::renderContent();
}