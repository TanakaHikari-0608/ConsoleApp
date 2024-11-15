#pragma once
//======================================
//	コマンド定義
//======================================
#ifndef __COMMAND_H
#define __COMMAND_H

enum Command {
	COMMAND_FIGHT,  // 戦う
	COMMAND_SPELL,  // 呪文
	COMMAND_ESCAPE, // 逃げる
	COMMAND_MAX,
};
#endif // __COMMAND_H