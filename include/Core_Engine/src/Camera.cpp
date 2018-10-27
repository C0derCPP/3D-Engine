#include <Core_Engine/Camera.h>

const float DEG2RAD = 3.141593f / 180.0f;
const GLfloat gravity = 0.95;

Camera::Camera
(
    GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY,
    GLfloat upZ, GLfloat yaw, GLfloat pitch)
    : front(Vector3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM)
{
    this->position = Vector3(posX, posY, posZ);
    this->worldUp = Vector3(upX, upY, upZ);
    this->yaw = yaw;
    this->pitch = pitch;
    this->updateCameraVectors();
}

Matrix4 Camera::getViewMatrix()
{
    Matrix4 mat4;
    return mat4.lookAt(this->position, this->position + this->front, this->up);
}

void Camera::processKeyboard(Camera_Movement direction, GLfloat deltaTime)
{
    GLfloat velocity = this->movementSpeed * deltaTime;

    if(FORWARD == direction)
    {
        this->position -= this->front * velocity;
    }

    if(BACKWARD == direction)
    {
        this->position += this->front * velocity;
    }

    if(LEFT == direction)
    {
        this->position -= this->right * velocity;
    }

    if(RIGHT == direction)
    {
        this->position += this->right * velocity;
    }
}

void Camera::processMouseMovement(GLFWwindow *window, GLdouble xpos, GLdouble ypos)
{
    GLboolean constrainPitch = true;

    if(firstMouse){
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    GLfloat xOffset = lastX - xpos;
    GLfloat yOffset = ypos - lastY;

    lastX = xpos;
    lastY = ypos;

    xOffset *= this->mouseSensitivity;
    yOffset *= this->mouseSensitivity;

    this->yaw += xOffset;
    this->pitch += yOffset;

    if(constrainPitch)
    {
        if(this->pitch > 89.0f)
        {
            this->pitch = 89.0f;
        }

        if(this->pitch < -89.0f)
        {
            this->pitch = -89.0f;
        }
    }

    this->updateCameraVectors();
}

void Camera::processMouseScroll(GLfloat yOffset)
{
    if(this->zoom >= 1.0f && this->zoom <= 45.0f)
    {
        this->zoom -= yOffset;
    }

    if(this->zoom <= 1.0f)
    {
        this->zoom = 1.0f;
    }

    if(this->zoom >= 45.0f)
    {
        this->zoom = 45.0f;
    }
}

void Camera::updateCameraVectors()
{
    Vector3 front;
    Math m;
    Matrix4 mat4;
    front.x = cos(DEG2RAD * this->yaw) * cos(DEG2RAD * this->pitch);
    front.y = sin(DEG2RAD * this->pitch);
    front.z = sin(DEG2RAD * this->yaw) * cos(DEG2RAD * this->pitch);

    this->front = m.normalize(front);
    this->right = m.normalize(m.cross(this->front, this->worldUp));
    this->up = m.normalize(m.cross(this->right, this->front));
}

void Camera::doMovement(Input& input, const double deltaTime)
{
    if(input.key(GLFW_KEY_W)){   processKeyboard (FORWARD, deltaTime);  }
    if(input.key(GLFW_KEY_S)){   processKeyboard (BACKWARD, deltaTime); }
    if(input.key(GLFW_KEY_A)){   processKeyboard (LEFT, deltaTime);     }
    if(input.key(GLFW_KEY_D)){   processKeyboard (RIGHT, deltaTime);    }
    if(input.key(GLFW_KEY_LEFT_SHIFT)){   movementSpeed *= 1.002;   }
    if(input.key(GLFW_KEY_C)){   movementSpeed /= 1.002;   }
}

