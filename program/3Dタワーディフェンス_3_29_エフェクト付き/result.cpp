//---------------------------
//インクルードファイル
//---------------------------
#include "result.h"
#include "fade.h"
#include "rank.h"
#include "Picture.h"
#include "keyinput.h"
#include "mouseinput.h"
#include "sound.h"

//---------------------------
//グローバル変数
//---------------------------
bool g_bUse2 = false;

//---------------------------
//初期化処理
//---------------------------
HRESULT InitResult(void)
{
	InitPicture();
	SetPicture(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT, PICTURE_RESULT);

	InitRank();
	PlaySound(SOUND_LABEL_BGM02);
	return S_OK;
}
//---------------------------
//終了処理
//---------------------------
void UninitResult(void)
{
	StopSound();
	UninitPicture();

	UninitRank();
}
//---------------------------
//更新処理
//---------------------------
void UpdateResult(void)
{
	static int nCnt;	//自動繊維タイマー
	int nNum = 0;		//rando用の変数

	nCnt++;				//タイマー加算

	UpdatePicture();

	UpdateRank();

	//タイマーが1584になるか || エンターキー押してたか
	if (nCnt >= 1584 && GetFade() == FADE_NONE || GetKeyboardTrigger(DIK_RETURN) == true && GetFade() == FADE_NONE || MouseDowan(MOUSE_WHEEL_BOTTON) == true && GetFade() == FADE_NONE)
	{
		SetFade(MODE_TITLE);
		PlaySound(SOUND_LABEL_Enter000);
		nCnt = 0;		//カウント初期化
	}
}
//---------------------------
//描画処理
//---------------------------
void DrawResult(void)
{
	DrawPicture();

	DrawRank();
}