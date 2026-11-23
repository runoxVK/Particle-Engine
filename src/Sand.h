#ifndef SAND_H
#define SAND_H

#include "SDL3/SDL_pixels.h"
#include "World.h"
#include <SDL3/SDL.h>

namespace Sand {
    // Base sand color: 0x5C, 0x40, 0x33
    inline constexpr int BASE_R = 92;
    inline constexpr int BASE_G = 64;
    inline constexpr int BASE_B = 51;

    // Create a grain with its own random shade (rolled ONCE, here)
    inline void spawn(World& world, int x, int y){
        world.setCell(x, y, 1);
        world.setShade(x, y, SDL_rand(25) - 12);
    }

    // Turn a stored shade into the grain's color s
    inline SDL_Color color(int shade){
        return SDL_Color{ (Uint8)(0x5C + shade), (Uint8)(0x40 + shade),
                          (Uint8)(0x33 + shade), 255 };
    }

    inline bool isSand(World& world, int x, int y){
        if(world.getCell(x, y) == 1){
            return true;
        }
        else {
            return false;
        }
    }

    inline void updateSandCells(World& world, int x, int y){
        if(world.getCellYDir(x, y, -1) == 0){
            world.moveCell(x, y, x, y+1);
        }

        // Check if water is beneath the sand
        else if(world.getCellYDir(x, y, -1) == 2){
            world.swapCell(x, y, x, y+1);
        }

        else if (world.getCell(x+1, y+1) == 2 && world.getCell(x-1,y+1) == 2){
            int r = SDL_rand(2);
            if(r == 0){
                world.swapCell(x, y, x+1, y+1);
            }
            else{
                world.swapCell(x, y, x-1, y+1);
            }
        }

        else if(world.getCell(x+1, y+1) == 2){
            world.swapCell(x, y, x+1, y+1);
        }
        else if(world.getCell(x-1,y+1) == 2){
            world.swapCell(x, y, x-1, y+1);
        }

        else if (world.getCell(x+1, y+1) == 0 && world.getCell(x-1,y+1) == 0){
            int r = SDL_rand(2);
            if(r == 0){
                world.moveCell(x, y, x+1, y+1);
            }
            else{
                world.moveCell(x, y, x-1, y+1);
            }
        }
        else if(world.getCell(x+1, y+1) == 0){
            world.moveCell(x, y, x+1, y+1);
        }
        else if(world.getCell(x-1,y+1) == 0){
            world.moveCell(x, y, x-1, y+1);
        }
        else{
            world.setCell(x, y, 1);
        }
    }


}
#endif
