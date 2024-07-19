//======================================　
//	キャラクター
//======================================
#include "Character.h"
#include "Utility.h" // GetRand()
#include <string.h>  // strcpy()
#include <stdio.h>   // printf()
#include <stdlib.h>  // rand(), RAND_MAX

// 呪文の消費MP
static const int SPELL_COST = 3;

// キャラクターセット
void SetCharacter(Character* ch, int hp, int mp, int attack, const char* name, const char* aa)
{
	ch->maxHp = hp;
	ch->maxMp = mp;
	ch->attack = attack;
	ch->name = name;
	ch->aa = aa;
}
// キャラの戦闘開始
void StartCharacter(Character* ch)
{
	ch->hp = ch->maxHp;
	ch->mp = ch->maxMp;
	ch->isEscape = false;
	ch->isEraseAa = false;
}
// 死亡か?
bool IsDeadCharacter(Character* ch)
{
	return ch->hp == 0;
}
// ダメージを受ける
void DamageCharacter(Character* ch, int damage)
{
	ch->hp -= damage;
	if (ch->hp < 0) {
		ch->hp = 0;
	}
}
// 回復する
void RecoverCharacter(Character* ch)
{
	ch->hp = ch->maxHp;
}
//  魔法が使えるか?
bool CanSpellCharacter(Character* ch)
{
	return ch->mp >= SPELL_COST;
}
// 魔法を使う
void UseSpellCharacter(Character* ch)
{
	ch->mp -= SPELL_COST;
	if (ch->mp < 0) {
		ch->mp = 0;
	}
}
// プレーヤ表示を行う
void IndicatePlayer(Character* ch)
{
    // ★ここをコーディングしてください。
    // 仕様を参考に、プレーヤの表示を行います。
}
// エネミー表示を行う
void IndicateEnemy(Character* ch)
{
    // ★ここをコーディングしてください。
    // 仕様を参考に、エネミーの表示を行います。
    // エネミーが死亡すると、アスキーアートは消します(表示しません)
}
// 攻撃力から与えるダメージを計算
int CalcDamage(Character* ch)
{
    // ★ここをコーディングしてください。
    // 敵に与えるダメージは、1～attack の乱数です。
    // Utility.cpp の GetRand(int max)を使用してください。
}
// 名前を取得
const char *GetName(Character* ch)
{
	return ch->name;
}
// 逃げ出したをセット
void SetEscapeCharacter(Character* ch)
{
	ch->isEscape = true;
}
// 逃げ出したか?
bool IsEscapeCharacter(Character* ch)
{
	return ch->isEscape;
}
// アスキーアート消すをセット
void SetEraseAa(Character* ch)
{
	ch->isEraseAa = true;
}
