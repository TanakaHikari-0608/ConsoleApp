#pragma once
//======================================
//      落ち物バズル ステージ
//======================================
#ifndef __STAGE_H
#define __STAGE_H
#include "BlockShape.h"
#include "FallBlock.h"

const int FIELD_WIDTH = 12;
const int FIELD_HEIGHT = 18;

typedef enum {
	BLK_NONE,  // ブロックなし
	BLK_WALL,  // 壁
	BLK_FIX,   // 定着ブロック
	BLK_FALL,  // 落下ブロック
	BLK_MAX,
}Block;

// ステージの定義
typedef struct {
	Block field[FIELD_HEIGHT][FIELD_WIDTH];
	FallBlock fallBlock;
	bool isGameOver;
} Stage;

// 指定位置のフィールドへセット
void SetField(Stage* stage, int x, int y, Block blk);
// 指定位置のフィールド取得
Block GetField(Stage* stage, int x, int y);
// 落ちブロックがフィールドに衝突?
bool BlockIntersectField(Stage* stage, FallBlock *fallBlock);
// 揃った行を消して、上から詰める
void EraseLine(Stage* stage);
// 画面描画
void DrawScreen(Stage* stage);
// ブロックを1つ落下させる
void MoveDownFallBlock(Stage* stage);
// 落ちブロックをセットアップ
void SetupFallBlock(Stage* stage);
// ステージ初期化
void InitializeStage(Stage* stage);
// 落ちブロックの取得
FallBlock GetFallBlock(Stage* stage);
// 落ちブロックのセット
void SetFallBlock(Stage* stage, FallBlock* fallBlock);
// ゲームオーバか?
bool IsGameOver(Stage*stage);

// ★ここにインクルードガード(終了)を記入してください
#endif // __STAGE_H