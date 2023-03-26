/* -----------------------------------------------------------------------------
    INCLUDES & GLOBALS
----------------------------------------------------------------------------- */

// clang-format off
#include <imgui.h>
#include <imnodes.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
// clang-format on

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "style.hpp"
#include "../nodes/population.hpp"
#include "../nodes/variable.hpp"
#include "../nodes/combinator.hpp"
#include "../pins/pin.hpp"
#include "../nodes/node.hpp"

static bool isContextMenuOpen = false;

/* -----------------------------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------------------------- */

void minimapHoverCallback(int nodeId, void *userData) {

    ImGui::SetTooltip("%s", (Node::allNodes[nodeId])->name.c_str());

}

// Context Menu --------------------------------------------

using NodeFactory = Node *(*)(char *);

#define NODE_ENTRY(name) { #name, createNode<name>}
const int MAX_NODE_NAME_LENGTH = 50;

template <typename T>
Node *createNode(char *name) {
    return new T(name);  // NOLINT(cppcoreguidelines-owning-memory)
}

static std::map<std::string, NodeFactory> nodeFactories = {
    NODE_ENTRY(Population),
    NODE_ENTRY(Variable),
    NODE_ENTRY(Combinator),
};

static NodeFactory *currentFactory = nullptr;
static std::string currentNodeName = "";
static char nodeName[MAX_NODE_NAME_LENGTH] = "";

void resetContextMenuState() {
    currentFactory = nullptr;
    nodeName[0] = '\0';
}

void openContextMenu() {
    isContextMenuOpen = true;
    resetContextMenuState();
}

void renderContextMenu() {
    if (ImGui::BeginPopupContextItem("Create Node")) {
        
        if (currentFactory) {
            ImGui::Text("New %s", currentNodeName.c_str());
            if (
                ImGui::InputText(
                    "##nodename", nodeName, MAX_NODE_NAME_LENGTH,
                    ImGuiInputTextFlags_EnterReturnsTrue
                ) || ImGui::Button("Create")
            ) {
                (*currentFactory)(nodeName);
                isContextMenuOpen = false;
                resetContextMenuState();
                ImGui::CloseCurrentPopup();
            }
        }

        else
            for (auto &[nodeName, nodeFactory] : nodeFactories)
                if (ImGui::Selectable(nodeName.c_str())) {
                    currentFactory = &nodeFactory;
                    currentNodeName = nodeName;
                    isContextMenuOpen = true;
                }

        ImGui::EndPopup();
    }

    if (isContextMenuOpen)
        ImGui::OpenPopup("Create Node");
}

void process() {

    // Rendering -------------------------------------------

    ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(40, 40, 50, 200));
    ImGui::Begin("simple node editor");

    renderContextMenu();

    ImNodes::BeginNodeEditor();

    if (ImNodes::IsEditorHovered()) {
        if (!isContextMenuOpen && ImGui::IsMouseClicked(ImGuiMouseButton_Right))
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

    ImNodes::MiniMap(.2f, ImNodesMiniMapLocation_BottomRight, minimapHoverCallback, nullptr);

    float mouseWheel = ImGui::GetIO().MouseWheel;

    if (mouseWheel != 0.0f && ImNodes::IsEditorHovered())
        ImNodes::EditorContextSmoothZoom(
            ImNodes::EditorContextGetZoom() + mouseWheel * .5f,
            ImGui::GetMousePos()
        );

    ImNodes::EndNodeEditor();
    ImGui::End();

    ImGui::PopStyleColor();

    // Link Processing --------------------------------------

    int srcId, dstId;
    if (ImNodes::IsLinkCreated(&srcId, &dstId))
        Pin::linkTogether(srcId, dstId);

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

    // clang-format off
    new Population("A");  // NOLINT(clang-diagnostic-writable-strings, clang-analyzer-cplusplus.NewDeleteLeaks)
    new Population("B");  // NOLINT(clang-diagnostic-writable-strings, clang-analyzer-cplusplus.NewDeleteLeaks)
    new Population("C");  // NOLINT(clang-diagnostic-writable-strings, clang-analyzer-cplusplus.NewDeleteLeaks)

    new Combinator("ab");  // NOLINT(clang-diagnostic-writable-strings, clang-analyzer-cplusplus.NewDeleteLeaks)
    new Combinator("abc");  // NOLINT(clang-diagnostic-writable-strings, clang-analyzer-cplusplus.NewDeleteLeaks)
    // clang-format on

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