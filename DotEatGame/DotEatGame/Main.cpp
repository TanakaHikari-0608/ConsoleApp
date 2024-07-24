//======================================
//	ƒhƒbƒgƒC[ƒgƒQ[ƒ€@ƒƒCƒ“
//======================================
#include "StageMoveCharacter.h"
#include "Stage.h"
#include "Character.h"
#include "Utility.h"
#include "IntervalTimer.h"
#include <stdio.h>  // printf(),putchar()
// ŠÖ”ƒvƒƒgƒ^ƒCƒv
void game();
void DrawGameOver();
void DrawCongratulations();

int main()
{
	InitRand();

	int c;
	do {
		game();
		printf("‚à‚¤ˆê“x(y/n)?");
		while (true) {
			c = GetKey();
			if (c == 'y' || c == 'n') {
				break;
			}
		}
	} while (c == 'y');
	return 0;
}

void game()
{
	Character player;
	Character monster1;
	Character monster2;
	Character monster3;
	Character monster4;
	Stage stage;

	InitCharacter(&player, CHARA_PLAYER, { 9, 13 });
	InitCharacter(&monster1, CHARA_RANDOM, { 1, 1 });
	InitCharacter(&monster2, CHARA_CHASE, { 17, 1 });
	InitCharacter(&monster3, CHARA_AMBUSH, { 1, 17 });
	InitCharacter(&monster4, CHARA_SIEGE, { 17, 17 });

	InitializeStage(&stage, &player);
	RegistMonster(&stage, &monster1);
	RegistMonster(&stage, &monster2);
	RegistMonster(&stage, &monster3);
	RegistMonster(&stage, &monster4);

	DrawMaze(&stage);
	WaitKey();

	IntervalTimer timer;
	StartTimer(&timer,2); // FPS=2
	while (true) {
		if (IsInterval(&timer)) {
			MoveMonsters(&stage);
			DrawMaze(&stage);
			if (IsGameOver(&stage)) {
				DrawGameOver();
				WaitKey();
				break;
			}
		}

		if (KeyAvailable()) {
			MovePlayer(&stage);
			DrawMaze(&stage);
			if(IsComplete(&stage)){
				DrawCongratulations();
				WaitKey();
				break;
			}
		}
	}
	FinalizeStage(&stage);
}
// uGame Overv•\¦
void DrawGameOver()
{
	ClearScreen();
	for (int i = 0; i < MAZE_HEIGHT; i++) {
		if (i == MAZE_HEIGHT / 2) {
			printf("          ‚f‚`‚l‚d@‚n‚u‚d‚q\n");
		}
		else {
			putchar('\n');
		}
	}
}
// uCongratulationsv•\¦
void DrawCongratulations()
{
	ClearScreen();
	for (int i = 0; i < MAZE_HEIGHT; i++) {
		if (i == MAZE_HEIGHT / 2) {
			printf("     ‚b‚n‚m‚f‚q‚`‚s‚t‚k‚`‚s‚h‚n‚m‚r!\n");
		}
		else {
			putchar('\n');
		}
	}
}