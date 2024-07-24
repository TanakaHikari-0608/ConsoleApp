#pragma once
//======================================
//      落ち物バズル 落ちブロック
//======================================
#ifndef __FALLBLOCK_H
#define __FALLBLOCK_H

#include "BlockShape.h"

typedef struct {
	int x, y;         // Shape左上の座標
	BlockShape shape; // 形状
} FallBlock;

// 落ちブロックの移動
void MoveFallBlock(FallBlock* fallBlock, int ofsx, int ofsy);
// 落ちブロックの回転
void RotateFallBlock(FallBlock* fallBlock);
// ランダムな落ちブロックをセット
void SetRandomFallBlock(FallBlock* fallBlock, int x, int y);
// 落ちブロックをプリント
void PrintFallBlock(FallBlock* fallBlock);

#endif __FALLBLOCK_H