#pragma once

#include <GL/glew.h>
#include <iostream>
#include <glfw3.h>
#include <cmath>
#include "Math/Matrix.h"
#include "Math/Vector.h"
#include "Math/Math.h"
#include "Input.h"

enum Camera_Movement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 50.0f;
const GLfloat SENSITIVITY = 0.5f;
const GLfloat ZOOM = 45.0f;

class Camera
{
    public:
        Camera(Vector3 position = Vector3(0.0f, 0.0f, 0.0f), Vector3 up = Vector3(0.0f, 1.0f, 0.0f),
        GLfloat yaw = YAW, GLfloat pitch = PITCH) : front(Vector3(0.0f, 0.0f, -1.0f)),
        movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM)
        {
            this->position = position;
            this->worldUp = up;
            this->yaw = yaw;
            this->pitch = pitch;
            this->updateCameraVectors();
        }

        Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY,
               GLfloat upZ, GLfloat yaw, GLfloat pitch);

        Matrix4 getViewMatrix();

        void processKeyboard(Camera_Movement direction, GLfloat deltaTime);
        void processMouseMovement(GLFWwindow *window, GLdouble xPos, GLdouble yPos);
        void processMouseScroll(GLfloat yOffset);
        void doMovement(Input& input, const double deltaTime);
        void doMouseMovement(Input& input);

        GLfloat getZoom(){ return this->zoom; };
        Vector3 getPosition() { return Vector3(position.x, position.y, position.z); }
        Vector3 getFront() { return Vector3(front.x, front.y, front.z); }

    protected:
    private:
        Vector3 position;
        Vector3 front;
        Vector3 up;
        Vector3 right;
        Vector3 worldUp;
        Vector3 velocity;

        GLfloat yaw;
        GLfloat pitch;

        GLfloat movementSpeed;
        GLfloat mouseSensitivity;
        GLfloat zoom;

        GLfloat lastX;
        GLfloat lastY;
        GLboolean firstMouse = true;

        Input manager;

        void updateCameraVectors();
};
