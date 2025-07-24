#include "TestActor.h"
#include <iostream>
#include "Level/Level.h"
void TestActor::Tick(float deltaTime)
{
	//Actor::Tick(deltaTime);
	Super::Tick(deltaTime);

	Level testLevel;

	std::cout << "TestActor Type ID Class : " << TypeIdClass() << '\n';
	std::cout << "TestActor Type ID Instance : " << TypeIdInstance() << '\n';
	std::cout << "Actor Type ID Class : " << Super::TypeIdClass() << '\n';
	std::cout << "Actor Type ID Instance : " << Super::TypeIdInstance() << '\n';

	auto instance = TypeIdInstance();
	auto typeclass = TypeIdClass();
	std::cout << "TestActor Type ID Class : " << typeclass << '\n';
	std::cout << "TestActor Type ID Instance : " << instance << '\n';

	size_t A = 30;
	size_t AddressClass = reinterpret_cast<size_t>(& A);
	const size_t& AddressInstnace = AddressClass;

	std::cout << "Address Class  : " << AddressClass << '\n';
	std::cout << "Address Instnace  : " << AddressInstnace << '\n';


	std::cout << "Are you Actor ?  : " << Is(Super::TypeIdInstance()) << '\n';
	std::cout << "Are you Level ?   :" << Is(testLevel.TypeIdInstance()) << '\n';


	std::cout << "나는 테스트 액터다~~~~~~~~~! FPS : " << (1.f / deltaTime) << '\n';
}
