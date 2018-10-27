#pragma once

#include <iostream>
#include <glfw3.h>
#include "Math/Vector.h"

class Input
{
    public:
        Input();
        ~Input();

        bool key(const int key);
        void keyCallBack(GLFWwindow *window, GLint key, GLint scan, GLint action, GLint mode);

        void mouseCallBack(GLFWwindow *window, GLdouble x_position, GLdouble y_position)
        { mouse_position = Vector2(x_position, y_position); }


        Vector2 getMousePosition(){ return mouse_position; }
        Vector2 getMouseOffset(){ return mouse_offset; }

        Vector2 temp;
    protected:
    private:
        GLboolean KEY[1024];
        Vector2 mouse_offset;
        Vector2 mouse_position;
};
