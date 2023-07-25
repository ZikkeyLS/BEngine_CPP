#include "BEngine.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <chrono>
#include "FrameBuffer.h"
#include "ScriptEngine.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

int BEngine::add(int a, int b)
{
	return a + b;
}

int BEngine::test()
{
    ScriptEngine::Initialize();

    GLFWwindow* window;
    BE_ASSERT(true);

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGL()) {
        std::cout << "Can't load GLAD!" << std::endl;
        return -1;
    }

    std::cout << "OpenGL " << GLVersion.major << "." << GLVersion.minor << std::endl;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 460");

    FrameBuffer sceneBuffer(640, 480);

    int time = 0;
    int framesPerSecond = 0;
    auto previousFrame = std::chrono::high_resolution_clock::now();

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0, 1, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Scene");
        {
            ImGui::BeginChild("GameRender");

            float width = ImGui::GetContentRegionAvail().x;
            float height = ImGui::GetContentRegionAvail().y;

            ImGui::Image(
                (ImTextureID)sceneBuffer.getFrameTexture(),
                ImGui::GetContentRegionAvail(),
                ImVec2(0, 1),
                ImVec2(1, 0)
            );
        }
        ImGui::EndChild();
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
   
        sceneBuffer.Bind();
        glClearColor(1, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        sceneBuffer.Unbind();

        glfwSwapBuffers(window);

        auto currentFrame = std::chrono::high_resolution_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(currentFrame - previousFrame);

        time += ms.count();

        if (time >= 1000) 
        {
            BE_INFO("Frames per second {}", time);
            time = 0;
            framesPerSecond = 0;
        }

        previousFrame = currentFrame;

        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}

void BEngine::untest()
{
    ScriptEngine::Shutdown();
}
