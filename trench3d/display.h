/*
========================================================
File: Display.h
Author: Kenneth Stepney
Purpose: Interface for the SDL window. Controls everything having to do with this window, 
rendering updating as well as handling click/close events 


========================================================
*/

#ifndef DISPLAY_H
#define DISPLAY_H 

#include <SDL2/SDL.h>
#include "defs.h"
#include "input.h"

//Declaration of a data type ends in a semicolon
class Display
{
    public:
        Display(e_std::e_str name, const e_std::e_word width, const e_std::e_word height);
        ~Display();

        e_std::e_bool init();
        void update();
        void close();
        void clearColor(const e_std::color_t* const color);

        void fillRect(e_std::e_word x, e_std::e_word y, e_std::e_word width, e_std::e_word height, const e_std::color_t* const color);
        //Draw a straigth line
        void drawLine(e_std::e_word start_x, e_std::e_word start_y, e_std::e_word end_x, e_std::e_word end_y, const e_std::color_t* const color);
        void putPixel(e_std::e_word x, e_std::e_word y, const e_std::color_t* const color);


        e_std::e_word getWidth() const {return m_width;}
        e_std::e_word getHeight() const {return m_height;}
        e_std::e_str getName() const {return m_name;}

        e_std::e_bool isRunning() const {return m_running;}
        void setRunning(e_std::e_bool value) { m_running = value; }
    private:
        SDL_Window* m_window;
        SDL_Surface* m_surface;

        e_std::e_word m_width;
        e_std::e_word m_height;
        e_std::e_str m_name;

        e_std::e_bool m_running;

        void handleInput();
};

#endif

