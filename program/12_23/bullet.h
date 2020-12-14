#pragma once
#ifndef _BULLET_H_
#define _BULLET_H_

//---------------------------
//インクルードファイル
//---------------------------
#include "main.h"

//---------------------------
//マクロ定義
//---------------------------
#define BULLET_X (1.0f)	//玉サイズX半径
#define BULLET_Y (1.0f)	//玉サイズY半径
#define BULLET_MOVE_SPEED (5.0f)	//弾のスピード
#define MAX_BULLET (256)			//玉の最大数
#define BULLET_SPAN (10)			//弾のクールタイム
#define MAX_TEX (1)					//テクスチャの数

//---------------------------
//構造体の定義
//---------------------------
typedef struct
{
	D3DXVECTOR3	Pos;		//位置
	D3DXVECTOR3 Move;		//移動量
	D3DXVECTOR3 rot;		//弾の方向
	D3DXMATRIX mtxWold;		//ワールドマトリックス
	D3DXMATRIX mtxView;		//カメラの向き
	float fWidth;			//幅
	float fHeight;			//高さ
	int nIdex;				//影の番号
	int nType;				//種類
	bool bUse;				//使ってるかどうか
} Bullet;
//---------------------------
//プロトタイプ宣言
//---------------------------
HRESULT InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight, int nType);	//位置、向いてる方向、幅、高さ、種類
Bullet *GetBullet(void);
#endif 
