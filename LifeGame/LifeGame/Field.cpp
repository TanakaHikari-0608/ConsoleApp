//========================================
//      ライフゲーム:フィールド
//========================================
#include "Field.h"
#include "Utility.h"
#include <stdio.h>   // puts()
#include <stdlib.h>  // exit()
// 関数プロトタイプ
static void clearCells(Field* field, bool* cells);
static void setCells(Field* field, bool* cells, int x, int y, bool isLive);
static bool getCells(Field* field, bool* cells, int x, int y);
static int getLivingCount(Field* field, bool* cells, int x, int y);
static bool isInCells(Field* field, int x, int y);
static void drawCells(Field* field, bool* cells);
static void transferPattern(Field* field, int dstX, int dstY, int srcWid, int srcHei, bool* srcPat);

// 初期化
void InitializeField(Field* field, int width, int height, bool isLoopCells)
{
	field->width = width;
	field->height = height;
	int cellsSize = width * height;
	field->cells[0] = (bool*)calloc(cellsSize, sizeof(bool));
	field->cells[1] = (bool*)calloc(cellsSize, sizeof(bool));
	if (field->cells[0] == nullptr || field->cells[1] == nullptr) {
		puts("calloc失敗");
		exit(1);
	}
	clearCells(field, field->cells[0]);
	clearCells(field, field->cells[1]);
	field->currentIdx = 0;
	field->isLoopCells = isLoopCells;
}
// 後始末
void FinalizeField(Field* field)
{
	free(field->cells[0]);
	free(field->cells[1]);
	field->cells[0] = nullptr;
	field->cells[1] = nullptr;
}
// フィールド描画
void DrawField(Field* field)
{
	bool *cells = field->cells[field->currentIdx];
	drawCells(field, cells);
}
// シミュレーション1ステップ進める
void StepSimulation(Field* field)
{
	int currentIdx = field->currentIdx;
	int nextIdx = (currentIdx != 0) ? 0 : 1;

	bool* now = field->cells[currentIdx];
	bool* next = field->cells[nextIdx];
	for (int y = 0; y < field->height; y++) {
		for (int x = 0; x < field->width; x++) {
			int count = getLivingCount(field, now, x, y);
			bool isLive = false;
			if (count <= 1) {
				isLive = false;
			}
			else if (count == 2) {
				isLive = getCells(field, now, x, y);
			}
			else if (count == 3) {
				isLive = true;
			}
			else {
				isLive = false;
			}
			setCells(field, next, x, y, isLive);
		}
	}
	field->currentIdx = nextIdx;
}

// パターンを転送する
void TransferPattern(Field* field, Pattern* pattern)
{
	field->isLoopCells = pattern->isLoopCells;
	int dstX = field->width / 2 - pattern->width / 2;
	int dstY = field->height / 2 - pattern->height / 2;
	clearCells(field, field->cells[field->currentIdx]);
	transferPattern(field, dstX, dstY, pattern->width, pattern->height, pattern->data);
}

// パターンを転送する
static void transferPattern(Field* field, int dstX, int dstY, int srcWid, int srcHei, bool *srcPat)
{
	bool *cells = field->cells[field->currentIdx];
	for (int y = 0; y < srcHei; y++) {
		for (int x = 0; x < srcWid; x++) {
			bool isLive = srcPat[y * srcWid + x];
			setCells(field, cells, dstX+x, dstY+y, isLive);
		}
	}
}

// 指定位置周辺の生存数を数える
static int getLivingCount(Field* field,bool *cells, int x, int y)
{
	int count = 0;
	// ★ここをコーディングしてください。
	return count;
}
// cellsクリア
static void clearCells(Field* field, bool* cells)
{
	for (int y = 0; y < field->height; y++) {
		for (int x = 0; x < field->width; x++) {
			setCells(field, cells, x, y, false);
		}
	}
}
// cells[x,y]セット
static void setCells(Field* field, bool* cells, int x, int y, bool isLive)
{
	if (isInCells(field, x, y) == false) {
		if (field->isLoopCells == false) {
			return;
		}
		// 左右、上下ループ時
		x = (x + field->width) % field->width;
		y = (y + field->height) % field->height;
	}
	// ★ここをコーディングしてください;
}
// cells[x,y]取得
static bool getCells(Field* field, bool* cells, int x, int y)
{
	if (isInCells(field, x, y) == false) {
		if (field->isLoopCells == false) {
			// 外側は全て not Live
			return false;
		}
		// 左右、上下ループ時
		x = (x + field->width) % field->width;
		y = (y + field->height) % field->height;
	}
	// ★ここをコーディングしてください;
}

static bool isInCells(Field* field, int x, int y)
{
	return 0 <= x && x < field->width
		&& 0 <= y && y < field->height;
}
// cellsを描画
static void drawCells(Field *field, bool* cells)
{
	ClearScreen();
	for (int y = 0; y < field->height; y++) {
		for (int x = 0; x < field->width; x++) {
			bool isLive = getCells(field, cells, x, y);
			printf("%s", isLive ? "■" : "・");
		}
		putchar('\n');
	}
}