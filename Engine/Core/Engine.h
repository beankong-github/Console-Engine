#pragma once
#include "Core.h"

/* TODO : 250723 
	✅ 키 입력 관리 (KeyState 배열)
	✅ 입력 확인 함수 (GetKeyDown, GetKeyUp)
	✅ Actor 추가
	✅ 이벤트 함수 추가 (BeginPlay, Tick, Render)
	✅ 레벨 추가 (가상 공간에 배치된 물제 관리 객체)
*/
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
	// 엔진 종료 플래그
	bool isQuit = false;

	// 키 입력 정보 관리 
	KeyState keyStates[255] = {};

	// 메인 레벨
	Level* mainLevel = nullptr;
};