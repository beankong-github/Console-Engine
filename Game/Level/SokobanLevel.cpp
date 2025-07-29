#include "SokobanLevel.h"
#include <iostream>
#include "Math/Vector2.h"
#include "Utils/Utils.h"
#include "Input.h"
#include "Game/Game.h"

// Actors
#include "Actor/Player.h"
#include "Actor/Ground.h"
#include "Actor/Wall.h"
#include "Actor/Box.h"
#include "Actor/Target.h"

SokobanLevel::SokobanLevel()
{
	ReadMapFile("Map.txt");
}

void SokobanLevel::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		Game::Get().ToggleMenu();
	}
}

void SokobanLevel::Render()
{
	Super::Render();

	if (isGameClear)
	{
		Utils::SetConsolePosition({ 30, 0 });
		Utils::SetConsoleColor(static_cast<WORD>(Color::Red));
		std::cout << "GameClear";
	}
}

bool SokobanLevel::CanPlayerMove(const Vector2& curPosition, const Vector2& newPosition)
{
	if (CheckGameClear())
	{
		isGameClear = true;
		return false;
	}

	// 박스 액터 모으기
	std::vector<Box*> boxActors;
	for (Actor* const actor : actors)
	{
		Box* box = actor->As<Box>();
		if (box)
		{
			boxActors.emplace_back(box);
		}
	}

	// 이동하려는 위치에 박스가 있는지 확인
	Box* searchBox = nullptr;
	for (Box* const boxActor : boxActors)
	{
		// 플레이어가 이동하려는 위치와 박스의 위치가 같은지 비교
		if (boxActor->Position() == newPosition)
		{
			searchBox = boxActor;
			break;
		}
	}

	// 이동하려는 위치에 박스가 있는 경우
	if (searchBox)
	{
		// 플레이어 이동 방향
		Vector2 direction = newPosition - curPosition;
		// 박스의 다음 위치
		Vector2 nextBoxPos = searchBox->Position() + direction;

		for (Box* const otherBox : boxActors)
		{
			if (otherBox == searchBox)
				continue;

			// #1 : 박스를 이동시키려는 위치에 다른 박스가 또 있는지 확인
			if (otherBox->Position() == nextBoxPos)
			{
				return false;
			}
		}

		for (Actor* const actor : actors)
		{
			// #2 : 박스를 이동시키려는 위치에 벽이 있는지 확인
			if (actor->Position() == nextBoxPos)
			{
				if (actor->As<Wall>())
				{
					return false;
				}
				// #3 : 박스 밀기 (박스를 이동시키려는 위치에 Ground, Target)
				if (actor->As<Ground>() || actor->As<Target>())
				{
					searchBox->SetPosition(nextBoxPos);
					
					CheckGameClear();
				}
				return true;
			}
		}

	}

	// 이동려는 위치에 박스가 없는 경우
	for (Actor* const actor : actors)
	{
		if (actor->Position() == newPosition)
		{
			// 벽이면 이동 불가
			if (actor->As<Wall>())
				return false;

			// 벽이 아니면 이동 가능!
			return true;
		}
	}

	// ???
	return false;
}

void SokobanLevel::ReadMapFile(const char* filename)
{
	// 최종 에셋 경로 완성
	char filepath[256] = {};
	sprintf_s(filepath, 256, "../Assets/%s", filename);

	FILE* file = nullptr;
	fopen_s(&file, filepath, "rt");

	if (file == nullptr)
	{
		__debugbreak;
		std::cout << "맵 파일 읽기 실패. : " << filepath << '\n';
		return;
	}

	// 파싱
	fseek(file, 0, SEEK_END);
	size_t fileSize = ftell(file);
	rewind(file);

	char* buffer = new char[fileSize + 1];
	//buffer[fileSize] = '\0';
	memset(buffer, 0, fileSize + 1);
	size_t readSize = fread(buffer, sizeof(char), fileSize, file);
	
	//if (fileSize != readSize)
	//{
	//	std::cout << "fileSize is not matched with readSize\n" << std::endl;
	//}
	
	// 배열 순회 인덱스
	int index = 0;
	// 문자열 길이 값
	int size = (int)readSize;
	// x, y 좌표
	Vector2 Position;

	while (index < size)
	{
		// 맵 문자 확인
		char mapCharacter = buffer[index++];
	
		if (mapCharacter == '\n')
		{
			Position.x = 0;
			++Position.y;
			
			// TODO  TEST - 삭제
			// std::cout << '\n';
			continue;
		}

		switch (mapCharacter)
		{
		case'1':
		case'#':
		{
			AddActor(new Wall (Position));
			//std::cout << "#";
		}
		break;
		case'.':
		{
			AddActor(new Ground(Position));

			//std::cout << ".";
		}
		break;
		case'p':
		{
			AddActor(new Ground(Position));
			AddActor(new Player(Position));
			//std::cout << "p";
		}
		break;
		case'b':
		{
			AddActor(new Ground(Position));
			AddActor(new Box(Position));
			//std::cout << "b";
		}
		break;
		case't':
		{
			AddActor(new Target(Position));
			++targetScore;
			//std::cout << "t";
		}
		break;
		}
	
		// x 좌표 증가
		++Position.x;
	}
	
	// 버퍼 해제
	delete[] buffer;

	fclose(file);


}

bool SokobanLevel::CheckGameClear()
{
	// 박스가 타겟 위치에 모두 옮겨졌는지 확인
	int currentScore = 0;
	
	std::vector<Actor*> targetActors;
	std::vector<Actor*> boxActors;
	for (Actor* const actor : actors)
	{
		if (actor->As<Target>())
		{
			targetActors.emplace_back(actor);
		}
		else if (actor->As<Box>())
		{
			boxActors.emplace_back(actor);
		}
	}

	// 박스와 타겟 액터 위치 비교
	for (Actor* const targetActor : targetActors)
	{
		for (Actor* const boxActor : boxActors)
		{
			if (targetActor->Position() == boxActor->Position())
			{
				++currentScore;
			}
		}
	}


	return currentScore == targetScore;
}
