#pragma once
#include "Window.h"
#include "BEngine.h"

namespace BEngine 
{
    Window::Window()
    {

    }

    int Window::Initialize(const std::string& name, const WindowSize& size)
	{
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0) 
        {
            BE_ERROR("SDL_Init Error: {}", SDL_GetError());
            return 1;
        }

        window = CreateWindow("BEngine", size);
        if (window == nullptr)
        {
            BE_ERROR("SDL_CreateWindow Error: {}", SDL_GetError());
            return 1;
        }

        OnInitialize();

        return 0;
	}

    void Window::Run()
    {
        OnStart();

        SDL_Event windowEvent;
        bool running = true;
        while (running)
        {
            while (SDL_PollEvent(&windowEvent) != 0)
            {
                OnWindowEvent(&windowEvent);

                if (windowEvent.type == SDL_QUIT)
                {
                    running = false;
                }
            }

            OnUpdate();
        }

        OnDestroy();

        SDL_DestroyWindow(window);
        window = nullptr;
        SDL_Quit();
    }
}
