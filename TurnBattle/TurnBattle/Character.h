#pragma once
//======================================
//	キャラクター
//======================================
// ★ここにインクルードガード(開始)を記入してください。

struct Character {
	int hp;     // HP
	int maxHp;  // 最大HP
	int mp;     // MP
	int maxMp;  // 最大MP
	int attack; // 攻撃力
	const char *name; // 名前
	const char *aa;   // アスキーアート
	bool isEscape;    // 逃げ出したフラグ
	bool isEraseAa;   // アスキーアートを消すフラグ
};
// キャラクターセット
void SetCharacter(Character* ch, int hp, int mp, int attack, const char* name, const char* aa);
// キャラの戦闘開始
void StartCharacter(Character* ch);
// 死亡か?
bool IsDeadCharacter(Character* ch);
// ダメージを受ける
void DamageCharacter(Character* ch,int damage);
// 回復する
void RecoverCharacter(Character* ch);
//  魔法が使えるか?
bool CanSpellCharacter(Character* ch);
// 魔法を使う
void UseSpellCharacter(Character* ch);
// プレーヤ表示を行う
void IndicatePlayer(Character* ch);
// エネミー表示を行う
void IndicateEnemy(Character* ch);
// 攻撃力から相手に与えるダメージを計算
int CalcDamage(Character* ch);
// 名前を取得
const char* GetName(Character* ch);
// 逃げ出したをセット
void SetEscapeCharacter(Character* ch);
// 逃げ出したか?
bool IsEscapeCharacter(Character* ch);
// AA消す
void SetEraseAa(Character* ch);
// ★ここにインクルードガード(終了)を記入してください。
