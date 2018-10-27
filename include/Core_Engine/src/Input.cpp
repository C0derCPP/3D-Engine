#include <Core_Engine/Input.h>

Input::Input()
{
    //ctor
}

Input::~Input()
{
    //dtor
}

bool Input::key(const int key)
{
    if(KEY[key])
        return true;
    else
        return false;
}

void Input::keyCallBack(GLFWwindow *window, GLint key, GLint scan, GLint action, GLint mode)
{
    if(key == GLFW_KEY_ESCAPE && GLFW_PRESS == action){ glfwSetWindowShouldClose(window, GL_TRUE);              }
    if(key == GLFW_KEY_1 && GLFW_PRESS == action){ glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);   }
    if(key == GLFW_KEY_2 && GLFW_PRESS == action){ glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); }

    std::cout << "key: " << key << std::endl;

    if(key >= 0 && key < 1024)
    {
        if(GLFW_PRESS == action){ KEY[key] = true; }
        else if(GLFW_RELEASE == action){ KEY[key] = false; }
    }
}
