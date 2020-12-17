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
#define MAX_WALL (64)	//壁の最大数
#define WALL_X (1.0f)	//壁の幅
#define WALL_Y (1.0f)	//壁の高さ

//---------------------------
//構造体
//---------------------------
typedef struct 
{
	D3DXVECTOR3	PosWall;		//位置
	D3DXVECTOR3 RotWall;		//向き
	D3DXMATRIX mtxWoldWall;		//ワールドマトリックス
	float fWidth;				//幅
	float fHeiht;				//高さ
	int nIdex;					//影の番号
	bool bUse;					//使ってるかどうか
} Wall;

//---------------------------
//プロトタイプ宣言
//---------------------------
HRESULT InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void DrawWall(void);
void SetWall(D3DXVECTOR3 RotWall, D3DXVECTOR3 PosWall, float fWith, float fHeight);	//位置、向き
#endif