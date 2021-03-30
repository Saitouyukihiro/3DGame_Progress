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
#include "Effect.h"

#if _DEBUG
#include "keyinput.h"
#endif // _DEBUG


bool g_EnemySpanUnlimted;
int g_nCntPpornUnlimted;
int g_nRoundUnlimted;
int g_nDethUnlimted;
int g_nLifeUnlimted;
float g_fSpeedUnlimted;
D3DXVECTOR3 g_posUnlimted[30];

//---------------------------
//初期化
//---------------------------
HRESULT InitUnlimted(void)
{
	srand((unsigned int)time(NULL));

	g_nRoundUnlimted = 0;
	g_nDethUnlimted = 0;
	g_nLifeUnlimted = 0;
	
	g_fSpeedUnlimted = 0;
	g_nCntPpornUnlimted = 0;
	g_EnemySpanUnlimted = true;

	for (int nCnt = 0; nCnt < 30; nCnt++)
	{
		g_posUnlimted[nCnt] = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
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
	//上右
	SetCube(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(100.0f, 0.0f, 400.0f));	//X,Y,Z
	SetCube(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(200.0f, 0.0f, 480.0f));
	SetCube(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(300.0f, 0.0f, 400.0f));
	SetCube(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(400.0f, 0.0f, 400.0f));

	//下右
	SetCube(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(100.0f, 0.0f, -400.0f));
	SetCube(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(200.0f, 0.0f, -480.0f));
	SetCube(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(300.0f, 0.0f, -400.0f));
	SetCube(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(400.0f, 0.0f, -400.0f));
	//==================================================================================	
	//上左
	SetCube(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-100.0f, 0.0f, 400.0f));
	SetCube(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-200.0f, 0.0f, 480.0f));
	SetCube(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-300.0f, 0.0f, 400.0f));
	SetCube(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-400.0f, 0.0f, 400.0f));

	//下左
	SetCube(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-100.0f, 0.0f, -400.0f));
	SetCube(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-200.0f, 0.0f, -480.0f));
	SetCube(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-300.0f, 0.0f, -400.0f));
	SetCube(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-400.0f, 0.0f, -400.0f));
	//==================================================================================

	//上２左
	SetCube(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-100.0f, 0.0f, 300.0f));
	SetCube(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-200.0f, 0.0f, 380.0f));
	SetCube(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-300.0f, 0.0f, 300.0f));
	SetCube(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-400.0f, 0.0f, 500.0f));

	//下２左
	SetCube(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-100.0f, 0.0f, -300.0f));
	SetCube(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-200.0f, 0.0f, -380.0f));
	SetCube(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-300.0f, 0.0f, -300.0f));
	SetCube(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-400.0f, 0.0f, -300.0f));
	//==================================================================================

	//上3左
	SetCube(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-100.0f, 0.0f, 200.0f));
	SetCube(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-200.0f, 0.0f, 180.0f));
	SetCube(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-300.0f, 0.0f, 100.0f));
	SetCube(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-400.0f, 0.0f, 100.0f));

	//下3左
	SetCube(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-100.0f, 0.0f, -200.0f));
	SetCube(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-200.0f, 0.0f, -180.0f));
	SetCube(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-300.0f, 0.0f, -100.0f));
	SetCube(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-400.0f, 0.0f, -100.0f));
	//==================================================================================

	//上4左
	SetCube(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(100.0f, 0.0f, 200.0f));
	SetCube(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(200.0f, 0.0f, 180.0f));
	SetCube(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(300.0f, 0.0f, 100.0f));
	SetCube(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(400.0f, 0.0f, 100.0f));

	//下4左
	SetCube(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(100.0f, 0.0f, -200.0f));
	SetCube(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(200.0f, 0.0f, -180.0f));
	SetCube(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(300.0f, 0.0f, -100.0f));
	SetCube(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(400.0f, 0.0f, -100.0f));
	//==================================================================================

	InitSpider();

	InitFloo();
	SetFloo(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1000.0f, 1000.0f, 0);

	InitWall();
	SetWall(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 500.0f, 500.0f), 1000.0f, 1000.0f, 0);
	SetWall(D3DXVECTOR3(0.0f, -D3DX_PI, 0.0f), D3DXVECTOR3(0.0f, 500.0f, -500.0f), 1000.0f, 1000.0f, 0);
	SetWall(D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(500.0f, 500.0f, 0.0f), 1000.0f, 1000.0f, 0);
	SetWall(D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f), D3DXVECTOR3(-500.0f, 500.0f, 0.0f), 1000.0f, 1000.0f, 0);
	InitShadow();

	InitGirl();
	SetGirl(D3DXVECTOR3(0.0f, 50.0f, -400.0f), 200.0f, 100.0f, 0);
	PlaySound(SOUND_LABEL_BGM03);
	return S_OK;
}

//---------------------------
//終了処理
//---------------------------
void UninitUnlimted(void)
{
	StopSound();

	UninitCount();
	UninitBullet();
	UninitGameUI();
	UninitMagazine();
	UninitScore();
	UninitGunModel();
	UninitPlayer();
	UninitTurret();
	UninitCube();
	UninitSpider();
	UninitFloo();
	UninitWall();
	UninitGirl();
	UninitShadow();
	UninitEffect();
}

