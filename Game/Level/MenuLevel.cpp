#include "MenuLevel.h"
#include "Game/Game.h"
#include "Utils/Utils.h"
#include "Input.h"

MenuLevel::MenuLevel()
{
	items.emplace_back(new MenuItem("Resume Game", []() {Game::Get().ToggleMenu(); }));
	items.emplace_back(new MenuItem("Quit Game", []() {Game::Get().Quit(); }));

	itemCount = static_cast<int>(items.size());
}

MenuLevel::~MenuLevel()
{
	for (MenuItem* item : items)
	{
		SafeDelete(item);
	}
	items.clear();
}

void MenuLevel::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	if (Input::Get().GetKeyDown(VK_UP))
	{
		currentIndex = (currentIndex - 1 + itemCount) % itemCount;
	}
	if (Input::Get().GetKeyDown(VK_DOWN))
	{
		currentIndex = (currentIndex + 1) % itemCount;
	}
	if (Input::Get().GetKeyDown(VK_RETURN))
	{
		items[currentIndex]->onSelectedCallBack();
	}

	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		QuitGame();
	}
}

void MenuLevel::Render()
{
	Super::Render();

	// 색상 및 좌표 정리
	Utils::SetConsolePosition({ 0,0 });
	Utils::SetConsoleColor(static_cast<WORD>(unselectedColor));

	// 메뉴 제목 출력
	std::cout << "Sokoban Game\n\n";

	// 메뉴 아이템 렌더링
	for (int i = 0; i < itemCount; ++i)
	{
		// 아이템 색상 확인
		Color textColor = (i == currentIndex) ? selectedColor : unselectedColor;
	
		// 색상 설정
		Utils::SetConsoleColor(static_cast<WORD>(textColor));

		// 메뉴 텍스트 출력
		std::cout << items[i]->menuText << '\n';
	}
}
