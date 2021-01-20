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
#define FADE_POLYGON_WIDTH (1280)
#define FADE_POLYGON_HEIGHT (720)

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
