#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "GameVars.h"
#include "SDLApplication.h"
#include "Water.h"

class GameManager{

    public:
        World world;
        SDLApplication app{world};

        GameManager(){ }

        void MainTick(){
            // Sand physics: bottom row up, so each grain moves once per frame
            for (int y = World::HEIGHT - 1; y >= 0; y--){
                for (int x = 0; x < World::WIDTH; x++){
                    if (Sand::isSand(world, x, y)){
                        Sand::updateSandCells(world, x, y);

                    }
                    else if(Water::isWater(world, x, y)){
                        Water::updateWaterCells(world, x, y);
                    }
                }
            }
        }

        // Main Loop
        void MainLoop(){

            while(isRunning){
                app.Input();
                app.Update();
                MainTick();
                app.Render();
            }
        }
};



#endif
