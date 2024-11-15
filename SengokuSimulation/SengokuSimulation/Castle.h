#pragma once
//======================================
//	戦国シミュレーション  城
//======================================
#ifndef __CASTLE_H
#define __CASTLE_H
#include "LordId.h"
#include "CastleId.h"

const int CONNECTED_SIZE = 10;

typedef struct {
    const char* name;    // 名前
    LordId owner;        // 城主
    int troopCount;      // 兵数
    CastleId connectedList[CONNECTED_SIZE]; // 接続された城のリスト
    int  curx, cury;     // 描画位置
    const char* mapName; // マップ上の名前
} Castle;

extern Castle castles[];

// 城の名前を取得
const char* GetCastleName(Castle* castle);
// 城主IDを取得
LordId GetCastleOwner(Castle* castle);
// 兵数を取得
int GetCastleTroopCount(Castle* castle);
// 近隣の城リストを取得
CastleId* GetCastleConnectedList(Castle* castle);
// 描画X座標を取得
int GetCastleCurx(Castle* castle);
// 描画Y座標を取得
int GetCastleCury(Castle* castle);
// マップ上の名前を取得
const char* GetCastleMapName(Castle* castle);
// 兵数を代入する
void SetCastleTroopCount(Castle* castle, int troopCount);
// 城主をセット
void SetCastleOwner(Castle* castle, LordId owner);
// 兵数に加算する
void AddCastleTroopCount(Castle* castle, int add);

#endif //  __CASTLE_H