#include "Actor.h"
#include <Windows.h>
#include <iostream>

Actor::Actor(const char image, Color color)
	: image(image)
	, color(color)
{

}

Actor::~Actor()
{
}

// 이벤트 함수
// 최초  
 void Actor::BeginPlay()
{
	 hasBeganPlay = true;

	
 }
// 매 프레임 호출
 void Actor::Tick(float deltaTime)
{
 }

// 그리기
 void Actor::Render()
{
	 // Win32 API
	 // 커서 위치 이동
	 static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	 // 커서 위치 이동
	 COORD coordinate;
	 coordinate.X = (short)position.x;
	 coordinate.Y = (short)position.y;
	 SetConsoleCursorPosition(handle, coordinate);
	
	 // 색상 변환F
	 SetConsoleTextAttribute(handle , color);

	// 그리기
	 std::cout << image;
 }

 void Actor::SetPosition(const Vector2& newPosition)
 {
	 // 커서 위치 이동
	 static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	 // 커서 위치 이동
	 COORD coordinate;
	 coordinate.X = (short)position.x;
	 coordinate.Y = (short)position.y;
	 SetConsoleCursorPosition(handle, coordinate);

	 // 그리기
	 std::cout << ' ';

	 position = newPosition;
 }

 inline Vector2 Actor::Position() const
 {
	 return position;
 }
