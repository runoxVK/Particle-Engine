#ifndef SAND_H
#define SAND_H

#include "World.h"
#include <SDL3/SDL.h>

namespace Sand {

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
            world.setCell(x, y, 0);
            world.setCell(x, y+1, 1);
        }

        else if (world.getCell(x+1, y+1) == 0 && world.getCell(x-1,y+1) == 0){
            int r = SDL_rand(2);
            if(r == 0){
                world.setCell(x, y, 0);
                world.setCell(x+1, y+1, 1);
            }
            else{
                world.setCell(x, y, 0);
                world.setCell(x-1, y+1, 1);

            }
        }
        else if(world.getCell(x+1, y+1) == 0){
            world.setCell(x, y, 0);
            world.setCell(x+1, y+1, 1);
        }
        else if(world.getCell(x-1,y+1) == 0){
            world.setCell(x, y, 0);
            world.setCell(x-1, y+1, 1);
        }
        else{
            world.setCell(x, y, 1);
        }
    }

}
#endif
