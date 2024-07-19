#pragma once
//======================================
//	リバーシ Vector2List
//======================================
// ★ここにインクルードガード(開始)を記入してください
#ifndef __VECTOR2_H
#define __VECTOR2_H

#include "Vector2.h"
typedef struct {
	int size;        // 配列サイズ
	int ptr;         // 格納ポインタ
	Vector2* array;  // 配列
} Vector2List;

// 初期化
void InitializeVector2List(Vector2List* list, int size);
// 後始末
void FinalizeVector2List(Vector2List* list);
// リストに追加
void AddVector2List(Vector2List* list, Vector2 pos);
// リストの要素数を得る
int GetCountVector2List(Vector2List* list);
// リストの要素を得る
Vector2 GetVector2List(Vector2List* list, int idx);
// リストをクリア
void ClearVector2List(Vector2List* list);

// ★ここにインクルードガード(終了)を記入してください
#endif // __VECTOR2_H