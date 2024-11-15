#pragma once
//======================================
//	戦国シミュレーション  城主
//======================================
#ifndef __LORD_H
#define __LORD_H

#include "LordId.h"

// 城主の名を取得
const char* GetLordFirstName(LordId id);
// 城主の姓を取得
const char* GetLordFamilyName(LordId id);
// 城主のマップ上の名前を取得
const char* GetLordMapName(LordId id);

#endif //  __LORD_H