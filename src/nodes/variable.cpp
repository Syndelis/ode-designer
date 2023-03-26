#include "variable.hpp"

#include <imnodes.h>
#include <iostream>

#include "../pins/numeric.hpp"

Variable::Variable(char *name) : Node(name) { pushOutput<NumericPin>(); }

void Variable::renderContent() {
    if (ImGui::Checkbox("Range?", &is_range)) {

        range_min = 0;
        range_max = 0;
    }

    ImGui::BeginDisabled(!is_range);
    ImGui::DragFloat("##range_min", &range_min, 2.5f, -FLT_MAX, 0, "%+.2f");
    ImGui::SameLine();
    ImGui::DragFloat("##range_max", &range_max, 2.5f, 0, FLT_MAX, "%+.2f");
    ImGui::EndDisabled();
}