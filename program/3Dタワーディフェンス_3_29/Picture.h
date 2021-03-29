#pragma once
#ifndef _PICTURE_H_
#define _PICTURE_H_

//---------------------------
//インクルードファイル
//---------------------------
#include "main.h"

//---------------------------
//マクロ定義
//---------------------------
#define MAX_PICTURE_TEX (PICTURE_TYPE_MAX)	//テクスチャの数
#define MAX_PICTURE (64)		//画像を出す数

//---------------------------
//列挙型.モードの種類
//---------------------------
typedef enum
{
	PICTURE_TITLE = 0,	//タイトル
	PICTURE_GAMESTERTS,
	PICTURE_5WAVE,		//5WAVEモード
	PICTURE_UNLIMITED,	//無制限モード
	PICTURE_RESULT,
	PICTURE_SELECT,
	PICTURE_OPERATE,
	PICTURE_TYPE_MAX,
} PICTURE_TYPE;

//---------------------------
//構造体の定義
//---------------------------
typedef struct
{
	D3DXVECTOR3 pos;	//ポリゴンの位置
	D3DXVECTOR3 move;	//移動量
	float fWidth;		//幅
	float fHeight;		//高さ
	PICTURE_TYPE aType;	//種類
	bool bClick;		//クリックしてるかどうか
	bool bUse;			//使ってるかどうか
} Picture;

//---------------------------
//プロトタイプ宣言
//---------------------------
HRESULT InitPicture(void);
void UninitPicture(void);
void UpdatePicture(void);
void DrawPicture(void);
void SetPicture(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWigth, float fHeight, PICTURE_TYPE aType);	//位置、幅、高さ、種類
#endif 
