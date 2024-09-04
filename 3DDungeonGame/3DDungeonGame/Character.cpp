//====================================
//	3Dダンジョン  キャラクタ
//======================================
#include "Character.h"
#include "Direction.h"
#include "Vector2.h"

// 初期化
void InitCharacter(Character* ch, Vector2 pos, Direction dir)
{
	ch->pos = pos;
	ch->dir = dir;
}
//　後ろを向く
void TurnBackCharacter(Character* ch)
{
	ch->dir = DirectionAdd(ch->dir, 2);
}
// 左を向く
void TurnLeftCharacter(Character* ch) 
{
	// 北→西→南→東
	ch->dir = DirectionAdd(ch->dir, 1);
}
// 右を向く
void TurnRightCharacter(Character* ch)
{
	// 北→東→南→西
	ch->dir = DirectionAdd(ch->dir, -1);
}