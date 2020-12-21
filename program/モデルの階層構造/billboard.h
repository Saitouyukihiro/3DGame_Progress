#pragma once
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_
//---------------------------
//インクルードファイル
//---------------------------
#include "main.h"

//---------------------------
//マクロ定義
//---------------------------
#define MAX_BILLBOARD (64)	//ビルボードの最大数
#define BILLBOARD_X (1.0f)		//ビルボードの幅
#define BILLBOARD_Y (1.0f)		//ビルボードの高さ

//---------------------------
//構造体
//---------------------------
typedef struct
{
	D3DXVECTOR3	Pos;		//位置
	D3DXVECTOR3 Move;		//移動量
	D3DXMATRIX mtxWold;		//ワールドマトリックス
	D3DXMATRIX mtxView;		//カメラの向き
	float fWidth;			//幅
	float fHeiht;			//高さ
	int nIdex;				//影の番号
	bool bUse;				//使ってるかどうか
} Billboard;

//---------------------------
//プロトタイプ宣言
//---------------------------
HRESULT InitBillboard(void);
void UninitBillboard(void);
void UpdateBillboard(void);
void DrawBillboard(void);
void SetBillboard(D3DXVECTOR3 pos, float fWidth, float fHeight);
#endif