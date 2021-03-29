#pragma once
#ifndef _WORLD_SKY_H_
#define _WORLD_SKY_H_
//---------------------------
//インクルードファイル
//---------------------------
#include "main.h"

//---------------------------
//マクロ定義
//---------------------------
#define MAX_SKY (1)		//半円メッシュフィールドの数
#define MAX_SKY_TEX (1)	//テクスチャの数
#define MS_SKY_X (0.5f)	//半円の半径X
#define MS_SKY_Y (0.5f)	//半円の半径Z

//---------------------------
//床タイプ
//---------------------------
#define SKY_MAX_VTX_X (4)	//横ブロックの数
#define SKY_MAX_VTX_Y (4)	//縦ブロックの数
#define SKY_MAX_VTX_Z (4)	//奥行ブロックの数
#define SKY_VTX_NUM_MAX ((SKY_MAX_VTX_X + 1) * (SKY_MAX_VTX_Z + 1))				//全体頂点の数
#define SKY_IDX_NUM_MAX ((SKY_MAX_VTX_X + 1) * (SKY_MAX_VTX_Z + 1) + (SKY_MAX_VTX_Z - 1) * (SKY_MAX_VTX_X + 3))	//インデックスの数
#define SKY_POLY_NUM_MAX (2 * SKY_MAX_VTX_X * SKY_MAX_VTX_Z + (SKY_MAX_VTX_Z * 4) - 4))	//△の数

//---------------------------
//構造体
//---------------------------
typedef struct
{
	D3DXVECTOR3	pos;		//位置
	D3DXVECTOR3 rot;		//向き
	D3DXMATRIX mtxWold;		//ワールドマトリックス
	float fWidth;			//幅
	float fHeight;			//高さ
	float fDepht;			//奥行
	int nTex;				//テクスチャ
	bool bUse;				//使ってるか
} Worldsky;
//---------------------------
//プロトタイプ宣言
//---------------------------
HRESULT InitSky(void);
void UninitSky(void);
void UpdateSky(void);
void DrawSky(void);
void SetSky(D3DXVECTOR3 rot, D3DXVECTOR3 pos, float fWidth, float fDepht, int nTex);	//向き、位置、幅、奥行、テクスチャ
#endif