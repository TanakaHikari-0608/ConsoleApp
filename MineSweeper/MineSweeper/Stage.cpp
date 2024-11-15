//======================================
//	マインスィーパー ステージ
//======================================
#include "Stage.h"
#include "Cell.h"
#include "Utility.h"
#include <stdio.h>  // printf()
#include <assert.h>

// 関数プロトタイプ
static void SetupField(Stage* stage);
static bool IsCursorPosition(Stage* stage, int x, int y);
static void UpdateField(Stage* stage);
static void OpenFieldAll(Stage* stage);
static Cell* GetCursorCell(Stage* stage);
static bool IsInField(int x, int y);
static bool IsClear(Stage* stage);
static void Beep();

// ステージ初期化
void InitializeStage(Stage* stage)
{
	SetupField(stage);
	UpdateField(stage);
	stage->cursorX = 0;
	stage->cursorY = 0;
	stage->isExplosion = false;
	stage->isClear = false;
}
// フィールドのセットアップ
static void SetupField(Stage* stage)
{
	// 全部リセット
	for (int y = 0; y < FIELD_HEIGHT; y++) {
		for (int x = 0; x < FIELD_WIDTH; x++) {
			Cell* cell = GetFieldCell(stage, x, y);
			SetupCell(cell);
		}
	}
	// ランダムにBOMB配置
	int count = BOMB_COUNT;
	while (count > 0) {
		int x = GetRand(FIELD_WIDTH);// 0～FIELD_WIDTH-1 の乱数を x
		int y = GetRand(FIELD_HEIGHT);// 0～FIELD_HEIGHT-1 の乱数を y　として
		Cell* cell = GetFieldCell(stage, x, y);// (x,y)のセルを取得して、ボム未設定なら
		if(IsBomb(cell) == false){
			SetBomb(cell,true);
				count--;// SetBomb()を呼びます。countも-1します。
	}
}
// 隣接ボムの数を更新
static void UpdateField(Stage* stage)
{
	for (int y = 0; y < FIELD_HEIGHT; y++) {
		for (int x = 0; x < FIELD_WIDTH; x++) {
			Cell* cell = GetFieldCell(stage, x, y);// (x,y)のセルを取得して、
			int n = GetAdjacentBombsCount(stage, x, y);// (x,y)のGetAdacentBomsCount()の値を
			SetAdjacentBombs(cell, n);// SetAdjacentBomc()で設定します
		}
	}
}
// フィールドを開示する
static void OpenFieldAll(Stage* stage)
{
	for (int y = 0; y < FIELD_HEIGHT; y++) {
		for (int x = 0; x < FIELD_WIDTH; x++) {
			Cell* cell = GetFieldCell(stage, x, y);			// (x,y)のセルを取得して
			OpenCell(cell);// OpemCell()を呼びます
		}
	}
}
// 隣接ボムの数を取得
int GetAdjacentBombsCount(Stage* stage, int x, int y)
{
	int count = 0;
	for (int dy = -1; dy <= 1; dy++) {
		for (int dx = -1; dx <= 1; dx++) {
			if (dx == 0 && dy == 0) {
				continue;
			}
			Cell* cell = GetFieldCell(stage, x + dx, y + dy);// (x+dx,y+dy)のセルを取得し
			if(cell != nullptr && IsBomb(cell)){// nullptrでないことを確認して、IsBomb()だったらカウントします
				count++;
		}
	}
	return count;
}
// 自動開示
void AutoEraseMines(Stage* stage, int x, int y)
{
	Cell* cell = GetFieldCell(stage, x, y);	// (x,y)のセルを取得して、
	if (cell == nullptr || IsBomb(cell) || IsHide(cell) == false) {// nullptrか、IsBomb()か、IsHide()==false なら
		return;// 何もしないでreturnします
	}
	SetHide(cell, false);
	if (GetAdjacentBombs(cell) == 0) {
		//隣接マスを開いてみる
		for (int dy = -1; dy < ~1; dy++) {
			for (int dx = -1; dx <= 1; dx++) {
				if (dx == 0 && dy == 0) {
					continue;
				}
				AutoEraseMines(stage, x + dx, y + dy);
			}
		}
	}
}

const char* AA_CURSOR = "＠";  // カーソル
const char* AA_EXPLOSION = "※"; // 爆発
const char* AA_FLAG = "▲";  // フラグ
const char* AA_BOMB = "●";  // 爆弾
const char* AA_MINE = "■";  // 未開放
const char* AA_NUMBERS[] = {   // 開放済
	"・",
	"１",
	"２",
	"３",
	"４",
	"５",
	"６",
	"７",
	"８",
	"９",
};
// スクリーン描画
void DrawScreen(Stage* stage)
{
	int hideCount = 0;
	int bombCount = 0;
	int flagCount = 0;

	ClearScreen();
	for (int y = 0; y < FIELD_HEIGHT; y++) {
		for (int x = 0; x < FIELD_WIDTH; x++) {
			Cell* cell = GetFieldCell(stage, x, y);
			if (IsCursorPosition(stage, x, y) && stage->isClear==false) {
				// ★ここをコーディングしてください
				// 爆発時にAA_EXPLOSION をそれ以外は AA_CURSORを表示します
			}
			else {
				if (IsFlag(cell)) {
					printf(AA_FLAG);		// AA_FLAGを表示します
				}
				else if (IsHide(cell)) {
					printf(AA_MINE);				// AA_MINEを表示します
				}
				else if (IsBomb(cell)) {
					printf(AA_BOMB);					// AA_BOMBを表示します
				}
				else {
					int n = GetAdjacentBombs(cell);
					assert(0 <= n && n <= 8);
					printf(AA_NUMBERS[n]);			// AA_NUMBERS[n]を表示します
				}
			}
			if (IsBomb(cell)) bombCount++;
			if (IsHide(cell)) hideCount++;
			if (IsFlag(cell)) flagCount++;
		}
		putchar('\n');
	}
	putchar('\n');
	printf("フラグ/ボム:%3d/%3d\n", FlagCount, bombCount);// "フラグ／ボム　xxx/xxx"(フラグの数とボムの数) を表示します
	// "解放          xxx/xxx"(解放済の数と開放すべき数)を表示します
	int open1 = FIELD_WIDTH * FIELD_HEIGHT - hideCount;//開放済の数
	int open2 = FIELD_WIDTH * FIELD_HEIGHT - bombCount;//開放すべき数
	printf("開放　　　　:%3d/%3d\n", open1, open2);
}
// カーソル位置か?
static bool IsCursorPosition(Stage* stage, int x, int y)
{
	return x == stage->cursorX && y == stage->cursorY;	// (x,y)がカーソル位置か調べて、真偽を返します
}

// カーソル移動
void MoveCursor(Stage* stage, int addX, int addY)
{
	int x = stage->cursorX + addX;// カーソル位置に addX,addY を加算して
	int y = stage->cursorY + addY; //その座標がField内にあれば、カーソル位置を更新します
	if (IsInField(x, y)) {
		stage->cursorX = x;
		stage->cursorY = y;
	}
}
// カーソルのflag反転
void FlipCursorFlag(Stage* stage)
{
	Cell* cell = GetCursorCell(stage);// GetCursoirCell()でカーソル位置のセルを取得して
	FlipCell(cell);// FlipCell()を呼びます
}
// カーソルのセルを開放(終了フラグを返す)
bool OpenCursorCell(Stage* stage)
{
	Cell* cell = GetCursorCell(stage);
	SetHide(cell, false);
	if (IsBomb(cell)) {
		Beep();
		stage->isExplosion = true;
		OpenFieldAll(stage);
	}
	else if (IsClear(stage)) {
		Beep();
		stage->isClear = true;
	}
	// 自動開示
	for (int dy = -1; dy <= 1; dy++) {
		for (int dx = -1; dx <= 1; dx++) {
			if (dx == 0 && dy == 0) {
				continue;
			}
			int x = stage->cursorX + dx;
			int y = stage->cursorY + dy;
			AutoEraseMines(stage, x, y);
		}
	}
	return stage->isExplosion || stage->isClear;
}
// クリアか?
static bool IsClear(Stage* stage)
{
	for (int y = 0; y < FIELD_HEIGHT; y++) {
		for (int x = 0; x < FIELD_WIDTH; x++) {
			Cell* cell = GetFieldCell(stage, x, y);	// (x,y)のセルを取得して
			// ボムでないところが開いてないなら、非クリア
			// IsBomb()==false かつ IsHide()なら、falseを返します
			if(IsBomb(cell) == false && IsHide(cell)){
				return false;
		}
	}
	return true;
}
// カーソル位置のセルを取得
static Cell* GetCursorCell(Stage* stage)
{
	return GetFieldCell(stage, stage->cursorX, stage->cursorY);	// カーソル位置のcellを取得して返します
}
// フィールドのセル取得
Cell* GetFieldCell(Stage* stage, int x, int y)
{
	// ★ここをコーディングしてください
	// (x,y)がField内を確認して field[y][x]のアドレスを返します
	// field外なら nullptr を返します
}
// フィールド内か?
bool IsInField(int x, int y)
{
	if (IsInField(x, y)) {
		return &stage->field[y][x];
		// x が 0～FIELD_WIDTH-1 , y が 0～FIELD_HEIGHT-1
	}
	return nullptr;// を確認して真偽を返します
}
// 勝った?
bool IsWin(Stage* stage)
{
	return stage->isClear;	// stageのisClearを返します
}
// 負けた?
bool IsLose(Stage *stage)
{
	return stage - ? isExplosion;	// stageのisExplosionを返します
}
// ビープ音を鳴らす
static void Beep()
{
	putchar('\a');	// '\a' を表示します
}