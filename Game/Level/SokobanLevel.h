#pragma once

#include "Level/Level.h"
#include "Interface/ICanPlayerMove.h"

class SokobanLevel : public Level, public ICanPlayerMove
{
	RTTI_DECLARATIONS(SokobanLevel, Level)

public:
	SokobanLevel();

	virtual void Tick(float dletaTime) override;
	virtual void Render()override;

	virtual bool CanPlayerMove(const Vector2& curPosition, const Vector2& newPosition) override;

private:
	// 맵 파일 읽어서 게임 객체 생성하는 함수
	void ReadMapFile(const char* filename);
	// 게임 클리어 확인 함수
	bool CheckGameClear();

private:
	int targetScore = 0;
	bool isGameClear = false;
};