#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "GameVars.h"
#include "SDLApplication.h"

class GameManager{

    public:
        SDLApplication app;

        GameManager(){ }

        // Main Loop
        void MainLoop(){

            while(isRunning){
                app.SDLTick();
            }
        }
};



#endif
