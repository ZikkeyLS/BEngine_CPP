#include "BEngine.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <ScriptEngine.h>

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


    glClearColor(0, 1, 0, 1);

    bool active = true;

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Really cool");
        ImGui::Text("Hello, world %d", 123);
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
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
