#pragma once
//======================================
//	コマンドUI
//======================================
#ifndef __COMMAND_UI_H
#define __COMMAND_UI_H

#include "Command.h"
#include "TurnBattle.h"

// プレーヤのコマンド取得
Command GetPlayerCommand(TurnBattle* btl);
// 敵のコマンド取得
Command GetEnemyCommand();

#endif // __COMMAND_UI_H