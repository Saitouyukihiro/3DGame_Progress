#pragma once
#ifndef _SPIDER_H_
#define _SPIDER_H_
//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "main.h"

//---------------------------
//�}�N����`
//---------------------------
#define MAX_SPIDER_MODEL (64)		//�G���f���̍ő吔
#define MAX_SPIDER_TEX (128)		//�G���f���̃p�[�c�̃e�N�X�`���̍ő吔
#define MAX_SPIDER_PARTS_NUM (6)	//�G���f���̃p�[�c�̍ő吔
#define MAX_SPIDER_KEY (8)		//�G���f���L�[�̍ő吔
#define G_POW (-0.5f)			//�d�̗͂�

//---------------------------
//�񋓌^.���[�h�̎��
//---------------------------
typedef enum
{
	SPIDER_STATE_WALK = 0,	//����
	SPIDER_STATE_ATTACK,		//�U��
	SPIDER_STATE_MAX			//���X�g�̐�
} Spidermodelstate;
typedef enum
{
	SPIDER_STATE_LOOK = 0,
	SPIDER_STATE_NOLOOK,
} Spiderlook;
typedef enum
{
	COLLISION_PLAYER = 0,
	COLLISION_GIRL,
	COLLISION_BULLET,
	COLLISION_MAX
} CollisionType;

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
} Spiderkey;

typedef struct
{
	float nFrame;							//�Đ��t���[��
	Spiderkey aKey[MAX_SPIDER_PARTS_NUM];		//���f�����̃L�[�v�f
} Spiderkeyinfo;

typedef struct
{
	bool bLoop;								//���[�v���邩
	int nNumKey;							//�L�[�̑���
	Spiderkeyinfo aKeyinfo[MAX_SPIDER_KEY];	//�L�[�̏��(�L�[�̑�����)
} Spidermotioninfo;

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
} Spidermodel;

typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 posold;		//�O��̈ʒu
	D3DXVECTOR3 move;		//�ړ���
	D3DXVECTOR3 posdfrc;	//���Ԃ�
	D3DXVECTOR3 rot;		//����
	D3DXMATRIX mtxWold;		//���[���h�}�g���b�N�X
	int nIdex;				//�e�̔ԍ�
	int nLife;								//�̗�
	bool bLand;				//�n�ʂɂ��Ă邩
	Spidermodel aModel[MAX_SPIDER_PARTS_NUM];	//���f���̃p�[�c
	int nNumModel = MAX_SPIDER_PARTS_NUM;	//���f���̃p�[�c��
	Spidermotioninfo aMotioninfo[SPIDER_STATE_MAX];	//���[�V�������
	int nNumnMotion;		//���[�V������
	bool bLoopMotion;		//���[�v���邩
	int	nNumKey;			//�L�[��
	int nKeyold;			//�O��̃L�[
	int nKey;				//�L�[No
	float fMotion;			//���[�V�����̃J�E���g
	float fLookigZ = 2000.0f;			//���イ���Ă�
	float fLookigX = 2000.0f;			//��
	float fWidth = 25.0f;					//���aX
	float fHight = 25.0f;					//���aY
	float fDepth = 25.0f;					//���aZ
	float fLength;
	float fAngle;
	float fMoveSpeed;
	Spidermodelstate aState;	//���[�V�������
	Spiderlook aLook;
	bool bCllision;
	bool bUse;				//�g���Ă邩
} Spider;
//---------------------------
//�v���g�^�C�v�錾
//---------------------------
HRESULT InitSpider(void);
void UninitSpider(void);
void UpdateSpider(void);
void DrawSpider(void);
void SetSpider(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife, float fMoveSpeed);
void SpiderLooknig(int nCntSpider);
bool CollisionSpider(D3DXVECTOR3 *pos, D3DXVECTOR3 *posold, D3DXVECTOR3 *move, float fWidth, float fHeight, CollisionType nType);
int DethCount(void);
void ResetsDeth(void);
Spider *GetSpider(void);
#endif