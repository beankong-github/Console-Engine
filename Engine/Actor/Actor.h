#pragma once
#include "Core.h"
#include "Math/Vector2.h"
#include "RTTI.h"

// TODO : 250723
// 위치
// 콘솔에 그리기
// 엔진의 이벤트 함수 호출 (Begin / Tick / Render)

enum Color
{
	BLUE				= 0x0001,
	GREEN			= 0x0002,
	RED				= 0x0004,
	WHITE			= BLUE | GREEN | BLUE,
	INTENSITY	= 0x0008
};


class Engine_API Actor : public RTTI
{
	RTTI_DECLARATIONS(Actor,RTTI)

public:
	Actor(const char image = ' ', Color color = Color::WHITE);
	virtual ~Actor();

	// 이벤트 함수
	// 객체 생애주기 최초 1회 실행 (초기화) 
	virtual void BeginPlay();
	// 매 프레임 호출
	virtual void Tick(float deltaTime);
	// 그리기
	virtual void Render();
	// BeginPlay 호출 여부
	inline bool HasBeganPlay() const { return hasBeganPlay; }

	// 위치를 설정하고 값을 읽는 함수
	void SetPosition(const Vector2& newPosition);
	inline Vector2 Position() const;

private:
	Vector2 position;
	Color color = Color::WHITE;
	char image = ' ';
	bool hasBeganPlay = false;
};