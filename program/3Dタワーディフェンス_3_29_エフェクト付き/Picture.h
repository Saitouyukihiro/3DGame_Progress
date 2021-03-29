#pragma once
#ifndef _PICTURE_H_
#define _PICTURE_H_

//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "main.h"

//---------------------------
//�}�N����`
//---------------------------
#define MAX_PICTURE_TEX (PICTURE_TYPE_MAX)	//�e�N�X�`���̐�
#define MAX_PICTURE (64)		//�摜���o����

//---------------------------
//�񋓌^.���[�h�̎��
//---------------------------
typedef enum
{
	PICTURE_TITLE = 0,	//�^�C�g��
	PICTURE_GAMESTERTS,
	PICTURE_5WAVE,		//5WAVE���[�h
	PICTURE_UNLIMITED,	//���������[�h
	PICTURE_RESULT,
	PICTURE_SELECT,
	PICTURE_OPERATE,
	PICTURE_TYPE_MAX,
} PICTURE_TYPE;

//---------------------------
//�\���̂̒�`
//---------------------------
typedef struct
{
	D3DXVECTOR3 pos;	//�|���S���̈ʒu
	D3DXVECTOR3 move;	//�ړ���
	float fWidth;		//��
	float fHeight;		//����
	PICTURE_TYPE aType;	//���
	bool bClick;		//�N���b�N���Ă邩�ǂ���
	bool bUse;			//�g���Ă邩�ǂ���
} Picture;

//---------------------------
//�v���g�^�C�v�錾
//---------------------------
HRESULT InitPicture(void);
void UninitPicture(void);
void UpdatePicture(void);
void DrawPicture(void);
void SetPicture(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWigth, float fHeight, PICTURE_TYPE aType);	//�ʒu�A���A�����A���
#endif 
