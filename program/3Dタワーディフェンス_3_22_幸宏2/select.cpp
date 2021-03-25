#include "select.h"
#include "Picture.h"
#include "Sound.h"

HRESULT InitSelect(void)
{
	InitPicture();
	SetPicture(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT, PICTURE_SELECT);
	SetPicture(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 450.0f, 75.0f, PICTURE_5WAVE);
	SetPicture(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + (200), 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 450.0f, 75.0f, PICTURE_UNLIMITED);
	

	PlaySound(SOUND_LABEL_BGM007);

	return S_OK;
}
void UninitSelect(void)
{
	StopSound();
	UninitPicture();
}
void UpdateSelect(void)
{
	UpdatePicture();
}
void DrawSelect(void)
{
	DrawPicture();
}