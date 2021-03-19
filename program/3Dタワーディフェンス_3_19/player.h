#pragma once
#ifndef _PLAYER_H
#define _PLAYER_H
//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "main.h"

//---------------------------
//�}�N����`
//---------------------------
#define MAX_PLAYER_MODEL (1)		//�v���C���[���f���̍ő吔
#define MAX_PLAYER_TEX (128)		//�v���C���[���f���̃p�[�c�̃e�N�X�`���̍ő吔
#define MAX_PLAYER_PARTS_NUM (1)	//�v���C���[���f���̃p�[�c�̍ő吔
#define MAX_PLAYER_KEY (8)			//�v���C���[���f���L�[�̍ő吔
#define G_POW (-0.5f)				//�d�̗͂�
#define JUMP_POW (10.0f)			//�W�����v��

//---------------------------
//�񋓌^.���[�h�̎��
//---------------------------
typedef enum
{
	PLAYER_STATE_NEUTRAL = 0,	//�j���[�g����
	PLAYER_STATE_WALK,			//����
	PLAYER_STATE_ATTACK,		//�U��
	PLAYER_STATE_CONSTRUCTTION,
	PLAYER_STATE_TURRET,
	PLAYER_STATE_CUBE,
	PLAYER_STATE_MAX			//���X�g�̐�
} Playermodelstate;

typedef enum
{
	PLAYER_CONSTRUCTTION_NONE = 0,
	PLAYER_CONSTRUCTTION_TURRET,
	PLAYER_CONSTRUCTTION_CUBE,
	PLAYER_CONSTRUCTTION_MAX			//���X�g�̐�
} Playerconstructtion;

//---------------------------
//�\����
//---------------------------
typedef struct
{
	float fPosX;	//�ʒuX
	float fPosY;	//�ʒuY
	float fPosZ;	//�ʒuZ
	float fRotX;	//����X
	float fRotY;	//����Y
	float fRotZ;	//����Z
} Playerkey;

typedef struct
{
	float nFrame;							//�Đ��t���[��
	Playerkey aKey[MAX_PLAYER_PARTS_NUM];	//���f�����̃L�[�v�f
} Playerkeyinfo;

typedef struct
{
	bool bLoop;								//���[�v���邩
	int nNumKey;							//�L�[�̑���
	Playerkeyinfo aKeyinfo[MAX_PLAYER_KEY];	//�L�[�̏��(�L�[�̑�����)
} Playermotioninfo;

typedef struct
{
	LPD3DXMESH pMesh;		//���b�V���̃|�C���^
	LPD3DXBUFFER pBuffMat;	//�}�e���A���̃|�C���^
	DWORD pnNumMat;			//�}�e���A���̐�
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 rot;		//����
	D3DXVECTOR3 vtxMin, vtxMax;	//���_�̒[���
	D3DXMATRIX mtxWold;		//���[���h�}�g���b�N�X
	int nIdx;				//�e���f���̃C���f�b�N�X
} Playermodel;


typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 posold;		//�O��̈ʒu
	D3DXVECTOR3 rot;		//����
	D3DXVECTOR3 move;		//�ړ���
	D3DXMATRIX mtxWold;		//���[���h�}�g���b�N�X
	int nIdex;				//�e�̔ԍ�
	int ngunIdex;
	bool bLand;				//�n�ʂɂ��Ă邩
	Playermodel aModel[MAX_PLAYER_PARTS_NUM];	//���f���̃p�[�c
	int nNumModel = MAX_PLAYER_PARTS_NUM;		//���f���̃p�[�c��
	int nTurretIdx;
	int nCubeIdx;
	Playermotioninfo aMotioninfo[PLAYER_STATE_MAX];	//���[�V�������
	int nNumnMotion;		//���[�V������
	bool bLoopMotion;		//���[�v���邩
	int	nNumKey;			//�L�[��
	int nKey;				//�L�[No
	float nMotion;			//���[�V�����̃J�E���g
	Playermodelstate aState;//���[�V�������
	Playerconstructtion aConst;
	bool bJump;				//�W�����v�̏��
	bool bUse;				//�g���Ă邩
} Player;

//---------------------------
//�v���g�^�C�v�錾
//---------------------------
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void SetPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
Player *GetPlayer(void);
#endif