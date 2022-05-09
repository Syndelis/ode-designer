/* -----------------------------------------------------------------------------
    INCLUDES & GLOBALS
----------------------------------------------------------------------------- */

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <imgui.h>
#include <imnodes.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include "style.h"
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include "../nodes/population.h"
#include "../nodes/variable.h"
#include "../pins/base.h"
#include "../nodes/base.h"

/* -----------------------------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------------------------- */

void minimapHoverCallback(int nodeId, void *userData) {

    ImGui::SetTooltip("%s", (Node::allNodes[nodeId])->name.c_str());

}

void process() {

    // Rendering -------------------------------------------

    ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(40, 40, 50, 200));
    ImGui::Begin("simple node editor");
    ImNodes::BeginNodeEditor();

    // Node Handling ---------------------------------------

    for (auto &[id, node] : Node::allNodes)
        node->process();

    // Link Drawing ----------------------------------------

    for (auto &[srcId, srcPin] : Pin::allPins)
        srcPin->renderLinks();

    ImNodes::MiniMap(.2f, ImNodesMiniMapLocation_BottomRight, minimapHoverCallback, nullptr);

    float mouseWheel = ImGui::GetIO().MouseWheel;

    if (mouseWheel && ImNodes::IsEditorHovered())
        ImNodes::EditorContextSmoothZoom(
            ImNodes::EditorContextGetZoom() + mouseWheel * .5f,
            ImGui::GetMousePos()
        );

    ImNodes::EndNodeEditor();
    ImGui::End();

    ImGui::PopStyleColor();

    // Link Processing --------------------------------------

    int srcId, dstId;
    if (ImNodes::IsLinkCreated(&srcId, &dstId)) {

        auto srcPin = Pin::allPins[srcId];
        auto dstPin = Pin::allPins[dstId];
        srcPin->link(dstPin);

    }

    int linkId;
    if (ImNodes::IsLinkHovered(&linkId)
        && ImGui::IsMouseClicked(0))
            Pin::unlink(linkId);

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
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable |\
    ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_NavEnableSetMousePos;

    auto io = ImGui::GetIO();
    auto iosevkaFont = io.Fonts->AddFontFromFileTTF("assets/fonts/Iosevka-regular.ttf", 16);
    io.FontDefault = iosevkaFont;

    setEelStyle(ImGui::GetStyle());
    ImNodes::CreateContext();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // Application Setup -----------------------------------

    auto testnode = new Population("A");
    auto testnode2 = new Population("B");
    auto testnode3 = new Variable("M₀");

    // Main Loop -------------------------------------------
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Draw Start ---------------------------------------

        ImGui::ShowDemoWindow();
        ImGuiID dock_id = ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), 0);
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