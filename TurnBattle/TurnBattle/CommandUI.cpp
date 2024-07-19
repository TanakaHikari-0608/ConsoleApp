//======================================
//	ターン制バトル コマンド入力
//======================================
#include "CommandUI.h"
#include "TurnBattle.h" // DrawBattlScreen()
#include "Utility.h"  // GetKey()
#include <stdio.h>  // printf()

const char* CommandName[] = {
	"たたかう",
	"じゅもん",
	"にげる",
};

// プレーヤのコマンド取得
Command GetPlayerCommand(TurnBattle *btl)
{
	int cmd = 0;
	while (true) {
		DrawBattleScreen(btl);
		for (int i = 0; i < COMMAND_MAX; i++) {
			const char *cur= (i == cmd) ? "＞" : "　";
			printf("%s%s\n", cur, CommandName[i]);
		}
		switch (GetKey()) {
		case ARROW_UP:
			cmd--;
			if (cmd < 0) {
				cmd = COMMAND_MAX - 1;
			}
			break;
		case ARROW_DOWN:
			cmd++;
			if (cmd >= COMMAND_MAX) {
				cmd = 0;
			}
			break;
		case DECIDE:
			return (Command)cmd;
		}
	}
}
// 敵のコマンド取得
Command GetEnemyCommand()
{
	return COMMAND_FIGHT;
}