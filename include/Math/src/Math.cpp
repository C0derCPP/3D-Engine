#include <Math/Math.h>

float Math::dot(Vector3 a, Vector3 b)
{
    return (a.x*b.x + a.y*b.y + a.z*b.z);
}

float Math::det(float a, float b, float c, float d)
{
    return a * d - b * c;
}

Vector3 Math::cross(Vector3 a, Vector3 b)
{
    return Vector3(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
}

double Math::sqrt(double num)
{
    double x0 = std::log(num);
    double x1 = (x0 - (((x0 * x0))/(2* x0)));
    x0 = x1;

    do{
        x1 = (x0 - (((x0 * x0) - num)/(2* x0)));
        x0 = x1;
    }
    while ((num / x1)+0.0001 < x0);

    return x1;
}

float Math::magnitude(Vector3 v)
{
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}
float Math::magnitude(Vector4 v)
{
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
}

Vector3 Math::normalize(Vector3 vec3) {
    const float EPSILON = 0.00001f;
    float xxyyzz = vec3.x*vec3.x + vec3.y*vec3.y + vec3.z*vec3.z;
    if(xxyyzz < EPSILON)
        return vec3;

    float invLength = sqrtf(xxyyzz);
    vec3.x = vec3.x / invLength;
    vec3.y = vec3.y / invLength;
    vec3.z = vec3.z / invLength;
    return vec3;
}

Vector4 Math::normalize(Vector4 vec4) {
    const float EPSILON = 0.00001f;
    float xxyyzz = vec4.x*vec4.x + vec4.y*vec4.y + vec4.z*vec4.z + vec4.w * vec4.w;
    if(xxyyzz < EPSILON)
        return vec4;

    float invLength = sqrtf(xxyyzz);
    vec4.x = vec4.x / invLength;
    vec4.y = vec4.y / invLength;
    vec4.z = vec4.z / invLength;
    return vec4;
}

