#pragma once
#include "Core.h"
class Engine_API Engine
{
public:
	// 생성자
	Engine();

	// 소멸자
	~Engine();
	
	// 엔진 실행 함수
	void Run();

	void Quit();

private:
	void  ProcessInput();
	void Update(float deltaTime = 0.f);
	void Render();

private:
	bool isQuit = false;
};