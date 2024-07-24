//======================================
//	2Dベクター
//======================================
#include "Vector2.h"

// ベクター加算(a+=b)
void AddVector2(Vector2 *a, Vector2 *b)
{
	a->x += b->x;
	a->y += b->y;
}
// 4方向のベクター取得
Vector2 GetDirVector2(DIRECTION d)
{
	static Vector2 dirVector2[] = {
		{0,-1}, //DIR_UP
		{-1,0 },//DIR_LEFT
		{0,1},  //DIR_DOWN,
		{1,0},  //DIR_RIGHT,
	};
	return dirVector2[d];
}

Vector2 Vector2Add(Vector2 a, Vector2 b)
{
	int x = a.x + b.x;
	int y = a.y + b.y;
	return { x,y };
}
Vector2 Vector2Sub(Vector2 a, Vector2 b)
{
	int x = a.x - b.x;
	int y = a.y - b.y;
	return { x,y };
}
bool Vector2Equ(Vector2 a, Vector2 b)
{
	return a.x == b.x && a.y == b.y;
}