//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
//�X�R�A�̃w�b�_�[
//Author�F�����G��
//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[

#ifndef _MAGAZINE_H_
#define _MAGAZINE_H_

#include "main.h"
#include "Player.h"

//�e�̃^�C�v(�K�v�ɂȂ����珇���ǉ����Ă�������)
typedef enum
{
	TYPE_ASSULT,
	TYPE_HANDGUN,
	TYPE_MAX,
} GUN_TYPE;

//�X�R�A�̍\����
typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
} Magazine;

typedef struct
{
	GUN_TYPE state;//�����^�C�v
} Equipment;

void InitMagazine(void);
void UninitMagazine(void);
void UpdateMagazine(void);
void DrawMagazine(void);

Magazine *GetMagazine(void);
Equipment * GetEquipment(void);
#endif


