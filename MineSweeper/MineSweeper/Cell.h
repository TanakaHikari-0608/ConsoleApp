#pragma once
//======================================
//	マインスィーパー セル
//======================================
#ifndef __CELL_H
#define __CELL_H

typedef struct {
	bool bomb;          // ボムが置いてある
	bool hide;          // 未開放
	bool flag;          // プレーヤがつけたフラグ
	int adjacentBombs;  // 隣接ボムの数
} Cell;

// Cellを初期化
void SetupCell(Cell* cell);
// bombか?
bool IsBomb(Cell* cell);
// bombをセット
void SetBomb(Cell *cell, bool value);
// mine か?
bool IsHide(Cell* cell);
// mineをセット
void SetHide(Cell* cell, bool value);
// mine か?
bool IsFlag(Cell* cell);
// mineをセット
void FlipFlag(Cell* cell);
// adjacentBombsを取得
int GetAdjacentBombs(Cell* cell);
// adjacentBombsをセット
void SetAdjacentBombs(Cell* cell,int value);
// 開示する
void OpenCell(Cell* cell);

#endif //  __CELL_H