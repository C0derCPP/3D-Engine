#include <Math/Matrix.h>

#include <Math/Vector.h>
#include <Math/Math.h>

const float DEG2RAD = 3.141593f / 180.0f;
const float RAD2DEG = 180.0f / 3.141593f;
const float EPSILON = 0.00001f;

Matrix3& Matrix3::transpose()
{
    std::swap(m[1],  m[3]);
    std::swap(m[2],  m[6]);
    std::swap(m[5],  m[7]);

    return *this;
}

Matrix3& Matrix3::invert()
{
    return *this;
}

Matrix4& Matrix4::transpose()
{
    std::swap(m[1],  m[4]);     //    [0  1   2  3]       [0  4  8  12]
    std::swap(m[2],  m[8]);     //    [4  5   6  7]  __\  [1  5  9  13]
    std::swap(m[3],  m[12]);    //    [8  9  10 11]    /  [2  6  10 14]
    std::swap(m[6],  m[9]);     //    [12 13 14 15]       [3  7  11 15]
    std::swap(m[7],  m[13]);
    std::swap(m[11], m[14]);

    return *this;
}

GLfloat Matrix4::getDeterminant() const
{
    return m[0] * getCofactor(m[5],m[6],m[7], m[9],m[10],m[11], m[13],m[14],m[15]) -
           m[1] * getCofactor(m[4],m[6],m[7], m[8],m[10],m[11], m[12],m[14],m[15]) +
           m[2] * getCofactor(m[4],m[5],m[7], m[8],m[9], m[11], m[12],m[13],m[15]) -
           m[3] * getCofactor(m[4],m[5],m[6], m[8],m[9], m[10], m[12],m[13],m[14]);
}

Matrix4& Matrix4::invert()
{
    return *this;
}

Matrix4& Matrix4::rotate(GLfloat angle, const Vector3& axis)
{
    return rotate(angle, axis.x, axis.y, axis.z);
}

Matrix4& Matrix4::rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
    GLfloat c = cosf(angle * DEG2RAD);    // cosine
    GLfloat s = sinf(angle * DEG2RAD);    // sine
    GLfloat c1 = 1.0f - c;                // 1 - c

    GLfloat
    m0 = m[0],  m4 = m[4],  m8 = m[8],  m12 = m[12],
    m1 = m[1],  m5 = m[5],  m9 = m[9],  m13 = m[13],
    m2 = m[2],  m6 = m[6], m10 = m[10], m14 = m[14];

    // build rotation matrix
    GLfloat r0 = x * x * c1 + c;
    GLfloat r1 = x * y * c1 + z * s;
    GLfloat r2 = x * z * c1 - y * s;
    GLfloat r4 = x * y * c1 - z * s;
    GLfloat r5 = y * y * c1 + c;
    GLfloat r6 = y * z * c1 + x * s;
    GLfloat r8 = x * z * c1 + y * s;
    GLfloat r9 = y * z * c1 - x * s;
    GLfloat r10= z * z * c1 + c;

    // multiply rotation matrix
    m[0] = r0 * m0 + r4 * m1 + r8 * m2;
    m[1] = r1 * m0 + r5 * m1 + r9 * m2;
    m[2] = r2 * m0 + r6 * m1 + r10* m2;
    m[4] = r0 * m4 + r4 * m5 + r8 * m6;
    m[5] = r1 * m4 + r5 * m5 + r9 * m6;
    m[6] = r2 * m4 + r6 * m5 + r10* m6;
    m[8] = r0 * m8 + r4 * m9 + r8 * m10;
    m[9] = r1 * m8 + r5 * m9 + r9 * m10;
    m[10]= r2 * m8 + r6 * m9 + r10* m10;
    m[12]= r0 * m12+ r4 * m13+ r8 * m14;
    m[13]= r1 * m12+ r5 * m13+ r9 * m14;
    m[14]= r2 * m12+ r6 * m13+ r10* m14;

    return *this;
}

Matrix4& Matrix4::rotateX(GLfloat angle)
{
    GLfloat c = cosf(angle * DEG2RAD);
    GLfloat s = sinf(angle * DEG2RAD);
    GLfloat m1 = m[1],  m2 = m[2],
          m5 = m[5],  m6 = m[6],
          m9 = m[9],  m10= m[10],
          m13= m[13], m14= m[14];

    m[1] = m1 * c + m2 *-s;
    m[2] = m1 * s + m2 * c;
    m[5] = m5 * c + m6 *-s;
    m[6] = m5 * s + m6 * c;
    m[9] = m9 * c + m10*-s;
    m[10]= m9 * s + m10* c;
    m[13]= m13* c + m14*-s;
    m[14]= m13* s + m14* c;

    return *this;
}

