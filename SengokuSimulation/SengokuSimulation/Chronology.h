#pragma once
//======================================
//	戦国シミュレーション  年表
//======================================
#ifndef __CHRONOLOGY_H
#define __CHRONOLOGY_H

typedef struct {
	int buffSize;
	char* buff;
	char* temp;
} Chronology;

// 初期化
void InitializeChronology(Chronology* chro, int buffSize);
// 後始末
void FinalizeChronology(Chronology* chro);
// クリア
void ClearChronology(Chronology* chro);
// 記録する
void RecordChronology(Chronology* chro, const char* fmt, ...);
// プリントする
void PrintChronology(Chronology* chro);

#endif // __CHRONOLOGY_H