#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <GL/gl.h>

typedef int32_t i32;
typedef uint32_t u32;
typedef int32_t b32;

#define WinWidth 800
#define WinHeight 600

int main(int ArgCount, char** Args)
{
    if (SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO) < 0) {
        printf("SDL Init Error: %s", SDL_GetError());
        return 0;
    }

    //set opengl attributes, supposed to happen before window creation
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); //OpenGL core profile
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3); //OpenGL 3+
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2); //OpenGL 3.2

    u32 WindowFlags = SDL_WINDOW_OPENGL;
    SDL_Window* Window = SDL_CreateWindow("CMP5334 FPS Camera", 100, 100, WinWidth, WinHeight, WindowFlags);
    assert(Window);
    SDL_GLContext Context = SDL_GL_CreateContext(Window);

    //initialize OpenGL stuff
    SDL_GLContext openglContext = SDL_GL_CreateContext(Window);
    printf("glGetString (GL_VERSION) returns %s\n", glGetString(GL_VERSION));

    b32 Running = 1;
    b32 FullScreen = 0;
    while (Running)
    {
        SDL_Event Event;
        while (SDL_PollEvent(&Event))
        {
            if (Event.type == SDL_KEYDOWN)
            {
                switch (Event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    Running = 0;
                    break;
                case 'f':
                    FullScreen = !FullScreen;
                    if (FullScreen)
                    {
                        SDL_SetWindowFullscreen(Window, WindowFlags | SDL_WINDOW_FULLSCREEN_DESKTOP);
                    }
                    else
                    {
                        SDL_SetWindowFullscreen(Window, WindowFlags);
                    }
                    break;
                default:
                    break;
                }
            }
            else if (Event.type == SDL_QUIT)
            {
                Running = 0;
            }
        }

        glViewport(0, 0, WinWidth, WinHeight);
        glClearColor(1.f, 0.f, 1.f, 0.f);
        glClear(GL_COLOR_BUFFER_BIT);

        SDL_GL_SwapWindow(Window);
    }
    SDL_GL_DeleteContext(openglContext);
    SDL_DestroyWindow(Window);
    SDL_Quit();
    return 0;
}