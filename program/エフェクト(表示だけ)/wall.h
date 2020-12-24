//ーーーーーーーーーーーーーーーーーーーーーーーーー
//壁のヘッダー
//Author：satou syusuke
//ーーーーーーーーーーーーーーーーーーーーーーーーー

#ifndef _WALL_H_
#define _WALL_H_

#define MAX_WALL (256)

typedef struct
{
	D3DXMATRIX mtxWorld;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;

	float fWhidth;
	float fHight;
	bool bUse;
} Wall;

//プレイヤー用の宣言
HRESULT InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void DrawWall(void);

void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWhidth, float fHight, int ntype);
#endif

