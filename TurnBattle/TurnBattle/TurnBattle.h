#pragma once
//======================================
//	ターン制バトル
//======================================
#ifndef __TURNBATTLE_H
#define __TURNBATTLE_H

#include "Character.h"
#include "Command.h"

typedef struct {
	Character* player;
	Character* enemy;
	int turn;
} TurnBattle;

// バトル設定
void SetTurnBattle(TurnBattle* btl, Character* player, Character* enemy);
// イントロ「～が現れた!!」表示
void IntroTurnBattle(TurnBattle* btl);
// バトル開始
void StartTurnBattle(TurnBattle* btl);
// バトル画面を描画
void DrawBattleScreen(TurnBattle* btl);
// プレーヤのターン実行(終了フラグを返す)
bool ExecPlayerTurn(TurnBattle* btl,Command cmd);
// 敵のターン実行(終了フラグを返す)
bool ExecEnemyTurn(TurnBattle* btl,Command cmd);
// 次のターン
void NextTurnBattle(TurnBattle* btl);

#endif // __TURNBATTLE_H