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

	InitRank();

	return S_OK;
}
//---------------------------
//終了処理
//---------------------------
void UninitResult(void)
{
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
		nCnt = 0;		//カウントしょきか
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