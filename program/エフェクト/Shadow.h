//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
//�e�̃w�b�_�[
//Author�Fsatou syusuke
//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[

#ifndef _SHADOW_H_
#define _SHADOW_H_

#define MAX_SHADOW (256)

typedef enum
{
	TYPE_PLAYER,
	TYPE_ENEMY,

	TYPE_MAX,
}ShadowType;

typedef struct
{
	D3DXMATRIX mtxWorld;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	float fWhidth;
	float fDepth;
	int ntype;
	bool bUse;
} Shadow;

//�v���C���[�p�̐錾
HRESULT InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);

void SetShadow(D3DXVECTOR3 pos, float fWhidth, float fDepth, int ntype);
#endif
