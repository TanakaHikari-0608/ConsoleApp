#pragma once
//======================================
//	IntList
//======================================
#ifndef __INT_LIST_H
#define __INT_LIST_H

typedef struct {
	int size;        // 配列サイズ
	int ptr;         // 格納ポインタ
	int* array;      // 配列
} IntList;

// 初期化
void InitializeIntList(IntList* list, int size);
// 後始末
void FinalizeIntList(IntList* list);
// リストに追加
void AddIntList(IntList* list, int value);
// リストの要素数を得る
int GetCountIntList(IntList* list);
// リストの要素を得る
int GetIntList(IntList* list, int idx);
// リストをクリア
void ClearIntList(IntList* list);
// リストをコピー
void CopyIntList(IntList* dst, IntList* src);
// リストをプリントする
void PrintIntList(IntList* list);
// ソートする
void SortIntList(IntList*list, int comp(int,int));
// 配列を取得する
int* GetArrayIntList(IntList* list);

#endif //  __INT_LIST_H
