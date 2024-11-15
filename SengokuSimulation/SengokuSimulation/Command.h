#pragma once
//======================================
//	戦国シミュレーション  コマンド
//======================================
#ifndef __COMMAND_H
#define __COMMAND_H

// 評定の結果
typedef enum {
	CMD_Cancel,     // なにもしない
	CMD_Attack,     // 攻撃
	CMD_Transit,    // 移送
} Command;

#endif //  __COMMAND_H
