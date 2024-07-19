#pragma once
//========================================
//      ライフゲーム:フィールド
//========================================
// ★ここにインクルードガード(開始)を記入してください。
#ifndef __FIELD_H
#define __FIELD_H
#include "Pattern.h"

typedef struct {
	int width;       // フィールド横幅
	int height;      // フィールド縦幅
	bool* cells[2];  // フィールド配列(width×height) 2セット
	int currentIdx;  // カレントのフィールドセット(0 or 1)
	bool isLoopCells; // フィールドの左右、上下がループしているか?
} Field;

// 初期化
void InitializeField(Field* field, int width, int height, bool isLoopCells);
// フィールドの描画
void DrawField(Field* field);
// シミュレーション1ステップ進める
void StepSimulation(Field* field);
// パターンの転送
void TransferPattern(Field* field,Pattern *pattern);
// 後始末
void FinalizeField(Field* field);

// ★ここにインクルードガード(終了)を記入してください。
#endif // __FIELD_H