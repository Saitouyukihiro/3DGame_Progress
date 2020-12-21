#pragma once
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_
//---------------------------
//インクルードファイル
//---------------------------
#include "main.h"

//---------------------------
//マクロ定義
//---------------------------
#define MAX_FIELD (8)		//メッシュフィールドの数
#define MAX_MESH_TEX (4)	//テクスチャの数
#define MS_X (1.0f)			//床の半径X
#define MS_Y (1.0f)			//床の半径Y
#define MS_Z (1.0f)			//床の半径Z

//---------------------------
//床タイプ
//---------------------------
#define FLOO_MAX_VTX_X (4)	//横ブロックの数
#define FLOO_MAX_VTX_Z (4)	//奥行ブロックの数
#define FLOO_VTX_NUM_MAX ((FLOO_MAX_VTX_X + 1) * (FLOO_MAX_VTX_Z + 1))				//全体頂点の数
#define FLOO_IDX_NUM_MAX ((FLOO_MAX_VTX_X + 1) * (FLOO_MAX_VTX_Z + 1) + (FLOO_MAX_VTX_Z - 1) * (FLOO_MAX_VTX_X + 3))	//インデックスの数
#define FLOO_POLY_NUM_MAX (2 * FLOO_MAX_VTX_X * FLOO_MAX_VTX_Z + (FLOO_MAX_VTX_Z * 4) - 4))	//△の数

//---------------------------
//壁タイプ
//---------------------------
#define WALL_MAX_VTX_X (5)	//横ブロックの数
#define WALL_MAX_VTX_Y (5)	//縦ブロックの数
#define WALL_VTX_NUM_MAX ((WALL_MAX_VTX_X + 1) * (WALL_MAX_VTX_Y + 1))				//全体頂点の数
#define WALL_IDX_NUM_MAX ((WALL_MAX_VTX_X + 1) * (WALL_MAX_VTX_Y + 1) + (WALL_MAX_VTX_Y - 1) * (WALL_MAX_VTX_X + 3))	//インデックスの数
#define WALL_POLY_NUM_MAX (2 * WALL_MAX_VTX_X * WALL_MAX_VTX_Y + (WALL_MAX_VTX_Y * 4) - 4))	//△の数

//---------------------------
//半円タイプ
//---------------------------
#define SEMICIRCLE_MAX_VTX_X (5)	//横ブロックの数
#define SEMICIRCLE_MAX_VTX_Y (5)	//縦ブロックの数
#define SEMICIRCLE_MAX_VTX_Z (5)	//奥行ブロックの数
#define SEMICIRCLE_VTX_NUM_MAX ((SEMICIRCLE_MAX_VTX_X + 1) * (SEMICIRCLE_MAX_VTX_Y + 1))				//全体頂点の数
#define SEMICIRCLE_IDX_NUM_MAX ((SEMICIRCLE_MAX_VTX_X + 1) * (SEMICIRCLE_MAX_VTX_Y + 1) + (SEMICIRCLE_MAX_VTX_Y - 1) * (SEMICIRCLE_MAX_VTX_X + 3))	//インデックスの数
#define SEMICIRCLE_POLY_NUM_MAX (2 * SEMICIRCLE_MAX_VTX_X * SEMICIRCLE_MAX_VTX_Y + (SEMICIRCLE_MAX_VTX_Y * 4) - 4))	//△の数

//---------------------------
//列挙型
//---------------------------
typedef enum
{
	FORM_FLOO = 0,		//床形
	FORM_WALL,			//壁形
	FORM_SEMICIRCLE,	//半円
	FORM_MAX			//リストの数
} MESH_FORM;

//---------------------------
//構造体
//---------------------------
typedef struct
{
	D3DXVECTOR3	Pos;		//位置
	D3DXVECTOR3 Rot;		//向き
	D3DXMATRIX mtxWold;		//ワールドマトリックス
	LPDIRECT3DVERTEXBUFFER9 pVtxBuffField;	//頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9 pIdxBuffFoeld;	//インデックスバッファへのポインタ
	float fWidth;			//幅
	float fHeiht;			//高さ
	float fDepht;			//奥行
	MESH_FORM aState;		//どんな形
	int nTex;				//テクスチャ
	bool bUse;				//使ってるか
} Field;
//---------------------------
//プロトタイプ宣言
//---------------------------
HRESULT InitMeshfield(void);
void UninitMeshfield(void);
void UpdateMeshfield(void);
void DrawMeshfield(void);
void SetField(D3DXVECTOR3 rot, D3DXVECTOR3 pos, float fWidth, float fHeight, float fDepht, int nTex, MESH_FORM aState);	//向き、位置、幅、高さ、奥行、テクスチャ、形
bool ColisionFeild(D3DXVECTOR3 *pos, D3DXVECTOR3 *posold, D3DXVECTOR3 *move, float fWidth, float fHeight, float fDepht, int nType);	//位置、前回の位置、移動量、幅、高さ、奥行、種類
Field *GetField(void);
#endif