#include "Input.h"
#include <Windows.h>

Input* Input::instance = nullptr;

Input::Input()
{
	instance = this;
}

Input& Input::Get()
{
	return *instance;
}

void Input::ProcessInput()
{
	// 키 입력 확인
	for (int ix = 0; ix < 255; ++ix)
	{
		keyStates[ix].isKeyDown = GetAsyncKeyState(ix) & 0x8000;
	}

}

void Input::SavePreviousKeyStates()
{
	// 현재 프레임의 입력을 기록
	for (int ix = 0; ix < 255; ++ix)
	{
		keyStates[ix].previousKeyDown = keyStates[ix].isKeyDown;
		keyStates[ix].isKeyDown = false;
	}
}


bool Input::GetKey(int keyCode) const
{
	return keyStates[keyCode].isKeyDown;
}

bool Input::GetKeyDown(int keyCode) const
{
	return keyStates[keyCode].isKeyDown && !keyStates[keyCode].previousKeyDown;
}

bool Input::GetKeyUp(int keyCode) const
{
	return !keyStates[keyCode].isKeyDown && keyStates[keyCode].previousKeyDown;
}
