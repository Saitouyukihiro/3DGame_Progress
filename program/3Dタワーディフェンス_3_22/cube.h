#pragma once
#ifndef _CUBE_H_
#define _CUBE_H_
//---------------------------
//インクルードファイル
//---------------------------
#include "main.h"

//---------------------------
//マクロ定義
//---------------------------
#define MAX_CUBE (64)	//壁の最大数
#define MAX_CUBE_TEX (64)

//---------------------------
//構造体
//---------------------------
typedef struct
{
	D3DXVECTOR3	pos;		//位置
	D3DXVECTOR3 rot;		//向き
	D3DXMATRIX mtxWold;		//ワールドマトリックス
	LPD3DXMESH pMesh;		//メッシュのポインタ
	LPD3DXBUFFER pBuffMat;	//マテリアルのポインタ
	DWORD pnNumMat;			//マテリアルの数
	D3DXVECTOR3 vtxMin, vtxMax;	//頂点の端情報
	float fWidth = 50.0f;					//直径X
	float fHight = 50.0f;					//直径Y
	float fDepth = 50.0f;					//直径Z
	bool bCollision;
	bool bUse;				//使ってるかどうか
} Cube;

//---------------------------
//プロトタイプ宣言
//---------------------------
HRESULT InitCube(void);
void UninitCube(void);
void UpdateCube(void);
void DrawCube(void);
int SetCubeUse(D3DXVECTOR3 rot, D3DXVECTOR3 pos, bool bCollision);
void SetCube(int nIdx, D3DXVECTOR3 rot, D3DXVECTOR3 pos, bool bCollision);	//向き、位置
bool CollisionCude(D3DXVECTOR3 *pos, D3DXVECTOR3 *posold, D3DXVECTOR3 *move, float fWidth, float fHeight);
Cube *GetCube(void);
#endif