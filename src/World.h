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

        // Shade for color on each cell
        std::vector<int> shade;

        World(): world(WIDTH*HEIGHT, 0), shade(WIDTH*HEIGHT, 0) {} //All Cells initialized to 0

        // Access cell
        int getCell(int x, int y) const {
               if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {

                   // Returns 100, saying this cell is a barrier
                   return 100;
               }

               // Gets the value at cell (x,y)
               return world[y * WIDTH + x];
        }

        // Get Cell Direction above/Below
        int getCellYDir(int x, int y, int dir) const {
            int realDir = -dir;
            if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT || y+realDir < 0|| y+realDir >= HEIGHT) {
                // Returns 100, saying this cell is a barrier
                return 100;
            }
            else{
                // Get Cell at (x, y+d)
                return world[(y+realDir) * WIDTH + x];
            }

            return 0;
        }

        // Get Cell Direction above/Below
        int getCellXDir(int x, int y, int dir) const {
            int realDir = -dir;
            if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT || x+realDir < 0|| x+realDir >= HEIGHT) {
                // Returns 100, saying this cell is a barrier
                return 100;
            }
            else{
                // Get Cell at (x+d, y)
                return world[y * WIDTH + (x+realDir)];
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


        int getShade(int x, int y) const {
               if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
                   return 0;
               }

               // Gets the shade at cell (x,y)
               return shade[y * WIDTH + x];
           }


        void setShade(int x, int y, int value) {
            if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
                std::cout << "Coordinates out of bounds";
                return;
            }

            // Sets cell (x,y) to your value
            shade[y * WIDTH + x] = value;

        }


        // Moves a grain AND its shade to a new spot
        void moveCell(int fromX, int fromY, int toX, int toY) {
            setCell(toX, toY, getCell(fromX, fromY));
            setShade(toX, toY, getShade(fromX, fromY));
            setCell(fromX, fromY, 0);
        }

        // Swap two cells completely (material and shade)
        void swapCell(int ax, int ay, int bx, int by){
            int cellA  = getCell(ax, ay);
            int shadeA = getShade(ax, ay);

            setCell(ax, ay, getCell(bx, by));
            setShade(ax, ay, getShade(bx, by));

            setCell(bx, by, cellA);
            setShade(bx, by, shadeA);
        }
};


#endif
