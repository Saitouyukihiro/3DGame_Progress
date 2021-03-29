#pragma once
#ifndef _TURRET_H_
#define _TURRET_H_
//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "main.h"

//---------------------------
//�}�N����`
//---------------------------
#define MAX_TURRET (64)	//�ǂ̍ő吔

//---------------------------
//�\����
//---------------------------
typedef struct
{
	D3DXVECTOR3	pos;		//�ʒu
	D3DXVECTOR3 rot;		//����
	D3DXMATRIX mtxWold;		//���[���h�}�g���b�N�X
	LPD3DXMESH pMesh;		//���b�V���̃|�C���^
	LPD3DXBUFFER pBuffMat;	//�}�e���A���̃|�C���^
	DWORD pnNumMat;			//�}�e���A���̐�
	D3DXVECTOR3 vtxMin, vtxMax;	//���_�̒[���
	bool bCollision;
	bool bUse;				//�g���Ă邩�ǂ���
} Turret;

//---------------------------
//�v���g�^�C�v�錾
//---------------------------
HRESULT InitTurret(void);
void UninitTurret(void);
void UpdateTurret(void);
void DrawTurret(void);
int SetTurretUse(D3DXVECTOR3 rot, D3DXVECTOR3 pos, bool bCollision);
void SetTurret(int nIdx, D3DXVECTOR3 rot, D3DXVECTOR3 pos, bool bCollision);	//�����A�ʒu
bool ColisionTurret(D3DXVECTOR3 *pos, D3DXVECTOR3 *posold, D3DXVECTOR3 *move, float fWidth, float fHeight, float fDepht, int nType);
Turret *GetTurret(void);
#endif