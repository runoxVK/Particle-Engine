#include "SDL3/SDL_events.h"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_keyboard.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_mouse.h"
#include "SDL3/SDL_video.h"
#include <SDL3/SDL.h>
//https://wiki.libsdl.org/SDL3/FrontPage
#include <iostream>



int main(){

    // Initializing a system (SDL_INIT_AUDIO later too)
    if(!SDL_Init(SDL_INIT_VIDEO)){
        SDL_Log("Failed!");
        return -1;
    }

    // Creating a pointer to the window and creating a window
    SDL_Window* window = SDL_CreateWindow("Falling Sand", 320, 240, SDL_WINDOW_RESIZABLE);
    if (!window) {
        SDL_Log("Window failed: %s", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    // Initializing event variable
    SDL_Event event;
    const bool* keystate = SDL_GetKeyboardState(nullptr);

    // SDL_WarpMouseInWindow(SDL_Window *window, float x, float y) --> forces Mouse position into a certain place
    bool isRunning = true;

    while(isRunning){

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



        //Game here
    }

    // Cleans up initialized system
    SDL_DestroyWindow(window);
    SDL_Quit();


    return 0;
}
