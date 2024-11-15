//======================================
//	戦国シミュレーション メイン
//======================================
#include "Stage.h"
#include "Lord.h"
#include "UI.h"
#include "Utility.h"
#include "Chronology.h"
#include <stdio.h>   // printf(),putchar()
#include <stdlib.h>
// 関数プロトタイプ
static void game();
static void DrawHonnojiEvent(Stage* stage);
static void DrawGameOver(Stage* stage);
static void DrawEnding(Stage *stage);

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

const int CHRONOLOGY_BUFF_SIZE = 1024;
const int START_YEAR = 1570;
extern Castle castles[];

static void game()
{
    Stage stage[1];
    Chronology chro[1];
    InitializeChronology(chro, CHRONOLOGY_BUFF_SIZE);
    InitializeStage(stage, castles, CASTLE_MAX, START_YEAR, chro);

    StartStage(stage);
    CastleId playerCastle = InputPlayerCastle(stage);
    SetPlayerLord(stage, playerCastle);
    IntroStage(stage, playerCastle);

    while (true) {
        // ターンの順番をシャフル
        MakeTurnOrder(stage);
        for (int i = 0; i < stage->castlesSize; i++) {
            // 各城のターン実行
            ExecTurn(stage,i);
            // プレーヤの負け?
            if (IsPlayerLose(stage)) {
                DrawGameOver(stage);
                goto exit;
            }
            // プレーヤの勝ち
            if (IsPlayerWin(stage)) {
                DrawEnding(stage);
                goto exit;
            }
        }
        // 年越し
        NextYear(stage);
        // 「本能寺の変」イベント
        if (IsHonnojiEvent(stage)) {
            SetHonnojiEvent(stage);
            DrawHonnojiEvent(stage);
        }
    }
exit:
    FinalizeStage(stage);
    FinalizeChronology(chro);
}

static void DrawHonnojiEvent(Stage *stage)
{
    DrawScreen(stage, DM_Event, 0);
    printf(
        "明智光秀「てきは　本能寺に　あり！\n"
        "\n"
        "明智光秀が　本能寺の　織田信長を　しゅうげきした！\n"
        "\n"
        "織田信長「ぜひに　およばず…\n"
        "\n"
        "織田信長は　本能寺に　ひをはなち　じがいした！\n"
        "\n"
        "ごじつ、羽柴秀吉が　山崎のたたかいで　明智光秀を　たおし、\n"
        "織田けの　こうけいの　ちいを　さんだつした！\n");

    WaitKey();
}

static void DrawGameOver(Stage* stage)
{
    DrawScreen(stage, DM_GameOver, 0);
    // 年表を表示
    PrintChronology(stage->chro);
    putchar('\n');
    printf("ＧＡＭＥ　ＯＶＥＲ\n");
    WaitKey();
}

static void DrawEnding(Stage* stage)
{
    DrawScreen(stage, DM_Ending, 0);
    // 年表を表示
    PrintChronology(stage->chro);
    int year = stage->year + 3;
    const char* name1 = GetLordFamilyName(stage, stage->playerLord);
    const char* name2 = GetLordFirstName(stage, stage->playerLord);
    printf("%dねん　 %s %sが　せいいたいしょうぐんに　にんぜられる\n", year, name1, name2);
    printf("%dねん　%s%sが　%sばくふを　ひらく\n", year, name1, name2, name1);
    putchar('\n');
    printf("ＴＨＥ　ＥＮＤ");
    WaitKey();
}