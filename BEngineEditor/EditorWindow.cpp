#include "EditorWindow.h"
#include "BEngine.h"
#include "FrameBuffer.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <chrono>

namespace BEngineEditor 
{
    unsigned int shaderProgram;
    unsigned int vertexShader;
    unsigned int fragmentShader;

    unsigned int VBO;
    unsigned int VAO;

    float vertices[] = {
         -0.5f, -0.5f, 0.0f,
          0.5f, -0.5f, 0.0f,
          0.0f,  0.5f, 0.0f
    };

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

        int width, height;
        glfwGetWindowSize(window, &width, &height);

        #pragma region DemoTriangleSetup

        const char* vertexShaderSource = "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "void main()\n"
            "{\n"
            "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
            "}\0";


        const char* fragmentShaderSource = "#version 330 core\n"
            "out vec4 FragColor;\n"
            "void main()\n"
            "{\n"
            "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
            "}\0";

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);

        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);

        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
#pragma endregion

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

    void EditorWindow::OnUpdate()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        sceneBuffer->Bind();
        glClearColor(1, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        sceneBuffer->Unbind();

        gameBuffer->Bind();
        glClearColor(0, 0, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        gameBuffer->Unbind();

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

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void EditorWindow::OnDestroy() 
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        glDeleteProgram(shaderProgram);

        delete sceneBuffer;
    }
}
