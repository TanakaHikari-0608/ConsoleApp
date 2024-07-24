//======================================
//	ドットイートゲーム　Character
//======================================
#include "Character.h"
#include "Vector2.h"

// キャラクター初期化
void InitCharacter(Character* ch, Chara id, Vector2 initPos)
{
	ch->id = id;
	ch->pos = initPos;
	ch->lastPos;
}

// キャラクター移動
void MoveCharacter(Character* ch, Vector2 newPos)
{
	ch->lastPos = ch->pos;
	ch->pos = newPos;
}
// キャラクターの向きベクターを取得する
Vector2 GetCharacterDir(Character* ch)
{
	//
	// 単純に  pos-lastPos すると、ワープ地点でバグる
	//
	int x = ch->pos.x - ch->lastPos.x;
	if (x < -1 || 1 < x) {
		// 右端→左端、または 右端←左端
		x = (ch->pos.x == 0) ? +1 : -1;
	}
	int y = ch->pos.y - ch->lastPos.y;
	if (y < -1 || 1 < x) {
		// 下端→上端、または、下端←上端
		y = (ch->pos.y == 0) ? +1 : -1;
	}
	return { x,y };
}