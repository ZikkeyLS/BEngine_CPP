#pragma once
#include "Window.h"
#include "BEngine.h"

namespace BEngine 
{
    Window::Window()
    {

    }

    int Window::Initialize(WindowSize size, std::string name)
	{
        if (!glfwInit())
            return -1;

        this->size = size;

        window = glfwCreateWindow(size.x, size.y, name.c_str(), NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            return -1;
        }

        glfwMakeContextCurrent(window);

        if (!gladLoadGL()) {
            BE_ERROR("Can't load GLAD!");
            return -1;
        }

        BE_INFO("OpenGL {}.{}", GLVersion.major, GLVersion.minor);

        OnInitialize();

        return 0;
	}

    void Window::Run()
    {
        OnStart();
        
        while (!glfwWindowShouldClose(window))
        {
            OnUpdate();

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        OnDestroy();

        glfwTerminate();
    }
}
