#pragma once
//======================================
//	戦国シミュレーション  UI
//======================================
#ifndef __UI_H
#define __UI_H
#include "Stage.h"
#include "Castle.h"
#include "Command.h"

// プレーヤの城を入力させる
CastleId InputPlayerCastle(Stage* stage);
// プレーヤターンを入力させる
Command InputPlayerTurn(Stage* stage, Castle* castle,CastleId *outTarget, int* sendTroopCount);

#endif // __UI_H
