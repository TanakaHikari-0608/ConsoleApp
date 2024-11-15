//======================================
//	マインスィーパー セル
//======================================
#include "Cell.h"
// セットフップ(初期化)状態にする
void SetupCell(Cell* cell)
{
	// ★ここをコーディングしてください
	cell->bomb = false;// cellのbombを false にセットします
	cell->hide = true;// cellのhideを true にセットします
	cell->flag = false;// cellのflagを false にセットします
	cell->adjacentBombs = 0;// cellのadjacentBombsを 0 にセットします
}
// bombか?
bool IsBomb(Cell* cell)
{
	// ★ここをコーディングしてください
	return cell->bomb;// cellのbombを返します
}
// bomb をセット
void SetBomb(Cell* cell, bool value)
{
	// ★ここをコーディングしてください
	cell->bomb = value;// cellのbombにvalueを代入します
}
// hideか?
bool IsHide(Cell* cell)
{
	// ★ここをコーディングしてください
	return cell->hide;// cellのhideを返します
}
// hide をセット
void SetHide(Cell* cell, bool value)
{
	// ★ここをコーディングしてください
	cell->hide = value;// cellのhideにvalueを代入します
}
// flagか?
bool IsFlag(Cell* cell)
{
	// ★ここをコーディングしてください
	return cell->flag;// cellのflagを返します
}
// flag を反転
void FlipFlag(Cell* cell)
{
	// ★ここをコーディングしてください
	cell->flag = !cell->flag;// cellのflagを反転します
}
// adjacentBombsを取得
int GetAdjacentBombs(Cell* cell)
{
	// ★ここをコーディングしてください
	return cell->adjacentBombs;// cellのadjacentBombsを返します
}
// adjacentBombsをセット
void SetAdjacentBombs(Cell* cell,int value)
{
	// ★ここをコーディングしてください
	cell->adjacentBombs = value;// cellのadjacentBombsにvalueを代入します
}
// 開示する
void OpenCell(Cell* cell)
{
	// ★ここをコーディングしてください
	cell->hide = false;// cellのhideにfalseを入れます
	cell->flag = false;// cellのflagにfalseを入れます
}