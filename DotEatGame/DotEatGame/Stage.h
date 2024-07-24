#pragma once
//======================================
//	ドットイートゲーム　Stage
//======================================
// ★ここにインクルードカード(開始)を記入してください
#ifndef __STAGE_H
#define __STAGE_H
#include "Character.h"
#include "Vector2List.h"

typedef enum {
	MAZE_NONE=' ',   // 空白
	MAZE_WALL='#',   // 壁
	MAZE_DOT='o',    // ドット
	MAZE_PLAYER=CHARA_PLAYER, // プレーヤ
	MAZE_RANDOM=CHARA_RANDOM, // 気まぐれモンスター
	MAZE_CHASE =CHARA_CHASE,  // 追いかけモンスター
	MAZE_AMBUSH=CHARA_AMBUSH, // 先回りモンスター
	MAZE_SIEGE =CHARA_SIEGE,  // 挟み撃ちモンスター
} Maze;

const int MAZE_HEIGHT = 19;
const int MAZE_WIDTH = 19;
const int MONSTER_SIZE = 4;
const int V2LIST_SIZE = 20;

typedef struct {
	char maze[MAZE_HEIGHT][MAZE_WIDTH + 1];
	Character* player;
	Character* monster[MONSTER_SIZE];
	int monsterNum;
	// GetChasePosition() ワーク
	Vector2List v2list;
	Vector2List v2temp;
	int distance[MAZE_HEIGHT][MAZE_WIDTH];
	Character* chaser;
} Stage;

// ステージ初期化
void InitializeStage(Stage* stage, Character* player);
// ステージ後始末
void FinalizeStage(Stage* stage);
// モンスター登録
void RegistMonster(Stage* stage, Character* monster);
// Maze描画
void DrawMaze(Stage* stage);
// ゲームオーバ?
bool IsGameOver(Stage* stage);
// ゲームクリア?
bool IsComplete(Stage* stage);
// Maze端のループ処理
Vector2 GetLoopPosition(Vector2 pos);
// Maze内の位置か?
bool IsInMaze(int x, int y);
// Maze(x,y)取得
char GetMaze(Stage* stage, int x, int y);
// Maze(x,y)セット
void SetMaze(Stage* stage, int x, int y, char c);

// ★ここにインクルードカード(終了)を記入してください
#endif // __STAGE_H