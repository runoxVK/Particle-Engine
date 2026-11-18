#include "SDL3/SDL_events.h"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_keyboard.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_mouse.h"
#include "SDL3/SDL_video.h"
#include <SDL3/SDL.h>
//https://wiki.libsdl.org/SDL3/FrontPage
#include <iostream>


struct SDLApplication{
    SDL_Window* window;
    bool isRunning = true;

    // Constructor
    SDLApplication(){
        SDL_Init(SDL_INIT_VIDEO);
        // Initializing a system (SDL_INIT_AUDIO later too)
        if(!SDL_Init(SDL_INIT_VIDEO)){
            SDL_Log("Failed!");
        }

        // Creating a pointer to the window and creating a window
        window = SDL_CreateWindow("Falling Sand", 320, 240, SDL_WINDOW_RESIZABLE);
        //SDL_GetWindowSize(SDL_Window *window, int *w, int *h) <-- Gets the window size if we re size it
        if (!window) {
            SDL_Log("Window failed: %s", SDL_GetError());
            SDL_Quit();
        }
    }

    // Destructor
    ~SDLApplication(){
        // Cleans up initialized system
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    //SDL Tick
    void SDLTick(){
        // Initializing event variable
        SDL_Event event;
        const bool* keystate = SDL_GetKeyboardState(nullptr);
        // SDL_WarpMouseInWindow(SDL_Window *window, float x, float y) --> forces Mouse position into a certain place

        //SDL_PollEvent(&event) returns 1 if any event is taking place
        // Event Handling Loop:
        while(SDL_PollEvent(&event)){

            //Quit
            if(event.type == SDL_EVENT_QUIT){
                isRunning = false;
            }

            //Key Clicked
            else if (event.type == SDL_EVENT_KEY_DOWN){
                SDL_Log("Key Pressed");

                // Checks if L is pressed
                if(keystate[SDL_SCANCODE_L] == true){
                    SDL_Log("L Key pressed");
                }

            }

            // Mouse Motion
            else if (event.type == SDL_EVENT_MOUSE_MOTION){
                    // There is also event.motion.xrel, event.motion.yrel
                    SDL_Log("x,y: %f, %f",event.motion.x, event.motion.y);
            }

            // Mouse Click
            else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN){
                SDL_Log("Mouse Pressed");
            }
        }
    }


    // Main Loop
    void MainLoop(){
      while(isRunning){
          SDLTick();
      }
    }


};




int main(){

    SDLApplication app;
    app.MainLoop();
    return 0;
}
