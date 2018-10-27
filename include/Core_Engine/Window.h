#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <string>
#include <GL/glew.h>
#include <glfw3.h>

#include <Math/Vector.h>

class Window
{
    public:
        Window();

        Window(const int WIDTH, const int HEIGHT, const GLchar* TITLE, bool VSYNC);

        template<typename F>
        void keyCallBack(F keyCallback){ glfwSetKeyCallback(WIN, keyCallback); }

        template<typename F>
        void cursorPosCallBack(F cursorCallBack){ glfwSetCursorPosCallback(WIN, cursorCallBack); }

        void setPosition(const Vector2 POSITION){ glfwSetWindowPos(WIN, POSITION.x, POSITION.y); }
        void setPosition(const int x, const int y){ glfwSetWindowPos(WIN, x, y); }

        void enable_cursor(){ glfwSetInputMode(WIN, GLFW_CURSOR, GLFW_CURSOR_NORMAL); }
        void disable_cursor(){ glfwSetInputMode(WIN, GLFW_CURSOR, GLFW_CURSOR_DISABLED); }
        void hide_cursor(){ glfwSetInputMode(WIN, GLFW_CURSOR, GLFW_CURSOR_HIDDEN); }

        GLfloat getDeltaTime(){ return deltaTime; }
        Vector2 getSize(){ return Vector2(width, height); }

        static void glfwerror(int id, const char* description){ std::cerr << description << std::endl; }
        void DEBUG_OUTPUT();

        void displayFPS()
        {
            frames++;
            if(currentFrame - lasttime >= 1.0)
            {
                second = 1.0;
                system("clear");
                std::cout << frames <<  "FPS" << std::endl << 1000.0/double(frames) << "ms" << std::endl;
                frames = 0;
                lasttime = currentFrame;
            }
            else
                second = 0;
        }

        void clear(const float r, const float g, const float b);
        void update();
        bool closed();

        ~Window()
        {
            glfwDestroyWindow(WIN);
            glfwTerminate();
        }

        double second;

    protected:
    private:
        void init();

        GLFWwindow* WIN;

        const int width;
        const int height;
        const bool vsync;
        const GLchar* title;

        GLfloat deltaTime = 0.0f;
        GLfloat lastFrame = 0.0f;

        double lasttime, currentFrame;
        int frames = 0;
};

Window::Window(const int WIDTH, const int HEIGHT, const GLchar* TITLE, bool VSYNC)
: width(WIDTH), height(HEIGHT), title(TITLE), vsync(VSYNC)
{
    lasttime = glfwGetTime();
    init();
}

void Window::DEBUG_OUTPUT()
{
    std::cerr << glewGetErrorString(glewInit()) << std::endl;
    std::cout << glewGetString(GLEW_VERSION) << std::endl;
    std::cout << "OpenGL ver: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL ver: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}

void Window::init()
{
    if(!glfwInit()){std::cout << "Initialization failed" << std::endl;}

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_DOUBLEBUFFER, 1);
    glfwWindowHint(GLFW_DEPTH_BITS, 24);

    glfwSetErrorCallback(&glfwerror);

    WIN = glfwCreateWindow(width, height, title, NULL, NULL);

    if(!WIN){
        std::cerr << title << ": WINDOW CREATION FAILED" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(WIN);
    glfwSwapInterval(vsync);
    glewExperimental = true;
    if (glewInit() != GLEW_OK){ std::cout << glewGetErrorString(glewInit()) << std::endl;}
}

void Window::clear(const float r, const float g, const float b)
{
    glClearColor(r, g, b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Window::update()
{
    currentFrame = glfwGetTime();

    int Width, Height;
    glfwGetFramebufferSize(WIN, &Width, &Height);
    glViewport(0, 0, Width, Height);
    glfwGetWindowSize(WIN, &Width, &Height);

    //swap buffer and check for events
    glfwSwapBuffers(WIN);
    glfwPollEvents();

    GLfloat currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}

bool Window::closed()
{
    return glfwWindowShouldClose(WIN);
}

#endif // WINDOW_H
