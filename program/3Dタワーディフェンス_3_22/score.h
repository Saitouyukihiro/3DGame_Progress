#pragma once
#ifndef _SCORE_H_
#define _SCORE_H_

//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "main.h"

//---------------------------
//�}�N����`
//---------------------------
#define MAX_SCOREDIGIT (5)	//�X�R�A�̌���
#define SCORE_Y (25)		//���a
#define SCORE_X (25)		//���a

//---------------------------
//�\���̂̒�`
//---------------------------
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
} Score;

//---------------------------
//�v���g�^�C�v�錾
//---------------------------
HRESULT InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
void AddScore(int nVolue);
int GetScore(void);
#endif