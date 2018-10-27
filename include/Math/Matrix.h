#pragma once

#include <iostream>
#include <GL/gl.h>
#include <cmath>
#include <iomanip>
#include <algorithm>

#include "Vector.h"
#include "Math.h"


/////////////////////////////////////////////////////////////////
//Matrix2D
/////////////////////////////////////////////////////////////////
typedef class Matrix2
{
public:
    // constructors
    Matrix2();  // init with identity
    Matrix2(const GLfloat src[4]);
    Matrix2(GLfloat m0, GLfloat m1, GLfloat m2, GLfloat m3);

    void set(const GLfloat src[4]);
    void set
    (
        GLfloat m0, GLfloat m1,
        GLfloat m2, GLfloat m3
    );

    Matrix2&    identity();
    Matrix2&    transpose();
    Matrix2&    invert();

    // operators
    Matrix2     operator+(const Matrix2& rhs) const;
    Matrix2     operator-(const Matrix2& rhs) const;
    Matrix2&    operator+=(const Matrix2& rhs);
    Matrix2&    operator-=(const Matrix2& rhs);
    Matrix2     operator*(const Matrix2& rhs) const;
    Matrix2&    operator*=(const Matrix2& rhs);
    GLboolean   operator==(const Matrix2& rhs) const;
    GLboolean   operator!=(const Matrix2& rhs) const;
    GLfloat     operator[](GLint index) const;
    GLfloat&    operator[](GLint index);

protected:

private:
    GLfloat m[4];

}mat2x2;


/////////////////////////////////////////////////////////////////
//Matrix3D
/////////////////////////////////////////////////////////////////
typedef class Matrix3
{
public:
    // constructors
    Matrix3();
    Matrix3(const GLfloat src[9]);
    Matrix3
    (
        GLfloat m0, GLfloat m1, GLfloat m2,     // 1st column
        GLfloat m3, GLfloat m4, GLfloat m5,     // 2nd column
        GLfloat m6, GLfloat m7, GLfloat m8      // 3rd column
    );

    void set(const GLfloat src[9]);
    void set
    (
        GLfloat m0, GLfloat m1, GLfloat m2,   // 1st column
        GLfloat m3, GLfloat m4, GLfloat m5,   // 2nd column
        GLfloat m6, GLfloat m7, GLfloat m8    // 3rd column
    );

    Matrix3&    identity();
    Matrix3&    transpose();
    Matrix3&    invert();

    // operators
    Matrix3     operator+(const Matrix3& rhs) const;
    Matrix3     operator-(const Matrix3& rhs) const;
    Matrix3&    operator+=(const Matrix3& rhs);
    Matrix3&    operator-=(const Matrix3& rhs);
    Matrix3     operator*(const Matrix3& rhs) const;
    Matrix3&    operator*=(const Matrix3& rhs);
    bool        operator==(const Matrix3& rhs) const;
    bool        operator!=(const Matrix3& rhs) const;
    GLfloat       operator[](GLint index) const;
    GLfloat&      operator[](GLint index);

protected:

private:
    GLfloat m[9];

}mat3x3;


