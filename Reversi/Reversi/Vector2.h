#pragma once
//======================================
//	リバーシ 2Dベクター
//======================================
// ★ここにインクルードガード(開始)を記入してください
#ifndef __VECTOR2_H
#define __VECTOR2_H



typedef struct {
	int x;
	int y;
} Vector2;

// ８方向
typedef enum {
	DIR_UP,
	DIR_UP_LEFT,
	DIR_LEFT,
	DIR_DOWN_LEFT,
	DIR_DOWN,
	DIR_DOWN_RIGHT,
	DIR_RIGHT,
	DIR_UP_RIGHT,
	DIR_MAX,
} DIRECTION;

// ベクター加算
void AddVector2(Vector2* a, Vector2* b);
// ８方向のベクター取得
Vector2 GetDirVector2(DIRECTION d);

// ★ここにインクルードガード(終了)を記入してください
#endif // __VECTOR2_H