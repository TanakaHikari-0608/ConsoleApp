//======================================
//      落ち物バズル ステージ
//======================================
#include "Stage.h"
#include "BlockShape.h"
#include "Utility.h"
#include <stdio.h>   // printf(),putchar()
#include <string.h>  // memcpy()

// 関数プロトタイプ
static void writeFallBlockToField(Stage* stage, FallBlock* fallBlock, Block block);
static bool isInField(int x, int y);

const Block defaultField[FIELD_HEIGHT][FIELD_WIDTH] = {
#define W  BLK_WALL
#define _  BLK_NONE
	{W,_,_,_,_,_,_,_,_,_,_,W}, // 0
	{W,_,_,_,_,_,_,_,_,_,_,W}, // 1
	{W,_,_,_,_,_,_,_,_,_,_,W}, // 2
	{W,_,_,_,_,_,_,_,_,_,_,W}, // 3
	{W,_,_,_,_,_,_,_,_,_,_,W}, // 4
	{W,_,_,_,_,_,_,_,_,_,_,W}, // 5
	{W,_,_,_,_,_,_,_,_,_,_,W}, // 6
	{W,_,_,_,_,_,_,_,_,_,_,W}, // 7
	{W,_,_,_,_,_,_,_,_,_,_,W}, // 8
	{W,_,_,_,_,_,_,_,_,_,_,W}, // 9
	{W,_,_,_,_,_,_,_,_,_,_,W}, // 10
	{W,_,_,_,_,_,_,_,_,_,_,W}, // 11
	{W,_,_,_,_,_,_,_,_,_,_,W}, // 12
	{W,_,_,_,_,_,_,_,_,_,_,W}, // 13
	{W,_,_,_,_,_,_,_,_,_,_,W}, // 14
	{W,_,_,_,_,_,_,_,_,_,_,W}, // 15
	{W,_,_,_,_,_,_,_,_,_,_,W}, // 16
	{W,W,W,W,W,W,W,W,W,W,W,W}, // 17
#undef _
#undef W
};

int point = 0;

const char* blockAA[] = {
	"　", //BLK_NONE
	"＋", //BLK_WALL
	"◆", //BLK_FIX
	"◇", //BLK_FALL
};
// ステージ初期化
void InitializeStage(Stage* stage)
{
	memcpy(stage->field, defaultField, sizeof(stage->field));
	stage->isGameOver = false;
	SetupFallBlock(stage);
	DrawScreen(stage);
}
// 指定座標のフィールドセット
void SetField(Stage* stage, int x, int y, Block block)
{
	//
	// ★ここをコーディングしてください
	// isInField()を確認して fieldの(x,y)に blockを格納します。
	// isInField()外なら、なにもしません
	//
	if (isInField(x, y))
	{
		stage->field[y][x] = block;
	}
}
// 指定座標のフィールド取得
Block GetField(Stage* stage, int x, int y)
{
	//
	// ★ここをコーディングしてください
	// isInField()を確認して、fieldの(x,y)の内容を返します
	// isInField()外なら、壁(BLK_WALL)を返します
	//
	if (isInField(x, y))
	{
		return stage->field[y][x];
	}
	return BLK_WALL;
}
// 落下ブロックがフィールド衝突?
bool BlockIntersectField(Stage* stage, FallBlock* fallBlock)
{
	// 
	// ★ここをコーディングしてください
	// fallBlockのshape を走査します(x,y)
	// fallBlockのshapeの1のところに対応する field を調べる
	// fieldのx座標はfallBlockのx + 走査x座標
	// fieldのy座標はfallBlockのy + 走査y座標
	// 調べたfieldが、空白(BLK_NONE)でなければ、衝突している
	// 
	BlockShape* shape = &fallBlock->shape;
	for (int y = 0; y < shape->size; y++)
	{
		int fieldY = fallBlock->y + y;
		for (int x = 0; x < shape->size; x++)
		{
			if (GetShapePattern(shape, x, y))
			{
				int fieldX = fallBlock->x + x;
				if (GetField(stage, fieldX, fieldY) != BLK_NONE)
				{
					return true;
				}
			}
		}
	}
	return false;
}

