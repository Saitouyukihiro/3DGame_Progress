#pragma once
#ifndef _WALL_H_
#define _WALL_H_
//---------------------------
//インクルードファイル
//---------------------------
#include "main.h"

//---------------------------
//マクロ定義
//---------------------------
#define MAX_WALL (4)	//壁の最大数
#define MAX_WALL_TEX (1)//テクスチャの数
#define WALL_X (0.5f)	//壁の幅
#define WALL_Y (0.5f)	//壁の高さ

//---------------------------
//構造体
//---------------------------
typedef struct
{
	D3DXVECTOR3	pos;		//位置
	D3DXVECTOR3 rot;		//向き
	D3DXMATRIX mtxWold;		//ワールドマトリックス
	float fWidth;			//幅
	float fHeiht;			//高さ
	int nType;				//種類
	bool bUse;				//使ってるかどうか
} Wall;

//---------------------------
//プロトタイプ宣言
//---------------------------
HRESULT InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void DrawWall(void);
void SetWall(D3DXVECTOR3 rot, D3DXVECTOR3 pos, float fWith, float fHeight, int nType);	//向き、位置、幅、高さ、種類
bool ColisionWall(D3DXVECTOR3 *pos, D3DXVECTOR3 *posold, D3DXVECTOR3 *move, float fWidth, float fHeight, float fDepht, int nType);	//位置、前回の位置、移動量、幅、高さ、奥行、種類
#endif