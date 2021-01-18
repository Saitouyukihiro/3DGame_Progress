//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
//�G�t�F�N�g�̃w�b�_�[
//Author�Fsatou syusuke
//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[

#ifndef _EFFECT_H_
#define _EFFECT_H_

#define MAX_EFFECT (20000)//��ʂɕK�v

typedef enum//�o���G�t�F�N�g�̋O��
{
	EFFECTTYPE_PLAYER,//�o���㓮���Ȃ�

	EFFECTTYPE_FOLL_ST,//�o���ꏊ���牺�ɗ�����
	EFFECTTYPE_FOLL_L,//�o���ꏊ���獶���ɗ�����
	EFFECTTYPE_FOLL_R,//�o���ꏊ����E���ɗ�����

	EFFECTTYPE_UP_ST,//�o���ꏊ�����ɏオ��
	EFFECTTYPE_UP_L,//�o���ꏊ���獶��ɏオ��
	EFFECTTYPE_UP_R,//�o���ꏊ����E��ɏオ��

	EFFECTTYPE_MAX,
} EFFECTTYPE;

typedef struct
{
	D3DXMATRIX mtxWorld;
	D3DXMATRIX mtxView;

	D3DXVECTOR3 pos;//�ʒu
	D3DXVECTOR3 move;
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
//�o���ʒu�@�F�@���@�����@�^�C�v�@����
Effect *GetEffect(void);
#endif