// 揃った行を消して、上から詰める
void EraseLine(Stage* stage)
{

	point--;
	for (int y = 0; y < FIELD_HEIGHT; y++) {
		bool completed = true;
		// 行が揃ったか?
		//
		// ★ここをコーディングしてください
		// y 行を走査します(x:0～FIELD_WIDTH-1)
		// fieldの(x,y)を取得して、空白(BLK_NONE)であれば
		// 行はそろっていないので、completedを偽にしてxループを抜けます
		//
		for (int x = 0; x < FIELD_HEIGHT; x++)
		{
			if (GetField(stage, x, y) == BLK_NONE)
			{
				completed = false;
				break;
			}
		}
		if (completed) {

			point++;
			// 行を消す
			//
			// ★ここをコーディングしてください
			// y行を走査します(x:0～FIELD_WIDTH-1)
			// fieldの(x,y)を取得して 固定ブロック(BLK_FIX)なら
			// 空白(BLK_NONE)に差し替えます
			//
			for (int x = 0; x < FIELD_WIDTH; x++)
			{
				if (GetField(stage, x, y) == BLK_FIX)
				{
					SetField(stage, x, y, BLK_NONE);
				}
			}
			// 上から詰める
			for (int x = 0; x < FIELD_WIDTH; x++) {
				for (int yy = y; yy >= 0; yy--) {
					if (GetField(stage, x, yy) == BLK_WALL) {
						break;
					}
					if (yy == 0) {
						// 最上段なら、空白を
						SetField(stage, x, yy, BLK_NONE);
					}
					else {
						// 最上段でなければ、1つ上を
						Block blk = GetField(stage, x, yy - 1);
						if (blk != BLK_WALL) {
							SetField(stage, x, yy, blk);
						}
						else {
							SetField(stage, x, yy, BLK_NONE);
						}
					}
				} // for yy
			} // for x
		} // completed
	} // for y
}
// 画面描画
void DrawScreen(Stage* stage)
{
	// 描画用ワーク
	Stage screen[1];
	memcpy(screen->field, stage->field, sizeof(stage->field));
	// 落下中のブロックを記入
	writeFallBlockToField(screen, &stage->fallBlock, BLK_FALL);
	// 描画
	ClearScreen();
	// 
	// ★ここをコーディングしてください
	// screenのfieldを走査します
	// screenのfieldの(x,y)を取得して、その内容の blockAA[] を表示します
	// ＋　　　　　　　　　　＋
	// ＋　　　　　　　　　　＋
	// ＋　　　　　　　　　　＋
	// ＋　　　　　　　　　　＋
	// ＋　　　　　　　　　　＋
	// ＋　　　　　　　　　　＋
	// ＋　　　　　　　　　　＋
	// ＋　　　　　　　　　　＋ 
	// ＋　　　　　　　　　　＋
	// ＋　　　　　　　　　　＋
	// ＋＋　　　　　　　　＋＋
	// ＋＋　　　　　　　　＋＋
	// ＋＋　　◇　　　　　＋＋
	// ＋＋　　◇　　　　　＋＋
	// ＋＋＋　◇　　　　＋＋＋
	// ＋＋＋　　　　　　＋＋＋
	// ＋＋＋＋　◆◆◆＋＋＋＋
	// ＋＋＋＋＋＋＋＋＋＋＋＋
	// 
	for (int y = 0; y < FIELD_HEIGHT; y++)
	{
		for (int x = 0; x < FIELD_WIDTH; x++)
		{
			Block blk = GetField(screen, x, y);
			printf("%s", blockAA[blk]);
		}
		printf("\n");
	}
	//PrintFallBlock(&stage->fallBlock);
	printf("%dpoint\n", point);
}
// ブロックを1つ落下させる
void MoveDownFallBlock(Stage* stage)
{
	FallBlock fallBlock = GetFallBlock(stage);
	MoveFallBlock(&fallBlock, 0, 1);
	// y+1が衝突するか?
	if (BlockIntersectField(stage, &fallBlock)) {
		// 落下ブロックを現在位置にfix
		writeFallBlockToField(stage, &stage->fallBlock, BLK_FIX);
		EraseLine(stage);
		// 新たな落下ブロックセットアップ
		SetupFallBlock(stage);
		if (BlockIntersectField(stage, &stage->fallBlock)) {
			stage->isGameOver = true;
		}
	}
	else {
		SetFallBlock(stage, &fallBlock);
	}
	DrawScreen(stage);
}
// 落ちブロックのセットアップ
void SetupFallBlock(Stage* stage)
{
	FallBlock* fallBlock = &stage->fallBlock;
	// 座標は、上辺中央
	int x = FIELD_WIDTH / 2 - fallBlock->shape.size / 2;
	SetRandomFallBlock(fallBlock, x, 0);
}
// 落ちブロックを取得
FallBlock GetFallBlock(Stage* stage)
{
	return stage->fallBlock;
}
// 落ちブロックをセット
void SetFallBlock(Stage* stage, FallBlock* fallBlock)
{
	stage->fallBlock = *fallBlock;
}
// ゲームオーバ?
bool IsGameOver(Stage* stage)
{
	return stage->isGameOver;
}
// 落下ブロックをフィールドへ記入する
static void writeFallBlockToField(Stage* stage, FallBlock* fallBlock, Block writeData)
{
	//
	// ★ここをコーディングしてください
	// fallBlockのshapeを走査します(x,y)
	// もし shapeの(x,y)が真なら、
	// 対応する field を調べ、空白なら writeDataを書き込みます
	//  fieldのx座標 = fallBlockのx座標 + 走査x座標
	//  fieldのy座標 = fallBlockのy座標 + 走査y座標
	//
	BlockShape* shape = &fallBlock->shape;
	for (int y = 0; y < shape->size; y++)
	{
		int fieldY = fallBlock->y + y;
		for (int x = 0; x < shape->size; x++)
		{
			int fieldX = fallBlock->x + x;
			if (GetShapePattern(shape, x, y))
			{
				if (GetField(stage, fieldX, fieldY) == BLK_NONE)
				{
					SetField(stage, fieldX, fieldY, writeData);
				}
			}
		}
	}
}
// 座標はフィールド内?
static bool isInField(int x, int y)
{
	return 0 <= x && x < FIELD_WIDTH
		&& 0 <= y && y < FIELD_HEIGHT;
}