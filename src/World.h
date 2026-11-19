#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <iostream>


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
                   std::cout << "Coordinates out of bounds";
               }

               // Gets the value at cell (x,y)
               return world[y * WIDTH + x];
           }

           // Modify cell safely
           void setCell(int x, int y, int value) {
               if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
                   std::cout << "Coordinates out of bounds";
               }

               // Sets cell (x,y) to your value
               world[y * WIDTH + x] = value;
           }



};

#endif
