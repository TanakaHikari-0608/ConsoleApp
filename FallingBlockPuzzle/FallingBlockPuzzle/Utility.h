//======================================
//	ユーティリティ
//======================================
#ifndef __UTILITY_H
#define __UTILITY_H

extern const char* EscBLACK;
extern const char* EscRED;
extern const char* EscGREEN;
extern const char* EscYELLOW;
extern const char* EscBLUE;
extern const char* EscMAZENTA;
extern const char* EscCYAN;
extern const char* EscWHITE;
extern const char* EscDEFAULT;

enum Key {
	ARROW_UP = 0xe048,
	ARROW_LEFT = 0xe04b,
	ARROW_DOWN = 0xe050,
	ARROW_RIGHT = 0xe04d,
	DECIDE = 0x0d,
	ESC = 0x1b,
	SPACE = 0x20,
};
// 乱数初期化
void InitRand();
// 0～max-1 の一様乱数を得る
int GetRand(int max);
// キー入力を待つ
void WaitKey();
// キー入力取得
Key GetKey();
// キー入力ありか?
bool KeyAvailable();
// スクリーン消去
void ClearScreen();

#endif // __UTILITY_H