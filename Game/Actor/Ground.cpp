#include "Ground.h"

Ground::Ground(const Vector2& position)
	:Actor('.', Color::White, position)
{	
	// 정렬 순서
	SetSortingOrder(0);
}
