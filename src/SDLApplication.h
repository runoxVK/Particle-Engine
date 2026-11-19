#ifndef SDLAPP_H
#define SDLAPP_H

#include "SDL3/SDL_events.h"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_keyboard.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_mouse.h"
#include "SDL3/SDL_pixels.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_stdinc.h"
#include "SDL3/SDL_surface.h"
#include "SDL3/SDL_timer.h"
#include "SDL3/SDL_video.h"
#include <SDL3/SDL.h>
//https://wiki.libsdl.org/SDL3/FrontPage
#include <iostream>
#include <string>
#include <vector>

#include "GameVars.h"



class SDLApplication{

    public:
        SDL_Window* window;
        //SDL_Surface* surface; // CPU-side pixel buffer -> Good for putting images or bitmaps on screen
        //Creating surface on window -> SDL_Surface* windowSurface = SDL_GetWindowSurface(window);
        // stores raw image data in CPU RAM with a defined pixel format

        SDL_Renderer* renderer; //Connection to the GPU -> Draws via the CPU -> Acts as an abstraction to OpenGL
        SDL_Texture* texture; // The texture is the image in GPU memory that gets drawn.

        // Constructor
        SDLApplication(){
            // Initializing a system (SDL_INIT_AUDIO later too)
            if(!SDL_Init(SDL_INIT_VIDEO)){
                SDL_Log("Failed!");
            }

            // Setting window variable (a pointer to the window) and creating a window
            window = SDL_CreateWindow("Falling Sand", 1028, 1028, SDL_WINDOW_RESIZABLE);

            renderer = SDL_CreateRenderer(window, nullptr); //Nullptr refers to what will be used to render (ex. OpenGL, Vulkan) -> We set to null so SDL can decide which to use

            if(renderer == nullptr){
                SDL_Log("Renderer Failed!");
            }
            else{
                SDL_Log("Renderer: %s", SDL_GetRendererName(renderer));
            }

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
            SDL_DestroyRenderer(renderer);
            SDL_Quit();
        }

        //SDL Tick
        void SDLTick(){
            Input();
            Update();
            Render();
        }

        // Gather Input
        void Input(){
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

        void Update(){

        }

        void drawPixel(int x, int y){
            //Sets draw color for drawing lines etc.
            SDL_SetRenderDrawColor(renderer, 0x5C, 0x40, 0x33, 0xFF);

            // Draw a point on the current rendering target at subpixel precision.
            SDL_RenderPoint(renderer, (float)x, (float)y);

        }
        void Render(){

            //Set Color for backdrop
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFD, 0xD0, 0xFF);
            SDL_RenderClear(renderer);


            // Presents Screen
            SDL_RenderPresent(renderer);



        }


};

#endif
