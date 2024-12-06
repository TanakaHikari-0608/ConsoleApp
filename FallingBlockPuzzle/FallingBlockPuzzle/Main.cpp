//======================================
//      落ち物バズル メイン
//======================================
#include "Stage.h"
#include "Utility.h"
#include "IntervalTimer.h"
#include <stdio.h>
// 関数プロトタイプ
static void game();

int main()
{
	InitRand();

	int c;
	do {
		game();
		printf("もう一度(y/n)?");
		while (true) {
			c = GetKey();
			if (c == 'y' || c == 'n') {
				break;
			}
		}
	} while (c == 'y');

	return 0;
}
// ゲーム
static void game()
{
	Stage stage[1];
	IntervalTimer timer[1];
	InitializeStage(stage);
	SetupFallBlock(stage);

	StartTimer(timer, 10); // FPS=1
	while (IsGameOver(stage) == false) {
		// 一定時間ごとに落ちブロックを1つ落とす
		if (IsInterval(timer)) {
			//
			// ★ここをコーディングしてください
			//  MoveDownFallBlock()をよびだします
			//
			MoveDownFallBlock(stage);

		}
		// キー入力で落ちブロック移動・回転
		if (KeyAvailable()) {
			FallBlock fallBlock = GetFallBlock(stage); // コピー取得
			bool change = false;
			switch (GetKey()) {
				//
				// ★ここをコーディングしてください
				// 入力されたキーが ARROW_DOWN,_LEFT,_RIGHTなら、fallBlockを下左右へ移動させます
				//  (MoveFallBlock()を呼ぶ, changeをセットする )
				// 入力されたキーが　" " (スペース)なら fallBlockを回転させます
				//  (RotateFallBlock()を呼ぶ, changeをセットする )
				//
			case ARROW_DOWN:
				MoveFallBlock(&fallBlock, 0, 1);
				change = true;
				break;
			case ARROW_LEFT:
				MoveFallBlock(&fallBlock, -1, 0);
				change = true;
				break;
			case ARROW_RIGHT:
				MoveFallBlock(&fallBlock, 1, 0);
				change = true;
				break;
			case ' ':
				RotateFallBlock(&fallBlock);
				change = true;
				break;
			}
			if (change) {
				// 移動または回転した落ちブロックがフィールド衝突なければ、更新
				if (BlockIntersectField(stage, &fallBlock) == false) {
					SetFallBlock(stage, &fallBlock);  // コピーセット
					DrawScreen(stage);
				}
			}
		}
	}
}