#pragma once
#ifndef _BULLET_H
#define _BULLET_H
//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "main.h"

//---------------------------
//�}�N����`
//---------------------------
#define BULLET_MOVE_SPEED (6.0f)	//�e�̑���
#define BULlET_SCALE_X (10.0f)	//�X�P�[���T�C�Y
#define BULLET_SCALE_Y (10.0f)	//�X�P�[���T�C�Y
#define BULLET_X (1.0f)	//�ʃT�C�YX���a
#define BULLET_Y (1.0f)	//�ʃT�C�YY���a
#define MAX_BULLET (256)			//�ʂ̍ő吔
#define MAX_BULLET_TEX (1)			//�e�N�X�`���̍ő吔
#define BULLET_SPAN (10)			//�e�̃N�[���^�C��

//---------------------------
//�񋓌^
//---------------------------
typedef enum
{
	BULLET_ASULT = 0,	//�A�T���g���C�t���̒e
	BULLET_MAX,			//���X�g�̐�
} Bullettype;

//---------------------------
//�\����
//---------------------------
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 posold;		//�O��̈ʒu
	D3DXVECTOR3 move;		//�ړ���
	D3DXVECTOR3 apos[4];	//
	D3DXVECTOR3 avec[4];	//
	D3DXVECTOR3 rot;		//����
	D3DXMATRIX mtxWold;		//���[���h�}�g���b�N�X
	D3DXMATRIX mtxView;		//�J�����̌���
	Bullettype aType;		//���
	float fWidth;			//��
	float fHeight;			//����
	int nIdex;				//�e�̔ԍ�	
	bool bUse;				//�g���Ă邩
} Bullet;

//---------------------------
//�v���g�^�C�v�錾
//---------------------------
HRESULT InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, float fWidth, float fHeight, Bullettype aType);	//�ʒu�A�����A�ړ��ʁA���A�����A���
Bullet *GetBullet(void);
#endif