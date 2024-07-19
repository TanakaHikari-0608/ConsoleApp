//======================================
//	リバーシ UI
//======================================
#include "Mode.h"
#include "Reversi.h"
#include "Vector2.h"
#include "Utility.h"
#include <stdio.h>  // printf()

Mode SelectMode()
{
	static const char* modeName[] = {
		"１Ｐ　ＧＡＭＥ",
		"２Ｐ　ＧＡＭＥ",
		"ＷＡＴＣＨ"
	};
	int sel = 0;
	while (true) {
		ClearScreen();
		puts("モードを選択して\nください\n");
		for (int i = 0; i < MODE_MAX; i++) {
			const char* cur = (sel == i) ? ">" : " ";
			printf("%s%s\n\n", cur, modeName[i]);
		}
		switch(GetKey()) {
		case ARROW_UP:
			sel--;
			if (sel < 0) {
				sel = MODE_MAX - 1;
			}
			break;
		case ARROW_DOWN:
			sel++;
			if (sel >= MODE_MAX) {
				sel = 0;
			}
			break;
		case DECIDE:
			return (Mode)sel;
		}
	}
}
// 位置入力
Vector2 InputPosition(Reversi* reversi)
{
	Vector2 pos = { 3,3 };
	while (true) {
		DrawScreen(reversi, pos,IN_PLAY);
		switch (GetKey()) {
		//
		// ★ここをコーディングしてください。
		// キー入力(ARROW_UP,_DOWN,_LEFT_RIGHT)によって
		//  カーソル位置(pos)を更新します
		//  pos.x は 0～BOARD_WID-1 で　右端と左端でループします。
		//  pos.y は 0～BOARD_HEI-1 で 上端と下端でループします。
		//
		case DECIDE:
			if (CheckCanPlace(reversi, reversi->turn, pos) == false) {
				printf("そこには　置けません\n");
				WaitKey();
				break;
			}
			return pos;
		}
	}