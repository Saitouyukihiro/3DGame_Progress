#pragma once
#ifndef _FADE_H_
#define _FADE_H_

//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "main.h"

//---------------------------
//�񋓌^
//---------------------------
typedef enum
{
	FADE_NONE = 0,
	FADE_IN,
	FADE_OUT,
	FADE_MAX
} FADE;

//---------------------------
//�}�N����`
//---------------------------

//---------------------------
//�v���g�^�C�v�錾
//---------------------------
void InitFade(MODE modeNext);
void UninitFade(void);
void UpdateFade(void);
void DrawFade(void);
void SetFade(MODE modeNext);
FADE GetFade(void);
#endif 
