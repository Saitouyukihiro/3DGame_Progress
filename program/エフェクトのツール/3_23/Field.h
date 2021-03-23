//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
//�|���S���̃w�b�_�[
//Author�Fsatou syusuke
//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[

#ifndef _FIELD_H_
#define _FIELD_H_

#define MAX_FIELD (4)
#define MS_X (1.0f)			//���̔��aX
#define MS_Y (1.0f)			//���̔��aY
#define MS_Z (1.0f)			//���̔��aZ

#define FLOO_MAX_VTX_X (4)	//���u���b�N�̐�
#define FLOO_MAX_VTX_Z (4)	//���s�u���b�N�̐�
#define FLOO_VTX_NUM_MAX ((FLOO_MAX_VTX_X + 1) * (FLOO_MAX_VTX_Z + 1))//�S�̒��_�̐�
#define FLOO_IDX_NUM_MAX ((FLOO_MAX_VTX_X + 1) * (FLOO_MAX_VTX_Z + 1) + (FLOO_MAX_VTX_Z - 1) * (FLOO_MAX_VTX_X + 3))//�C���f�b�N�X�̐�
#define FLOO_POLY_NUM_MAX (2 * FLOO_MAX_VTX_X * FLOO_MAX_VTX_Z + (FLOO_MAX_VTX_Z * 4) - 4))	//���̐�


typedef enum
{
	FIELDTYPE_NOMAL,
	FIELDTYPE_MAX,
} FIELDTYPE;

typedef struct
{
	D3DXVECTOR3 pos;						//�ʒu
	D3DXVECTOR3 rot;						//��]
	D3DXMATRIX mtxwold;						//���[���h�}�g���b�N�X
	LPDIRECT3DVERTEXBUFFER9 pVtxBuffField;	//���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 pIdxBuffField;	//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	float fWidth;							//��
	float fDepht;							//���s
	int ntype;								//�^�C�v
	bool bUse;								//�g�p���Ă邩
} Field;


//�v���C���[�p�̐錾
HRESULT InitField(void);
void UninitField(void);
void UpdateField(void);
void DrawField(void);

void SetField(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fDepht,int ntype);

#endif
