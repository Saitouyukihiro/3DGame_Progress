#pragma once
#ifndef _WALL_H_
#define _WALL_H_
//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "main.h"

//---------------------------
//�}�N����`
//---------------------------
#define MAX_WALL (4)	//�ǂ̍ő吔
#define MAX_WALL_TEX (1)//�e�N�X�`���̐�
#define WALL_X (0.5f)	//�ǂ̕�
#define WALL_Y (0.5f)	//�ǂ̍���

//---------------------------
//�\����
//---------------------------
typedef struct
{
	D3DXVECTOR3	pos;		//�ʒu
	D3DXVECTOR3 rot;		//����
	D3DXMATRIX mtxWold;		//���[���h�}�g���b�N�X
	float fWidth;			//��
	float fHeiht;			//����
	int nType;				//���
	bool bUse;				//�g���Ă邩�ǂ���
} Wall;

//---------------------------
//�v���g�^�C�v�錾
//---------------------------
HRESULT InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void DrawWall(void);
void SetWall(D3DXVECTOR3 rot, D3DXVECTOR3 pos, float fWith, float fHeight, int nType);	//�����A�ʒu�A���A�����A���
bool ColisionWall(D3DXVECTOR3 *pos, D3DXVECTOR3 *posold, D3DXVECTOR3 *move, float fWidth, float fHeight, float fDepht, int nType);	//�ʒu�A�O��̈ʒu�A�ړ��ʁA���A�����A���s�A���
#endif