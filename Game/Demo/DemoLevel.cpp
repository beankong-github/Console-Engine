#include "DemoLevel.h"
#include "TestActor.h"
#include <iostream>

DemoLevel::DemoLevel()
{
	AddActor(new TestActor());

	// 테스트로 맵 파일 읽기
	FILE* file = nullptr;
	fopen_s(&file, "../Assets/Map.txt", "rb");

	// 예외 처리
	if (file == nullptr)
	{
		__debugbreak();
		std::cout << "Faile to open Map.txt file\n";
			return;
	}

	// 파일 크기 확인
	// 파일 위치 화인
	fseek(file, 0, SEEK_END);
	// 이동한 지점의 위치 반환
	size_t filesize = ftell(file);
	// 파일 위치 커서 되돌리기
	fseek(file, 0, SEEK_SET);
	rewind(file);

	// 데이터 저장을 위한 버퍼 할당
	//	char* buffer = new char[filesize + 1];
	char buffer[256] = {};
	while (!feof(file))
	{
		fgets(buffer, 256, file);
		// 파일 한 줄 글자 길이 읽기
		int lineLength = (int)strlen(buffer);
		// Parsing
		for (int i = 0; i < lineLength; ++i)
		{
			char mapCharacter = buffer[i];

			switch (mapCharacter)
			{
				case '#':
				{
					std::cout << '#';
				}
				break;
				case '.':
				{
					std::cout << '.';
				}
				break;
				case 'p':
				{
					std::cout << 'p';
				}
				break;
				case 'b':
				{
					std::cout << 'b';
				}
				break;
				case 't':
				{
					std::cout << 't';
				}
				break;
			}
	}
		std::cout << '\n';
	}

	// 파일닫기
	fclose(file);
}

void DemoLevel::BeginPlay()
{
	//std::cout << "데모 레벨 BeginPlay 호출!\n";
}
