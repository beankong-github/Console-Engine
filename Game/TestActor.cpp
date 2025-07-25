#include "TestActor.h"
#include <iostream>
#include "Level/Level.h"
#include "Engine.h"
#include <Windows.h>

TestActor::TestActor()
	:Super('O', Color::RED)
{

}

void TestActor::Tick(float deltaTime)
{
	//Actor::Tick(deltaTime);
	Super::Tick(deltaTime);

	// Tick Test
	//std::cout << "나는 테스트 액터다~~~~~~~~~! FPS : " << (1.f / deltaTime) << '\n';
	
	// RTTI Test
	// std::cout << "Are you Actor ?  : " << Is(Super::TypeIdInstance()) << '\n';

	//std::cout << Engine::Get().count;

	if (Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		Engine::Get().Quit();
	}

	if (Engine::Get().GetKey(VK_RIGHT) && Position().x < 30)
	{
		Vector2 position = Position();
		position.x += 1;
		SetPosition(position);
	}	
	if (Engine::Get().GetKey(VK_LEFT) && Position().x > 0)
	{
		Vector2 position = Position();
		position.x -= 1;
		SetPosition(position);
	}	
	if (Engine::Get().GetKey(VK_UP) && Position().y > 0)
	{
		Vector2 position = Position();
		position.y -= 1;
		SetPosition(position);
	}	
	if (Engine::Get().GetKey(VK_DOWN) && Position().y < 20)
	{
		Vector2 position = Position();
		position.y += 1;
		SetPosition(position);
	}
}
