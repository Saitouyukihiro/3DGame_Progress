#pragma once
#ifndef _GIRL_H
#define _GIRL_H
//---------------------------
//インクルードファイル
//---------------------------
#include "main.h"

//---------------------------
//マクロ定義
//---------------------------
#define MAX_GIRL (5)	//ビルボードの最大数
#define MAX_GIRL_TEX (3)//ビルボードのテクスチャ
#define GIRL_X (0.5)	//ビルボードの幅
#define GIRL_Y (0.5)	//ビルボードの高さ

//---------------------------
//列挙型.モードの種類
//---------------------------
typedef enum
{
	GIRL_STATE_LEFT = 0,	//歩く
	GIRL_STATE_RIGHT,		//攻撃
	GIRL_STATE_NONE,
	GIRL_STATE_MAX			//リストの数
} Girlmove;

//---------------------------
//構造体
//---------------------------
typedef struct
{
	D3DXVECTOR3	pos;		//位置
	D3DXVECTOR3 posold;
	D3DXVECTOR3 move;		//移動量
	D3DXMATRIX mtxWold;		//ワールドマトリックス
	D3DXMATRIX mtxView;		//カメラの向き
	Girlmove aState;
	float fWidth;			//幅
	float fHeiht;			//高さ
	float fLookigZ = 100.0f;			//ちゅうしてん
	float fLookigX = 100.0f;			//幅
	int nAnim;				//アニメーション
	int nIdex;				//影の番号
	int nType;				//種類
	bool bUse;				//使ってるかどうか
} Girl;

//---------------------------
//プロトタイプ宣言
//---------------------------
HRESULT InitGirl(void);
void UninitGirl(void);
void UpdateGirl(void);
void DrawGirl(void);
void SetGirl(D3DXVECTOR3 pos, float fWidth, float fHeight, int nType);
void GirlLooking(D3DXVECTOR3 pos);
Girl *GetGirl(void);
#endif