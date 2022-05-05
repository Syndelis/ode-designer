/* -----------------------------------------------------------------------------
    INCLUDES & GLOBALS
----------------------------------------------------------------------------- */

#include <iostream>
#include <string>
#include <vector>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui_node_editor.h>
#include "style.h"
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include "../nodes/population.h"

namespace Editor = ax::NodeEditor;

/* -----------------------------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------------------------- */

auto testnode = new Population();

void draw(Editor::EditorContext *editorContext) {

    ImGui::Begin("simple node editor");
    Editor::SetCurrentEditor(editorContext);
    Editor::Begin("My Editor", ImVec2(0.0, 0.0f));

    testnode->draw();
    
    Editor::End();
    Editor::SetCurrentEditor(nullptr);
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
    auto io = ImGui::GetIO();
    setEelStyle(ImGui::GetStyle());

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // Node Editor Setup -----------------------------------
    static auto editorContext = Editor::CreateEditor(nullptr);

    // Main Loop -------------------------------------------
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Draw Start ---------------------------------------

        draw(editorContext);

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
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;

}