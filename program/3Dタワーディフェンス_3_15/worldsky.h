#pragma once
#ifndef _WORLD_SKY_H_
#define _WORLD_SKY_H_
//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "main.h"

//---------------------------
//�}�N����`
//---------------------------
#define MAX_SKY (1)		//���~���b�V���t�B�[���h�̐�
#define MAX_SKY_TEX (1)	//�e�N�X�`���̐�
#define MS_SKY_X (0.5f)	//���~�̔��aX
#define MS_SKY_Y (0.5f)	//���~�̔��aZ

//---------------------------
//���^�C�v
//---------------------------
#define SKY_MAX_VTX_X (4)	//���u���b�N�̐�
#define SKY_MAX_VTX_Y (4)	//�c�u���b�N�̐�
#define SKY_MAX_VTX_Z (4)	//���s�u���b�N�̐�
#define SKY_VTX_NUM_MAX ((SKY_MAX_VTX_X + 1) * (SKY_MAX_VTX_Z + 1))				//�S�̒��_�̐�
#define SKY_IDX_NUM_MAX ((SKY_MAX_VTX_X + 1) * (SKY_MAX_VTX_Z + 1) + (SKY_MAX_VTX_Z - 1) * (SKY_MAX_VTX_X + 3))	//�C���f�b�N�X�̐�
#define SKY_POLY_NUM_MAX (2 * SKY_MAX_VTX_X * SKY_MAX_VTX_Z + (SKY_MAX_VTX_Z * 4) - 4))	//���̐�

//---------------------------
//�\����
//---------------------------
typedef struct
{
	D3DXVECTOR3	pos;		//�ʒu
	D3DXVECTOR3 rot;		//����
	D3DXMATRIX mtxWold;		//���[���h�}�g���b�N�X
	float fWidth;			//��
	float fHeight;			//����
	float fDepht;			//���s
	int nTex;				//�e�N�X�`��
	bool bUse;				//�g���Ă邩
} Worldsky;
//---------------------------
//�v���g�^�C�v�錾
//---------------------------
HRESULT InitSky(void);
void UninitSky(void);
void UpdateSky(void);
void DrawSky(void);
void SetSky(D3DXVECTOR3 rot, D3DXVECTOR3 pos, float fWidth, float fDepht, int nTex);	//�����A�ʒu�A���A���s�A�e�N�X�`��
#endif