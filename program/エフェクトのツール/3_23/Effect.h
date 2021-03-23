//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
//�G�t�F�N�g�̃w�b�_�[
//Author�Fsatou syusuke
//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[

#ifndef _EFFECT_H_
#define _EFFECT_H_

#define MAX_EFFECT (10000)//��ʂɕK�v
#define CIRCLE (float(rand() % 314) / 100.0f - float(rand() % 314) / 100.0f) //�~�̃}�N��
#define POSRAND (rand() % 10 + 10)

typedef enum
{
	EFFECTTYPE_CIRCLE,//�~�`�ɏo��
	EFFECTTYPE_STRIGHIT,//�܂������ɔ��
	EFFECTTYPE_FOLL,//�オ�����㗎����
	EFFECTTYPE_POP,//�e����

	EFFECTTYPE_MAX,
} EFFECTTYPE;

typedef struct
{
	D3DXMATRIX mtxWorld;
	D3DXMATRIX mtxView;

	D3DXVECTOR3 pos;//�ʒu
	D3DXVECTOR3 rot;

	D3DXVECTOR3 move;

	int colorR;
	int colorG;
	int colorB;
	int colorA;

	int ntype;
	int nlife;

	float fHight;
	float fWhidth;

	bool bUse;

} Effect;

typedef struct
{
	int colorR;
	int colorG;
	int colorB;
	int colorA;

	int MinColorR;
	int MinColorG;
	int MinColorB;
	int MinColorA;

	D3DXVECTOR3 move;
	D3DXVECTOR3 rot;

	float fHight;
	float fWhidth;

	int SerectType;
	int SerectColor;
	int nLifeSerect;
	int nRadius;
	int nDensity;
} Effectstate;

//�v���C���[�p�̐錾
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);

void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR color, D3DXVECTOR3 rot, float fWhidth, float fHight, int ntype, int nLife);//�o���ʒu�@�F�E���ˊp�x�@���@�����@�^�C�v�@����

Effect *GetEffect(void);
Effectstate * GetEffectstate(void);
#endif

