#ifndef WATER_H
#define WATER_H

#include "SDL3/SDL_pixels.h"
#include "World.h"
#include <SDL3/SDL.h>

//Water is 2
namespace Water {

    inline constexpr int BASE_R = 16;
    inline constexpr int BASE_G = 45;
    inline constexpr int BASE_B = 158;

    inline constexpr int DISPERSION = 5;   // how many cells water can slide sideways per frame


    // How far water at (x, y) can slide in direction dir (-1 = left, +1 = right)
    inline int spreadDistance(World& world, int x, int y, int dir){
        int dist = 0;

        // Checks in that direction by dispersion rate cells and if it hits anything within disperion rate then thats the distance
        for (int i = 1; i <= DISPERSION; i++){
            if (world.getCell(x + dir * i, y) != 0) break;   // hit something, stop
            dist = i;
        }
        return dist;
    }

    // Create a grain with its own random shade (rolled ONCE, here)
    inline void spawn(World& world, int x, int y){
        world.setCell(x, y, 2);
        world.setShade(x, y, SDL_rand(25) - 12);
    }

    // Turn a stored shade into the grain's color s
    inline SDL_Color color(int shade){
        return SDL_Color{ (Uint8)(0x16 + shade), (Uint8)(0x2D + shade),
                          (Uint8)(0x9E + shade), 255 };
    }

    inline bool isWater(World& world, int x, int y){
        if(world.getCell(x, y) == 2){
            return true;
        }
        else {
            return false;
        }
    }

    inline void updateWaterCells(World& world, int x, int y){
        bool below = world.getCell(x, y+1) == 0;
        bool downLeft  = world.getCell(x-1, y+1) == 0;
        bool downRight = world.getCell(x+1, y+1) == 0;

        //Fall straight down
        if (below){
            world.moveCell(x, y, x, y+1);
        }
        //Fall diagonally (random side if both are open)
        else if (downLeft && downRight){
            int rand = (SDL_rand(2) == 0);
            if (rand == 0){
                world.moveCell(x, y, x-1, y+1);
            }
            else{
                world.moveCell(x, y, x+1, y+1);

            }
        }
        else if (downLeft){
            world.moveCell(x, y, x-1, y+1);
        }
        else if (downRight){
            world.moveCell(x, y, x+1, y+1);
        }

        // Side ways spread
        else {
            int dir = (SDL_rand(2) == 0);
            if(dir == 0){
                dir = -1;
            }
            else{
                dir = 1;
            }
            int dist = spreadDistance(world, x, y, dir);

            if (dist == 0){// blocked that way, try the other side
                dir = -dir;
                dist = spreadDistance(world, x, y, dir);
            }
            if (dist > 0){
                world.moveCell(x, y, x + dir * dist, y);
            }
        }
    }


}
#endif
