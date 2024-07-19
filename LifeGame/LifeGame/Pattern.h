#pragma once
//========================================
//      ライフゲーム:パターン
//========================================
// ★ここにインクルードカード(開始)を記入してください

typedef struct {
	int width;         // パターンの横幅
	int height;        // パターンの縦幅
	bool* data;        // パターン
	const char* name;  // パターンの名前
	bool isLoopCells;  // フィールドの左右、上下がループしているか?
} Pattern;

// パターン選択を行う
Pattern* SelectPattern();

// ★ここにインクルードカード(終了)を記入してください