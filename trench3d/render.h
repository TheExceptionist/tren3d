/*
========================================================
File: render.h
Author: Kenneth Stepney
Purpose: Handles the Raycasting algorithm for rendering a view to the display


========================================================
*/

#ifndef RENDER_H
#define RENDER_H

#include "defs.h"
#include "display.h"
#include "objects.h"

#define MAX_MAP_WIDTH 10
#define MAX_MAP_HEIGHT 10

#define NS 0
#define EW 1

const int m_map[MAX_MAP_WIDTH][MAX_MAP_HEIGHT] =
{
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 2, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 2, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 2, 2, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 2, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 2, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

class Render
{
    public:
        Render(Display& display);
        virtual ~Render();

        e_std::e_bool init();
        void update();

        //Used for testing
        void setPlayer(Entity* player);
    private:
        Display& m_display;
        Entity* m_player;

        void drawCeil(const e_std::color_t& color);
        void drawFloor(const e_std::color_t& color);
        void drawWalls();

        #ifdef DEBUG
            //int m_map[MAX_MAP_WIDTH][MAX_MAP_HEIGHT];

            //void fillMap();
        #endif
};

#endif