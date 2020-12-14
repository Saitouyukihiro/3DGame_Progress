#pragma once
#ifndef _FIXED_MODEL_H_
#define _FIXED_MODEL_H_
//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "main.h"

//---------------------------
//�}�N����`
//---------------------------
#define MAX_FIXED_MODEL (3)		//���f���̐�
#define MAX_FIXEMODEL_TEX (128)	//�e�N�X�`���̐�

//---------------------------
//�񋓌^
//---------------------------
typedef enum
{
	MODEL_HERTS = 0,	//�n�[�g
	MODEL_CAT,			//�`�[�L
	MODEL_TYPE_MAX		//���X�g�̐�
} MODEL_TYPE;

//---------------------------
//�\����
//---------------------------
typedef struct
{
	DWORD pnNumMatModel;		//�}�e���A���̐�
	D3DXVECTOR3 PosModel;		//�ʒu
	D3DXVECTOR3 RotModel;		//����
	D3DXVECTOR3 vtxMinModel, vtxMaxModel;	//���_�̒[���
	D3DXMATRIX mtxWoldModel;	//���[���h�}�g���b�N�X
	LPD3DXMESH pMeshFixedmodel;		//���b�V���̃|�C���^
	LPD3DXBUFFER pBuffMatFixedmodel;//�}�e���A���̃|�C���^
	MODEL_TYPE aType;			//���
	int nIdex;					//�e�̔ԍ�
	float fWidth;
	float fHeight;
	float fDepht;
	bool bUse;					//�g���Ă邩
} Fixedmodel;
//---------------------------
//�v���g�^�C�v�錾
//---------------------------
HRESULT InitFixedModel(void);
void UninitFixedModel(void);
void UpdateFixedModel(void);
void DrawFixedModel(void);
void SetFixedModel(D3DXVECTOR3 PosModel, D3DXVECTOR3 RotModel, MODEL_TYPE Type);
#endif