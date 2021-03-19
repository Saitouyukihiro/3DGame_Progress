//**************************************************************
//UI表示のヘッダー
//**************************************************************

#ifndef _UI_H_
#define _UI_H_

#include"main.h"

#define MAX_GAMEUI (128)//UIの最大数

//構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;//位置
	D3DXVECTOR3 move;//移動量
	D3DXCOLOR color;//色
	int ntype;//種類
	float fWidth;
	float fHeight;
	bool bUse;//使用してるか
} GAMEUI;

//他の所で点滅だとかにに使う
typedef struct
{
	int Serect;
} UIserect;

void InitGameUI(void);
void UninitGameUI(void);
void UpdateGameUI(void);
void DrawGameUI(void);

void SetGameUI(D3DXVECTOR3 pos,float fWidth,float fHeight ,int ntype);

GAMEUI * GetGameUI(void);
UIserect * GetUIserect(void);

#endif


