#pragma once
//======================================
//	戦国シミュレーション  城主ID
//======================================
#ifndef __LORD_ID_H
#define __LORD_ID_H

typedef enum {
    LORD_DATE,      // 伊達輝宗
    LORD_UESUGI,    // 上杉謙信
    LORD_TAKEDA,    // 武田信玄
    LORD_HOJO,      // 北条氏政
    LORD_TOKUGAWA,  // 徳川家康
    LORD_ODA,       // 織田信長
    LORD_ASHIKAGA,  // 足利義昭
    LORD_MORI,      // 毛利元就
    LORD_CHOSOKABE, // 長宗我部元親
    LORD_SIMAZU,    // 島津義久
    LORD_HASHIBA,   // 羽柴秀吉
    LORD_MAX,       // (種類の数)
    LORD_NONE = -1,
} LordId;

#endif //  __LORD_ID_H