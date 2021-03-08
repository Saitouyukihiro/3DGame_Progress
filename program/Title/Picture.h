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
	PICTURE_TYPE_TITLE = 0,			//�^�C�g��
	PICTURE_TYPE_ENTER,				//�v�b�V���g�D�G���^�[
	PICTURE_TYPE_GUYS_00,			//�K�C�Y00
	PICTURE_TYPE_GUYS_01,			//�K�C�Y01
	PICTURE_TYPE_GUYS_02,			//�K�C�Y02
	PICTURE_TYPE_GUYS_03,			//�K�C�Y03
	PICTURE_TYPE_GUNLINE_00,		//�e���̐�
	PICTURE_TYPE_GUNREMAINING_00,	//�ō��e��(�A�T���g)
	PICTURE_TYPE_RESULT,			//���U���g���
	PICTURE_TYPE_ROUND,				//R
	PICTURE_TYPE_RETICLE_00,		//���e�B�N��
	PICTURE_TYPE_1ST,				//�����L���O
	PICTURE_TYPE_2ND,				//�����L���O
	PICTURE_TYPE_3RD,				//�����L���O
	PICTURE_TYPE_MAX				//���X�g�̐�
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
	bool bUse;			//�g���Ă邩�ǂ���
} Picture;

//---------------------------
//�v���g�^�C�v�錾
//---------------------------
HRESULT InitPicture(void);
void UninitPicture(void);
bool UpdatePicture(void);
void DrawPicture(void);
bool SetPicture(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWigth, float fHeight, PICTURE_TYPE aType);	//�ʒu�A���A�����A���
#endif 
