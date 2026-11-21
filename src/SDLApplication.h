#ifndef SDLAPP_H
#define SDLAPP_H

#include "SDL3/SDL_events.h"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_keyboard.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_mouse.h"
#include "SDL3/SDL_pixels.h"
#include "SDL3/SDL_rect.h"
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
#include "World.h"
#include "Camera.h"



class SDLApplication{

    public:
        SDL_Window* window;
        //SDL_Surface* surface; // CPU-side pixel buffer -> Good for putting images or bitmaps on screen
        //Creating surface on window -> SDL_Surface* windowSurface = SDL_GetWindowSurface(window);
        // stores raw image data in CPU RAM with a defined pixel format

        SDL_Renderer* renderer; //Connection to the GPU -> Draws via the CPU -> Acts as an abstraction to OpenGL
        SDL_Texture* texture; // The texture is the image in GPU memory that gets drawn: https://www.youtube.com/watch?v=r8T-SPCz4JM&list=PLvv0ScY6vfd-RZSmGbLkZvkgec6lJ0BfX&index=23

        World world;
        Camera camera;

        // Mouse Position x and y
        int posX = 0;
        int posY = 0;
        bool isPressed = false;

        // Constructor
        SDLApplication(){
            // Initializing a system (SDL_INIT_AUDIO later too)
            if(!SDL_Init(SDL_INIT_VIDEO)){
                SDL_Log("Failed!");
            }

            // Setting window variable (a pointer to the window) and creating a window
            window = SDL_CreateWindow("Falling Sand", 1028, 1028, SDL_WINDOW_RESIZABLE);

            //SDL_GetWindowSize(SDL_Window *window, int *w, int *h) <-- Gets the window size if we re size it
            if (!window) {
                SDL_Log("Window failed: %s", SDL_GetError());
                SDL_Quit();
            }

            // Renderer creation in window
            renderer = SDL_CreateRenderer(window, nullptr); //Nullptr refers to what will be used to render (ex. OpenGL, Vulkan) -> We set to null so SDL can decide which to use
            if(renderer == nullptr){
                SDL_Log("Renderer Failed!");
            }
            else{
                SDL_Log("Renderer: %s", SDL_GetRendererName(renderer));
            }
            SDL_SetRenderVSync(renderer, 1);


            // sets a device‑independent resolution and presentation mode for a renderer, so the render target always appears at a fixed logical size regardless of actual window or display resolution
            SDL_SetRenderLogicalPresentation(renderer, 1028, 1028, SDL_LOGICAL_PRESENTATION_LETTERBOX);



        }

        // Destructor
        ~SDLApplication(){
            // Cleans up initialized system
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
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

            const bool* keys = SDL_GetKeyboardState(nullptr);
            // SDL_WarpMouseInWindow(SDL_Window *window, float x, float y) --> forces Mouse position into a certain place

            // Move ~8 screen pixels per frame at any zoom (at least 1 cell)
            int panSpeed = SDL_max(1, 8 / camera.zoom);

            //SDL_PollEvent(&event) returns 1 if any event is taking place
            // Event Handling Loop:
            while(SDL_PollEvent(&event)){
                //Convert the coordinates in an event to render coordinates.
                SDL_ConvertEventToRenderCoordinates(renderer, &event);
                //Quit
                if(event.type == SDL_EVENT_QUIT){
                    isRunning = false;
                }

                //Key Clicked
                else if (event.type == SDL_EVENT_KEY_DOWN){
                    SDL_Log("Key Pressed");

                    // Checks if L is pressed
                    if(keys[SDL_SCANCODE_L] == true){
                        SDL_Log("L Key pressed");
                    }

                    // Boolean that checks if panning and ONLY check camera clamp IF panning for optimization
                    if (keys[SDL_SCANCODE_W]){
                        camera.camY -= panSpeed;  // up
                    }
                    if (keys[SDL_SCANCODE_S]){
                        camera.camY += panSpeed;  // down
                    }
                    if (keys[SDL_SCANCODE_A]){
                        camera.camX -= panSpeed;  // left
                    }
                    if (keys[SDL_SCANCODE_D]){
                        camera.camX += panSpeed;  // right
                    }
                }


                // Mouse Motion
                else if (event.type == SDL_EVENT_MOUSE_MOTION){
                    // There is also event.motion.xrel, event.motion.yrel
                    SDL_Log("x,y: %f, %f",event.motion.x, event.motion.y);
                    posX = int(event.motion.x);
                    posY = int(event.motion.y);

                }

                // Mouse Click
                else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN){
                    SDL_Log("Mouse Pressed");
                    isPressed = true;

                }

                else if (event.type == SDL_EVENT_MOUSE_BUTTON_UP){
                    isPressed = false;
                }

                // Mouse Wheel -> Zoom toward the cursor
                else if (event.type == SDL_EVENT_MOUSE_WHEEL){

                    // Remember which cell is under the mouse before zooming
                    int cellX = camera.getCellX(posX);
                    int cellY = camera.getCellY(posY);

                    // Change the zoom (only if it's within the limits)
                    bool zoomChanged = false;
                    if (event.wheel.y > 0 && camera.zoom < 16){
                        camera.zoom *= 2;
                        zoomChanged = true;
                    }
                    else if (event.wheel.y < 0 && camera.zoom > 1){
                        camera.zoom /= 2;
                        zoomChanged = true;
                    }

                    // Move the camera so that same cell is back under the mouse
                    if (zoomChanged){
                        camera.camX = cellX - posX / camera.zoom;
                        camera.camY = cellY - posY / camera.zoom;
                    }
                }
            }
        }

        void Update(){
            camera.clamp();
            if(isPressed){
                // Cells are passed through the camera transform first
                world.setCell(camera.getCellX(posX), camera.getCellY(posY), 1);

            }

            // Sand physics: bottom row up, so each grain moves once per frame
            for (int y = World::HEIGHT - 1; y >= 0; y--){
                for (int x = 0; x < World::WIDTH; x++){
                    if (world.isSand(x, y)){
                        world.updateSandCells(x, y);
                    }
                }
            }
        }

        void drawPixel(int x, int y){

            // Pixels are passed through the camera
            int dx = camera.getPixelX(x);
            int dy = camera.getPixelY(y);


            //Initialize rectangle to be drawn
            SDL_FRect rect;
            rect.x = (float)dx;
            rect.y = (float)dy;
            rect.w = camera.zoom;
            rect.h = camera.zoom;

            // Draw "Pixel" at camera transformed positions
            SDL_RenderFillRect(renderer, &rect);

        }

        void Render(){

            //Set Color for backdrop
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFD, 0xD0, 0xFF);
            SDL_RenderClear(renderer);


            //Sets draw color for drawing lines etc.
            SDL_SetRenderDrawColor(renderer, 0x5C, 0x40, 0x33, 0xFF);

            for(int j=0; j<world.HEIGHT; j++){       // y outside
                for(int i=0; i<world.WIDTH; i++){    // x inside
                    if(world.getCell(i, j) == 1){
                        drawPixel(i, j);
                    }
                }
            }

            // Presents Screen
            SDL_RenderPresent(renderer);
        }

};

#endif
