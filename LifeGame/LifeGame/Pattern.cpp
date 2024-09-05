//========================================
//      ライフゲーム:パターン
//========================================
#include "Pattern.h"
#include "Utility.h"
#include <stdio.h>

static bool _block[4][4] = {
	{0,0,0,0},
	{0,1,1,0},
	{0,1,1,0},
	{0,0,0,0},
};
static bool _tab[5][5] = {
	{0,0,0,0,0},
	{0,0,1,0,0},
	{0,1,0,1,0},
	{0,0,1,0,0},
	{0,0,0,0,0},
};
static bool _boat[5][5] = {
	{0,0,0,0,0},
	{0,1,1,0,0},
	{0,1,0,1,0},
	{0,0,1,0,0},
	{0,0,0,0,0},
};
static bool _snake[4][6] = {
	{0,0,0,0,0,0},
	{0,1,1,0,1,0},
	{0,1,0,1,1,0},
	{0,0,0,0,0,0},
};

static bool _ship[5][5] = {
	{0,0,0,0,0},
	{0,1,1,0,0},
	{0,1,0,1,0},
	{0,0,1,1,0},
	{0,0,0,0,0},
};

static bool _aircarrier[5][6] = {
	{0,0,0,0,0,0},
	{0,1,1,0,0,0},
	{0,1,0,0,1,0},
	{0,0,0,1,1,0},
	{0,0,0,0,0,0},
};
static bool _beehive[5][6] = {
	{0,0,0,0,0,0},
	{0,0,1,1,0,0},
	{0,1,0,0,1,0},
	{0,0,1,1,0,0},
	{0,0,0,0,0,0},
};

static bool _barge[6][6] = {
	{0,0,0,0,0,0},
	{0,0,1,0,0,0},
	{0,1,0,1,0,0},
	{0,0,1,0,1,0},
	{0,0,0,1,0,0},
	{0,0,0,0,0,0},
};
static bool _pond[6][6] = {
	{0,0,0,0,0,0},
	{0,0,1,1,0,0},
	{0,1,0,0,1,0},
	{0,1,0,0,1,0},
	{0,0,1,1,0,0},
	{0,0,0,0,0,0},
};

//static bool _blinker[5][5] = {
//};
//static bool _frog[6][6] = {
//};
//static bool _beecon[6][6] = {
//};
//static bool _clock[6][6] = {
//};
//static bool _pulsar[17][17] = {
//};
//static bool _octagon [10][10] = {
//};
//static bool _galaxy[15][15] = {
//};
//static bool _pentadecathlon[18][11] = {
//};
//static bool _r_pentomono[5][5] = {
//};
//static bool _diehard[5][10] = {
//};
//static bool _acorn[5][9] = {
//};
//static bool _glider[6][6] = {
//};
//static bool _lightship[7][9] = {
//};
//static bool _midship[9][10] = {
//};
//static bool _largeship[9][11] = {
//};
//static bool _griderGun1[11][38] = {
//};
//static bool _griderGun2[23][35] = {
//};
//static bool _breeding_10cell[8][10] = {
//};
//static bool _breeding_5x5[7][7] = {
//};
//static bool _breeding_12x2[4][14] = {
//};
//static bool _breeding_h1[3][41] = {
//};
//static bool _shushupopo[20][7] = {
//};
//static bool _max[29][29] = {
//};

static Pattern patterns[] = {
	// 【固定物体】
	{4,4,(bool*)_block,"ブロック",true},
	{5,5,(bool*)_tab,"タブ",true},
	{5,5,(bool*)_boat,"ボート",true},
	{6,4,(bool*)_snake,"へび",true},
	{5,5,(bool*)_ship,"船",true},
	{6,5,(bool*)_aircarrier,"空母",true},
	{6,5,(bool*)_beehive,"蜂の巣",true},
	{6,6,(bool*)_barge,"はしけ",true},
	{6,6,(bool*)_pond,"池",true},
	// 【振動子】
//	{5,5,(bool*)_blinker,"ブリンカー",true},
//	{6,6,(bool*)_frog,"ヒキガエル",true},
//	{6,6,(bool*)_beecon,"ビーコン",true},
//	{6,6,(bool*)_clock,"時計",true},
//	{17,17,(bool*)_pulsar,"パルサー",true},
//	{10,10,(bool*)_octagon,"八角形",true},
//	{15,15,(bool*)_galaxy,"銀河",true},
	// 【長寿型】
//	{11,18,(bool*)_pentadecathlon,"ペンタデカスロン",true},
//	{5,5,(bool*)_r_pentomono,"Rペントミノ",true},
//	{10,5,(bool*)_diehard,"ダイ・ハード" ,true},
//	{9,5,(bool*)_acorn,"どんぐり",true},
	// 【移動物体】
//	{6,6,(bool*)_glider,"グライダー",true},
//	{9,7,(bool*)_lightship,"軽量級宇宙船",true},
//	{10,9,(bool*)_midship,"中量級宇宙船",true},
//	{11,9,(bool*)_largeship,"重量級宇宙船",true},
	// 【繁殖型】
//	{38,11,(bool*)_griderGun1,"ゴスパーのグライダー銃",false},  // ループなし
//	{35,23,(bool*)_griderGun2,"シムキンのグライダー銃",false},  // ループなし
//	{10,8,(bool*)_breeding_10cell,"繁殖型10セル",true},
//	{7,7,(bool*)_breeding_5x5,"繁殖型5x5の矩形",true},
//	{14,4,(bool*)_breeding_12x2,"繁殖型12x2の矩形",true},
//	{41,3,(bool*)_breeding_h1,"繁殖型高さ1",true},
//	{7,20,(bool*)_shushupopo,"シュシュポッポ",false},
//	{29,29,(bool*)_max,"マックス",false},
};

const int patternSize = sizeof(patterns) / sizeof(patterns[0]);
static int sel = 0;

Pattern* SelectPattern()
{
	while (true) {
		ClearScreen();
		for (int i = 0; i < patternSize; i++) {
			const char* cur = (sel == i) ? "＞" : "　";
			printf("%s%s\n", cur, patterns[i].name);
		}
		switch (GetKey()) {
		case ARROW_UP:
			sel--;
			if (sel < 0) {
				sel = patternSize - 1;
			}
			break;
		case ARROW_DOWN:
			sel++;
			if (sel >= patternSize) {
				sel = 0;
			}
			break;
		case DECIDE:
			return &patterns[sel];
		case ESC:
			return nullptr;
		}
	}
}