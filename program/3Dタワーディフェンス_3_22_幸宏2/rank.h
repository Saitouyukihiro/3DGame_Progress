#pragma once
#ifndef _RANK_H_
#define _RANK_H_

//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "main.h"

//---------------------------
//�}�N����`
//---------------------------
#define MAX_RANK (3)		//�����L���O�̐�
#define RANK_Y (25 * 2)		//���a
#define RANK_X (25 * 2)		//���a

//---------------------------
//�\���̂̒�`
//---------------------------
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
} RANK;

//---------------------------
//�v���g�^�C�v�錾
//---------------------------
HRESULT InitRank(void);
void UninitRank(void);
void UpdateRank(void);
void DrawRank(void);
#endif