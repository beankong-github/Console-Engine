#include "Engine.h"
#include <iostream>
#include <Windows.h>

// 윈도우즈
// 단순 입력 처리
// ✅타이머 (시간 계산)

Engine::Engine()
{
}

Engine::~Engine()
{
}

void Engine::Run()
{

	// 밀리 세컨드 단위로 현재 시간을 알려준다.
	//float currentTime = timeGetTime();
	LARGE_INTEGER currentTime;
	LARGE_INTEGER previousTime;
	QueryPerformanceCounter(&currentTime);
	previousTime = currentTime;

	// 하드웨어 시계의 정밀도 가져오기
	// 나중에 초(second)로 변환하기 위해
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);

	// 타겟 프레임 지정
	float targetFrameRate = 60.f;
	float oneFrameTime = 1.0f / targetFrameRate;

	// GameLoop
	while (true)
	{
		if (isQuit)
		{
			std::cout << "Shutdown the engine" << std::endl;
			break;
		}
		// 프레임 시간 계산
		// (현재 시간 - 이전 시간) / 주파수 => 초단위
		QueryPerformanceCounter(&currentTime);
		float deltaTime = (currentTime .QuadPart- previousTime.QuadPart) / (float)frequency.QuadPart;

		ProcessInput();

		// 프레임 제한
		if (deltaTime >= oneFrameTime)
		{
			Update(deltaTime);
			Render();

			// 시간 업데이트
			previousTime = currentTime;
		}
	}
}

void Engine::Quit()
{
	isQuit = true;
}

void Engine::ProcessInput()
{
	// ESC 키 눌림 확인
	if (GetAsyncKeyState(VK_ESCAPE)&0x8000)
	{
		Quit();
	}
}

void Engine::Update(float deltaTime)
{
	std::cout << "FPS : " << 1.f / deltaTime << std::endl;
}

void Engine::Render()
{
}
