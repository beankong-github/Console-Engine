#include "Level.h"
#include "Actor/Actor.h"
Level::Level()
{
}

Level::~Level()
{
}

void Level::AddActor(Actor* newActor)
{
	 // TODO : 예외 처리 필요 (중복확인)
	actors.emplace_back(newActor);
}

// 엔진 이벤트 함수
void Level::BeginPlay()
{
	for (Actor* const actor : actors)
	{
		if (actor->HasBeganPlay())
		{
			continue;
		}
		actor->BeginPlay();
	}
}
void Level::Tick(float deltaTime)
{
	for (Actor* const actor : actors)
	{
		actor->Tick(deltaTime);
	}
}

void Level::Render()
{
	for (Actor* const actor : actors)
	{

		actor->Render();
	}
}
