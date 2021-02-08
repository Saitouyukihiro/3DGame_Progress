#pragma once
#ifndef _SPIDER_H_
#define _SPIDER_H_
//---------------------------
//インクルードファイル
//---------------------------
#include "main.h"

//---------------------------
//マクロ定義
//---------------------------
#define MAX_SPIDER_MODEL (1)		//敵モデルの最大数
#define MAX_SPIDER_TEX (128)		//敵モデルのパーツのテクスチャの最大数
#define MAX_SPIDER_PARTS_NUM (6)	//敵モデルのパーツの最大数
#define MAX_SPIDER_KEY (8)		//敵モデルキーの最大数
#define G_POW (-0.5f)			//重力の力

//---------------------------
//列挙型.モードの種類
//---------------------------
typedef enum
{
	SPIDER_STATE_WALK = 0,	//歩く
	SPIDER_STATE_ATTACK,		//攻撃
	SPIDER_STATE_MAX			//リストの数
} Spidermodelstate;

//---------------------------
//構造体
//---------------------------
typedef struct
{
	float fPosX;	//位置X
	float fPosY;	//位置Y
	float fPosZ;	//位置Z
	float fRotX;	//向きX
	float fRotY;	//向きY
	float fRotZ;	//向きZ
} Spiderkey;

typedef struct
{
	float nFrame;							//再生フレーム
	Spiderkey aKey[MAX_SPIDER_PARTS_NUM];		//モデル毎のキー要素
} Spiderkeyinfo;

typedef struct
{
	bool bLoop;								//ループするか
	int nNumKey;							//キーの総数
	Spiderkeyinfo aKeyinfo[MAX_SPIDER_KEY];	//キーの情報(キーの総数分)
} Spidermotioninfo;

typedef struct
{
	LPD3DXMESH pMesh;		//メッシュのポインタ
	LPD3DXBUFFER pBuffMat;	//マテリアルのポインタ
	DWORD pnNumMat;			//マテリアルの数
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 rot;		//向き
	D3DXVECTOR3 vtxMin, vtxMax;	//頂点の端情報
	D3DXMATRIX mtxWold;		//ワールドマトリックス
	int nIdx;				//親モデルのインデックス
} Spidermodel;

typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 posold;		//前回の位置
	D3DXVECTOR3 move;		//移動量
	D3DXVECTOR3 posdfrc;	//さぶん
	D3DXVECTOR3 rot;		//向き
	D3DXMATRIX mtxWold;		//ワールドマトリックス
	int nIdex;				//影の番号
	bool bLand;				//地面についてるか
	Spidermodel aModel[MAX_SPIDER_PARTS_NUM];	//モデルのパーツ
	int nNumModel = MAX_SPIDER_PARTS_NUM;	//モデルのパーツ数
	Spidermotioninfo aMotioninfo[SPIDER_STATE_MAX];	//モーション情報
	int nNumnMotion;		//モーション数
	bool bLoopMotion;		//ループするか
	int	nNumKey;			//キー数
	int nKeyold;			//前回のキー
	int nKey;				//キーNo
	float fMotion;			//モーションのカウント
	Spidermodelstate aState;	//モーション種類
	bool bCllision;
	bool bUse;				//使ってるか
} Spider;
//---------------------------
//プロトタイプ宣言
//---------------------------
HRESULT InitSpider(void);
void UninitSpider(void);
void UpdateSpider(void);
void DrawSpider(void);
void SetSpider(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
Spider *GetSpider(void);
#endif