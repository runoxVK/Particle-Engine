#include "SDL3/SDL_events.h"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_keyboard.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_mouse.h"
#include "SDL3/SDL_stdinc.h"
#include "SDL3/SDL_surface.h"
#include "SDL3/SDL_timer.h"
#include "SDL3/SDL_video.h"
#include <SDL3/SDL.h>
//https://wiki.libsdl.org/SDL3/FrontPage
#include <iostream>
#include <string>

#include "GameManager.h"


int main(){

    GameManager game;
    game.MainLoop();
    return 0;
}
