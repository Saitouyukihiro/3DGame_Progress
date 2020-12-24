//ーーーーーーーーーーーーーーーーーーーーーーーーー
//エフェクトのヘッダー
//Author：satou syusuke
//ーーーーーーーーーーーーーーーーーーーーーーーーー

#ifndef _EFFECT_H_
#define _EFFECT_H_

#define MAX_EFFECT (10000)

typedef enum
{
	EFFECTTYTPE_PLAYER,
	EFFECTTYPE_MAX,
} EFFECTTYPE;

typedef struct
{
	D3DXMATRIX mtxWorld;
	D3DXMATRIX mtxView;

	D3DXVECTOR3 pos;//位置
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

Effect *GetEffect(void);
#endif

