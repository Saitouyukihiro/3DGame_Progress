#pragma once
#ifndef _MODEL_H_
#define _MODEL_H_
//---------------------------
//インクルードファイル
//---------------------------
#include "main.h"

//---------------------------
//マクロ定義
//---------------------------
#define MAX_MODEL (1)
#define MAX_MODEL_NUM (9)
#define G_POW (-0.5f)

//---------------------------
//構造体
//---------------------------
typedef struct
{
	LPD3DXMESH pMeshModel;		//メッシュのポインタ
	LPD3DXBUFFER pBuffMatModel;	//マテリアルのポインタ
	DWORD pnNumMatModel;		//マテリアルの数
	D3DXVECTOR3 PosModel;		//位置
	D3DXVECTOR3 RotModel;		//向き
	D3DXVECTOR3 vtxMinModel, vtxMaxModel;	//頂点の端情報
	D3DXMATRIX mtxWoldModel;	//ワールドマトリックス
	int nIdxModel;				//親モデルのインデックス
} Model;

typedef struct
{
	D3DXVECTOR3 PosModel;			//位置
	D3DXVECTOR3 PosoldModel;		//前回の位置
	D3DXVECTOR3 Move;				//移動量
	D3DXVECTOR3 RotModel;			//向き
	D3DXMATRIX mtxWoldModel;		//ワールドマトリックス
	int nIdex;						//影の番号
	bool bLand;						//地面についてるか
	Model aModel[MAX_MODEL_NUM];	//モデルのパーツ
	int nNumModel = MAX_MODEL_NUM;	//モデルのパーツ数
} Player;
//---------------------------
//プロトタイプ宣言
//---------------------------
HRESULT InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);
void PlayerInfo(void);
Player *GetPlayer(void);
#endif