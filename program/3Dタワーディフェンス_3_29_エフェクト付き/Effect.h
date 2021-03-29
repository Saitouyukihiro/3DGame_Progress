//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
//�G�t�F�N�g�̃w�b�_�[
//Author�Fsatou syusuke
//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[

#ifndef _EFFECT_H_
#define _EFFECT_H_

#define MAX_EFFECT (5000)//��ʂɕK�v
#define LOADFILENAME "data/Effect.txt"
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

	int MinColorR;
	int MinColorG;
	int MinColorB;
	int MinColorA;

	int ntype;
	int nlife;

	float fMinWhidth;
	float fMinHight;

	float fHight;
	float fWhidth;

	bool bUse;

} Effect;

typedef struct
{

	D3DXVECTOR3 move;
	D3DXVECTOR3 rot;

	int nRadius;
	int nDensity;

	int colorR;
	int colorG;
	int colorB;
	int colorA;

	int MinColorR;
	int MinColorG;
	int MinColorB;
	int MinColorA;

	float fMinWhidth;
	float fMinHight;

	float fHight;
	float fWhidth;

	int ntype;
	int nlife;

} Effectstate;

//�v���C���[�p�̐錾
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);

void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR color, D3DXCOLOR Mincolor,D3DXVECTOR3 rot, float fWhidth, float fHight, float fMinWhidth,float fMinHight, int ntype, int nLife);

void SetEffectState(void);

Effect *GetEffect(void);
Effectstate * GetEffectstate(void);
#endif

