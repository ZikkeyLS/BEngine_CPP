#include "EditorWindow.h"
#include "BEngine.h"
#include "FrameBuffer.h"
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <chrono>

namespace BEngineEditor 
{
    void EditorWindow::OnInitialize()
    {
        BEngine::ScriptEngine::Initialize();

        context = SDL_GL_CreateContext(window);

        if (!gladLoadGL())
        {
            BE_ERROR("Can't load GLAD!");
            return;
        }

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
#ifdef NDEBUG
        io.IniFilename = "BEngineEditorGUI.ini";
#endif
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        ImGui::StyleColorsDark();
        ImGui_ImplSDL2_InitForOpenGL(window, context);
        ImGui_ImplOpenGL3_Init("#version 460");

        int width, height;
        SDL_GetWindowSize(window, &width, &height);

        sceneBuffer = new FrameBuffer(width, height);
        gameBuffer = new FrameBuffer(width, height);
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

    void EditorWindow::OnWindowEvent(SDL_Event* windowEvent)
    {
        ImGui_ImplSDL2_ProcessEvent(windowEvent);
    }

    void EditorWindow::OnUpdate()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        OnRender();
        OnGUI();

        SDL_GL_SwapWindow(window);
    }

    void EditorWindow::OnDestroy() 
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();

        delete sceneBuffer;
        delete gameBuffer;

        SDL_GL_DeleteContext(context);
    }

    SDL_Window* EditorWindow::CreateWindow(const std::string& name, const WindowSize& size)
    {
        return SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, size.x, size.y, 
            SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED | SDL_WINDOW_OPENGL);
    }

    void EditorWindow::OnRender()
    {
        sceneBuffer->Bind();
        glClearColor(1, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        sceneBuffer->Unbind();

        gameBuffer->Bind();
        glClearColor(0, 0, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        gameBuffer->Unbind();
    }

    void EditorWindow::OnGUI()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        OnProjectGUI();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void EditorWindow::OnLoaderGUI()
    {

    }

    void EditorWindow::OnProjectGUI()
    {
        ImGuiID dockspaceID = ImGui::GetID("BEngineDockspace");
        ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_None;
        ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), dockspaceFlags);
        ImGui::DockSpaceOverViewport();

        ImGui::Begin("Scene");
        {
            float width = ImGui::GetContentRegionAvail().x;
            float height = ImGui::GetContentRegionAvail().y;

            // Think about rescaling framebuffers.
            sceneBuffer->RescaleFrameBuffer(width, height);

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

            // Think about rescaling framebuffers.
            gameBuffer->RescaleFrameBuffer(width, height);

            ImGui::Image(
                (ImTextureID)gameBuffer->getFrameTexture(),
                ImGui::GetContentRegionAvail(),
                ImVec2(0, 1),
                ImVec2(1, 0)
            );
        }
        ImGui::End();
    }
}