/////////////////////////////////////////////////////////////////
//Matrix4D
/////////////////////////////////////////////////////////////////
typedef class Matrix4 : public Math
{
    public:
        Matrix4();

        Matrix4(const GLfloat stc[16]);

        Matrix4
        (
            GLfloat m00, GLfloat m01, GLfloat m02, GLfloat m03, // 1st column
            GLfloat m04, GLfloat m05, GLfloat m06, GLfloat m07, // 2nd column
            GLfloat m08, GLfloat m09, GLfloat m10, GLfloat m11, // 3rd column
            GLfloat m12, GLfloat m13, GLfloat m14, GLfloat m15  // 4th column
        );

        void set(const GLfloat src[16]);
        void set(
            GLfloat m00, GLfloat m01, GLfloat m02, GLfloat m03, // 1st column
            GLfloat m04, GLfloat m05, GLfloat m06, GLfloat m07, // 2nd column
            GLfloat m08, GLfloat m09, GLfloat m10, GLfloat m11, // 3rd column
            GLfloat m12, GLfloat m13, GLfloat m14, GLfloat m15  // 4th column
        );

        const GLfloat* get() const;

        Matrix4 perspective(GLfloat FOV, GLfloat ASPECT, GLfloat zNear, GLfloat zFar);
        Matrix4 orthogonal
        (
         const GLfloat left, const GLfloat right,
         const GLfloat bottom, const GLfloat top,
         const GLfloat zNear, const GLfloat zFar
        );

        Matrix4 lookAt(Vector3 const &eye, Vector3 const &center, Vector3 const &up);

        Matrix4& identity();
        Matrix4& transpose();
        Matrix4& invert();
        Matrix4& translate(const Vector3& v);
        Matrix4& translate(GLfloat x, GLfloat y, GLfloat z);
        Matrix4& scale(GLfloat s);
        Matrix4& scale(GLfloat x, GLfloat y, GLfloat z);

        void        setRow(int index, const float row[4]);
        void        setRow(int index, const Vector4& v);
        void        setRow(int index, const Vector3& v);
        void        setColumn(int index, const float col[4]);
        void        setColumn(int index, const Vector4& v);
        void        setColumn(int index, const Vector3& v);

        GLfloat getDeterminant() const;

        Matrix4& rotateX(GLfloat angle);
        Matrix4& rotateY(GLfloat angle);
        Matrix4& rotateZ(GLfloat angle);
        Matrix4& rotate(GLfloat angle, const Vector3& axis);
        Matrix4& rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);

        // operators
        Matrix4     operator+(const Matrix4& rhs);
        Matrix4     operator-(const Matrix4& rhs);
        Matrix4     operator*(const Matrix4& rhs);
        Vector4     operator*(const Vector4& rhs) const;
        Vector3     operator*(const Vector3& rhs) const;
        Matrix4&    operator+=(const Matrix4& rhs);
        Matrix4&    operator-=(const Matrix4& rhs);
        Matrix4&    operator*=(const Matrix4& rhs);
        bool        operator==(const Matrix4& n) const;
        bool        operator!=(const Matrix4& n) const;
        GLfloat     operator[](GLint index) const;
        GLfloat&    operator[](GLint index);

    protected:
    private:
        GLfloat getCofactor
        (
            GLfloat m0, GLfloat m1, GLfloat m2,
            GLfloat m3, GLfloat m4, GLfloat m5,
            GLfloat m6, GLfloat m7, GLfloat m8
        ) const;

        GLfloat m[16];
        GLfloat tm[16];

}mat4x4;

std::ostream& operator<< (std::ostream& output, Matrix4& mat4);

inline Math::Math()
{
    //void constructor
}

inline Matrix4::Matrix4()
{
    identity();
}

inline const GLfloat* Matrix4::get() const
{
    return m;
}

inline void Matrix4::set
(
    GLfloat m00, GLfloat m01, GLfloat m02, GLfloat m03,
    GLfloat m04, GLfloat m05, GLfloat m06, GLfloat m07,
    GLfloat m08, GLfloat m09, GLfloat m10, GLfloat m11,
    GLfloat m12, GLfloat m13, GLfloat m14, GLfloat m15)
{
    m[0] = m00;  m[1] = m01;  m[2] = m02;  m[3] = m03;
    m[4] = m04;  m[5] = m05;  m[6] = m06;  m[7] = m07;
    m[8] = m08;  m[9] = m09;  m[10]= m10;  m[11]= m11;
    m[12]= m12;  m[13]= m13;  m[14]= m14;  m[15]= m15;
}

inline void Matrix4::setRow(int index, const float row[4])
{
    m[index] = row[0];  m[index + 4] = row[1];  m[index + 8] = row[2];  m[index + 12] = row[3];
}

inline void Matrix4::setRow(int index, const Vector4& v)
{
    m[index] = v.x;  m[index + 4] = v.y;  m[index + 8] = v.z;  m[index + 12] = v.w;
}

inline void Matrix4::setRow(int index, const Vector3& v)
{
    m[index] = v.x;  m[index + 4] = v.y;  m[index + 8] = v.z;
}

inline void Matrix4::setColumn(int index, const float col[4])
{
    m[index*4] = col[0];  m[index*4 + 1] = col[1];  m[index*4 + 2] = col[2];  m[index*4 + 3] = col[3];
}

inline void Matrix4::setColumn(int index, const Vector4& v)
{
    m[index*4] = v.x;  m[index*4 + 1] = v.y;  m[index*4 + 2] = v.z;  m[index*4 + 3] = v.w;
}

inline void Matrix4::setColumn(int index, const Vector3& v)
{
    m[index*4] = v.x;  m[index*4 + 1] = v.y;  m[index*4 + 2] = v.z;
}

inline GLfloat Matrix4::getCofactor(GLfloat m0, GLfloat m1, GLfloat m2,
                           GLfloat m3, GLfloat m4, GLfloat m5,
                           GLfloat m6, GLfloat m7, GLfloat m8) const
{
    return m0 * (m4 * m8 - m5 * m7) -
           m1 * (m3 * m8 - m5 * m6) +
           m2 * (m3 * m7 - m4 * m6);
}

