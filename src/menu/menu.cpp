#include "menu.hpp"
#include "src/plot/plot.hpp"

void resetContextMenuState() {
    currentFactory = nullptr;
    nodeName[0]    = '\0';
}

void openContextMenu() {
    isContextMenuOpen = true;
    resetContextMenuState();
}

void renderContextMenu() {

    if (ImGui::BeginPopupContextItem("Create Node")) {

        if (currentFactory) {
            ImGui::Text("New %s", currentNodeName.c_str());
            if (ImGui::InputText(
                    "##nodename", nodeName, MAX_NODE_NAME_LENGTH,
                    ImGuiInputTextFlags_EnterReturnsTrue
                )
                || ImGui::Button("Create"))
            {
                (*currentFactory)(nodeName);
                isContextMenuOpen = false;
                resetContextMenuState();
                ImGui::CloseCurrentPopup();
            }
        }

        else
            for (auto &[nodeName, nodeFactory] : nodeFactories)
                if (ImGui::Selectable(nodeName.c_str())) {
                    currentFactory    = &nodeFactory;
                    currentNodeName   = nodeName;
                    isContextMenuOpen = true;
                }
        ImGui::EndPopup();
    }

    /*else if (simulate){
    }*/
    if (isContextMenuOpen) {

        ImGui::OpenPopup("Create Node");
    }
}

void menuOpenfile() {
    // File open
    auto f = pfd::open_file(
        "Choose file", "~", { "Files (.json)", "*.json *", "All Files", "*" },
        pfd::opt::none
    );
}

void menuSavefile() {
    // File save
    auto f = pfd::save_file(
        "Choose file to save",
        pfd::path::home() + pfd::path::separator() + "readme.txt",
        { "Text Files (.txt .text)", "*.txt *.text" }, pfd::opt::force_overwrite
    );
}

void menuBarFile() {

    if (ImGui::MenuItem("New")) {
    }

    if (ImGui::MenuItem("Open", "Ctrl+O")) {

        menuOpenfile();
    }
    if (ImGui::MenuItem("Plot CSV file")) {

        auto f = pfd::open_file(
            "Choose file", "~", { "Files (.csv)", "*.csv *", "All Files", "*" },
            pfd::opt::none
        );
        if (!f.result().empty()) {

            plot_data = readCSV_MultidimensionalArray(f.result()[0]);

            std::cout << "deu bom" << std::endl;
            std::cout << plot_data.size() << std::endl;
            open_plot = true;
        }
    }

    if (ImGui::MenuItem("Save", "Ctrl+S")) {
        menuSavefile();
    }
    if (ImGui::MenuItem("Save As..")) {
        menuSavefile();
    }
}

void menuBarEdit() {

    if (ImGui::BeginMenu("Generate Code")) {

        static float f;

        ImGui::InputFloat("Start_time", &f);
        ImGui::InputFloat("Dt", &f);
        ImGui::InputFloat("tfinal", &f);

        if (ImGui::BeginMenu("Export_Codes")) {
            if (ImGui::MenuItem("Python")) {
            }
            if (ImGui::MenuItem("C++")) {
            }
            if (ImGui::MenuItem("C")) {
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Simulate Model")) {

        static float f;

        ImGui::InputFloat("Start_time", &f);
        ImGui::InputFloat("Dt", &f);
        ImGui::InputFloat("tfinal", &f);
        ImGui::Button("Simulate");

        ImGui::EndMenu();
    }
}