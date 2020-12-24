//**************************************************************
//弾のヘッダー
//Author：佐藤秀亮
//**************************************************************

#ifndef _BULLET_H_
#define _BULLET_H_

#include"main.h"

//マクロ定義
#define MAX_BULLET (255)//弾最大数
#define MAX_BULLET_SIZE_X (7.0f)//弾のサイズ(X)
#define MAX_BULLET_SIZE_Y (7.0f)//弾のサイズ(Y)

typedef enum
{
	BULLETTYPE_PLAYER = 0,//プレイヤーの弾
	BULLETTYPE_MAX,
} BULLETTYPE;

typedef struct
{
	D3DXMATRIX mtxWorld;//マトリックス
	D3DXVECTOR3 pos;//位置
	D3DXVECTOR3 rot;//回転

	int nlife;//射程
	int ntype;//弾のタイプ
	bool bUse;//使用状況

} Bullet;

void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);

void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int ntype);//位置、向き、種類

Bullet *GetBullet(void);
#endif