inline Matrix4& Matrix4::translate(const Vector3& v)
{
    return translate(v.x, v.y, v.z);
}

inline Matrix4& Matrix4::translate(GLfloat x, GLfloat y, GLfloat z)
{
    m[0] += m[3] * x;   m[4] += m[7] * x;   m[8] += m[11]* x;   m[12]+= m[15]* x;
    m[1] += m[3] * y;   m[5] += m[7] * y;   m[9] += m[11]* y;   m[13]+= m[15]* y;
    m[2] += m[3] * z;   m[6] += m[7] * z;   m[10]+= m[11]* z;   m[14]+= m[15]* z;

    return *this;
}

inline Matrix4& Matrix4::scale(GLfloat s)
{
    return scale(s, s, s);
}

inline Matrix4& Matrix4::scale(GLfloat x, GLfloat y, GLfloat z)
{
    m[0] *= x;   m[4] *= x;   m[8] *= x;   m[12] *= x;
    m[1] *= y;   m[5] *= y;   m[9] *= y;   m[13] *= y;
    m[2] *= z;   m[6] *= z;   m[10]*= z;   m[14] *= z;
    return *this;
}

inline Matrix4& Matrix4::identity()
{
    m[0] = m[5] = m[10] = m[15] = 1.0f;
    m[1] = m[2] = m[3] = m[4] = m[6] = m[7] = m[8] = m[9] = m[11] = m[12] = m[13] = m[14] = 0.0f;
}


inline Matrix4::Matrix4
(
    GLfloat m00, GLfloat m01, GLfloat m02, GLfloat m03, // 1st column
    GLfloat m04, GLfloat m05, GLfloat m06, GLfloat m07, // 2nd column
    GLfloat m08, GLfloat m09, GLfloat m10, GLfloat m11, // 3rd column
    GLfloat m12, GLfloat m13, GLfloat m14, GLfloat m15  // 4th column
)
{
    m[0] = m00; m[1] = m01; m[2] = m02; m[3] = m03;      // 1st column
    m[4] = m04; m[5] = m05; m[6] = m06; m[7] = m07;      // 2nd column
    m[8] = m08; m[9] = m09; m[10] = m10; m[11] = m11;    // 3rd column
    m[12] = m12; m[13] = m13; m[14] = m14; m[15] = m15;  // 4th column
}

inline Matrix4 Matrix4::operator+(const Matrix4& rhs)
{
    m[0] += rhs.m[0];
    m[1] += rhs.m[1];
    m[2] += rhs.m[2];
    m[3] += rhs.m[3];
    m[4] += rhs.m[4];
    m[5] += rhs.m[5];
    m[6] += rhs.m[6];
    m[7] += rhs.m[7];
    m[8] += rhs.m[8];
    m[9] += rhs.m[9];
    m[10] += rhs.m[10];
    m[11] += rhs.m[11];
    m[12] += rhs.m[12];
    m[13] += rhs.m[13];
    m[14] += rhs.m[14];
    m[15] += rhs.m[15];

    return *this;
}

inline Matrix4 Matrix4::operator-(const Matrix4& rhs)
{
    m[0] *= rhs.m[0];
    m[1] *= rhs.m[1];
    m[2] *= rhs.m[2];
    m[3] *= rhs.m[3];
    m[4] *= rhs.m[4];
    m[5] *= rhs.m[5];
    m[6] *= rhs.m[6];
    m[7] *= rhs.m[7];
    m[8] *= rhs.m[8];
    m[9] *= rhs.m[9];
    m[10] *= rhs.m[10];
    m[11] *= rhs.m[11];
    m[12] *= rhs.m[12];
    m[13] *= rhs.m[13];
    m[14] *= rhs.m[14];
    m[15] *= rhs.m[15];

    return *this;
}

