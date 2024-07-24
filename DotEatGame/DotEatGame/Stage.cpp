//======================================
//	ドットイートゲーム　Stage
//======================================
#include "Stage.h"
#include "Character.h"
#include "Utility.h"
#include <stdio.h>   // printf(),putchar()
#include <string.h>  // memcpy()
#include <assert.h>

// 関数プロットタイプ
static const char* GetMazeAA(char c);

const int INIT_DISTANCE = -1;

const char defaultMaze[MAZE_HEIGHT][MAZE_WIDTH + 1] = {
	"#########o#########",
	"#ooooooo#o#ooooooo#",
	"#o###o#o#o#o#o###o#",
	"#o# #o#ooooo#o# #o#",
	"#o###o###o###o###o#",
	"#ooooooooooooooooo#",
	"#o###o###o###o###o#",
	"#ooo#o#ooooo#o#ooo#",
	"###o#o#o###o#o#o###",
	"oooooooo# #oooooooo",
	"###o#o#o###o#o#o###",
	"#ooo#o#ooooo#o#ooo#",
	"#o###o###o###o###o#",
	"#oooooooo oooooooo#",
	"#o###o###o###o###o#",
	"#o# #o#ooooo#o# #o#",
	"#o###o#o#o#o#o###o#",
	"#ooooooo#o#ooooooo#",
	"#########o#########"
};
// ステージ初期化
void InitializeStage(Stage* stage, Character* player)
{
	memcpy(stage->maze, defaultMaze, sizeof(stage->maze));
	stage->player = player;
	stage->monsterNum = 0;
	stage->chaser = nullptr;
	InitializeVector2List(&stage->v2list, V2LIST_SIZE);
	InitializeVector2List(&stage->v2temp, V2LIST_SIZE);
}
// ステージ後始末
void FinalizeStage(Stage* stage)
{
	FinalizeVector2List(&stage->v2list);
	FinalizeVector2List(&stage->v2temp);
}
// モンスター登録
void RegistMonster(Stage* stage, Character* monster)
{
	assert(stage->monsterNum < MONSTER_SIZE);
	stage->monster[stage->monsterNum++] = monster;
	if (monster->id == CHARA_CHASE) {
		stage->chaser = monster;
	}
}
// メイズ描画
void DrawMaze(Stage* stage)
{
	Stage screen;
	memcpy(screen.maze, stage->maze,sizeof(screen.maze));
	// キャラをMazeに書き込む
	Character* player = stage->player;
	SetMaze(&screen, player->pos.x, player->pos.y, player->id);
	for (int i = 0; i < stage->monsterNum; i++) {
		Character* monster = stage->monster[i];
		SetMaze(&screen, monster->pos.x, monster->pos.y, monster->id);
	}
	ClearScreen();
	for (int y = 0; y < MAZE_HEIGHT; y++) {
		for (int x = 0; x < MAZE_WIDTH; x++) {
			char c = GetMaze(&screen, x, y);
			printf("%s", GetMazeAA(c));
		}
		putchar('\n');
	}

	// デバッグ
//	printf("player(%d,%d)\n", player->pos.x, player->pos.y);
//	for (int i = 0; i < stage->monsterNum; i++) {
//		Character* mon = stage->monster[i];
//		printf("monster-%d(%d,%d)\n", mon->id, mon->pos.x, mon->pos.y);
//	}
}
// ゲームオーバ?
bool IsGameOver(Stage* stage)
{
	Character* player = stage->player;
	for (int i = 0; i < stage->monsterNum; i++) {
		Character* monster = stage->monster[i];
		if (Vector2Equ(monster->pos, player->pos)) {
			return true;
		}
	}
	return false;
}
// ゲーム完了(ドット完食)?
bool IsComplete(Stage* stage)
{
	for (int y = 0; y < MAZE_HEIGHT; y++) {
		for (int x = 0; x < MAZE_WIDTH; x++) {
			if (GetMaze(stage, x, y) == MAZE_DOT) {
				return false;
			}
		}
	}
	return true;
}
// Maze(x,y)取得
char GetMaze(Stage* stage, int x, int y)
{
	if (IsInMaze(x, y)) {
		return stage->maze[y][x];
	}
	return MAZE_WALL;
}
// Maze(x,y)セット
void SetMaze(Stage* stage, int x, int y, char c)
{
	if (IsInMaze(x, y)) {
		stage->maze[y][x] = c;
	}
}

// Mazeのアスキーアート取得
static const char* GetMazeAA(char c)
{
	switch (c) {
	default: assert(false);
	case MAZE_NONE: return "　";
	case MAZE_WALL:return "■";
	case MAZE_DOT:return "・";
	case MAZE_PLAYER:return "〇";
	case MAZE_RANDOM:return "☆";
	case MAZE_CHASE :return "凸";
	case MAZE_AMBUSH:return "◇";
	case MAZE_SIEGE :return "凹";
	}
}
// MAZE端を超えた座標のループ処理(補正)
Vector2 GetLoopPosition(Vector2 pos)
{
	pos.x = (pos.x + MAZE_WIDTH) % MAZE_WIDTH;
	pos.y = (pos.y + MAZE_HEIGHT) % MAZE_HEIGHT;
	return pos;
}
// Maze内の位置か?
bool IsInMaze(int x, int y) 
{
	return 0 <= x && x < MAZE_WIDTH
		&& 0 <= y && y < MAZE_HEIGHT;
}
