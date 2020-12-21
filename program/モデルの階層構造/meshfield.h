#pragma once
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_
//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "main.h"

//---------------------------
//�}�N����`
//---------------------------
#define MAX_FIELD (8)		//���b�V���t�B�[���h�̐�
#define MAX_MESH_TEX (4)	//�e�N�X�`���̐�
#define MS_X (1.0f)			//���̔��aX
#define MS_Y (1.0f)			//���̔��aY
#define MS_Z (1.0f)			//���̔��aZ

//---------------------------
//���^�C�v
//---------------------------
#define FLOO_MAX_VTX_X (4)	//���u���b�N�̐�
#define FLOO_MAX_VTX_Z (4)	//���s�u���b�N�̐�
#define FLOO_VTX_NUM_MAX ((FLOO_MAX_VTX_X + 1) * (FLOO_MAX_VTX_Z + 1))				//�S�̒��_�̐�
#define FLOO_IDX_NUM_MAX ((FLOO_MAX_VTX_X + 1) * (FLOO_MAX_VTX_Z + 1) + (FLOO_MAX_VTX_Z - 1) * (FLOO_MAX_VTX_X + 3))	//�C���f�b�N�X�̐�
#define FLOO_POLY_NUM_MAX (2 * FLOO_MAX_VTX_X * FLOO_MAX_VTX_Z + (FLOO_MAX_VTX_Z * 4) - 4))	//���̐�

//---------------------------
//�ǃ^�C�v
//---------------------------
#define WALL_MAX_VTX_X (5)	//���u���b�N�̐�
#define WALL_MAX_VTX_Y (5)	//�c�u���b�N�̐�
#define WALL_VTX_NUM_MAX ((WALL_MAX_VTX_X + 1) * (WALL_MAX_VTX_Y + 1))				//�S�̒��_�̐�
#define WALL_IDX_NUM_MAX ((WALL_MAX_VTX_X + 1) * (WALL_MAX_VTX_Y + 1) + (WALL_MAX_VTX_Y - 1) * (WALL_MAX_VTX_X + 3))	//�C���f�b�N�X�̐�
#define WALL_POLY_NUM_MAX (2 * WALL_MAX_VTX_X * WALL_MAX_VTX_Y + (WALL_MAX_VTX_Y * 4) - 4))	//���̐�

//---------------------------
//���~�^�C�v
//---------------------------
#define SEMICIRCLE_MAX_VTX_X (5)	//���u���b�N�̐�
#define SEMICIRCLE_MAX_VTX_Y (5)	//�c�u���b�N�̐�
#define SEMICIRCLE_MAX_VTX_Z (5)	//���s�u���b�N�̐�
#define SEMICIRCLE_VTX_NUM_MAX ((SEMICIRCLE_MAX_VTX_X + 1) * (SEMICIRCLE_MAX_VTX_Y + 1))				//�S�̒��_�̐�
#define SEMICIRCLE_IDX_NUM_MAX ((SEMICIRCLE_MAX_VTX_X + 1) * (SEMICIRCLE_MAX_VTX_Y + 1) + (SEMICIRCLE_MAX_VTX_Y - 1) * (SEMICIRCLE_MAX_VTX_X + 3))	//�C���f�b�N�X�̐�
#define SEMICIRCLE_POLY_NUM_MAX (2 * SEMICIRCLE_MAX_VTX_X * SEMICIRCLE_MAX_VTX_Y + (SEMICIRCLE_MAX_VTX_Y * 4) - 4))	//���̐�

//---------------------------
//�񋓌^
//---------------------------
typedef enum
{
	FORM_FLOO = 0,		//���`
	FORM_WALL,			//�ǌ`
	FORM_SEMICIRCLE,	//���~
	FORM_MAX			//���X�g�̐�
} MESH_FORM;

//---------------------------
//�\����
//---------------------------
typedef struct
{
	D3DXVECTOR3	Pos;		//�ʒu
	D3DXVECTOR3 Rot;		//����
	D3DXMATRIX mtxWold;		//���[���h�}�g���b�N�X
	LPDIRECT3DVERTEXBUFFER9 pVtxBuffField;	//���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 pIdxBuffFoeld;	//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	float fWidth;			//��
	float fHeiht;			//����
	float fDepht;			//���s
	MESH_FORM aState;		//�ǂ�Ȍ`
	int nTex;				//�e�N�X�`��
	bool bUse;				//�g���Ă邩
} Field;
//---------------------------
//�v���g�^�C�v�錾
//---------------------------
HRESULT InitMeshfield(void);
void UninitMeshfield(void);
void UpdateMeshfield(void);
void DrawMeshfield(void);
void SetField(D3DXVECTOR3 rot, D3DXVECTOR3 pos, float fWidth, float fHeight, float fDepht, int nTex, MESH_FORM aState);	//�����A�ʒu�A���A�����A���s�A�e�N�X�`���A�`
bool ColisionFeild(D3DXVECTOR3 *pos, D3DXVECTOR3 *posold, D3DXVECTOR3 *move, float fWidth, float fHeight, float fDepht, int nType);	//�ʒu�A�O��̈ʒu�A�ړ��ʁA���A�����A���s�A���
Field *GetField(void);
#endif