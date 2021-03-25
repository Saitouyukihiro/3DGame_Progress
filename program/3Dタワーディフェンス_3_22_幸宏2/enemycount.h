#pragma once
#ifndef _ENEMYCOUNT_H_
#define _ENEMYCOUNT_H_

//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "main.h"

//---------------------------
//�}�N����`
//---------------------------
#define MAX_ENEMY_COUNT_DIGIT (2)	//�X�R�A�̌���
#define ENEMY_COUNT_Y (25)		//���a
#define ENEMY_COUNT_X (25)		//���a

//---------------------------
//�\���̂̒�`
//---------------------------
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
} Enemycount;

//---------------------------
//�v���g�^�C�v�錾
//---------------------------
HRESULT InitCount(void);
void UninitCount(void);
void UpdateCount(void);
void DrawCount(void);
int GetCount(void);
#endif