#pragma once
#include "Core.h"

//Todo : 250725
//- Engine 싱글톤 구현

class Level;
class Engine_API Engine
{

	struct KeyState
	{
		// 현재 프레임에 키가 눌렸는지
		bool isKeyDown = false;
		// 이전 프레임에 키가 눌렸는지
		bool previousKeyDown = false;
	};

public:
	// 생성자
	Engine();

	// 소멸자
	~Engine();
	
	static Engine& Get();

	// 엔진 실행 함수
	void Run();

	// 레벨 추가
	void AddLevel(Level* newLevel);


	// 키 확인 함수
	inline bool GetKey(int keyCode) const;
	inline bool GetKeyDown(int keyCode)const;
	inline bool GetKeyUp(int keyCode) const;

	void Quit();

private:
	void  ProcessInput();
	void BeginPlay();
	void Tick(float deltaTime = 0.f);
	void Render();

private:
	static Engine* instance;
	static int count;

	// 엔진 종료 플래그
	bool isQuit = false;

	// 키 입력 정보 관리 
	KeyState keyStates[255] = {};

	// 메인 레벨
	Level* mainLevel = nullptr;
};