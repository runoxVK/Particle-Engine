#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <iostream>
#include <SDL3/SDL.h>


class World{

    public:

        static constexpr int WIDTH = 1028;
        static constexpr int HEIGHT = 1028;

        // 2D world stored as a flat vector
        /* 2D view (WIDTH = 4):         flat vector:
        y=0: [ 0  1  2  3 ]          [0 1 2 3 | 4 5 6 7 | 8 9 10 11]
        y=1: [ 4  5  6  7 ]            row 0     row 1     row 2
        y=2: [ 8  9 10 11 ]
        */

        std::vector<int> world;

        World(): world(WIDTH*HEIGHT, 0){} //All Cells initialized to 0

        // Access cell
        int getCell(int x, int y) const {
               if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {

                   // Returns 2, saying this cell is a barrier
                   return 2;
               }

               // Gets the value at cell (x,y)
               return world[y * WIDTH + x];
           }

        // Get Cell Below
        int getCellYDir(int x, int y, int dir) const {
            int realDir = -dir;

            if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT || y+realDir < 0|| y+realDir >= HEIGHT) {
                // Returns 2, saying this cell is a barrier
                return 2;
            }
            else{
                // Get Cell at (x, y+d)
                return world[(y+realDir) * WIDTH + x];
            }

            return 0;
        }


        // Modify cell safely
        void setCell(int x, int y, int value) {
               if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
                   std::cout << "Coordinates out of bounds";
                   return;
               }

               // Sets cell (x,y) to your value
               world[y * WIDTH + x] = value;
           }

        bool isSand(int x, int y){
            if(getCell(x, y) == 1){
                return true;
            }
            else {
                return false;
            }
        }

        void updateSandCells(int x, int y){
            if(getCellYDir(x, y, -1) == 0){
                setCell(x, y, 0);
                setCell(x, y+1, 1);
            }
            else if (getCell(x+1, y+1) == 0 && getCell(x-1,y+1) == 0){
                int r = SDL_rand(2);
                if(r == 0){
                    setCell(x, y, 0);
                    setCell(x+1, y+1, 1);
                }
                else{
                    setCell(x, y, 0);
                    setCell(x-1, y+1, 1);

                }
            }
            else if(getCell(x+1, y+1) == 0){
                setCell(x, y, 0);
                setCell(x+1, y+1, 1);
            }
            else if(getCell(x-1,y+1) == 0){
                setCell(x, y, 0);
                setCell(x-1, y+1, 1);
            }
            else{
                setCell(x, y, 1);
            }
        }

};

#endif
