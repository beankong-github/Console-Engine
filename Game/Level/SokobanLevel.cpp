#include "SokobanLevel.h"
#include <iostream>
#include "Math/Vector2.h"

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

bool SokobanLevel::CanPlayerMove(const Vector2& curPosition, const Vector2& newPosition)
{
	return true;
}

void SokobanLevel::ReadMapFile(const char* filename)
{
	// 최종 에셋 경로 완성
	char filepath[256] = {};
	sprintf_s(filepath, 256, "../Assets/%s", filename);

	FILE* file = nullptr;
	fopen_s(&file, filepath, "rb");

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
	
	if (fileSize != readSize)
	{
		std::cout << "fileSize is not matched with readSize\n" << std::endl;
	}
	
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
			std::cout << '\n';
			continue;
		}

		switch (mapCharacter)
		{
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
