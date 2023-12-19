/* -----------------------------------------------------------------------------
    INCLUDES & GLOBALS
----------------------------------------------------------------------------- */

// clang-format off
#include <cstdio>
#include <limits>
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
#include <sstream>
#include <vector>
#define ODEIR_DEFINITION
#include <odeir.hpp>
#undef ODEIR_DEFINITION

#include "../menu/menu.hpp"
#include "../plot/plot.hpp"
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

void plotGraphs(){
    int tabToBeRemoved = -1;
    for (std::size_t n = 0; n < plot_layout.active_tabs.size(); n++){
        bool open = true;
        char name[16];
        snprintf(name, IM_ARRAYSIZE(name), "Tab_%d", plot_layout.active_tabs[n]);
        if (ImGui::BeginTabItem(name, &(open))){
            int base_id = (plot_layout.active_tabs[n])*(plot_layout.rows*plot_layout.cols);
            if (plots.size() == 1){
                if (plot_all)
                    plotAll(plots[0]);
                else 
                    plot(plots[0], plot_layout, base_id);
            }
            else if (plots.size() > 1) {
                plotDifferentScenarios(plots,plot_layout, base_id);
            }                
            ImGui::EndTabItem();
        }
        if (!open) {
            tabToBeRemoved = n;
        }
    }

    if (tabToBeRemoved != -1){
        plot_layout.active_tabs.erase(plot_layout.active_tabs.Data + tabToBeRemoved);                        
    }
}


void process() {

    // Rendering -------------------------------------------------------------

    ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(40, 40, 50, 200));
    ImGui::Begin("Modeling and Simulation Software");

    if (ImGui::Shortcut(ImGuiMod_Ctrl | ImGuiKey_O)) {

        menuOpenfile();
    }

    if (ImGui::BeginMainMenuBar()) {

        if (ImGui::BeginMenu("File")) {
            menuBarFile();
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Simulation")) {
            menuBarEdit();
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }

    if (ImGui::Shortcut(ImGuiMod_Ctrl | ImGuiKey_S)) {

        serialize();
    }

    static ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_AutoSelectNewTabs | ImGuiTabBarFlags_Reorderable | ImGuiTabBarFlags_FittingPolicyResizeDown 
        | ImGuiTabBarFlags_TabListPopupButton;
    tab_bar_flags &= ~(ImGuiTabBarFlags_FittingPolicyMask_ ^ ImGuiTabBarFlags_FittingPolicyResizeDown);
    tab_bar_flags &= ~(ImGuiTabBarFlags_FittingPolicyMask_ ^ ImGuiTabBarFlags_FittingPolicyScroll);

    //ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_TabListPopupButton;
    if (ImGui::BeginTabBar("Tab bar", tab_bar_flags)) {

        if (ImGui::BeginTabItem("Model")){

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

        //test timer
        if (flag_simulation && !plot_all){
            if (ode != nullptr && ode->t <= ode->tf){
                ode->advanceStep();                 
                for (int i = 0; i < plots[0].num_of_cols; i++)
                    plots[0].data[i].push_back(ode->u[i]);
                
                plots[0].num_of_lines++;
                ode->save();
                plotGraphs();
                ode->t += ode->dt;
                if (ode->t > ode->tf) {
                    flag_simulation = false;
                    ode->finishSimulation();
                    ode = nullptr;
                }
            }
        }
        else {
            plotGraphs();
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

    auto window = glfwCreateWindow(1280, 720, "Hello World", NULL, NULL);

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
    ImPlot::CreateContext();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // Application Setup -----------------------------------


    // Main Loop -------------------------------------------
    while (!glfwWindowShouldClose(window)) {

        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Draw Start ---------------------------------------

        ImGuiID dock_id
            = ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), 0);
        ImGui::SetNextWindowDockID(dock_id, true);
        ImGui::ShowDemoWindow();
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
    ImPlot::DestroyContext();
    ImNodes::DestroyContext();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}