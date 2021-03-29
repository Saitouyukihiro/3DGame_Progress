//**************************************************************
//UI�\���̃w�b�_�[
//**************************************************************

#ifndef _UI_H_
#define _UI_H_

#include"main.h"

#define MAX_GAMEUI (128)//UI�̍ő吔

//�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXVECTOR3 move;//�ړ���
	D3DXCOLOR color;//�F
	int ntype;//���
	float fWidth;
	float fHeight;
	bool bUse;//�g�p���Ă邩
} GAMEUI;

//���̏��œ_�ł��Ƃ��ɂɎg��
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


