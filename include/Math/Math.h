#pragma once

#include <iostream>
#include <vector>
#include <limits.h>
#include <cmath>
#include <GL/gl.h>

#include <Math/Vector.h>

class Math
{
    public:

        Math();

        static GLfloat dot(Vector3 a, Vector3 b);

        GLfloat det(GLfloat a, GLfloat b, GLfloat c, GLfloat d);
        Vector3 cross(Vector3 a, Vector3 b);
        GLdouble sqrt(GLdouble num);
        GLfloat magnitude(Vector3 v);
        GLfloat magnitude(Vector4 v);
        Vector3 normalize(Vector3 vec3);
        Vector4 normalize(Vector4 vec4);


    protected:
    private:
};
