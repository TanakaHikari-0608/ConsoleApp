#pragma once
//======================================
//	戦国シミュレーション  ステージ
//======================================
#ifndef __STAGE_H
#define __STAGE_H

#include "Castle.h"
#include "Lord.h"
#include "Chronology.h"

typedef enum {
	DM_Intro,    // ゲーム開始時
	DM_Turn,     // ターン中
	DM_Event,    // イベント発生中
	DM_GameOver, // ゲームオーバ中
	DM_Ending,   // エンディング中
} DrawMode;

typedef struct {
	Castle* castles;
	int castlesSize;
	int year;             // 年
	LordId playerLord;    // プレーヤ大名
	Chronology* chro;     // 年表
	CastleId turnOrder[CASTLE_MAX];
	bool isHonnojiEvent;  // 本能寺の変あったか?
} Stage;

// 初期化
void InitializeStage(Stage* stage, Castle chasles[], int castlesSize, int startYear, Chronology* chro);
// 後始末
void FinalizeStage(Stage* stage);
// スタート
void StartStage(Stage* stage);
// プレーヤ大名のセット
void SetPlayerLord(Stage* stage, CastleId playerCastle);
// イントロメッセージ
void IntroStage(Stage* stage, CastleId playerCastle);
// スクリーン描画
void DrawScreen(Stage* stage, DrawMode mode, int turn);
// ターンの順番をシャッフル
void MakeTurnOrder(Stage* stage);
// 年越し
void NextYear(Stage *stage);
// 「本能寺の変」か?
bool IsHonnojiEvent(Stage* stage);
// 「本能寺の変」フラグセット
void SetHonnojiEvent(Stage* stage);
// ターン実行
void ExecTurn(Stage *stage, int turn);
// プレーヤの負け?
bool IsPlayerLose(Stage* stage);
// プレーヤの勝ち?
bool IsPlayerWin(Stage* stage);
//---------------------------------------------------------
// 城の名前を取得
const char* GetCastleName(Stage* stage, CastleId castleId);
// 城の城主を取得
LordId GetCastleOwner(Stage* stage, CastleId castleId);
// 城の城主を設定
void SetCastleOwner(Stage* stage, CastleId id, LordId owner);
// 城の兵数を取得
int GetCastleTroopCount(Stage* stage, CastleId id);
// 兵数をセット
void SetCastleTroopCount(Stage* stage, CastleId id, int troopCount);
// 城の近隣リストを取得
CastleId* GetCastleConnectedList(Stage* stage, CastleId id);
// 城のマップ名を取得
const char* GetCastleMapName(Stage* stage, CastleId id);
//---------------------------------------------------------
// 城主の名を取得
const char* GetLordFirstName(Stage *stage,LordId id);
// 城主の姓を取得
const char* GetLordFamilyName(Stage *stage,LordId id);
// 城主のマップ上の名前を取得
const char* GetLordMapName(Stage* stage,LordId id);

#endif // __STAGE_H