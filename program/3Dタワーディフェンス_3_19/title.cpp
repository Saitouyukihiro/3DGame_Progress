//=============================================================================
//タイトルの処理
//=============================================================================
#include "Title.h"
#include "keyinput.h"
#include "Fade.h"
#include "Picture.h"

//-----------------------------------------------------------------------------
//図形の初期化処理
//-----------------------------------------------------------------------------
void InitTitle(void)
{
	InitPicture();
	SetPicture(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT, PICTURE_TITLE);
	SetPicture(D3DXVECTOR3(SCREEN_WIDTH / 2, 1380 / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 400, 150, PICTURE_GAMESTERTS);
}

//-----------------------------------------------------------------------------
//終了処理
//-----------------------------------------------------------------------------
void UninitTitle(void)
{
	UninitPicture();
}


//-----------------------------------------------------------------------------
//更新処理
//-----------------------------------------------------------------------------
void UpdateTitle(void)
{
	UpdatePicture();
	//次の画面に変わる
	if (GetKeyboardTrigger(DIK_RETURN) == true && GetFade() == FADE_NONE)
	{
		SetFade(MODE_SELECT);
	}
}

//-----------------------------------------------------------------------------
//描画処理
//-----------------------------------------------------------------------------
void DrawTitle(void)
{
	DrawPicture();
}