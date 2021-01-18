//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
//�r���{�[�h�̃w�b�_�[
//Author�Fsatou syusuke
//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[

#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#define MAX_BILLBOARD (256)

typedef enum
{
	TYPE_BILLBOARDPLAYER,
	TYPE_BILLBOARDFIRE,
	TYPE_BILLBOARMAX,
} BILLBOARTYPE;

typedef struct
{
	D3DXMATRIX mtxWorld;
	D3DXMATRIX mtxView;
	D3DXVECTOR3 pos;

	int ntype;
	int nlife;
	float fWhidth;
	float fHight;
	bool bUse;

} Billboard;

//�v���C���[�p�̐錾
HRESULT InitBillboard(void);
void UninitBillboard(void);
void UpdateBillboard(void);
void DrawBillboard(void);

void SetBillboard(D3DXVECTOR3 pos, float fWhidth, float fHight, int ntype);

Billboard *GetBillboard(void);
#endif
