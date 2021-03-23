#pragma once
#ifndef _ENEMYCOUNT_H_
#define _ENEMYCOUNT_H_

//---------------------------
//インクルードファイル
//---------------------------
#include "main.h"

//---------------------------
//マクロ定義
//---------------------------
#define MAX_ENEMY_COUNT_DIGIT (2)	//スコアの桁数
#define ENEMY_COUNT_Y (25)		//半径
#define ENEMY_COUNT_X (25)		//半径

//---------------------------
//構造体の定義
//---------------------------
typedef struct
{
	D3DXVECTOR3 pos;	//位置
} Enemycount;

//---------------------------
//プロトタイプ宣言
//---------------------------
HRESULT InitCount(void);
void UninitCount(void);
void UpdateCount(void);
void DrawCount(void);
int GetCount(void);
#endif