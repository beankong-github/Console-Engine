#include "Player.h"
#include "windows.h"
#include "Engine.h"
#include "Input.h"

Player::Player(const Vector2& position)
	: Actor('P', Color::Red, position)
{
	// 정렬 순서
	SetSortingOrder(3);
}

void Player::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	
	if (Input::Get().GetKeyDown(VK_RIGHT))
	{
		Vector2 position = Position();
		position.x += 1;
		SetPosition(position);
	}
	if (Input::Get().GetKeyDown(VK_LEFT))
	{
		Vector2 position = Position();
		position.x -= 1;
		SetPosition(position);
	}
	if (Input::Get().GetKeyDown(VK_UP))
	{
		Vector2 position = Position();
		position.y -= 1;
		SetPosition(position);
	}
	if (Input::Get().GetKeyDown(VK_DOWN))
	{
		Vector2 position = Position();
		position.y += 1;
		SetPosition(position);
	}
}

