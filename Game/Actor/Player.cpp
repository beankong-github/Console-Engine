#include "Player.h"
#include "windows.h"
#include "Engine.h"
#include "Input.h"
#include "Interface/ICanPlayerMove.h"
#include "Level/Level.h"
#include <iostream>

Player::Player(const Vector2& position)
	: Actor('P', Color::Red, position)
{
	// 정렬 순서
	SetSortingOrder(3);
}

void Player::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner())
	{
		canPlayerMoveInterface = dynamic_cast<ICanPlayerMove*>(GetOwner());

		if (!canPlayerMoveInterface)
		{
			std::cout << "오너 레벨 -> ICanPlayerMove 캐스팅 실패";
		}
	}
}

void Player::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	
	Vector2 curPos = Position();
	Vector2 nextPos = curPos;

	if (Input::Get().GetKeyDown(VK_RIGHT))
	{
		nextPos.x += 1;
		if(canPlayerMoveInterface->CanPlayerMove(curPos, nextPos))
			SetPosition(nextPos);
	}
	if (Input::Get().GetKeyDown(VK_LEFT))
	{
		nextPos.x -= 1;
		if (canPlayerMoveInterface->CanPlayerMove(curPos, nextPos))
			SetPosition(nextPos);
	}
	if (Input::Get().GetKeyDown(VK_UP))
	{
		nextPos.y -= 1;
		if (canPlayerMoveInterface->CanPlayerMove(curPos, nextPos))
			SetPosition(nextPos);
	}
	if (Input::Get().GetKeyDown(VK_DOWN))
	{
		nextPos.y += 1;
		if (canPlayerMoveInterface->CanPlayerMove(curPos, nextPos))
			SetPosition(nextPos);
	}
}

