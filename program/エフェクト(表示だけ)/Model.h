//ーーーーーーーーーーーーーーーーーーーーーーーーー
//モデルのヘッダー
//Author：satou syusuke
//ーーーーーーーーーーーーーーーーーーーーーーーーー

#ifndef _MODEL_H_
#define _MODEL_H_

#define MAX_MODEL (3)

typedef struct
{
	LPD3DXMESH pMeshModel = NULL;//メッシュへのポインタ
	LPD3DXBUFFER pBuffMatModel = NULL;//マテリアルへのポインタ
	DWORD nNumMatmodel = 0;		//マテリアルの数

	D3DXVECTOR3 pos;//位置
	D3DXVECTOR3 rot;//回転

	D3DXVECTOR3 VtxMinModel; //頂点の最小値
	D3DXVECTOR3 VtxMaxModel; //頂点の最大値
	D3DXMATRIX mtxWorldModel;

	int nIndxModelParent;//親モデルのインデックス
} Model;

typedef struct
{
	D3DXVECTOR3 pos;//位置
	D3DXVECTOR3 rot;//回転
	D3DXMATRIX mtxWorldPlayer;//ワールドマトリックス

	Model aModel[MAX_MODEL];
	int nNumModel;
}Player;


//プレイヤー用の宣言
void InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);

Player *GetModel(void);
#endif

