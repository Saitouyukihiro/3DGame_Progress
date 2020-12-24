//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
//�G�t�F�N�g�̃w�b�_�[
//Author�Fsatou syusuke
//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[

#ifndef _EFFECT_H_
#define _EFFECT_H_

#define MAX_EFFECT (10000)

typedef enum
{
	EFFECTTYTPE_PLAYER,
	EFFECTTYPE_MAX,
} EFFECTTYPE;

typedef struct
{
	D3DXMATRIX mtxWorld;
	D3DXMATRIX mtxView;

	D3DXVECTOR3 pos;//�ʒu
	D3DXCOLOR color; //�F

	int ntype;
	int nlife;

	float fHight;
	float fWhidth;

	bool bUse;

} Effect;

//�v���C���[�p�̐錾
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);

void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR color, float fWhidth, float fHight, int ntype, int nLife);

Effect *GetEffect(void);
#endif

