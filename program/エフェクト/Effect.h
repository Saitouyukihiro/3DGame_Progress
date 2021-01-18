//ーーーーーーーーーーーーーーーーーーーーーーーーー
//エフェクトのヘッダー
//Author：satou syusuke
//ーーーーーーーーーーーーーーーーーーーーーーーーー

#ifndef _EFFECT_H_
#define _EFFECT_H_

#define MAX_EFFECT (20000)//大量に必要

typedef enum//出現エフェクトの軌道
{
	EFFECTTYPE_PLAYER,//出現後動かない

	EFFECTTYPE_FOLL_ST,//出現場所から下に落ちる
	EFFECTTYPE_FOLL_L,//出現場所から左下に落ちる
	EFFECTTYPE_FOLL_R,//出現場所から右下に落ちる

	EFFECTTYPE_UP_ST,//出現場所から上に上がる
	EFFECTTYPE_UP_L,//出現場所から左上に上がる
	EFFECTTYPE_UP_R,//出現場所から右上に上がる

	EFFECTTYPE_MAX,
} EFFECTTYPE;

typedef struct
{
	D3DXMATRIX mtxWorld;
	D3DXMATRIX mtxView;

	D3DXVECTOR3 pos;//位置
	D3DXVECTOR3 move;
	D3DXCOLOR color; //色

	int ntype;
	int nlife;

	float fHight;
	float fWhidth;

	bool bUse;

} Effect;

//プレイヤー用の宣言
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);

void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR color, float fWhidth, float fHight, int ntype, int nLife);
//出現位置　色　幅　高さ　タイプ　寿命
Effect *GetEffect(void);
#endif

