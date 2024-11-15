//======================================
//	戦国シミュレーション  AI
//======================================
#include "AI.h"
#include "IntList.h"
#include "Troop.h"  // TROOP_XXXX
#include "CastleId.h"
#include "Utility.h"  // GetRand()
 
// 関数プロトタイプ
static CastleId getMinTroopCastle(IntList* intList, Stage* stage);
static bool isFrontCastle(Stage* stage, CastleId caseltId);
static int cmpCastleByTroop(int a, int b);

static Stage* s_stage;

// NPCターンの入力(思考)
Command InputNpcTurn(Stage* stage, Castle* castle, CastleId* outTarget, int* outTroopCount)
{
	LordId npcLord = GetCastleOwner(castle);
	int npcTroopCount = GetCastleTroopCount(castle);
	Command cmd = CMD_Cancel;

	IntList enemyCastleList[1];
	InitializeIntList(enemyCastleList, CASTLE_MAX);

	// 隣接する敵の城をリスティング
	CastleId* connectedList = GetCastleConnectedList(castle);
	for (int i = 0; ; i++) {
		CastleId id = connectedList[i];
		if (id == CASTLE_NONE) break;
		if (GetCastleOwner(stage, id) != npcLord) {
			AddIntList(enemyCastleList, id);
		}
	}
	if (GetCountIntList(enemyCastleList) > 0) {
		// TroopCount最小の城を取得
		CastleId targetCastle = getMinTroopCastle(enemyCastleList, stage);

		// 攻め込む条件チェック
		//  ・こちらの兵力は標準値以上であるか?
		//  ・こちらの兵力が守備兵を差し引いて相手の2倍以上か?
		int tgtTroopCount = GetCastleTroopCount(stage, targetCastle);
		if (npcTroopCount >= TROOP_BASE
			|| npcTroopCount - 1 >= tgtTroopCount * 2) {

			int troopCount = npcTroopCount - 1;
			if (troopCount < 0) {
				troopCount = 0;
			}

			*outTarget = targetCastle;
			*outTroopCount = troopCount;
			cmd=CMD_Attack;
		}
	}
	else {
		// 隣接する敵がいない
		IntList cnnctCastleList[1];
		IntList frontCastleList[1];
		InitializeIntList(cnnctCastleList, CASTLE_MAX);
		InitializeIntList(frontCastleList, CASTLE_MAX);
		// 前線の城をリスティング
		for (int i = 0; ; i++) {
			CastleId id = connectedList[i];
			if (id == CASTLE_NONE) break;
			if (isFrontCastle(stage, id)) {
				AddIntList(frontCastleList, id);
			}
			AddIntList(cnnctCastleList, id);
		}

		CastleId targetCastle;
		int sendTroopCount;
		if (GetCountIntList(frontCastleList) > 0) {
			targetCastle = getMinTroopCastle(frontCastleList, stage);
			sendTroopCount = TROOP_MAX - GetCastleTroopCount(stage, targetCastle);
			if (sendTroopCount > npcTroopCount) {
				// 前線の城に送るなら、全部
				sendTroopCount = npcTroopCount;
			}
		}
		else {
			targetCastle = getMinTroopCastle(cnnctCastleList, stage);
			sendTroopCount = TROOP_MAX - GetCastleTroopCount(stage, targetCastle);
			int tmp = npcTroopCount - (TROOP_BASE - 1);
			if (sendTroopCount > tmp) {
				// 前線でないなら、BASE-1 を残して、それより大きい分を
				sendTroopCount = tmp;
			}
		}
		if (sendTroopCount > 0) {
			*outTarget = targetCastle;
			*outTroopCount = sendTroopCount;
			cmd = CMD_Transit;
		}
		FinalizeIntList(cnnctCastleList);
		FinalizeIntList(frontCastleList);
	}
	FinalizeIntList(enemyCastleList);

	return cmd;
}
// CastleIdリストから Troop最小を取得する
static CastleId getMinTroopCastle(IntList* intList, Stage* stage)
{
	// TroopCountの小さい順にソート
	s_stage = stage;
	SortIntList(intList, cmpCastleByTroop);
	// TroopCount最小の数をかぞえる
	int* array = GetArrayIntList(intList);
	int  count = GetCountIntList(intList);
	int minTroopCount = GetCastleTroopCount(stage,(CastleId)array[0]);
	int i = 1;
	for (; i < count; i++) {
		if (minTroopCount < GetCastleTroopCount(stage, (CastleId)array[i])) {
			break;
		}
	}
	// TroopCount最小の中からランダムに選ぶ
	int idx = GetRand(i);
	return (CastleId)array[idx];
}
// 前線の城か?
static bool isFrontCastle(Stage* stage, CastleId castleId)
{
	// 隣接に敵がいれば前線の城である
	CastleId* connectedList = GetCastleConnectedList(stage, castleId);
	LordId owner = GetCastleOwner(stage, castleId);
	for (int i = 0; ; i++) {
		CastleId id = connectedList[i];
		if (id == CASTLE_NONE) break;
		if (GetCastleOwner(stage, id) != owner) {
			return true;
		}
	}
	return false;
}
// ソートのための比較関数
static int cmpCastleByTroop(int a,int b)
{
	int troop_a=GetCastleTroopCount(s_stage, (CastleId)a);
	int troop_b=GetCastleTroopCount(s_stage, (CastleId)b);
	return troop_a - troop_b;
}
