#ifndef CAM_H
#define CAM_H

#include <SDL3/SDL.h>
#include "World.h"

class Camera{
    public:
        int camX = 0;
        int camY = 0;
        int zoom = 4;

        static constexpr int SCREEN_W = 1028;   // matches your logical presentation size
        static constexpr int SCREEN_H = 1028;

        Camera(){}

        int getCellX(int pixelX) const{
            return (pixelX/zoom + camX);

        }

        int getCellY(int pixelY) const{
            return (pixelY/zoom + camY);

        }

        int getPixelX(int cellX) const{
            return ((cellX - camX)*zoom);

        }

        int getPixelY(int cellY) const{
            return((cellY - camY)*zoom);

        }

        // Keep the camera inside the world
        void clamp(){
            int viewW = SCREEN_W / zoom;   // how many cells fit across the screen
            int viewH = SCREEN_H / zoom;

            // Clamping takes a number and forces it to stay inside a range
            /*
             If x is outside the range a values between a and b, the returned value will be a or b as appropriate.
             Otherwise, x is returned.
             */
            camX = SDL_clamp(camX, 0, World::WIDTH  - viewW);
            camY = SDL_clamp(camY, 0, World::HEIGHT - viewH);
        }


};

#endif
