#include <iomanip>
#include <Math/Vector.h>


/////////////////////////////////////////////////////////////////////////////////
//Vector2D
/////////////////////////////////////////////////////////////////////////////////
Vector2::Vector2()
{
    //constructor
}

void Vector2::set(GLfloat x, GLfloat y)
{
    this->x = x;
    this->y = y;
}

Vector2 Vector2::operator= (const Vector2& vec)
{
    return Vector2(x = vec.x, y = vec.y);
}

Vector2 Vector2::operator+ (const Vector2& vec)const
{
    return Vector2(x + vec.x, y + vec.y);
}

Vector2 Vector2::operator- (const Vector2& vec)const
{
    return Vector2(x - vec.x, y - vec.y);
}

Vector2 Vector2::operator/ (const Vector2& vec)const
{
    return Vector2(x / vec.x, y / vec.y);
}

Vector2 Vector2::operator/ (const float& num)const
{
    return Vector2(x / num, y / num);
}

Vector2 Vector2::operator* (const Vector2& vec)const
{
    return Vector2(x * vec.x, y * vec.y);
}

Vector2 Vector2::operator* (const float& num)const
{
    return Vector2(x * num, y * num);
}

std::ostream& operator<< (std::ostream& output, const Vector2& vec)
{
    return output << std::fixed << std::setprecision(5) << "[" << vec.x << ", " << vec.y << "]";
}


/////////////////////////////////////////////////////////////////////////////////
//Vector3D
/////////////////////////////////////////////////////////////////////////////////
Vector3::Vector3()
{
    //constructor
}

void Vector3::set(GLfloat x, GLfloat y, GLfloat z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3 Vector3::operator= (const Vector3& vec)
{
    return Vector3(x = vec.x, y = vec.y, z = vec.z);
}

Vector3 Vector3::operator+ (const Vector3& vec)const
{
    return Vector3(x + vec.x, y + vec.y, z + vec.z);
}

Vector3 Vector3::operator- (const Vector3& vec)const
{
    return Vector3(x - vec.x, y - vec.y, z - vec.z);
}

Vector3 Vector3::operator/ (const Vector3& vec)const
{
    return Vector3(x / vec.x, y / vec.y, z / vec.z);
}

Vector3 Vector3::operator/ (const float& num)const
{
    return Vector3(x / num, y / num, z / num);
}

Vector3 Vector3::operator* (const Vector3& vec)const
{
    return Vector3(x * vec.x, y * vec.y, z * vec.z);
}

Vector3 Vector3::operator* (const float& num)const
{
    return Vector3(x * num, y * num, z * num);
}

std::ostream& operator<< (std::ostream& output, const Vector3& vec)
{
    return output << std::fixed << std::setprecision(5) << "[" << vec.x << ", " << vec.y << ", " << vec.z << "]";
}


/////////////////////////////////////////////////////////////////////////////////
//Vector4D
/////////////////////////////////////////////////////////////////////////////////
void Vector4::set(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

Vector4 Vector4::operator= (const Vector4& vec)
{
    return Vector4(x = vec.x, y = vec.y, z = vec.z, w = vec.w);
}

Vector4 Vector4::operator+ (const Vector4& vec)const
{
    return Vector4(x + vec.x, y + vec.y, z + vec.z, w + vec.w);
}

Vector4 Vector4::operator- (const Vector4& vec)const
{
    return Vector4(x - vec.x, y - vec.y, z - vec.z, w - vec.w);
}

Vector4 Vector4::operator/ (const Vector4& vec)const
{
    return Vector4(x / vec.x, y / vec.y, z / vec.z, w / vec.w);
}

Vector4 Vector4::operator/ (const float& num)const
{
    return Vector4(x / num, y / num, z / num, w / num);
}

Vector4 Vector4::operator* (const Vector4& vec)const
{
    return Vector4(x * vec.x, y * vec.y, z * vec.z, w * vec.w);
}

Vector4 Vector4::operator* (const float& num)const
{
    return Vector4(x * num, y * num, z * num, w * num);
}

std::ostream& operator<< (std::ostream& output, const Vector4& vec)
{
    return output << std::fixed << std::setprecision(5) << "[" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << "]";
}
