#include "Wall.h"

Wall::Wall(const Vector2& position)
	:Actor('#', White, position)
{
	// 정렬 순서
	SetSortingOrder(0);
}
