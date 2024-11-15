//======================================
//	IntList(intの可変長配列)
//======================================
#include "IntList.h"
#include <stdio.h>   // printf()
#include <stdlib.h>  // calloc(),free(),exit()
// 初期化
void InitializeIntList(IntList* list, int size)
{
	list->array = (int*)calloc(size, sizeof(int));
	if (list->array == nullptr) {
		printf("calloc失敗\n");
		exit(1);
	}
	list->size = size;
	list->ptr = 0;
}
// 後始末
void FinalizeIntList(IntList* list)
{
	free(list->array);
	list->array=nullptr;
	list->size = 0;
	list->ptr = 0;
}
// リストに追加
void AddIntList(IntList* list, int value)
{
	if (list->ptr < list->size) {
		list->array[list->ptr++] = value;
	}
}
// リストの要素数を得る
int GetCountIntList(IntList* list)
{
	return list->ptr;
}
// リストの要素を得る
int GetIntList(IntList* list, int idx)
{
	if (idx < list->ptr) {
		return list->array[idx];
	}
	return  -1;
}
// リストをクリアする
void ClearIntList(IntList* list)
{
	list->ptr = 0;
}
// リストをコピーする
void CopyIntList(IntList* dst, IntList* src)
{
	ClearIntList(dst);
	int count = GetCountIntList(src);
	for (int i = 0; i < count; i++) {
		int value = GetIntList(src, i);
		AddIntList(dst, value);
	}
}
// リストをプリント(デバッグ用)
void PrintIntList(IntList* list)
{
	printf("IntList(%d):", list->ptr);
	for (int i = 0; i < list->ptr; i++) {
		printf("%d ", list->array[i]);
	}
	putchar('\n');
}
// 比較関数を用いてソート
void SortIntList(IntList *list,int comp(int,int))
{
	// 選択ソートを行う
	for (int i = 0; i < list->ptr-1; i++) {
		int minIdx = i;
		int min = list->array[minIdx];
		for (int j = i + 1; j < list->ptr; j++) {
			if (comp(min, list->array[j]) > 0) {
				minIdx = j;
				min = list->array[minIdx];
			}
		}
		if (minIdx != i) {
			// array[i]とarray[minIdx] 交換
			list->array[minIdx] = list->array[i];
			list->array[i] = min;
		}
	}
}
// 配列を取得する
int* GetArrayIntList(IntList* list)
{
	return list->array;
}
