//======================================
//      ライフゲーム メイン
//======================================
#include "Field.h"
#include "Pattern.h"
#include "IntervalTimer.h"
#include "Utility.h"
#include <stdio.h>  // printf()
// 関数プロトタイプ
void game();
// 定数
const int FIELD_WIDTH = 48;
const int FIELD_HEIGHT = 48;
const int FPS = 10;

int main()
{
	InitRand();

    int c;
    do {
        game();
        printf("もう一度(y/n)?");
        while (true) {
            c = GetKey();
            if (c == 'y' || c == 'n') {
                break;
            }
        }
    } while (c == 'y');
    
    return 0;
}

void game()
{
    const int patternWidth = 10;
    const int patternHeight = 8;
    bool _pattern[patternHeight][patternWidth] = {
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,1,0,0},
        {0,0,0,0,0,1,0,1,1,0},
        {0,0,0,0,0,1,0,1,0,0},
        {0,0,0,0,0,1,0,0,0,0},
        {0,0,0,1,0,0,0,0,0,0},
        {0,1,0,1,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0}
    };
    Pattern pattern = {
        patternWidth,     // パターンの横幅
        patternHeight,    // パターンの縦幅
        (bool*)_pattern,  // パターン
        "",               // パターンの名前
        true,             // ループ
    };

    Field field;
    IntervalTimer timer;

    InitializeField(&field, FIELD_WIDTH, FIELD_HEIGHT, true);
    TransferPattern(&field, &pattern);

    DrawField(&field);
    StartTimer(&timer, FPS);
    while (true) {
        if (IsInterval(&timer)) {
            StepSimulation(&field);
            DrawField(&field);
        }
        if (KeyAvailable()) {
            int c = GetKey();
            // ESCキーで game()終了
            if (c == ESC) {
                break;
            }
            else if (c == 'p') {
                Pattern* pat = SelectPattern();
                if (pat != nullptr) {
                    TransferPattern(&field, pat);
                    DrawField(&field);
                    WaitKey();
                }
            }
            else{
                // その他のキーで一時停止
                do{
                    StepSimulation(&field);
                    DrawField(&field);
                    // Spaceキーで１ステップずつ
                }while (GetKey() == SPACE);
            }
        }
    }

    FinalizeField(&field);
}