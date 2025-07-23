#include "DemoLevel.h"
#include "TestActor.h"
#include <iostream>

DemoLevel::DemoLevel()
{
	AddActor(new TestActor());
}

void DemoLevel::BeginPlay()
{
	std::cout << "데모 레벨 BeginPlay 호출!\n";
}
