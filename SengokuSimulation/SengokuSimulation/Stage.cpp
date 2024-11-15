//======================================
//	í‘ƒVƒ~ƒ…ƒŒ[ƒVƒ‡ƒ“  ƒXƒe[ƒW
//======================================
#include "Stage.h"
#include "Lord.h"
#include "Castle.h"
#include "Utility.h"
#include "Troop.h"
#include "UI.h"
#include "AI.h"
#include <stdio.h>  // printf(),putchar()
#include <stdlib.h> // calloc(),free(),exit()
#include <assert.h> // assert()
// ŠÖ”ƒvƒƒgƒ^ƒCƒv
static void printTurnOrder(Stage* stage, int turn);
static void ExecPlayerTurn(Stage* stage, CastleId currentCastle, Command cmd, CastleId targetCastle, int sendTroopCount);
static void ExecNpcTurn(Stage* stage, CastleId currentCastle, Command cmd, CastleId targetCastle, int sendTroopCount);
static void TransitTroop(Stage* stage, Castle* castle, CastleId targetCastle, int sendTroopCount);
static void AttackTroop(Stage* stage, Castle* castle, CastleId targetCastle, int sendTroopCount);
static void SiegeBattle(Stage* stage, LordId offenseLord, int offenseTroopCount, CastleId defenseCastle);
static int getCastleCount(Stage* stage, LordId lord);
static Castle* GetCastle(Stage* stage, CastleId id);
static LordId changeLordId(Stage* stage, LordId id);

