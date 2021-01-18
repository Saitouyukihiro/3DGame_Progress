//ーーーーーーーーーーーーーーーーーーーーーーーーー
//モデルのヘッダー
//Author：satou syusuke
//ーーーーーーーーーーーーーーーーーーーーーーーーー

#ifndef _ENEMY_H_
#define _ENEMY_H_

#define MAX_PARTS (3)
#define MAX_ENEMY (64)

typedef struct
{
	LPD3DXMESH pMeshEnemy = NULL;//メッシュへのポインタ
	LPD3DXBUFFER pBuffMatEnemy = NULL;//マテリアルへのポインタ
	DWORD nNumMatEnemy = 0;		//マテリアルの数

	D3DXVECTOR3 pos;//位置
	D3DXVECTOR3 rot;//回転

	D3DXVECTOR3 VtxMinEnemy; //頂点の最小値
	D3DXVECTOR3 VtxMaxEnemy; //頂点の最大値
	D3DXMATRIX mtxWorldEnemy;

	int nIndxModelParent;//親モデルのインデックス
} ENEMY;

typedef enum
{
	ENEMYTYPE_LMG,
	ENEMYTYPE_MAX,
}ENEMYTYPE;

typedef struct
{
	D3DXVECTOR3 pos;//位置
	D3DXVECTOR3 rot;//回転
	D3DXMATRIX mtxWorldEnemy;//ワールドマトリックス

	ENEMY aEnemy[MAX_PARTS];
	int nNumEnemy;

	int ntype;
	bool bUse;
	int nLife;
}Enemy;


//プレイヤー用の宣言
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);

void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife, int ntype);

Enemy *GetEnemy(void);
#endif


