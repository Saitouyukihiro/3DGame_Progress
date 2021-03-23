#pragma once
#ifndef _FLOO_H_
#define _FLOO_H_
//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "main.h"

//---------------------------
//�}�N����`
//---------------------------
#define MAX_FLOO (1)		//�����b�V���t�B�[���h�̐�
#define MAX_FLOO_TEX (1)	//�e�N�X�`���̐�
#define MS_FLOO_X (0.5f)	//���̔��aX
#define MS_FLOO_Z (0.5f)	//���̔��aZ

//---------------------------
//���^�C�v
//---------------------------
#define FLOO_MAX_VTX_X (10)	//���u���b�N�̐�
#define FLOO_MAX_VTX_Z (10)	//���s�u���b�N�̐�
#define FLOO_VTX_NUM_MAX ((FLOO_MAX_VTX_X + 1) * (FLOO_MAX_VTX_Z + 1))				//�S�̒��_�̐�
#define FLOO_IDX_NUM_MAX ((FLOO_MAX_VTX_X + 1) * (FLOO_MAX_VTX_Z + 1) + (FLOO_MAX_VTX_Z - 1) * (FLOO_MAX_VTX_X + 3))	//�C���f�b�N�X�̐�
#define FLOO_POLY_NUM_MAX (2 * FLOO_MAX_VTX_X * FLOO_MAX_VTX_Z + (FLOO_MAX_VTX_Z * 4) - 4))	//���̐�

//---------------------------
//�\����
//---------------------------
typedef struct
{
	D3DXVECTOR3	pos;		//�ʒu
	D3DXVECTOR3 rot;		//����
	D3DXMATRIX mtxWold;		//���[���h�}�g���b�N�X
	float fWidth;			//��
	float fDepht;			//���s
	int nTex;				//�e�N�X�`��
	bool bUse;				//�g���Ă邩
} Field;
//---------------------------
//�v���g�^�C�v�錾
//---------------------------
HRESULT InitFloo(void);
void UninitFloo(void);
void UpdateFloo(void);
void DrawFloo(void);
void SetFloo(D3DXVECTOR3 rot, D3DXVECTOR3 pos, float fWidth, float fDepht, int nTex);	//�����A�ʒu�A���A���s�A�e�N�X�`��
bool ColisionFloo(D3DXVECTOR3 *pos, D3DXVECTOR3 *posold, D3DXVECTOR3 *move, float fWidth, float fHeight, float fDepht, int nType);	//�ʒu�A�O��̈ʒu�A�ړ��ʁA���A�����A���s�A���
Field *GetFloo(void);
#endif