// ‰Šú‰»
void InitializeStage(Stage* stage, Castle castles[], int castlesSize, int startYear, Chronology* chro)
{
	stage->year = startYear;
	stage->chro = chro;
	stage->castles = (Castle*)calloc(castlesSize, sizeof(Castle));
	if (stage->castles == nullptr) {
		printf("calloc¸”s");
		exit(1);
	}
	for (int i = 0; i < castlesSize; i++) {
		stage->castles[i] = castles[i];  // ƒRƒs[
	}
	stage->castlesSize = castlesSize;
	stage->playerLord = LORD_NONE;
	stage->isHonnojiEvent = false;
}
// Œãn––
void FinalizeStage(Stage* stage)
{
	free(stage->castles);
	stage->castles = nullptr;
}
// ƒXƒ^[ƒg
void StartStage(Stage* stage)
{
	for (int i = 0; i < stage->castlesSize; i++) {
		SetCastleOwner(stage, (CastleId)i, (LordId)i);
		SetCastleTroopCount(stage, (CastleId)i, TROOP_BASE);
	}
}
// ƒvƒŒ[ƒ„‘å–¼‚ÌƒZƒbƒg
void SetPlayerLord(Stage *stage, CastleId castleId)
{
	stage->playerLord = GetCastleOwner(stage, castleId);
}
// ƒCƒ“ƒgƒƒƒbƒZ[ƒW
void IntroStage(Stage* stage, CastleId playerCastle)
{
	printf("%s‚³‚ÜA %s‚©‚ç@‚Ä‚ñ‚©‚Æ‚¤‚¢‚Â‚ğ\n‚ß‚´‚µ‚Ü‚µ‚å‚¤‚¼I\n"
		, GetLordFirstName(stage, stage->playerLord)
		, GetCastleName(stage, playerCastle)
	);
	WaitKey();
}
// ƒXƒNƒŠ[ƒ“•`‰æ
void DrawScreen(Stage* stage, DrawMode mode, int turn)
{
	ClearScreen();
	printf("%s",
		//0       1         2         3         4   
		//23456789012345678901234567890123456789012345678901234
		"1570‚Ë‚ñ@````````````````@@@@@`\n"      // 01
		"@@@@@````````````````@0•Ä‘ò5@`\n"      // 02
		"``````````````````1t“ú5@ˆÉ’B@``\n"      // 03
		"```````````````@``ã™@@@@@``\n"      // 04
		"```````````````@`@@@@@@@@``\n"      // 05
		"``````````````@@@@@2çUçP5@@@``\n"      // 06
		"`````````````@@@@@@•“c@@@```\n"      // 07
		"``````@@@@@@@5Šò•Œ5@@@@@@@@```\n"      // 08
		"````@7‹g“c5@6“ñğ5@D“c@4‰ªè5@3¬“c5@```\n"      // 09
		"```@@–Ñ—˜@@‘«—˜@@@@@“¿ì@@–kğ`````\n"      // 10
		"``@```````@@@``````````````\n"      // 11
		"`@@@`@8‰ª–L5``@```````````````\n"      // 12
		"`@@@``’·@```````````````````\n"      // 13
		"`9“àé5```````````````````````\n"      // 14
		"`“‡’Ã````````````````````````\n"      // 15
		"```````````````````````````\n"      // 16
		"\n");

	PrintCursor(1, 1); printf("%4d‚Ë‚ñ", stage->year);
	for (int i = 0; i < stage->castlesSize; i++) {
		for (int i = 0; i < stage->castlesSize; i++);
		Castle* castle = GetCastle(stage, (CastleId)i);
		int curx = GetCastleCurx(castle);
		int cury = GetCastleCury(castle);
		LordId owner = GetCastleOwner(castle);
		int troopCount = GetCastleTroopCount(castle);
		const char* mapName = GetCastleMapName(castle);
		PrintCursor(curx, cury);
		printf("%d%s%d", i, mapName, troopCount);
			(curx, cury + 1);
		printf("%s", GetLordMapName(stage, owner));
	}
	PrintCursor(1, 18);
}
// ƒ^[ƒ“‚Ì‡”Ô‚ğƒVƒƒƒbƒtƒ‹
void MakeTurnOrder(Stage* stage)
{
	CastleId* turnOrder = stage->turnOrder;
	for (int i = 0; i < stage->castlesSize; i++) {
		turnOrder[i] =(CastleId) i;
	}
	for (int i = 0; i < stage->castlesSize; i++) {
		int j = GetRand(stage->castlesSize);
		//turnOrder[i]‚ÆturnOrder[j]‚ğƒXƒƒbƒv
		CastleId tmp = turnOrder[i];
		turnOrder[i] = turnOrder[j];
		turnOrder[j] = tmp;
	}
}
// ”N‰z‚µ
void NextYear(Stage* stage)
{
	stage->year++;
	for (int i = 0; i < stage->castlesSize; i++) {
		Castle* castle = GetCastle(stage, (CastleId)i);
		int troopCount = GetCastleTroopCount(castle);
		if (troopCount < TROOP_BASE) {
			// •º”‚ª BASE‚æ‚è¬‚È‚ç ‘ˆõ
			AddCastleTroopCount(castle, +1);
		}
		else if (troopCount > TROOP_BASE) {
			// •º”‚ª BASE‚æ‚è‘å‚È‚ç Œ¸ˆõ
			AddCastleTroopCount(castle, -1);
		}
	}
}
// u–{”\›‚Ì•Ïv‚©?
bool IsHonnojiEvent(Stage* stage)
{
	return stage->year == 1582
		&& GetCastleOwner(stage, CASTLE_NIJO) == LORD_ODA;
}
// u–{”\›‚Ì•Ïvƒtƒ‰ƒOƒZƒbƒg
void SetHonnojiEvent(Stage* stage)
{
	stage->isHonnojiEvent = true;
}
// ƒ^[ƒ“Às
void ExecTurn(Stage* stage, int turn)
{
	CastleId currentCastle = stage->turnOrder[turn];
	Castle* castle = GetCastle(stage, currentCastle);
	LordId owner = GetCastleOwner(castle);

	DrawScreen(stage, DM_Turn, turn);
	printTurnOrder(stage, turn);
	printf("%s‚¯‚Ì@%s‚Ì@‚Ğ‚å‚¤‚¶‚å‚¤‚¿‚ã‚¤c\n"
		, GetLordFamilyName(owner)
		, GetCastleName(stage, currentCastle)
	);
	putchar('\n');

	CastleId targetCastle;
	int sendTroopCount;
	Command cmd;
	if (owner == stage->playerLord) {
		cmd = InputPlayerTurn(stage, castle, &targetCastle, &sendTroopCount);
		ExecPlayerTurn(stage, currentCastle, cmd, targetCastle, sendTroopCount);
	}
	else {
		cmd = InputNpcTurn(stage, castle, &targetCastle, &sendTroopCount);
		ExecNpcTurn(stage, currentCastle, cmd, targetCastle, sendTroopCount);
	}
}
// ƒvƒŒ[ƒ„ƒ^[ƒ“‚ğÀs
static void ExecPlayerTurn(Stage *stage,CastleId currentCastle,Command cmd,CastleId targetCastle,int sendTroopCount)
{
	Castle* castle = GetCastle(stage, currentCastle);
	switch (cmd) {
	case CMD_Cancel:
		printf("‚µ‚ñ‚®‚ñ‚ğ@‚Æ‚è‚â‚ß‚Ü‚µ‚½\n");
		WaitKey();
		break;
	case CMD_Transit:
		TransitTroop(stage, castle, targetCastle, sendTroopCount);
		printf("%s‚É@%d‚É‚ñ@‚¢‚Ç‚¤@‚µ‚Ü‚µ‚½"
			, GetCastleName(stage, targetCastle)
			, sendTroopCount * TROOP_UNIT
		);
		WaitKey();
		break;

	case CMD_Attack:
		printf("%s‚É@%d‚É‚ñ‚Å@‚µ‚ã‚Â‚¶‚ñ‚¶‚á`II\n"
			, GetCastleName(stage, targetCastle)
			, sendTroopCount * TROOP_UNIT
		);
		WaitKey();
		AttackTroop(stage, castle, targetCastle, sendTroopCount);
		break;
	}
}
// NPCƒ^[ƒ“‚ğÀs
static void ExecNpcTurn(Stage* stage, CastleId currentCastle,Command cmd, CastleId targetCastle, int sendTroopCount)
{
	Castle* castle = GetCastle(stage, currentCastle);
	LordId owner = GetCastleOwner(stage, currentCastle);
	switch (cmd) {
	case CMD_Cancel:
		//printf("‚µ‚ñ‚®‚ñ‚ğ@‚Æ‚è‚â‚ß‚Ü‚µ‚½\n");
		//WaitKey();
		break;
	case CMD_Transit:
		TransitTroop(stage, castle, targetCastle, sendTroopCount);
		printf("%s‚©‚ç@%s‚É@%d‚É‚ñ@‚¢‚Ç‚¤@‚µ‚Ü‚µ‚½\n"
			, GetCastleName(stage, currentCastle)
			, GetCastleName(stage, targetCastle)
			, sendTroopCount * TROOP_UNIT
		);
		WaitKey();
		break;

	case CMD_Attack:
		printf("%s‚Ì@%s%s‚ª@%s‚É@‚¹‚ß‚±‚İ‚Ü‚µ‚½I\n"
			, GetCastleName(stage,currentCastle)
			, GetLordFamilyName(stage,owner)
			, GetLordFirstName(stage,owner)
			, GetCastleName(stage, targetCastle)
		);
		WaitKey();
		AttackTroop(stage, castle, targetCastle, sendTroopCount);
		break;
	}
}
// ˆÚ‘—ˆ—
static void TransitTroop(Stage* stage, Castle* castle, CastleId targetCastle, int sendTroopCount)
{
	AddCastleTroopCount(castle, -sendTroopCount);
	Castle* target = GetCastle(stage, targetCastle);
	AddCastleTroopCount(target, sendTroopCount);
}
// ”h•º(UŒ‚)ˆ—
static void AttackTroop(Stage* stage, Castle* castle, CastleId targetCastle, int sendTroopCount)
{
	AddCastleTroopCount(castle, -sendTroopCount);
	LordId offenseLord = GetCastleOwner(castle);
	SiegeBattle(stage, offenseLord, sendTroopCount, targetCastle);
}
// ƒvƒŒ[ƒ„‚Ì•‰‚¯?
bool IsPlayerLose(Stage *stage)
{
	// ƒvƒŒ[ƒ„‚Ìé‚ª–³‚­‚È‚Á‚½‚ç•‰‚¯!!
	return getCastleCount(stage, stage->playerLord) == 0;
}
// ƒvƒŒ[ƒ„‚ÌŸ‚¿?
bool IsPlayerWin(Stage* stage)
{
	// ƒvƒŒ[ƒ„‚Ìé‚Å–„‚Ü‚Á‚½‚çŸ‚¿
	return getCastleCount(stage, stage->playerLord) == stage->castlesSize;
}
// ƒ^[ƒ“‡”Ô‚ğƒvƒŠƒ“ƒg
static void printTurnOrder(Stage *stage, int turn)
{
	for (int i = 0; i < stage->castlesSize; i++) {
		const char* cur = (i == turn) ? "„" : "@";
		CastleId id = (CastleId)stage->turnOrder[i];
		printf("%s%s", cur, GetCastleMapName(stage, id));
	}
	putchar('\n');
	putchar('\n');
}
// •ïˆÍí“¬‚ğs‚¤
static void SiegeBattle(Stage* stage, LordId offenseLord, int offenseTroopCount, CastleId defenseCastle)
{
	ClearScreen();
	printf("` %s‚Ì@‚½‚½‚©‚¢`\n", GetCastleName(stage, defenseCastle));
	putchar('\n');
	LordId defenseLord = GetCastleOwner(stage, defenseCastle);
	int defenseTroopCount = GetCastleTroopCount(stage, defenseCastle);

	while (true) {
		printf("%s‚®‚ñi%4d‚É‚ñj@‚w@%s‚®‚ñi%4d‚É‚ñj\n"
			, GetLordFamilyName(offenseLord)
			, offenseTroopCount * TROOP_UNIT
			, GetLordFamilyName(defenseLord)
			, defenseTroopCount * TROOP_UNIT
		);
		WaitKey();
		if (offenseTroopCount <= 0 || defenseTroopCount <= 0) {
			break;
		}

		int rnd = GetRand(3);
		if (rnd == 0) {
			defenseTroopCount--;
			SetCastleTroopCount(stage, defenseCastle, defenseTroopCount);
		}
		else {
			offenseTroopCount--;
		}
	}
	putchar('\n');

	if (defenseTroopCount <= 0) {
		// –hŒä‘¤‚Ì•‰‚¯
		SetCastleOwner(stage, defenseCastle, offenseLord);
		SetCastleTroopCount(stage, defenseCastle, offenseTroopCount);

		printf("%s@‚ç‚­‚¶‚å‚¤II\n"
			, GetCastleName(stage,defenseCastle)
		);
		putchar('\n');

		printf("%s‚Í@ %s‚¯‚Ì@‚à‚Ì‚Æ‚È‚è‚Ü‚·\n"
			, GetCastleName(stage, defenseCastle)
			, GetLordFamilyName(offenseLord)
		);
		WaitKey();

		if (getCastleCount(stage,defenseLord) <= 0) {
			RecordChronology(stage->chro
				, "%d‚Ë‚ñ@%s%s‚ª@%s‚Å@%s%s‚ğ@‚Ù‚ë‚Ú‚·\n"
				, stage->year
				, GetLordFamilyName(stage,offenseLord)
				, GetLordFirstName(stage,offenseLord)
				, GetCastleName(stage, defenseCastle)
				, GetLordFamilyName(stage,defenseLord)
				, GetLordFirstName(stage,defenseLord)
			);
		}
	}
	else {
		// UŒ‚‘¤‚Ì•‰‚¯
		printf("%s‚®‚ñ@‚©‚¢‚ß‚ÂII\n"
			, GetLordFamilyName(stage, offenseLord)
		);
		putchar('\n');
		printf("%s‚®‚ñ‚ª@%s‚ğ@‚Ü‚à‚è‚«‚è‚Ü‚µ‚½I\n"
			, GetLordFamilyName(stage,defenseLord)
			, GetCastleName(stage, defenseCastle)
		);
		WaitKey();
	}
}
// ”CˆÓ‚Ìowner‚Ìé‚ğ”‚¦‚é
static int getCastleCount(Stage* stage, LordId lord)
{
	int castleCount = 0;
	for (int i = 0; i < stage->castlesSize; i++) {
		LordId owner = GetCastleOwner(stage, (CastleId)i);
		if (owner == lord) {
			castleCount++;
		}
	}
	return castleCount;
}
//---------------------------------------------------------
// é‚Ì–¼‘O‚ğ“¾‚é
const char* GetCastleName(Stage* stage, CastleId id)
{
	Castle* castle = GetCastle(stage, id);
	return GetCastleName(castle);
}
// é‚Ìéå‚ğæ“¾
LordId GetCastleOwner(Stage* stage, CastleId id)
{
	Castle* castle = GetCastle(stage, id);
	return GetCastleOwner(castle);
}
// é‚Ìéå‚ğƒZƒbƒg
void SetCastleOwner(Stage* stage, CastleId id, LordId owner)
{
	
}
// •º”‚ğ“¾‚é
int GetCastleTroopCount(Stage* stage, CastleId id)
{
	
}
// •º”‚ğƒZƒbƒg
void SetCastleTroopCount(Stage* stage, CastleId id, int troopCount)
{
	// š‚±‚±‚ğƒR[ƒfƒBƒ“ƒO‚µ‚Ä‚­‚¾‚³‚¢B
	// id => Castleƒ|ƒCƒ“ƒ^[æ“¾‚µ‚Ä 
	// SetCastleTroopCount()‚ğŒÄ‚Ñ‚Ü‚·
}
// é‚Ì‹ß—×ƒŠƒXƒg‚ğæ“¾
CastleId* GetCastleConnectedList(Stage* stage, CastleId id)
{
	// š‚±‚±‚ğƒR[ƒfƒBƒ“ƒO‚µ‚Ä‚­‚¾‚³‚¢B
	// id => Castleƒ|ƒCƒ“ƒ^[æ“¾‚µ‚Ä 
	// SetCastleConnectedList()‚ğŒÄ‚Ñ‚Ü‚·
}
// é‚Ìƒ}ƒbƒv–¼‚ğæ“¾
const char* GetCastleMapName(Stage* stage, CastleId id)
{
	// š‚±‚±‚ğƒR[ƒfƒBƒ“ƒO‚µ‚Ä‚­‚¾‚³‚¢B
	// id => Castleƒ|ƒCƒ“ƒ^[æ“¾‚µ‚Ä 
	// GetCastleMapName()‚ğŒÄ‚Ñ‚Ü‚·
}
// id‚©‚ç Castle* ‚ğæ“¾
static Castle* GetCastle(Stage* stage, CastleId id)
{
	assert(0 <= id && id < stage->castlesSize);
	// š‚±‚±‚ğƒR[ƒfƒBƒ“ƒO‚µ‚Ä‚­‚¾‚³‚¢B
	// id => Castleƒ|ƒCƒ“ƒ^[æ“¾‚µ‚Ü‚· 
}
//--------------------------------------
// éå‚Ì–¼‚ğæ“¾
const char* GetLordFirstName(Stage* stage, LordId id)
{
	// š‚±‚±‚ğƒR[ƒfƒBƒ“ƒO‚µ‚Ä‚­‚¾‚³‚¢
	// chnageLordId()‚Å id •ÏX‚µ‚½ŒãA
	// GetLordFirstName()‚ğŒÄ‚Ñ‚Ü‚·
}
// éå‚Ì©‚ğæ“¾
const char* GetLordFamilyName(Stage* stage, LordId id)
{
	// š‚±‚±‚ğƒR[ƒfƒBƒ“ƒO‚µ‚Ä‚­‚¾‚³‚¢
	// chnageLordId()‚Å id •ÏX‚µ‚½ŒãA
	// GetLordFamilyName()‚ğŒÄ‚Ñ‚Ü‚·
}
// éå‚Ìƒ}ƒbƒvã‚Ì–¼‘O‚ğæ“¾
const char* GetLordMapName(Stage* stage, LordId id)
{
	// š‚±‚±‚ğƒR[ƒfƒBƒ“ƒO‚µ‚Ä‚­‚¾‚³‚¢
	// chnageLordId()‚Å id •ÏX‚µ‚½ŒãA
	// GetLordMapName()‚ğŒÄ‚Ñ‚Ü‚·
}
// éåID‚Ì•ÏX
static LordId changeLordId(Stage* stage, LordId id)
{
	// u–{”\›‚Ì•ÏvŒã‚ÍAD“cM’·=>‰HÄG‹g
	// š‚±‚±‚ğƒR[ƒfƒBƒ“ƒO‚µ‚Ä‚­‚¾‚³‚¢B
	// isHonnojiEvent‚ª—§‚Á‚Ä‚¢‚½‚ç D“cM’·‚Ìid‚È‚ç>‰HÄG‹g‚É•Ï‚¦‚Ä‚­‚¾‚³‚¢
}
