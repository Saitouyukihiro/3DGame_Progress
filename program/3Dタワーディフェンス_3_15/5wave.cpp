//---------------------------
//インクルードファイル
//---------------------------
#include "main.h"
#include "floo.h"
#include "wall.h"
#include "girl.h"
#include "shadow.h"
#include "camara.h"
#include "player.h"
#include "spider.h"
#include "turret.h"
#include "cube.h"

//---------------------------
//初期化
//---------------------------
HRESULT Init5wave(void)
{
	InitCamera();

	InitPlayer();
	SetPlayer(D3DXVECTOR3(0.0f, 1000.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	InitTurret();

	InitCube();

	InitSpider();
	SetSpider(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	InitFloo();
	SetFloo(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 4000.0f, 4000.0f, 0);

	InitWall();
	SetWall(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 2000.0f, 2000.0f), 4000.0f, 4000.0f, 0);
	SetWall(D3DXVECTOR3(0.0f, -D3DX_PI, 0.0f), D3DXVECTOR3(0.0f, 2000.0f, -2000.0f), 4000.0f, 4000.0f, 0);
	SetWall(D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(2000.0f, 2000.0f, 0.0f), 4000.0f, 4000.0f, 0);
	SetWall(D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f), D3DXVECTOR3(-2000.0f, 2000.0f, 0.0f), 4000.0f, 4000.0f, 0);
	InitShadow();

	InitGirl();
	SetGirl(D3DXVECTOR3(0.0f, 187.5f, -1980.0f), 500.0f, 375.0f, 0);

	return S_OK;
}

//---------------------------
//終了処理
//---------------------------
void Uninit5wave(void)
{
	UninitCamera();
	UninitPlayer();
	UninitTurret();
	UninitCube();
	UninitSpider();
	UninitFloo();
	UninitWall();
	UninitGirl();
	UninitShadow();
}

//---------------------------
//更新処理
//---------------------------
void Update5wave(void)
{
	UpdateCamera();
	UpdatePlayer();
	UpdateTurret();
	UpdateCube();
	UpdateSpider();
	UpdateFloo();
	UpdateWall();
	UpdateGirl();
	UpdateShadow();

	SetCamera();
}

//---------------------------
//描画処理
//---------------------------
void Draw5wave(void)
{
	DrawPlayer();
	DrawSpider();
	DrawTurret();
	DrawCube();
	DrawFloo();
	DrawWall();
	DrawGirl();
	DrawShadow();
}