#include "Vector2.h"
#include <iostream>

 Vector2 Vector2::Zero = Vector2(0,0);
 Vector2 Vector2::One = Vector2(1,1);
 Vector2 Vector2::Up = Vector2(0,1);
 Vector2 Vector2::Right = Vector2(1, 0);

Vector2::Vector2(int x, int y)
    : x(x)
    , y(y)
{
}

Vector2::~Vector2()
{
    if (stringBuffer == nullptr)
        return;

     delete[] stringBuffer;
}

Vector2 Vector2::operator+(const Vector2& other) const
{
    return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator-(const Vector2& other) const
{
    return Vector2(x - other.x, y - other.y);
}

const char* Vector2::ToString()
{
    // (x, y) 형식 문자열로 출력
    if (stringBuffer != nullptr)
    {
        delete[] stringBuffer;
    }

    stringBuffer = new char[1024];
    sprintf_s(stringBuffer, 1024,"(%d, %d)", x, y);
    
    return stringBuffer;
}
