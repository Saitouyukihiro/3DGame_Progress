#pragma once
#ifndef _FLOO_H_
#define _FLOO_H_
//---------------------------
//インクルードファイル
//---------------------------
#include "main.h"

//---------------------------
//マクロ定義
//---------------------------
#define MAX_FLOO (1)		//床メッシュフィールドの数
#define MAX_FLOO_TEX (1)	//テクスチャの数
#define MS_FLOO_X (0.5f)	//床の半径X
#define MS_FLOO_Z (0.5f)	//床の半径Z

//---------------------------
//床タイプ
//---------------------------
#define FLOO_MAX_VTX_X (10)	//横ブロックの数
#define FLOO_MAX_VTX_Z (10)	//奥行ブロックの数
#define FLOO_VTX_NUM_MAX ((FLOO_MAX_VTX_X + 1) * (FLOO_MAX_VTX_Z + 1))				//全体頂点の数
#define FLOO_IDX_NUM_MAX ((FLOO_MAX_VTX_X + 1) * (FLOO_MAX_VTX_Z + 1) + (FLOO_MAX_VTX_Z - 1) * (FLOO_MAX_VTX_X + 3))	//インデックスの数
#define FLOO_POLY_NUM_MAX (2 * FLOO_MAX_VTX_X * FLOO_MAX_VTX_Z + (FLOO_MAX_VTX_Z * 4) - 4))	//△の数

//---------------------------
//構造体
//---------------------------
typedef struct
{
	D3DXVECTOR3	pos;		//位置
	D3DXVECTOR3 rot;		//向き
	D3DXMATRIX mtxWold;		//ワールドマトリックス
	float fWidth;			//幅
	float fDepht;			//奥行
	int nTex;				//テクスチャ
	bool bUse;				//使ってるか
} Field;
//---------------------------
//プロトタイプ宣言
//---------------------------
HRESULT InitFloo(void);
void UninitFloo(void);
void UpdateFloo(void);
void DrawFloo(void);
void SetFloo(D3DXVECTOR3 rot, D3DXVECTOR3 pos, float fWidth, float fDepht, int nTex);	//向き、位置、幅、奥行、テクスチャ
bool ColisionFloo(D3DXVECTOR3 *pos, D3DXVECTOR3 *posold, D3DXVECTOR3 *move, float fWidth, float fHeight, float fDepht, int nType);	//位置、前回の位置、移動量、幅、高さ、奥行、種類
Field *GetFloo(void);
#endif