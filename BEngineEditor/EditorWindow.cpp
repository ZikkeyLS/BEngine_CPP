#include "EditorWindow.h"
#include "BEngine.h"
#include "FrameBuffer.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <chrono>

namespace BEngineEditor 
{

    void EditorWindow::OnInitialize()
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
#ifdef NDEBUG
        io.IniFilename = "BEngineEditorGUI.ini";
#endif
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 460");
        sceneBuffer = new FrameBuffer(640, 480);
    }

    int time = 0;
    int framesPerSecond = 0;
    std::chrono::steady_clock::time_point previousFrame;

    void EditorWindow::OnStart()
    {
        time = 0;
        framesPerSecond = 0;
        previousFrame = std::chrono::high_resolution_clock::now();
    }

    void EditorWindow::OnUpdate()
    {
        glClearColor(0, 1, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGuiID dockspaceID = ImGui::GetID("BEngineDockspace");
        ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_None;
        ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), dockspaceFlags);
        ImGui::DockSpaceOverViewport();

        ImGui::Begin("Scene");
        {
            float width = ImGui::GetContentRegionAvail().x;
            float height = ImGui::GetContentRegionAvail().y;

            ImGui::Image(
                (ImTextureID)sceneBuffer->getFrameTexture(),
                ImGui::GetContentRegionAvail(),
                ImVec2(0, 1),
                ImVec2(1, 0)
            );

        }
        ImGui::End();

        ImGui::Begin("Game");
        {
            float width = ImGui::GetContentRegionAvail().x;
            float height = ImGui::GetContentRegionAvail().y;

            ImGui::Image(
                (ImTextureID)sceneBuffer->getFrameTexture(),
                ImGui::GetContentRegionAvail(),
                ImVec2(0, 1),
                ImVec2(1, 0)
            );
        }
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        sceneBuffer->Bind();
        glClearColor(1, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        sceneBuffer->Unbind();
    }

    void EditorWindow::OnDestroy() 
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        delete sceneBuffer;
    }
}
