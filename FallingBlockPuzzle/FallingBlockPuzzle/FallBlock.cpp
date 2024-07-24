//======================================
//      落ち物バズル 落ちブロック
//======================================
#include "FallBlock.h"
#include "Utility.h"  // GetRand()
#include <stdio.h>

// 落ちブロックの移動
void MoveFallBlock(FallBlock* fallBlock, int ofsx, int ofsy)
{
	fallBlock->x += ofsx;
	fallBlock->y += ofsy;
}
// 落ちブロックの回転
void RotateFallBlock(FallBlock* fallBlock)
{
	RotateShape(&fallBlock->shape);
}
// ランダムな落ちブロックをセット
void SetRandomFallBlock(FallBlock* fallBlock,int x,int y)
{
	int idx = GetRand(blockShapesSize);
	SetShape(&fallBlock->shape, idx);
	//0～3回、回転する
	int rotateCount = GetRand(4);
	for (int i = 0; i < rotateCount; i++) {
		RotateShape(&fallBlock->shape);
	}
	fallBlock->x = x;
	fallBlock->y = y;
}
// 落ちブログをプリント
void PrintFallBlock(FallBlock* fallBlock)
{
	printf("(%d,%d)\n", fallBlock->x, fallBlock->y);
	PrintShape(&fallBlock->shape);
}