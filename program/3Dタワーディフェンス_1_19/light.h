#pragma once
#ifndef _LIGHT_H_
#define _LIGHT_H_
//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "main.h"

//---------------------------
//�}�N����`
//---------------------------
#define MAX_LIGHT (3)			//���C�g�̐�

//---------------------------
//�v���g�^�C�v�錾
//---------------------------
HRESULT InitLight(void);
void UninitLight(void);
void UpdateLight(void);
#endif