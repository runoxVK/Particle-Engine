#include "SDL3/SDL_events.h"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_keyboard.h"
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

    bool isRunning = true;

    while(isRunning){

        //SDL_PollEvent(&event) returns 1 if any event is taking place
        // Event Handling Loop:
        while(SDL_PollEvent(&event)){
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
        }



        //Game here
    }

    // Cleans up initialized system
    SDL_DestroyWindow(window);
    SDL_Quit();


    return 0;
}
