#include "Engine.h"
#include <iostream>
#include <Windows.h>
#include "Level/Level.h"

// 정적 변수 초기화
Engine* Engine::instance = nullptr;

Engine::Engine()
{
	instance = this;

	// 콘솔 커서 끄기	
	CONSOLE_CURSOR_INFO info;
	info.bVisible = false;
	info.dwSize = 1;
	SetConsoleCursorInfo(
		GetStdHandle(STD_OUTPUT_HANDLE)
		, &info
	);
}

Engine::~Engine()
{
	if (mainLevel)
	{
		delete mainLevel;
		mainLevel = nullptr;
	}
}

Engine& Engine::Get()
{
	// TODO: insert return statement here
	return *instance;
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
			// 정리
			SetConsoleTextAttribute(
				GetStdHandle(STD_OUTPUT_HANDLE)
				, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED
			);

			std::cout << "\nShutdown the engine" << std::endl;
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
			BeginPlay();
			Tick(deltaTime);
			Render();

			// 시간 업데이트
			previousTime = currentTime;
		
			// 현재 프레임의 입력을 기록
			for (int ix = 0; ix < 255; ++ix)
			{
				keyStates[ix].previousKeyDown = keyStates[ix].isKeyDown;
				keyStates[ix].isKeyDown = false;
			}
		}
	}

}

void Engine::AddLevel(Level* newLevel)
{
	// 기존 레벨 제거
	if (mainLevel)
	{
		delete mainLevel;
	}
	mainLevel = newLevel;
}

bool Engine::GetKey(int keyCode) const
{
	return keyStates[keyCode].isKeyDown;
}

bool Engine::GetKeyDown(int keyCode) const
{
	return keyStates[keyCode].isKeyDown && !keyStates[keyCode].previousKeyDown;
}

bool Engine::GetKeyUp(int keyCode) const
{
	return !keyStates[keyCode].isKeyDown && keyStates[keyCode].previousKeyDown;
}


void Engine::Quit()
{
	isQuit = true;
}

void Engine::ProcessInput()
{
	// 키 입력 확인
	for (int ix = 0; ix < 255; ++ix)
	{
		keyStates[ix].isKeyDown = GetAsyncKeyState(ix) & 0x8000;
	}

}

void Engine::BeginPlay()
{
	if (mainLevel)
	{
		mainLevel->BeginPlay();
	}
}

void Engine::Tick(float deltaTime)
{
	//std::cout << "FPS : " << 1.f / deltaTime << std::endl;

	//if (GetKeyDown('A'))
	//{
	//	std::cout << "Key Down\n";
	//}
	//if (GetKey('A'))
	//{
	//	std::cout << "Key\n";
	//}
	//if (GetKeyUp('A'))
	//{
	//	std::cout << "Key Up\n";
	//}

	// 레벨 업데이트
	if (mainLevel)
	{
		mainLevel->Tick(deltaTime);
	}

	// ESC 키 눌림 확인
	//if (GetKeyDown(VK_ESCAPE))
	//{
	//	Quit();
	//}
}

void Engine::Render()
{
	// 정리
	SetConsoleTextAttribute(
		GetStdHandle(STD_OUTPUT_HANDLE)
		, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED
	);

	if (mainLevel)
	{
		mainLevel->Render();
	}
}
