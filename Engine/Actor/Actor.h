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
	Blue			= 0x0001,
	Green			= 0x0002,
	Red				= 0x0004,
	White			= Blue | Green | Red,
	Intensity	= 0x0008
};


class Engine_API Actor : public RTTI
{
	friend class Level;

	RTTI_DECLARATIONS(Actor,RTTI)

public:
	Actor(
		const char image = ' '
		, Color color = Color::White
		, const Vector2& position = Vector2::Zero
	);
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

	// Sorting Order 설정
	void SetSortingOrder(unsigned int sortingOrder);
	inline int GetSortingOrder();
private:
	// 개체의 위치
	Vector2 position;
	// 텍스트 색상
	Color color = Color::White;
	// 그릴 값
	char image = ' ';
	// Begin Play 호출 확인
	bool hasBeganPlay = false;
	// 정렬 순서
	unsigned int sortingOrder = 0;
};