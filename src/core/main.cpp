/* -----------------------------------------------------------------------------
    INCLUDES & GLOBALS
----------------------------------------------------------------------------- */

// clang-format off
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui_internal.h>
#include <imgui.h>
#include <imnodes.h>
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

#include "../nodes/combinator.hpp"
#include "../nodes/node.hpp"
#include "../nodes/population.hpp"
<<<<<<< Updated upstream
=======
#include "../nodes/variable.hpp"
#include "../portable-file-dialogs/portable-file-dialogs.h"

>>>>>>> Stashed changes
#include "../pins/pin.hpp"
#include "../portable-file-dialogs/portable-file-dialogs.h"

static bool isContextMenuOpen = false;

/* -----------------------------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------------------------- */
//retirar essas funções daqui, criar um header
static void MenuFile();
static void MenuEdit();

void minimapHoverCallback(int nodeId, void *userData) {

    ImGui::SetTooltip("%s", (Node::allNodes[nodeId])->name.c_str());
}

void serialize() {

    Model model = ModelBuilder<InitialState>()
        .setMetadata(0, 0, 0);

    for (auto &[id, node] : Node::allNodes)
        model = node->serializeInto(model);
    
    //Pegar esse serialize em vez de mostrar no terminal, abrir e salvar em um arquivo.
    std::cout << model.toJson() << std::endl;
}

// Context Menu --------------------------------------------

using NodeFactory = Node *(*)(char *);

#define NODE_ENTRY(name)          \
    {                             \
#name, createNode < name> \
    }
const int MAX_NODE_NAME_LENGTH = 50;

template <typename T>
Node *createNode(char *name) {
    return new T(name); // NOLINT(cppcoreguidelines-owning-memory)
}

static std::map<std::string, NodeFactory> nodeFactories = {
    NODE_ENTRY(Population),
    NODE_ENTRY(Combinator),
};

static NodeFactory *currentFactory         = nullptr;
static std::string currentNodeName         = "";
static char nodeName[MAX_NODE_NAME_LENGTH] = "";

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

    if (isContextMenuOpen)
        ImGui::OpenPopup("Create Node");
}
void test_open_file(){
    // File open
    auto f = pfd::open_file("Choose file","~",
                            { "Files (.json)", "*.json *",
                              "All Files", "*"},
                            pfd::opt::none);
}
void test_save_file(){
    // File save
    auto f = pfd::save_file("Choose file to save",
                            pfd::path::home() + pfd::path::separator() + "readme.txt",
                            { "Text Files (.txt .text)", "*.txt *.text" },
                            pfd::opt::force_overwrite);
}
<<<<<<< Updated upstream

=======
>>>>>>> Stashed changes
void process() {

    // Rendering -------------------------------------------

    ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(40, 40, 50, 200));
    ImGui::Begin("simple node editor");

    if(ImGui::IsKeyPressed(ImGuiMod_Ctrl) | ImGui::IsKeyPressed(ImGuiKey_O)){

        test_open_file();
    }

<<<<<<< Updated upstream
    if(ImGui::IsKeyPressed(ImGuiMod_Ctrl) | ImGui::IsKeyPressed(ImGuiKey_O)){

        test_open_file();
    }

=======
>>>>>>> Stashed changes
    if(ImGui::BeginMainMenuBar()){
        if(ImGui::BeginMenu("File")){
            MenuFile();
            ImGui::EndMenu();
        }
        if(ImGui::BeginMenu("Edit")){
            MenuEdit();
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    if (ImGui::Shortcut(ImGuiMod_Ctrl | ImGuiKey_S)) {
        std::cout << "Ctrl S apertado!" << std::endl;
        serialize();
    }

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

    ImNodes::MiniMap(
        .2f, ImNodesMiniMapLocation_BottomRight, minimapHoverCallback, nullptr
    );

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
    if (ImNodes::IsLinkHovered(&linkId) && ImGui::IsMouseClicked(0))
        Pin::unlink(linkId);
}

/* -----------------------------------------------------------------------------
    MAIN CODE
----------------------------------------------------------------------------- */
static void MenuFile(){
    
    if (ImGui::MenuItem("New")){}
<<<<<<< Updated upstream
    
    if (ImGui::MenuItem("Open", "Ctrl+O")){

       test_open_file();
        
    }
    if (ImGui::MenuItem("Save", "Ctrl+S")) {
        test_save_file();
    }
    if (ImGui::MenuItem("Save As..")) {
        test_save_file();
    }
=======
>>>>>>> Stashed changes
    if (ImGui::MenuItem("Open", "Ctrl+O")){

       test_open_file();
        
    }
    if (ImGui::MenuItem("Save", "Ctrl+S")) {
        test_save_file();
    }
    if (ImGui::MenuItem("Save As..")) {
        test_save_file();
    }
}

static void MenuEdit(){

    if(ImGui::BeginMenu("Generate Code")){

        static float f;
        ImGui::InputFloat("Start_time", &f);
        ImGui::InputFloat("Dt", &f);
        ImGui::InputFloat("tfinal", &f);
        
        if(ImGui::BeginMenu("Export_Codes")){
            if(ImGui::MenuItem("Python")){}
            if(ImGui::MenuItem("C++")){}
            if(ImGui::MenuItem("C")){}
            ImGui::EndMenu();

        }
        ImGui::EndMenu();
    }
    if(ImGui::BeginMenu("Simulate Model")){

        static float f;
        ImGui::InputFloat("Start_time", &f);
        ImGui::InputFloat("Dt", &f);
        ImGui::InputFloat("tfinal", &f);
        ImGui::Button("Simulate");

        ImGui::EndMenu();
    }
}

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

    // Main Loop -------------------------------------------
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Draw Start ---------------------------------------

        ImGui::ShowDemoWindow();
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