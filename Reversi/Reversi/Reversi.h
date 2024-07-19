#pragma once
//======================================
//	リバーシ
//======================================
// ★ここにインクルードガード(開始)を記入してください
#ifndef __REVERSI_H
#endif __REVERSI_H
#include "Mode.h"
#include "Vector2.h"
#include "Vector2List.h"
#include <assert.h>   // assert()

const int BOARD_WID = 8;
const int BOARD_HEI = 8;

// Board状態、ターン(BLACK,WHITE)
typedef enum {
	NONE,
	BLACK,
	WHITE,
	OUT,
}Cell;

// リバーシ構造体
typedef struct {
	Cell board[BOARD_HEI][BOARD_WID];
	Cell turn;  // BLACK<=>WHITE
	Mode mode;  // MODE_1P,MODE_2P,WATCH
} Reversi;

// 描画時のステータス
typedef enum {
	IN_PLAY,   // プレイ中
	NO_PLACE,  // 打てる場所がない
	RESULT,    // リザルト
}DrawStatus;

// ボードに値をセット
void SetBoard(Reversi* reversi, int x, int y, Cell value);
// ボードの値を取得
Cell GetBoard(Reversi* reversi, int x, int y);
// 初期化
void Init(Reversi* reversi,Mode mode);
// 次のターン
void NextTurn(Reversi* reversi);
// 画面描画
void DrawScreen(Reversi* reversi,Vector2 pos, DrawStatus stat);
// 指定位置に置けるか?
bool CheckCanPlace(Reversi* reversi, Cell myself, Vector2 pos, bool turnOver = false);
// 石がどこかに置けるか?
bool CheckCanPlaceAll(Reversi* reversi, Cell myself);
// 石が置けるところをリスティング
void ListCanPlaceAll(Reversi* reversi, Cell myself, Vector2List* list);
// 石の数をカウント
int GetDiskCount(Reversi* reversi, Cell myself);
// プレーヤ操作か?
bool IsHumanPlayer(Reversi* reversi);
//  相手を得る
Cell GetOpponent(Cell myself);
// ★ここにインクルードガード(終了)を記入してください
#endif // __REVERSI_H