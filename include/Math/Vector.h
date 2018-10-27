#pragma once

#include <iostream>
#include <GL/gl.h>
#include <vector>
#include <limits.h>
#include <cmath>

/////////////////////////////////////////////////////////////////////////////////
//Vector2D
/////////////////////////////////////////////////////////////////////////////////
class Vector2
{
    public:
        GLfloat x;
        GLfloat y;

        Vector2();

        Vector2(GLfloat x, GLfloat y) : x(x), y(y) {};

        void set(GLfloat x, GLfloat y);
        const float get() { float arrvector[2] = {x, y}; return* arrvector; };

        Vector2 operator= (const Vector2& vec);
        Vector2 operator+ (const Vector2& vec)const;
        Vector2 operator- (const Vector2& vec)const;
        Vector2 operator/ (const Vector2& vec)const;
        Vector2 operator/ (const float& num)const;
        Vector2 operator* (const Vector2& vec)const;
        Vector2 operator* (const float& num)const;


    protected:
    private:
};

std::ostream& operator<< (std::ostream& output, const Vector2& vec);


/////////////////////////////////////////////////////////////////////////////////
//Vector3D
/////////////////////////////////////////////////////////////////////////////////
class Vector3
{
    public:
        GLfloat x;
        GLfloat y;
        GLfloat z;

        Vector3();
        Vector3(GLfloat xyz) : x(xyz), y(xyz), z(xyz) {};

        Vector3(GLfloat x, GLfloat y, GLfloat z) : x(x), y(y), z(z) {};
        Vector3&    normal();
        Vector3    normalize(Vector3 vec3);
        bool        equal(const Vector3& vec, float e) const;

        void set(GLfloat x, GLfloat y, GLfloat z);
        const float get() { float arrvector[3] = {x, y, z}; return* arrvector; };

        Vector3 operator= (const Vector3& vec);
        Vector3 operator+ (const Vector3& vec)const;
        Vector3 operator- (const Vector3& vec)const;
        Vector3 operator/ (const Vector3& vec)const;
        Vector3 operator/ (const float& num)const;
        Vector3 operator* (const Vector3& vec)const;
        Vector3 operator* (const float& num)const;
        Vector3 operator+= (const Vector3& vec);
        Vector3 operator-= (const Vector3& vec);

    protected:
    private:
};

std::ostream& operator<< (std::ostream& output, const Vector3& vec);

inline Vector3 Vector3::operator+= (const Vector3& vec)
{
    this->x += vec.x;
    this->y += vec.y;
    this->z += vec.z;
    return *this;
}

inline Vector3 Vector3::operator-= (const Vector3& vec)
{
    this->x -= vec.x;
    this->y -= vec.y;
    this->z -= vec.z;
    return *this;
}

/////////////////////////////////////////////////////////////////////////////////
//Vector4D
/////////////////////////////////////////////////////////////////////////////////
class Vector4
{
    public:
        GLfloat x;
        GLfloat y;
        GLfloat z;
        GLfloat w;

        Vector4() : x(0), y(0), z(0), w(0) {};

        Vector4(GLfloat x, GLfloat y, GLfloat z, GLfloat w) : x(x), y(y), z(z), w(w) {};

        void set(GLfloat x, GLfloat y, GLfloat z, GLfloat w);

        Vector4 operator= (const Vector4& vec);
        Vector4 operator+ (const Vector4& vec)const;
        Vector4 operator- (const Vector4& vec)const;
        Vector4 operator/ (const Vector4& vec)const;
        Vector4 operator/ (const GLfloat& num)const;
        Vector4 operator* (const Vector4& vec)const;
        Vector4 operator* (const GLfloat& num)const;

    protected:
    private:
};

std::ostream& operator<< (std::ostream& output, const Vector4& vec);
