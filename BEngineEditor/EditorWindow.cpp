#include "EditorWindow.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace BEngineEditor 
{
    void EditorWindow::OnInitialize()
    {
        IMGUI_CHECKVERSION();
        uiContext = ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 460");
    }

    void EditorWindow::OnStart()
    {
        glClearColor(0, 1, 0, 1);
    }

    void EditorWindow::OnDestroy() 
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
}
