#pragma once
//======================================
//	戦国シミュレーション  AI
//======================================
#ifndef __AI_H
#define __AI_H
#include "Stage.h"
#include "Castle.h"
#include "Command.h"

// NPCターンの入力(思考)
Command InputNpcTurn(Stage* stage, Castle* castle, CastleId* outTarget, int* outTroopCount);

#endif //  __AI_H