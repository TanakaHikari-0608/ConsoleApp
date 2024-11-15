#pragma once
//======================================
//	マインスィーパー ステージ
//======================================
#ifndef __STAGE_H
#define __STAGE_H

#include "Cell.h"

const int FIELD_WIDTH = 9;
const int FIELD_HEIGHT = 9;
// ボムの設置数
const int BOMB_COUNT = 10;

typedef struct {
	Cell field[FIELD_HEIGHT][FIELD_WIDTH];
	int cursorX; // カーソル座標
	int cursorY;
	bool isExplosion; // 爆発した!!
	bool isClear;  // クリアした!!
} Stage;

// ステージの初期化
void InitializeStage(Stage* stage);
// スクリーン描画
void DrawScreen(Stage* stage);
// 隣接ボムの数を取得
int GetAdjacentBombsCount(Stage* stage, int x, int y);
// 自動掘りすすめ
void AutoEraseMines(Stage *stage,int x, int y);
// カーソルのセルのflagを反転.
void FlipCursorFlag(Stage* stage);
// カーソルのセルを開放(終了フラグを返す)
bool OpenCursorCell(Stage* stage);
// カーソル移動
void MoveCursor(Stage* stage, int addX, int addY);
// フィールドのセルを取得する
Cell *GetFieldCell(Stage* stage, int x, int y);
// 勝った?
bool IsWin(Stage* stage);
// 負けた?
bool IsLose(Stage* stage);

#endif //  __STAGE_H
