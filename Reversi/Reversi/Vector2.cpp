//======================================
//	リバーシ 2Dベクター
//======================================
#include "Vector2.h"

// ベクター加算(a+=b)
void AddVector2(Vector2 *a, Vector2 *b)
{
	a->x += b->x;
	a->y += b->y;
}
// ８方向のベクター取得
Vector2 GetDirVector2(DIRECTION d)
{
	static Vector2 dirVector2[] = {
		{0,-1}, //DIR_UP
		{-1,-1},//DIR_UP_LEFT
		{-1,0 },//DIR_LEFT
		{-1,1},	//DIR_DOWN_LEFT,
		{0,1},  //DIR_DOWN,
		{1,1},  //DIR_DOWN_RIGHT,
		{1,0},  //DIR_RIGHT,
		{1,-1}, //DIR_UP, RIGHT,
	};
	return dirVector2[d];
}