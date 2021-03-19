#include "select.h"
#include "Picture.h"

HRESULT InitSelect(void)
{
	InitPicture();
	SetPicture(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 450.0f, 75.0f, PICTURE_5WAVE);
	SetPicture(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + (200), 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 450.0f, 75.0f, PICTURE_UNLIMITED);

	return S_OK;
}
void UninitSelect(void)
{
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