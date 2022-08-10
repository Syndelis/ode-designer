#include "echo.h"
#include <imgui.h>

#define FMT_HEADER_ONLY
#include <fmt/std.h>

void EchoPin::renderContent() {

    ImGui::PushItemWidth(100);

    if (data.index())
        ImGui::TextUnformatted(fmt::format("{}", data).c_str());

    else ImGui::Text("Unattributed");

}