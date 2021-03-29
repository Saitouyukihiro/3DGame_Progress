#pragma once
#ifndef _GUNMODEL_H_
#define _GUNMODEL_H_
//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "main.h"

//---------------------------
//�}�N����`
//---------------------------
#define MAX_GUN_MODEL (32)	//���f���̐�
#define MAX_GUN_TEX (128)	//�e�N�X�`���̐�

//---------------------------
//�񋓌^
//---------------------------
typedef enum
{
	HANDGUN = 0,	//�n���h�K��
	ASULTRIFLE,		//�A�T���g
	GUN_MODELMAX,	//���X�g�̐�
} Guntype;

//---------------------------
//�\����
//---------------------------
typedef struct
{
	DWORD pnNumMat;		//�}�e���A���̐�
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 rot;		//����
	D3DXVECTOR3 vtxMin, vtxMax;	//���_�̒[���
	D3DXMATRIX mtxWold;		//���[���h�}�g���b�N�X
	D3DXMATRIX mtxView;		//�J�����̌���
	LPD3DXMESH pMesh;		//���b�V���̃|�C���^
	LPD3DXBUFFER pBuffMat;//�}�e���A���̃|�C���^
	Guntype aType;			//���
	int nCnt;
	bool bUse;					//�g���Ă邩
} Gunmodel;
//---------------------------
//�v���g�^�C�v�錾
//---------------------------
HRESULT InitGunModel(void);
void UninitGunModel(void);
void UpdateGunModel(void);
void DrawGunModel(void);
int SetGunModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, Guntype Type);
Guntype SetPointGunModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nIdx);
bool CollisionGunModel(D3DXVECTOR3 *pos, D3DXVECTOR3 *posold, D3DXVECTOR3 *move, float fWidth, float fHeight, int *nIdx);
#endif