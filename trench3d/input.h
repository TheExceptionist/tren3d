/*
========================================================
File: render.h
Author: Kenneth Stepney
Purpose: Handles the specific functionality/actions to be executed when a key is pressed


========================================================
*/

#ifndef INPUT_H
#define INPUT_H

#include "defs.h"

enum
{
	KEY_LEFT,
	KEY_RIGHT,
	KEY_UP,
	KEY_DOWN,

	KEY_NUM
};

class KeyBinding
{
public:
    KeyBinding() {}
	virtual ~KeyBinding() {}
	virtual void execute() = 0;
};

class InputManager
{
public:
    InputManager();
    virtual ~InputManager();

    static InputManager& get() 
    {
        static InputManager* manager = new InputManager();
        return *manager;
    }

    //void setPlayer(Entity* player) { m_player = player;}

    KeyBinding& getKey(const int code);
    
    bool init();
    void move(const int x, const int y) { printf("Moving: (%d, %d)", x, y); /*m_player->move(x, y);*/ }
private:
   // Entity* m_player;

    KeyBinding* m_left;
    KeyBinding* m_right;
    KeyBinding* m_up;
    KeyBinding* m_down;
};

class MoveKeys : public KeyBinding
{
public:
	MoveKeys(InputManager& input, const int x, const int y) : m_input(input),
        m_x(x), m_y(y) {}

	virtual void execute() {  m_input.move(m_x, m_y); }
protected:
	int m_x, m_y;
private:
    InputManager& m_input;
};

#endif