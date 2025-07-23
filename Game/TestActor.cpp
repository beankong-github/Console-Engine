#include "TestActor.h"
#include <iostream>

void TestActor::Tick(float deltaTime)
{
	Actor::Tick(deltaTime);

	std::cout << "나는 테스트 액터다~~~~~~~~~! FPS : " << (1.f / deltaTime) << '\n';
}
