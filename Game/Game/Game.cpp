#include "Game.h"
#include "Core.h"
#include "Level/SokobanLevel.h"
#include "Level/MenuLevel.h"

Game* Game::instance = nullptr;

Game::Game()
{
	instance = this;

	// 메인 레벨 추가
	AddLevel(new SokobanLevel());

	// 메뉴 레벨
	menuLevel = new MenuLevel();

	ToggleMenu();
}

Game::~Game()
{
	CleanUp();
}

void Game::ToggleMenu()
{
	// 화면 정리
	system("cls");

	// 토글 처리
	showMenu = !showMenu;

	if (showMenu)
	{
		backLevel = mainLevel;
		mainLevel = menuLevel;
	}
	else
	{
		mainLevel = backLevel;

	}
}

void Game::CleanUp()
{
	// 이떄는 main Level -> menu level
	if (showMenu)
	{
		// 게임 레벨 제거
		SafeDelete(backLevel);
		mainLevel = nullptr;
	}
	
	SafeDelete(menuLevel);
	Engine::CleanUp();
}

Game& Game::Get()
{
	return *instance;
}

