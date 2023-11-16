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

        graphics = new DX11Graphics();

        graphics->Initialize(window);

        int width, height;
        SDL_GetWindowSize(window, &width, &height);

        sceneBuffer = graphics->CreateFrameBuffer(width, height);
        gameBuffer = graphics->CreateFrameBuffer(width, height);

        GraphicsContext* main = new GraphicsContext();
        main->bufferColor = glm::vec4(0, 0, 0, 1);
        GraphicsContext* scene = new GraphicsContext();
        scene->frameBuffer = sceneBuffer;
        scene->bufferColor = glm::vec4(1, 0, 0, 1);
        GraphicsContext* game = new GraphicsContext();
        game->frameBuffer = gameBuffer;
        game->bufferColor = glm::vec4(0, 0.5, 0, 1);

        graphics->AddGraphicsContext(main);
        graphics->AddGraphicsContext(scene);
        graphics->AddGraphicsContext(game);
    }

    void EditorWindow::OnStart()
    {  
    }

    void EditorWindow::OnWindowEvent(SDL_Event* windowEvent)
    {
        ImGui_ImplSDL2_ProcessEvent(windowEvent);
    }

    void EditorWindow::OnUpdate()
    {
        graphics->Update();
        OnGUI();
        graphics->LateUpdate();
    }

    void EditorWindow::OnDestroy() 
    {
        graphics->Destroy();

        // delete sceneBuffer;
        // delete gameBuffer;
    }

    SDL_Window* EditorWindow::CreateWindowInstance(const std::string& name, const WindowSize& size)
    {
        return SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, size.x, size.y, 
            SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED | SDL_WINDOW_OPENGL);
    }

    void EditorWindow::OnGUI()
    {
        graphics->PreUI();
        OnProjectGUI();
        //OnLoaderGUI();
        graphics->PostUI();
    }

    void EditorWindow::OnLoaderGUI()
    {
        ImGuiID dockspaceID = ImGui::GetID("BEngineDockspace");
        ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_None;
        ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), dockspaceFlags);

        ImGui::Begin("Test123");
        {
            ImGui::Text("Test :(");
        }
        ImGui::End();
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
