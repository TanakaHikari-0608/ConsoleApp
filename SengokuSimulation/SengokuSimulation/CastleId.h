#pragma once
//======================================
//	戦国シミュレーション  城ID
//======================================
#ifndef __CASTLE_ID_H
#define __CASTLE_ID_H

typedef enum {
    CASTLE_YONEZAWA,        // 米沢城
    CASTLE_KASUGAYAMA,      // 春日山城
    CASTLE_TSUTSUJIGASAKI,  // 躑躅ヶ崎館
    CASTLE_ODAWARA,         // 小田原城
    CASTLE_OKAZAKI,         // 岡崎城
    CASTLE_GIFU,            // 岐阜城
    CASTLE_NIJO,            // 二条城
    CASTLE_YOSHIDAKORIYAMA, // 吉田郡山城
    CASTLE_OKO,             // 岡豊城
    CASTLE_UCHI,            // 内城
    CASTLE_MAX,             // (種類の数)
    CASTLE_NONE = -1,         // リスト終端
} CastleId;

#endif //  __CASTLE_ID_H