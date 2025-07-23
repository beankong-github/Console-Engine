#include "Actor.h"

Actor::Actor()
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
}