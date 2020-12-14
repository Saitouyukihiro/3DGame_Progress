#pragma once
#ifndef _LIGHT_H_
#define _LIGHT_H_
//---------------------------
//インクルードファイル
//---------------------------
#include "main.h"

//---------------------------
//マクロ定義
//---------------------------
#define MAX_LIGHT (3)			//ライトの数
#define LIGHT_MOVE_SPEED (1.0f)	//ライトの移動スピード

//---------------------------
//構造体
//---------------------------
typedef struct 
{
	bool bUse;		//どれを使ってるか
	bool bSelect;	//ついてるか消してるか
	D3DXVECTOR3 Rot;
} LightSelect;

//---------------------------
//プロトタイプ宣言
//---------------------------
HRESULT InitLight(void);
void UninitLight(void);
void UpdateLight(void);
void LightInfo(void);
void LightTxt(void);
D3DLIGHT9 *GetLight(void);
LightSelect *GetLightSelect(void);
#endif