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
	int nIdex;					//影の番号
} Model;
//---------------------------
//プロトタイプ宣言
//---------------------------
HRESULT InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);
void ModelInfo(void);
Model *GetModel(void);
#endif