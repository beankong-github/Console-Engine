#pragma once
#include "Core.h"
#include "Input.h"

class Level;
class Engine_API Engine
{
public:
	// 생성자
	Engine();

	// 소멸자
	virtual ~Engine();
	
	static Engine& Get();

	// 엔진 실행 함수
	void Run();

	// 레벨 추가
	void AddLevel(Level* newLevel);

	// 메모리 해제 함수
	virtual void CleanUp();

	// 종료 함수
	void Quit();

private:
	void BeginPlay();
	void Tick(float deltaTime = 0.f);
	void Render();

protected:
	static Engine* instance;
	static int count;

	// 엔진 종료 플래그
	bool isQuit = false;

	// 입력 관리자
	Input input;

	// 메인 레벨
	Level* mainLevel = nullptr;
};