//---------------------------
//インクルードファイル
//---------------------------
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
#include "ui.h"
#include "score.h"
#include "Magazine.h"
#include "gunmodel.h"
#include "bullet.h"
#include "fade.h"
#include "enemycount.h"
#include "Sound.h"
#include "cube.h"
#include "camara.h"
#include "Effect.h"
#if _DEBUG
#include "keyinput.h"
#endif // _DEBUG


bool g_EnemySpan;
int g_nCntPporn;
int g_nRound;
int g_nDeth;
int g_nLife;
float g_fSpeed;
D3DXVECTOR3 g_pos[30];

//---------------------------
//初期化
//---------------------------
HRESULT Init5wave(void)
{
	srand((unsigned int)time(NULL));

	g_nRound = 0;
	g_nDeth = 0;
	g_nLife = 0;
	g_fSpeed = 0;
	g_nCntPporn = 0;
	g_EnemySpan = true;

	for (int nCnt = 0; nCnt < 30; nCnt++)
	{
		g_pos[nCnt] = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	}

	InitCount();

	InitBullet();

	InitGameUI();

	InitMagazine();

	InitScore();

	InitGunModel();
	InitEffect();

	InitPlayer();
	SetPlayer(D3DXVECTOR3(0.0f, 1000.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	InitTurret();

	InitCube();
	SetCube(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetCube(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(100.0f, 0.0f, 0.0f));

	InitSpider();

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
	PlaySound(SOUND_LABEL_BGM03);
	return S_OK;
}

//---------------------------
//終了処理
//---------------------------
void Uninit5wave(void)
{
	StopSound();

	UninitCount();
	UninitBullet();
	UninitGameUI();
	UninitMagazine();
	UninitScore();
	UninitGunModel();
	UninitEffect();
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
	g_nCntPporn++;

#if _DEBUG
	if (GetKeyboardTrigger(DIK_RETURN) == true && GetFade() == FADE_NONE)
	{
		SetFade(MODE_RESULT);
	}
#endif // _DEBUG


	UpdatePlayer();
	UpdateCount();
	UpdateBullet();
	UpdateGameUI();
	UpdateMagazine();
	UpdateScore();
	UpdateGunModel();
	UpdateEffect();
	UpdateTurret();
	UpdateCube();
	UpdateSpider();
	UpdateFloo();
	UpdateWall();
	UpdateGirl();
	UpdateShadow();

	g_nDeth = DethCount();

	if (g_nCntPporn > (144 * 3))
	{
		if (g_nRound <= 5 && g_EnemySpan == true)
		{
			for (int nSet = 0; nSet < 10; nSet++)
			{
				SetSpider(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1, 0.0f);
#if (0)
				int nX = float(rand() % 2);
				int nZ = float(rand() % 2);

				g_nLife = rand() % 3 + 1;
				g_fSpeed = float(rand() % 2 + 2) / 10;

				if (nX == 0)
				{
					g_pos[nSet].x = -1900;
				}
				else if (nX == 1)
				{
					g_pos[nSet].x = 1900;
				}

				if (nZ == 0)
				{
					g_pos[nSet].z = 1900;
				}
				else if (nZ == 1)
				{
					g_pos[nSet].z = -1900;
				}
				SetSpider(g_pos[nSet], D3DXVECTOR3(0.0f, 0.0f, 0.0f), g_nLife, g_fSpeed);
#endif // (0)
			}
			g_EnemySpan = false;
		}
		g_nCntPporn = 0;
	}
	if (g_nRound <= 5 && g_nDeth >= 10)
	{
		g_nRound++;
		ResetsDeth();
		g_EnemySpan = true;
	}
	if (g_nRound > 5 && GetFade() == FADE_NONE)
	{
		SetFade(MODE_RESULT);
	}
}

//---------------------------
//描画処理
//---------------------------
void Draw5wave(void)
{
	DrawBullet();
	DrawGameUI();
	DrawCount();
	DrawMagazine();
	DrawScore();
	DrawGunModel();
	DrawPlayer();
	DrawSpider();
	DrawTurret();
	DrawCube();
	DrawFloo();
	DrawWall();
	DrawGirl();
	DrawShadow();
	DrawEffect();

}