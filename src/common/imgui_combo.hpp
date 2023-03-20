#ifndef IMGUI_COMBO_H
#define IMGUI_COMBO_H

#define IMGUI_COMBO(name, items, selected_idx, flags) \
    if (\
        ImGui::BeginCombo(name, items[selected_idx], flags) \
    ) {\
        for (int _cur_iter = 0; _cur_iter < IM_ARRAYSIZE(items); _cur_iter++) {\
            bool is_selected = (selected_idx == _cur_iter);\
            if (ImGui::Selectable(items[_cur_iter], is_selected))\
                selected_idx = _cur_iter;\
            if (is_selected)\
                ImGui::SetItemDefaultFocus();\
        }\
        ImGui::EndCombo();\
    }

#endif