inline Matrix4 Matrix4::operator*(const Matrix4& rhs)
{
    return Matrix4
    (
        m[0]*rhs[0] + m[1]*rhs[4] + m[2]*rhs[8] + m[3]*rhs[12],
        m[0]*rhs[1] + m[1]*rhs[5] + m[2]*rhs[9] + m[3]*rhs[13],
        m[0]*rhs[2] + m[1]*rhs[6] + m[2]*rhs[10] + m[3]*rhs[14],
        m[0]*rhs[3] + m[1]*rhs[7] + m[2]*rhs[11] + m[3]*rhs[15],

        m[4]*rhs[0] + m[5]*rhs[4] + m[6]*rhs[8] + m[7]*rhs[12],
        m[4]*rhs[1] + m[5]*rhs[5] + m[6]*rhs[9] + m[7]*rhs[13],
        m[4]*rhs[2] + m[5]*rhs[6] + m[6]*rhs[10] + m[7]*rhs[14],
        m[4]*rhs[3] + m[5]*rhs[7] + m[6]*rhs[11] + m[7]*rhs[15],

        m[8]*rhs[0] + m[9]*rhs[4] + m[10]*rhs[8] + m[11]*rhs[12],
        m[8]*rhs[1] + m[9]*rhs[5] + m[10]*rhs[9] + m[11]*rhs[13],
        m[8]*rhs[2] + m[9]*rhs[6] + m[10]*rhs[10] + m[11]*rhs[14],
        m[8]*rhs[3] + m[9]*rhs[7] + m[10]*rhs[11] + m[11]*rhs[15],

        m[12]*rhs[0] + m[13]*rhs[4] + m[14]*rhs[8] + m[15]*rhs[12],
        m[12]*rhs[1] + m[13]*rhs[5] + m[14]*rhs[9] + m[15]*rhs[13],
        m[12]*rhs[2] + m[13]*rhs[6] + m[14]*rhs[10] + m[15]*rhs[14],
        m[12]*rhs[3] + m[13]*rhs[7] + m[14]*rhs[11] + m[15]*rhs[15]
    );
}

inline Vector4 Matrix4::operator*(const Vector4& rhs) const
{
    return Vector4(m[0]*rhs.x + m[4]*rhs.y + m[8]*rhs.z  + m[12]*rhs.w,
                   m[1]*rhs.x + m[5]*rhs.y + m[9]*rhs.z  + m[13]*rhs.w,
                   m[2]*rhs.x + m[6]*rhs.y + m[10]*rhs.z + m[14]*rhs.w,
                   m[3]*rhs.x + m[7]*rhs.y + m[11]*rhs.z + m[15]*rhs.w);
}

inline Vector3 Matrix4::operator*(const Vector3& rhs) const
{
    return Vector3(m[0]*rhs.x + m[4]*rhs.y + m[8]*rhs.z + m[12],
                   m[1]*rhs.x + m[5]*rhs.y + m[9]*rhs.z + m[13],
                   m[2]*rhs.x + m[6]*rhs.y + m[10]*rhs.z+ m[14]);
}

inline Matrix4& Matrix4::operator+=(const Matrix4& rhs)
{
    *this = *this + rhs;

    return *this;
}

inline Matrix4& Matrix4::operator-=(const Matrix4& rhs)
{
    *this = *this - rhs;

    return *this;
}

inline Matrix4& Matrix4::operator*=(const Matrix4& rhs)
{
    *this = *this * rhs;
    return *this;
}

inline bool Matrix4::operator==(const Matrix4& n) const
{
    return (m[0] == n[0])  && (m[1] == n[1])  && (m[2] == n[2])  && (m[3] == n[3])  &&
           (m[4] == n[4])  && (m[5] == n[5])  && (m[6] == n[6])  && (m[7] == n[7])  &&
           (m[8] == n[8])  && (m[9] == n[9])  && (m[10]== n[10]) && (m[11]== n[11]) &&
           (m[12]== n[12]) && (m[13]== n[13]) && (m[14]== n[14]) && (m[15]== n[15]);
}
inline bool Matrix4::operator!=(const Matrix4& n) const
{
    return (m[0] != n[0])  || (m[1] != n[1])  || (m[2] != n[2])  || (m[3] != n[3])  ||
           (m[4] != n[4])  || (m[5] != n[5])  || (m[6] != n[6])  || (m[7] != n[7])  ||
           (m[8] != n[8])  || (m[9] != n[9])  || (m[10]!= n[10]) || (m[11]!= n[11]) ||
           (m[12]!= n[12]) || (m[13]!= n[13]) || (m[14]!= n[14]) || (m[15]!= n[15]);
}

inline std::ostream& operator<< (std::ostream& output, Matrix4& mat4)
{
    output << std::fixed << std::setprecision(5) <<
    "          ======Matrix==4x4======\n" <<
    "[ " << mat4[0] << "    " << mat4[1] << "    " << mat4[2] << "    "  << mat4[3] << " ]\n" <<
    "[ " << mat4[4] << "    " << mat4[5] << "    " << mat4[6] << "    " << mat4[7] << " ]\n" <<
    "[ " << mat4[8] << "    " << mat4[9] << "    " << mat4[10] << "    " << mat4[11] << " ]\n" <<
    "[ " << mat4[12] << "    " << mat4[13] << "    " << mat4[14] << "    " << mat4[15] << " ]";

    return output;
}

inline GLfloat Matrix4::operator[](GLint index) const
{
    return m[index];
}

inline GLfloat& Matrix4::operator[](GLint index)
{
    return m[index];
}
