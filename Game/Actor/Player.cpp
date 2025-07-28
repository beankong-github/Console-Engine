#include "Player.h"

Player::Player(const Vector2& position)
	: Actor('P', Color::Red, position)
{

}

void Player::Tick(float deltaTime)
{
	Super::Tick(deltaTime);


	// TODO : 입력 처리
}

