#include "Box.h"

Box::Box(const Vector2& position)
	:Actor('B', Color::Green, position)
{
	// 정렬 순서
	SetSortingOrder(2);
}
