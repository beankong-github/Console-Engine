#include "Target.h"

Target::Target(const Vector2& position)
	:Actor('T', Color::Blue, position)
{
	// 정렬 순서
	SetSortingOrder(1);
}
