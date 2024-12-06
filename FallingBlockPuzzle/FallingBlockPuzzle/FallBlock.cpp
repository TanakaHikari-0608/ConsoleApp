//======================================
//      落ち物バズル 落ちブロック
//======================================
#include "FallBlock.h"
#include "Utility.h"  // GetRand()
#include <stdio.h>

// 落ちブロックの移動
void MoveFallBlock(FallBlock* fallBlock, int ofsx, int ofsy)
{
	//
	// ★ここをコーディングしてください
	// fallBlockのx座標 に ofsx を足しこみます
	// fallBlockのy座標 に ofsy を足しこみます
	//
	fallBlock->x += ofsx;
	fallBlock->y += ofsy;
}
// 落ちブロックの回転
void RotateFallBlock(FallBlock* fallBlock)
{
	//
	// ★ここをコーディングしてください
	//　fallBlockのshape の回転を呼び出します
	//
	RotateShape(&fallBlock->shape);
}
// ランダムな落ちブロックをセット
void SetRandomFallBlock(FallBlock* fallBlock, int x, int y)
{
	//
	// ★ここをコーディングしてください
	// (1) 0～blockShapedSize-1 の乱数を取得して、そのインデックスでfallBlockのshapeにSetShape()します
	// (2) 0～3 の乱数を取得して、その回数 fallBlockのshapeを回転します
	// (3) x,y を fallBlockのx,y座標に代入します
	//
	int idx = GetRand(blockShapesSize);
	SetShape(&fallBlock->shape, idx);
	//0～3回、回転する
	int rotateCount = GetRand(4);
	for (int i = 0; i < rotateCount; i++)
	{
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