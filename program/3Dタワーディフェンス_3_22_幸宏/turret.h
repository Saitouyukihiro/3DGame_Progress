#pragma once
#ifndef _TURRET_H_
#define _TURRET_H_
//---------------------------
//インクルードファイル
//---------------------------
#include "main.h"

//---------------------------
//マクロ定義
//---------------------------
#define MAX_TURRET (64)	//壁の最大数

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
	bool bCollision;
	bool bUse;				//使ってるかどうか
} Turret;

//---------------------------
//プロトタイプ宣言
//---------------------------
HRESULT InitTurret(void);
void UninitTurret(void);
void UpdateTurret(void);
void DrawTurret(void);
int SetTurretUse(D3DXVECTOR3 rot, D3DXVECTOR3 pos, bool bCollision);
void SetTurret(int nIdx, D3DXVECTOR3 rot, D3DXVECTOR3 pos, bool bCollision);	//向き、位置
bool ColisionTurret(D3DXVECTOR3 *pos, D3DXVECTOR3 *posold, D3DXVECTOR3 *move, float fWidth, float fHeight, float fDepht, int nType);
Turret *GetTurret(void);
#endif