Matrix4& Matrix4::rotateY(GLfloat angle)
{
    GLfloat c = cosf(angle * DEG2RAD);
    GLfloat s = sinf(angle * DEG2RAD);
    GLfloat m0 = m[0],  m2 = m[2],
          m4 = m[4],  m6 = m[6],
          m8 = m[8],  m10= m[10],
          m12= m[12], m14= m[14];

    m[0] = m0 * c + m2 * s;
    m[2] = m0 *-s + m2 * c;
    m[4] = m4 * c + m6 * s;
    m[6] = m4 *-s + m6 * c;
    m[8] = m8 * c + m10* s;
    m[10]= m8 *-s + m10* c;
    m[12]= m12* c + m14* s;
    m[14]= m12*-s + m14* c;

    return *this;
}

Matrix4& Matrix4::rotateZ(GLfloat angle)
{
    GLfloat c = cosf(angle * DEG2RAD);
    GLfloat s = sinf(angle * DEG2RAD);
    GLfloat m0 = m[0],  m1 = m[1],
          m4 = m[4],  m5 = m[5],
          m8 = m[8],  m9 = m[9],
          m12= m[12], m13= m[13];

    m[0] = m0 * c + m1 *-s;
    m[1] = m0 * s + m1 * c;
    m[4] = m4 * c + m5 *-s;
    m[5] = m4 * s + m5 * c;
    m[8] = m8 * c + m9 *-s;
    m[9] = m8 * s + m9 * c;
    m[12]= m12* c + m13*-s;
    m[13]= m12* s + m13* c;

    return *this;
}

Matrix4 Matrix4::perspective(GLfloat FOV ,GLfloat ASPECT, GLfloat zNear, GLfloat zFar)
{
    GLfloat yScale = tan((DEG2RAD * FOV) / 2);

    Matrix4 Result = identity();

    Result[0] = 1 / (ASPECT * yScale);
    Result[1] = 0.0f;
    Result[2] = 0.0f;
    Result[3] = 0.0f;

    Result[4] = 0.0f;
    Result[5] = 1 / yScale;
    Result[6] = 0.0f;
    Result[7] = 0.0f;

    Result[8]  = 0.0f;
    Result[9]  = 0.0f;
    Result[10] = -(zFar + zNear) / (zFar - zNear);
    Result[11] = -1.0f;

    Result[12] = 0.0f;
    Result[13] = 0.0f;
    Result[14] = -(2 * zFar * zNear) / (zFar - zNear);
    Result[15] = 0.0f;

    Result.transpose();

    return Result;
}

Matrix4 Matrix4::orthogonal
(
    const GLfloat left, const GLfloat right,
    const GLfloat bottom, const GLfloat top,
    const GLfloat zNear, const GLfloat zFar
)
{
    Matrix4 ortho;
    ortho[0] = 2 / (right - left);
    ortho[1] = 0;
    ortho[2] = 0;
    ortho[3] = 0;

    ortho[4] = 0;
    ortho[5] = 2 / (top - bottom);
    ortho[6] = 0;
    ortho[7] = 0;

    ortho[8] = 0;
    ortho[9] = 0;
    ortho[10] = -2 / (zFar - zNear);
    ortho[11] = 0;

    ortho[12] = -((right + left) / (right - left));
    ortho[13] = -((top + bottom) / (top - bottom));
    ortho[14] = -((zFar + zNear) / (zFar - zNear));
    ortho[15] = 1;

    ortho.transpose();

    return ortho;
}

Matrix4 Matrix4::lookAt(Vector3 const &eye, Vector3 const &center, Vector3 const &up)
{
    Vector3 const f(normalize(center - eye));
    Vector3 const s(normalize(cross(f, up)));
    Vector3 const u(cross(s, f));

    mat4x4 Result;

    Result[0] = s.x;           Result[4] = u.x;           Result[8]  = f.x;          Result[12] = 0;
    Result[1] = s.y;           Result[5] = u.y;           Result[9]  = f.y;          Result[13] = 0;
    Result[2] = s.z;           Result[6] = u.z;           Result[10] = f.z;          Result[14] = 0;
    Result[3] = -dot(s, eye);  Result[7] = -dot(u, eye);  Result[11] = -dot(f, eye); Result[15] = 1;

    Result.transpose();

    return Result;
}