//---------------------------
//更新処理
//---------------------------
void UpdateUnlimted(void)
{
	g_nCntPpornUnlimted++;

#if _DEBUG
	if (GetKeyboardTrigger(DIK_RETURN) == true && GetFade() == FADE_NONE)
	{
		SetFade(MODE_RESULT);
	}
#endif // _DEBUG


	UpdateCount();
	UpdateBullet();
	UpdateGameUI();
	UpdateMagazine();
	UpdateScore();
	UpdateGunModel();
	UpdatePlayer();
	UpdateTurret();
	UpdateCube();
	UpdateSpider();
	UpdateFloo();
	UpdateWall();
	UpdateGirl();
	UpdateShadow();
	UpdateEffect();
	g_nDethUnlimted = DethCount();

	if (g_nCntPpornUnlimted > (144 * 3))
	{
		if (g_nRoundUnlimted <= 5 && g_EnemySpanUnlimted == true)
		{
			for (int nSet = 0; nSet < 10; nSet++)
			{
				//SetSpider(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1, 0.0f);
#if (1)
				int nX = float(rand() % 2);
				int nZ = float(rand() % 2);

				g_nLifeUnlimted = rand() % 3 + 1;
				g_fSpeedUnlimted = float(rand() % 2 + 2) / 10;

				if (nX == 0)
				{
					g_posUnlimted[nSet].x = -480;
				}
				else if (nX == 1)
				{
					g_posUnlimted[nSet].x = 480;
				}

				if (nZ == 0)
				{
					g_posUnlimted[nSet].z = 480;
				}
				else if (nZ == 1)
				{
					g_posUnlimted[nSet].z = -480;
				}
				SetSpider(g_posUnlimted[nSet], D3DXVECTOR3(0.0f, 0.0f, 0.0f), g_nLifeUnlimted, g_fSpeedUnlimted);
#endif // (0)
				g_EnemySpanUnlimted = false;
				g_nCntPpornUnlimted = 0;
			}
		}
		if (g_nRoundUnlimted >= 6 && g_nRoundUnlimted <= 10 && g_EnemySpanUnlimted == true)
		{
			for (int nSet = 0; nSet < 20; nSet++)
			{
				//SetSpider(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1, 0.0f);
#if (1)
				int nX = float(rand() % 2);
				int nZ = float(rand() % 2);

				g_nLifeUnlimted = rand() % 5 + 1;
				g_fSpeedUnlimted = float(rand() % 3 + 2) / 10;

				if (nX == 0)
				{
					g_posUnlimted[nSet].x = -480;
				}
				else if (nX == 1)
				{
					g_posUnlimted[nSet].x = 480;
				}

				if (nZ == 0)
				{
					g_posUnlimted[nSet].z = 480;
				}
				else if (nZ == 1)
				{
					g_posUnlimted[nSet].z = -480;
				}
				SetSpider(g_posUnlimted[nSet], D3DXVECTOR3(0.0f, 0.0f, 0.0f), g_nLifeUnlimted, g_fSpeedUnlimted);
#endif // (0)
				g_EnemySpanUnlimted = false;
				g_nCntPpornUnlimted = 0;
			}
		}
		if (g_nRoundUnlimted <= 11 && g_nRoundUnlimted <= 100 && g_EnemySpanUnlimted == true)
		{
			for (int nSet = 0; nSet < 30; nSet++)
			{
				//SetSpider(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1, 0.0f);
#if (1)
				int nX = float(rand() % 2);
				int nZ = float(rand() % 2);

				g_nLifeUnlimted = rand() % 8 + 1;
				g_fSpeedUnlimted = float(rand() % 4 + 2) / 10;

				if (nX == 0)
				{
					g_posUnlimted[nSet].x = -480;
				}
				else if (nX == 1)
				{
					g_posUnlimted[nSet].x = 480;
				}

				if (nZ == 0)
				{
					g_posUnlimted[nSet].z = 480;
				}
				else if (nZ == 1)
				{
					g_posUnlimted[nSet].z = -480;
				}
				SetSpider(g_posUnlimted[nSet], D3DXVECTOR3(0.0f, 0.0f, 0.0f), g_nLifeUnlimted, g_fSpeedUnlimted);
#endif // (0)
				g_EnemySpanUnlimted = false;
				g_nCntPpornUnlimted = 0;
			}
		}
	}
	if (g_nRoundUnlimted <= 5 && g_nDethUnlimted >= 10)
	{
		g_nRoundUnlimted++;
		ResetsDeth();
		g_EnemySpanUnlimted = true;
	}
	if (g_nRoundUnlimted >= 6 && g_nRoundUnlimted <= 10 && g_nDethUnlimted >= 20)
	{
		g_nRoundUnlimted++;
		ResetsDeth();
		g_EnemySpanUnlimted = true;
	}
	if (g_nRoundUnlimted >= 11 && g_nRoundUnlimted <= 100 && g_nDethUnlimted >= 30)
	{
		g_nRoundUnlimted++;
		ResetsDeth();
		g_EnemySpanUnlimted = true;
	}
}

//---------------------------
//描画処理
//---------------------------
void DrawUnlimted(void)
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