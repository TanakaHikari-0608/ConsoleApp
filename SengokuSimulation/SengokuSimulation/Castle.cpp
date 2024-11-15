//======================================
//	戦国シミュレーション  城
//======================================
#include "Castle.h"
#include "Lord.h"
#include "Troop.h"

Castle castles[] =
{
	// CASTLE_YONEZAWA   米沢城 
	{
		"米沢城",   // 名前
		LORD_DATE,  // 城主
		TROOP_BASE, // 兵数
		// 接続された城のリスト
		{
			CASTLE_KASUGAYAMA,  // 春日山城
			CASTLE_ODAWARA,     // 小田原城
			CASTLE_NONE,
		},
		45, 2,      // 描画位置
		"米沢",     // マップ上の名前
	},
	// CASTLE_KASUGAYAMA 春日山城
	{
		"春日山城",     // 名前
		LORD_UESUGI,    // 城主
		TROOP_BASE,     // 兵数
		// 接続された城のリスト
		{
			CASTLE_YONEZAWA,        // 米沢城
			CASTLE_TSUTSUJIGASAKI,  // 躑躅ヶ崎館
			CASTLE_GIFU,             // 岐阜城
			CASTLE_NONE,
		},
		37, 3,          // 描画位置
		"春日",         // マップ上の名前
	},
	// CASTLE_TSUTSUJIGASAKI 躑躅ヶ崎館
	{
		"躑躅ヶ崎館",   // 名前
		LORD_TAKEDA,    // 城主
		TROOP_BASE,     // 兵数
		// 接続された城のリスト
		{
			CASTLE_KASUGAYAMA,  // 春日山城
			CASTLE_ODAWARA,     // 小田原城
			CASTLE_OKAZAKI,     // 岡崎城
			CASTLE_NONE,
		},
		39, 6,          // 描画位置
		"躑躅",         // マップ上の名前
	},
	// CASTLE_ODAWARA    小田原城
	{
		"小田原城", // 名前
		LORD_HOJO,  // 城主
		TROOP_BASE, // 兵数
		// 接続された城のリスト
		{
			CASTLE_YONEZAWA,        // 米沢城
			CASTLE_TSUTSUJIGASAKI,  // 躑躅ヶ崎館
			CASTLE_OKAZAKI,         // 岡崎城
			CASTLE_NONE,
		},
		41, 9,      // 描画位置
		"小田",     // マップ上の名前
	},
	// CASTLE_OKAZAKI    岡崎城
	{
		"岡崎城",       // 名前
		LORD_TOKUGAWA,  // 城主
		TROOP_BASE,     // 兵数
		// 接続された城のリスト
		{
			CASTLE_TSUTSUJIGASAKI,  // 躑躅ヶ崎館
			CASTLE_ODAWARA,         // 小田原城
			CASTLE_GIFU,            // 岐阜城
			CASTLE_NONE,
		},
		33, 9,          // 描画位置
		"岡崎",         // マップ上の名前
	},
	// CASTLE_GIFU   岐阜城
	{
		"岐阜城",   // 名前
		LORD_ODA,   // 城主
		TROOP_BASE, // 兵数
		// 接続された城のリスト
		{
			CASTLE_KASUGAYAMA,  // 春日山城
			CASTLE_OKAZAKI,     // 岡崎城
			CASTLE_NIJO,        // 二条城
			CASTLE_NONE,
		},
		27, 8,      // 描画位置
		"岐阜",     // マップ上の名前
	},
	// CASTLE_NIJO   二条城
	{
		"二条城",       // 名前
		LORD_ASHIKAGA,  // 城主
		TROOP_BASE,     // 兵数
		// 接続された城のリスト
		{
			CASTLE_GIFU,            // 岐阜城
			CASTLE_YOSHIDAKORIYAMA, // 吉田郡山城
			CASTLE_OKO,             // 岡豊城
			CASTLE_NONE,
		},
		19, 9,          // 描画位置
		"二条",         // マップ上の名前
	},
	// CASTLE_YOSHIDAKORIYAMA    吉田郡山城
	{
		"吉田郡山城",   // 名前
		LORD_MORI,      // 城主
		TROOP_BASE,     // 兵数
		// 接続された城のリスト
		{
			CASTLE_NIJO,    // 二条城
			CASTLE_OKO,     // 岡豊城
			CASTLE_UCHI,    // 内城
			CASTLE_NONE,
		},
		11, 9,          // 描画位置
		"吉田",         // マップ上の名前
	},
	// CASTLE_OKO    岡豊城
	{	
		"岡豊城",       // 名前
		LORD_CHOSOKABE, // 城主
		TROOP_BASE,     // 兵数
		// 接続された城のリスト
		{
			CASTLE_NIJO,            // 二条城
			CASTLE_YOSHIDAKORIYAMA, // 吉田郡山城
			CASTLE_UCHI,            // 内城
			CASTLE_NONE,
		},
		13,12,          // 描画位置
		"岡豊",         // マップ上の名前
	},
	// CASTLE_UCHI  内城
	{
		"内城",         // 名前
		LORD_SIMAZU,    // 城主
		TROOP_BASE,     // 兵数
		//  接続された城のリスト
		{
			CASTLE_YOSHIDAKORIYAMA, // 吉田郡山城
			CASTLE_OKO,             // 岡豊城
			CASTLE_NONE,
		},
		 3,14,          // 描画位置
		"内城",         // マップ上の名前
	},
};
// 城の名前を取得
const char* GetCastleName(Castle* castle)
{
	return castle->name;
}
// 城主IDを取得
LordId GetCastleOwner(Castle* castle)
{
	return castle->owner;
}
// 兵数を取得
int GetCastleTroopCount(Castle* castle)
{
	return castle->troopCount;
}
// 近隣の城リストを取得
CastleId* GetCastleConnectedList(Castle* castle)
{
	return castle->connectedList;
}
// 描画X座標を取得
int GetCastleCurx(Castle* castle)
{
	return castle->curx;
}
// 描画Y座標を取得
int GetCastleCury(Castle* castle)
{
	return castle->cury;
}
// マップ上の名前を取得
const char* GetCastleMapName(Castle* castle)
{
	return castle->mapName;
}
// 兵数を代入する
void SetCastleTroopCount(Castle* castle, int troopCount)
{
	castle->troopCount = troopCount;
// 城主をセット
void SetCastleOwner(Castle* castle, LordId owner)
{
	castle->owner = owner;
}
// 兵数に加算
void AddCastleTroopCount(Castle* castle, int add)
{
	int value = castle->troopCount + add;
	if (value < 0;) {
		value = 0;
	}
	else if (value > TROOP_MAX) {
		value = 0;
	}
	castle->troopCount = value;
}
