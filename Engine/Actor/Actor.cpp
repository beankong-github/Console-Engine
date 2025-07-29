#include "Actor.h"
#include <Windows.h>
#include <iostream>
#include "Utils/Utils.h"

Actor::Actor(const char image, Color color, const Vector2& position) 
	: image(image)
	, color(color)
	, position(position)
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
	 // 콘솔 출력을 제어하는 핸들 가져오기
	 // static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	 // 커서 위치 이동
	 COORD coordinate;
	 coordinate.X = (short)position.x;
	 coordinate.Y = (short)position.y;
	 Utils::SetConsolePosition(coordinate);
	 //SetConsoleCursorPosition(handle, coordinate);
	
	 // 색상 변환
	//SetConsoleTextAttribute(handle, color);
	 Utils::SetConsoleColor(static_cast<WORD>(color));

	// 그리기
	 std::cout << image;
 }

 void Actor::SetPosition(const Vector2& newPosition)
 {
	 // 콘솔 출력을 제어하는 핸들 가져오기
	 //static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	 // 커서 위치 이동
	 COORD coordinate;
	 coordinate.X = (short)position.x;
	 coordinate.Y = (short)position.y;
	 //SetConsoleCursorPosition(handle, coordinate);
	 Utils::SetConsolePosition(coordinate);

	 // 그리기
	 std::cout << ' ';

	 position = newPosition;
 }

 inline Vector2 Actor::Position() const
 {
	 return position;
 }

 void Actor::SetSortingOrder(unsigned int sortingOrder)
 {
	 this->sortingOrder = sortingOrder;
 }

 inline int Actor::GetSortingOrder()
 {
	 return sortingOrder;
 }
