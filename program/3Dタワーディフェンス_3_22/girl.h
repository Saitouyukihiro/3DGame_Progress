#pragma once
#ifndef _GIRL_H
#define _GIRL_H
//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "main.h"

//---------------------------
//�}�N����`
//---------------------------
#define MAX_GIRL (5)	//�r���{�[�h�̍ő吔
#define MAX_GIRL_TEX (3)//�r���{�[�h�̃e�N�X�`��
#define GIRL_X (0.5)	//�r���{�[�h�̕�
#define GIRL_Y (0.5)	//�r���{�[�h�̍���

//---------------------------
//�񋓌^.���[�h�̎��
//---------------------------
typedef enum
{
	GIRL_STATE_LEFT = 0,	//����
	GIRL_STATE_RIGHT,		//�U��
	GIRL_STATE_NONE,
	GIRL_STATE_MAX			//���X�g�̐�
} Girlmove;

//---------------------------
//�\����
//---------------------------
typedef struct
{
	D3DXVECTOR3	pos;		//�ʒu
	D3DXVECTOR3 posold;
	D3DXVECTOR3 move;		//�ړ���
	D3DXMATRIX mtxWold;		//���[���h�}�g���b�N�X
	D3DXMATRIX mtxView;		//�J�����̌���
	Girlmove aState;
	float fWidth;			//��
	float fHeiht;			//����
	float fLookigZ = 100.0f;			//���イ���Ă�
	float fLookigX = 100.0f;			//��
	int nAnim;				//�A�j���[�V����
	int nIdex;				//�e�̔ԍ�
	int nType;				//���
	bool bUse;				//�g���Ă邩�ǂ���
} Girl;

//---------------------------
//�v���g�^�C�v�錾
//---------------------------
HRESULT InitGirl(void);
void UninitGirl(void);
void UpdateGirl(void);
void DrawGirl(void);
void SetGirl(D3DXVECTOR3 pos, float fWidth, float fHeight, int nType);
void GirlLooking(D3DXVECTOR3 pos);
Girl *GetGirl(void);
#endif