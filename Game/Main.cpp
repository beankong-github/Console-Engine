#include <iostream>
#include "Engine.h"
#include "Demo\DemoLevel.h"
#include "Level/SokobanLevel.h"
#include "Game/Game.h"
#include "Level/MenuLevel.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	Game sokoban;
	//engine.AddLevel(new DemoLevel());
	//sokoban.AddLevel(new MenuLevel() /*new SokobanLevel()*/);
	sokoban.Run();
}