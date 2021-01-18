//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
//���f���̃w�b�_�[
//Author�Fsatou syusuke
//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[

#ifndef _ENEMY_H_
#define _ENEMY_H_

#define MAX_PARTS (3)
#define MAX_ENEMY (64)

typedef struct
{
	LPD3DXMESH pMeshEnemy = NULL;//���b�V���ւ̃|�C���^
	LPD3DXBUFFER pBuffMatEnemy = NULL;//�}�e���A���ւ̃|�C���^
	DWORD nNumMatEnemy = 0;		//�}�e���A���̐�

	D3DXVECTOR3 pos;//�ʒu
	D3DXVECTOR3 rot;//��]

	D3DXVECTOR3 VtxMinEnemy; //���_�̍ŏ��l
	D3DXVECTOR3 VtxMaxEnemy; //���_�̍ő�l
	D3DXMATRIX mtxWorldEnemy;

	int nIndxModelParent;//�e���f���̃C���f�b�N�X
} ENEMY;

typedef enum
{
	ENEMYTYPE_LMG,
	ENEMYTYPE_MAX,
}ENEMYTYPE;

typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXVECTOR3 rot;//��]
	D3DXMATRIX mtxWorldEnemy;//���[���h�}�g���b�N�X

	ENEMY aEnemy[MAX_PARTS];
	int nNumEnemy;

	int ntype;
	bool bUse;
	int nLife;
}Enemy;


//�v���C���[�p�̐錾
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);

void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife, int ntype);

Enemy *GetEnemy(void);
#endif


