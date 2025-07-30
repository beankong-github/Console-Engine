#include "Engine.h"
#include <iostream>
#include <Windows.h>

#include "Level/Level.h"
#include "Utils/Utils.h"
#include "Input.h"

// 정적 변수 초기화
Engine* Engine::instance = nullptr;

// Console 이벤트 발생시 호출 될 콜백 함수
BOOL WINAPI ConsoleMessageProcedure(DWORD CtrlType)
{
	switch (CtrlType)
	{
		case CTRL_CLOSE_EVENT:
		{
			// Engine 메모리 해제
			Engine::Get().CleanUp();
			return true;
		}
		return false;
	}

	return false;
}

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

	// Console 이벤트 발생시 호출 될 콜백 함수 등록
	SetConsoleCtrlHandler(ConsoleMessageProcedure, TRUE);

	// 엔진 설정 로드
	LoadEngineSettings();
}

Engine::~Engine()
{
	CleanUp();
}


Engine& Engine::Get()
{
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
	float targetFrameRate =  settings.framerate == 0.f? 60.f  : settings.framerate;
	float oneFrameTime = 1.0f / targetFrameRate;

	// GameLoop
	while (true)
	{
		if (isQuit)
		{
			// 정리
			Utils::SetConsoleColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
			//SetConsoleTextAttribute(
			//	GetStdHandle(STD_OUTPUT_HANDLE)
			//	, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED
			//);

			std::cout << "\nShutdown the engine" << std::endl;
			break;
		}
		// 프레임 시간 계산
		// (현재 시간 - 이전 시간) / 주파수 => 초단위
		QueryPerformanceCounter(&currentTime);
		float deltaTime = (currentTime .QuadPart- previousTime.QuadPart) / (float)frequency.QuadPart;

		input.ProcessInput();

		// 프레임 제한
		if (deltaTime >= oneFrameTime)
		{
			BeginPlay();
			Tick(deltaTime);
			Render();

			// 제목에 fps 출력
			char title[50] = {};
			sprintf_s(title, 50, "DeltaTime : %f", deltaTime);
			SetConsoleTitleA(title);


			// 시간 업데이트
			previousTime = currentTime;
			
			input.SavePreviousKeyStates();
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

void Engine::CleanUp()
{
	SafeDelete(mainLevel);

	/*if (mainLevel)
	{
		delete mainLevel;
		mainLevel = nullptr;
	}*/
}

void Engine::Quit()
{
	isQuit = true;
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
	Utils::SetConsoleColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
	//SetConsoleTextAttribute(
	//	GetStdHandle(STD_OUTPUT_HANDLE)
	//	, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED
	//);

	if (mainLevel)
	{
		mainLevel->Render();
	}
}

void Engine::LoadEngineSettings()
{
	//엔진 설정 파일 열기
	FILE* file = nullptr;
	fopen_s(&file, "../Settings/EngineSettings.txt", "rt");
	if (file == nullptr)
	{
		std::cout << "Failed to load engine settings.\n";
		__debugbreak;
		return;
	}

	// 로드
	// FP(File Position) 포인터를 가장 뒤로 옮기기
	fseek(file, 0, SEEK_END);
	// 이 위치 구하기
	size_t fileSize = ftell(file);
	// 다시 첫 위치로
	rewind(file); // fseek(file, 0, SEEK_SET);

	// 파일 내용을 저장할 버퍼할당
	char* buffer = new  char[fileSize + 1];
	memset(buffer, 0, fileSize + 1);

	// 내용 읽기
	size_t readSize = fread(buffer, sizeof(char), fileSize, file);

	// 파싱(parsing, 구문해석)
	char* context = nullptr;
	char* token = nullptr;
	token = strtok_s(buffer, "\n", &context);

	// 구문 분석
	while (token != nullptr)
	{
		// 키와 값 분리
		char header[10] = {};

		// 이 함수가 제대로 동작하려면 키와 값 사이의 빈칸이 있어야 함
		sscanf_s(token, "%s", header, 10);

		if (strcmp(header, "framerate") == 0)
		{
			sscanf_s(token, "framerate = %f", &settings.framerate);
		}	
		else if (strcmp(header, "width") == 0)
		{
			sscanf_s(token, "width = %d", &settings.width);
		}
		else if (strcmp(header, "height") == 0)
		{
			sscanf_s(token, "height = %d", &settings.height);
		}

		// 그 다음 줄 분리
		token = strtok_s(nullptr, "\n", &context);

	}

	// 파일 내용 할당 해제
	SafeDeleteArray(buffer);

	// 파일 닫기
	fclose(file);
}
