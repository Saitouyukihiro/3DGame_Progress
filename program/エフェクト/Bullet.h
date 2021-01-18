//**************************************************************
//�e�̃w�b�_�[
//Author�F�����G��
//**************************************************************

#ifndef _BULLET_H_
#define _BULLET_H_

#include"main.h"

//�}�N����`
#define MAX_BULLET (255)//�e�ő吔
#define MAX_BULLET_SIZE_X (7.0f)//�e�̃T�C�Y(X)
#define MAX_BULLET_SIZE_Y (7.0f)//�e�̃T�C�Y(Y)

typedef enum
{
	BULLETTYPE_PLAYER = 0,//�v���C���[�̒e
	BULLETTYPE_MAX,
} BULLETTYPE;

typedef struct
{
	D3DXMATRIX mtxWorld;//�}�g���b�N�X
	D3DXVECTOR3 pos;//�ʒu
	D3DXVECTOR3 rot;//��]

	int nlife;//�˒�
	int ntype;//�e�̃^�C�v
	bool bUse;//�g�p��

} Bullet;

void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);

void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int ntype);//�ʒu�A�����A���

Bullet *GetBullet(void);
#endif

