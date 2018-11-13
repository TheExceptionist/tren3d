#include "input.h"

InputManager::InputManager()
{
	m_left = new MoveKeys(*this, -1, 0);
	m_right = new MoveKeys(*this, 1, 0);
	m_up = new MoveKeys(*this, 0, -1);
	m_down = new MoveKeys(*this, 0, 1);
}

InputManager::~InputManager()
{
	delete m_left;
	delete m_right;
	delete m_up; 
	delete m_down;
}

bool InputManager::init()
{
    bool success = true;
    return success;
}

KeyBinding& InputManager::getKey(const int code)
{
    switch(code)
    {
        case KEY_RIGHT:
        {
            return *m_right;
        } 
        case KEY_LEFT:
        {
            return *m_left;
        } 
        case KEY_UP:
        {
            return *m_up;
        } 
        case KEY_DOWN:
        {
            return *m_down;
        } 
    }
}