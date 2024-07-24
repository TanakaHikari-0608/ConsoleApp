#pragma once
//======================================
//	2Dベクター
//======================================
// ★ここにインクルードカード(開始)を記入してください
#ifndef __VECTOR2_H
#define __VECTOR2_H

typedef struct {
	int x;
	int y;
} Vector2;

// ４方向
typedef enum {
	DIR_UP,
	DIR_LEFT,
	DIR_DOWN,
	DIR_RIGHT,
	DIR_MAX,
} DIRECTION;

// ベクター加算
void AddVector2(Vector2* a, Vector2* b);
// ４方向のベクター取得
Vector2 GetDirVector2(DIRECTION d);
// 2Dベクターの加算
Vector2 Vector2Add(Vector2 a, Vector2 b);
// 2Dベクターの減算
Vector2 Vector2Sub(Vector2 a, Vector2 b);
// 2Dベクターの等価?
bool Vector2Equ(Vector2 a, Vector2 b);

// ★ここにインクルードカード(終了)を記入してください
#endif // __VECTOR2_H