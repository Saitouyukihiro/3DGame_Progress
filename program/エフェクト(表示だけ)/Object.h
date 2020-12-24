//ーーーーーーーーーーーーーーーーーーーーーーーーー
//オブジェクトのヘッダー
//Author：satou syusuke
//ーーーーーーーーーーーーーーーーーーーーーーーーー
//#if 0

#ifndef _OBJECT_H_
#define _OBJECT_H_

#define MAX_OBJECT (255)//最大オブジェクト

#define MAX_COLLISION (20)
#define MIN_COLLISION (20)

typedef enum
{
	OBJECTTYPE_TANK = 0,//戦車
	OBJECTTYPE_SANDBAG,	//土嚢
	OBJECTTYPE_BLOCK00,//テクスチャブロック
	OBJECTTYPE_BLOCK01,//テクスチャブロック
	OBJECTTYPE_MAX,
} OBJECTTYPE;

typedef struct
{
	D3DXVECTOR3 pos;//位置
	D3DXVECTOR3 rot;//回転
	D3DXCOLOR Color;//色

	D3DXVECTOR3 VtxMinObject; //頂点の最小値
	D3DXVECTOR3 VtxMaxObject; //頂点の最大値

	D3DXMATRIX mtxObject;//ワールドマトリックス

	int ntype;//使用タイプ
	bool bUse;//使用状況
} Object;

//プレイヤー用の宣言
void InitObject(void);
void UninitObject(void);
void UpdateObject(void);
void DrawObject(void);

void SetObject(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int ntype);

Object *GetObject(void);
#endif

//#endif

