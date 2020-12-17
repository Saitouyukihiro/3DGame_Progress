#pragma once
#ifndef _MODEL_H_
#define _MODEL_H_
//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "main.h"

//---------------------------
//�}�N����`
//---------------------------
#define MAX_MODEL (1)
#define MAX_MODEL_NUM (9)
#define G_POW (-0.5f)

//---------------------------
//�\����
//---------------------------
typedef struct
{
	LPD3DXMESH pMeshModel;		//���b�V���̃|�C���^
	LPD3DXBUFFER pBuffMatModel;	//�}�e���A���̃|�C���^
	DWORD pnNumMatModel;		//�}�e���A���̐�
	D3DXVECTOR3 PosModel;		//�ʒu
	D3DXVECTOR3 RotModel;		//����
	D3DXVECTOR3 vtxMinModel, vtxMaxModel;	//���_�̒[���
	D3DXMATRIX mtxWoldModel;	//���[���h�}�g���b�N�X
	int nIdxModel;				//�e���f���̃C���f�b�N�X
} Model;

typedef struct
{
	D3DXVECTOR3 PosModel;			//�ʒu
	D3DXVECTOR3 PosoldModel;		//�O��̈ʒu
	D3DXVECTOR3 Move;				//�ړ���
	D3DXVECTOR3 RotModel;			//����
	D3DXMATRIX mtxWoldModel;		//���[���h�}�g���b�N�X
	int nIdex;						//�e�̔ԍ�
	bool bLand;						//�n�ʂɂ��Ă邩
	Model aModel[MAX_MODEL_NUM];	//���f���̃p�[�c
	int nNumModel = MAX_MODEL_NUM;	//���f���̃p�[�c��
} Player;
//---------------------------
//�v���g�^�C�v�錾
//---------------------------
HRESULT InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);
void PlayerInfo(void);
Player *GetPlayer(void);
#endif