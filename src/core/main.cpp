/* -----------------------------------------------------------------------------
    INCLUDES & GLOBALS
----------------------------------------------------------------------------- */

// clang-format off
#include <cstdio>
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui_internal.h>
#include <imgui.h>
#include <imnodes.h>
#include <implot.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
// clang-format on

#include "style.hpp"

#include <iostream>
#include <map>
#include <string>
#include <vector>
#define ODEIR_DEFINITION
#include <odeir.hpp>
#undef ODEIR_DEFINITION

#include "../menu/menu.hpp"

#include "../pins/pin.hpp"

/* -----------------------------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------------------------- */

void minimapHoverCallback(int nodeId, void *userData) {

    ImGui::SetTooltip("%s", (Node::allNodes[nodeId])->name.c_str());
}

void serialize() {

    Model model = ModelBuilder<InitialState>().setMetadata(0, 0, 0);

    for (auto &[id, node] : Node::allNodes)
        model = node->serializeInto(model);

    // Pegar esse serialize em vez de mostrar no terminal, abrir e salvar em um
    // arquivo.
    std::cout << model.toJson() << std::endl;
}

// Context Menu --------------------------------------------

void process() {

    // Rendering -------------------------------------------------------------

    ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(40, 40, 50, 200));
    ImGui::Begin("simple node editor");

    if (ImGui::Shortcut(ImGuiMod_Ctrl | ImGuiKey_O)) {

        menuOpenfile();
    }

    if (ImGui::BeginMainMenuBar()) {

        if (ImGui::BeginMenu("File")) {
            menuBarFile();
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Edit")) {
            menuBarEdit();
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }

    if (ImGui::Shortcut(ImGuiMod_Ctrl | ImGuiKey_S)) {

        std::cout << "Ctrl S apertado!" << std::endl;

        serialize();
    }

    static bool teste = true;

    ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_TabListPopupButton;
    if (ImGui::BeginTabBar("Teste", tab_bar_flags)) {

        if (ImGui::BeginTabItem("Model", &teste)){

            renderContextMenu();
            
            ImNodes::BeginNodeEditor();

            if (ImNodes::IsEditorHovered()) {
                if (!isContextMenuOpen
                    && ImGui::IsMouseClicked(ImGuiMouseButton_Right))
                    openContextMenu();
            }
            else
                isContextMenuOpen = false;

            // Node Handling ---------------------------------------

            for (auto &[id, node] : Node::allNodes)
                node->process();

            // Link Drawing ----------------------------------------

            for (auto &[srcId, srcPin] : Pin::allPins)
                srcPin->renderLinks();

            ImNodes::MiniMap(
                .2f, ImNodesMiniMapLocation_BottomRight, minimapHoverCallback,
                nullptr
            );

            float mouseWheel = ImGui::GetIO().MouseWheel;

            if (mouseWheel != 0.0f && ImNodes::IsEditorHovered())
                ImNodes::EditorContextSmoothZoom(
                    ImNodes::EditorContextGetZoom() + mouseWheel * .5f,
                    ImGui::GetMousePos()
                );

            ImNodes::EndNodeEditor();

            // Link Processing --------------------------------------

            int srcId, dstId;
            if (ImNodes::IsLinkCreated(&srcId, &dstId))
                Pin::linkTogether(srcId, dstId);

            int linkId;
            if (ImNodes::IsLinkHovered(&linkId) && ImGui::IsMouseClicked(0))
                Pin::unlink(linkId);
            
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Simulation", &teste)) {

            ImGui::Text("Simulation");
            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }
    ImGui::PopStyleColor();
    ImGui::End();
}

/* -----------------------------------------------------------------------------
    MAIN CODE
----------------------------------------------------------------------------- */
int main() {

    // GLFW Setup ------------------------------------------
    glfwInit();
    glfwWindowHint(GLFW_SAMPLES, 4); // AA

    auto window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Vsync

    // GL Setup --------------------------------------------
    glClearColor(.0, .0, .0, 1.);
    glEnable(GL_MULTISAMPLE); // AA

    // ImGui Setup -----------------------------------------
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable
                                | ImGuiConfigFlags_NavEnableKeyboard
                                | ImGuiConfigFlags_NavEnableSetMousePos;

    auto io = ImGui::GetIO();
    auto iosevkaFont
        = io.Fonts->AddFontFromFileTTF("assets/fonts/Iosevka-regular.ttf", 16);
    io.FontDefault = iosevkaFont;

    setEelStyle(ImGui::GetStyle());
    ImNodes::CreateContext();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // Application Setup -----------------------------------

    // clang-format off
    new Population("A");  // NOLINT(clang-diagnostic-writable-strings, clang-analyzer-cplusplus.NewDeleteLeaks)
    new Population("B");  // NOLINT(clang-diagnostic-writable-strings, clang-analyzer-cplusplus.NewDeleteLeaks)
    new Population("C");  // NOLINT(clang-diagnostic-writable-strings, clang-analyzer-cplusplus.NewDeleteLeaks)

    new Combinator("ab");  // NOLINT(clang-diagnostic-writable-strings, clang-analyzer-cplusplus.NewDeleteLeaks)
    new Combinator("abc");  // NOLINT(clang-diagnostic-writable-strings, clang-analyzer-cplusplus.NewDeleteLeaks)
    // clang-format on

    ImPlot::CreateContext();

    // Main Loop -------------------------------------------
    while (!glfwWindowShouldClose(window)) {

        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Draw Start ---------------------------------------

        ImGui::ShowDemoWindow();
        ImPlot::ShowDemoWindow();

        ImGuiID dock_id
            = ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), 0);
        ImGui::SetNextWindowDockID(dock_id, true);
        process();

        // Draw End -----------------------------------------

        glFlush();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup ---------------------------------------------

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImNodes::DestroyContext();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}