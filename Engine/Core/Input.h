#pragma once
#include "Core.h"

class Engine_API Input
{
	// 칭구 칭긔
	friend class Engine;

	// 키입력 확인을 위한 구조체 선언
	struct KeyState
	{
		// 현재 프레임에 키가 눌렸는지
		bool isKeyDown = false;
		// 이전 프레임에 키가 눌렸는지
		bool previousKeyDown = false;
	};

public:
	Input();

	static Input& Get();

	// 키 확인 함수
	inline bool GetKey(int keyCode) const;
	inline bool GetKeyDown(int keyCode)const;
	inline bool GetKeyUp(int keyCode) const;

private:
	// 키 입력 처리
	void  ProcessInput();
	void SavePreviousKeyStates();

private:
	// 싱글톤 인스턴스
	static Input* instance;
	
	// 키 입력 정보 관리 
	KeyState keyStates[255] = {};

};