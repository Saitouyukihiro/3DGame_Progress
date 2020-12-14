#pragma once
#ifndef _FIXED_MODEL_H_
#define _FIXED_MODEL_H_
//---------------------------
//インクルードファイル
//---------------------------
#include "main.h"

//---------------------------
//マクロ定義
//---------------------------
#define MAX_FIXED_MODEL (3)		//モデルの数
#define MAX_FIXEMODEL_TEX (128)	//テクスチャの数

//---------------------------
//列挙型
//---------------------------
typedef enum
{
	MODEL_HERTS = 0,	//ハート
	MODEL_CAT,			//チー猫
	MODEL_TYPE_MAX		//リストの数
} MODEL_TYPE;

//---------------------------
//構造体
//---------------------------
typedef struct
{
	DWORD pnNumMatModel;		//マテリアルの数
	D3DXVECTOR3 PosModel;		//位置
	D3DXVECTOR3 RotModel;		//向き
	D3DXVECTOR3 vtxMinModel, vtxMaxModel;	//頂点の端情報
	D3DXMATRIX mtxWoldModel;	//ワールドマトリックス
	LPD3DXMESH pMeshFixedmodel;		//メッシュのポインタ
	LPD3DXBUFFER pBuffMatFixedmodel;//マテリアルのポインタ
	MODEL_TYPE aType;			//種類
	int nIdex;					//影の番号
	float fWidth;
	float fHeight;
	float fDepht;
	bool bUse;					//使ってるか
} Fixedmodel;
//---------------------------
//プロトタイプ宣言
//---------------------------
HRESULT InitFixedModel(void);
void UninitFixedModel(void);
void UpdateFixedModel(void);
void DrawFixedModel(void);
void SetFixedModel(D3DXVECTOR3 PosModel, D3DXVECTOR3 RotModel, MODEL_TYPE Type);
#endif