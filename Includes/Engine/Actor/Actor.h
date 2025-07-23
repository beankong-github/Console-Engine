#pragma once
#include "Core.h"
#include "Math/Vector2.h"

// TODO : 250723
// 위치
// 콘솔에 그리기
// 엔진의 이벤트 함수 호출 (Begin / Tick / Render)

class Engine_API Actor
{

public:
	Actor();
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

private:
	Vector2 position;
	char image = ' ';
	bool hasBeganPlay = false;
};