//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
//���f���̃w�b�_�[
//Author�Fsatou syusuke
//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[

#ifndef _MODEL_H_
#define _MODEL_H_

#define MAX_MODEL (3)

typedef struct
{
	LPD3DXMESH pMeshModel = NULL;//���b�V���ւ̃|�C���^
	LPD3DXBUFFER pBuffMatModel = NULL;//�}�e���A���ւ̃|�C���^
	DWORD nNumMatmodel = 0;		//�}�e���A���̐�

	D3DXVECTOR3 pos;//�ʒu
	D3DXVECTOR3 rot;//��]

	D3DXVECTOR3 VtxMinModel; //���_�̍ŏ��l
	D3DXVECTOR3 VtxMaxModel; //���_�̍ő�l
	D3DXMATRIX mtxWorldModel;

	int nIndxModelParent;//�e���f���̃C���f�b�N�X
} Model;

typedef enum
{
	PLAYERSTATE_NOMAL,
	PLAYERSTATE_RELOAD,
	PLAYERSTATE_MAX,
}PLAYERSTATE;

typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXVECTOR3 rot;//��]
	D3DXMATRIX mtxWorldPlayer;//���[���h�}�g���b�N�X

	Model aModel[MAX_MODEL];
	PLAYERSTATE state;
	//�����[�h�֌W
	int MugzineBullet;//�}�K�W���e��
	int ReloadTime;//�����[�h����

	int nNumModel;
}Player;


//�v���C���[�p�̐錾
void InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);

Player *GetModel(void);
#endif

