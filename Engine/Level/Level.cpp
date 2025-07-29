#include "Level.h"
#include "Actor/Actor.h"
#include "Input.h"
#include "Engine.h"
#include <Windows.h>

Level::Level()
{
}

Level::~Level()
{
	// 메모리 해제
	for (Actor* actor : actors)
	{
		SafeDelete(actor);
	}

	// std::vector 정리
	actors.clear();
}

void Level::AddActor(Actor* newActor)
{
	 // TODO : 예외 처리 필요 (중복확인)
	newActor->SetOwner(this);
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
	// 창 종료 확인
	QuitGame();

	for (Actor* const actor : actors)
	{
		actor->Tick(deltaTime);
	}
}

void Level::Render()
{
	SortActorsBySortingOrder();
	
	// Render Path
	for (Actor* const actor : actors)
	{
		// 깊이 검사 (같은 위치에 정렬 순서가 높은 액터가 있는지 확인)
		Actor* searchActor = nullptr;
		for (Actor* const otherActor : actors)
		{
			if (actor == otherActor)
				continue;

			if (actor->Position() == otherActor->Position()
				&& actor->sortingOrder < otherActor->sortingOrder)
			{
				searchActor = otherActor;
				break;
			}
		}
		
		// 위치가 같고 정렬 우선순위가 더 높은 액터가 하나라도 있으면 그리지 않는다.
		if (searchActor)
		{
			continue;
		}

		//그리기 전에 정렬 순서 기준으로 재배치
		actor->Render();
	}
}

void Level::SortActorsBySortingOrder()
{
	// Bubble Sort
	for (int i = 0; i < (int)actors.size(); ++i)
	{
		for (int j = 0; j < (int)actors.size()-1; ++j)
		{
			if (actors[j]->sortingOrder > actors[j + 1]->sortingOrder)
			{
				std::swap(actors[j], actors[j + 1]);
			}
		}
	}
}

void Level::QuitGame()
{
	// 입력처리
	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		Engine::Get().Quit();
		return;
	}
}
