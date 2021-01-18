//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
//�I�u�W�F�N�g�̃w�b�_�[
//Author�Fsatou syusuke
//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
//#if 0

#ifndef _OBJECT_H_
#define _OBJECT_H_

#define MAX_OBJECT (255)//�ő�I�u�W�F�N�g

#define MAX_COLLISION (20)
#define MIN_COLLISION (20)

typedef enum
{
	OBJECTTYPE_TANK = 0,//���
	OBJECTTYPE_SANDBAG,	//�y�X
	OBJECTTYPE_BLOCK00,//�e�N�X�`���u���b�N
	OBJECTTYPE_BLOCK01,//�e�N�X�`���u���b�N
	OBJECTTYPE_MAX,
} OBJECTTYPE;

typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXVECTOR3 rot;//��]
	D3DXCOLOR Color;//�F

	D3DXVECTOR3 VtxMinObject; //���_�̍ŏ��l
	D3DXVECTOR3 VtxMaxObject; //���_�̍ő�l

	D3DXMATRIX mtxObject;//���[���h�}�g���b�N�X

	int ntype;//�g�p�^�C�v
	bool bUse;//�g�p��
} Object;

//�v���C���[�p�̐錾
void InitObject(void);
void UninitObject(void);
void UpdateObject(void);
void DrawObject(void);

void SetObject(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int ntype);

Object *GetObject(void);
#endif

//#endif

