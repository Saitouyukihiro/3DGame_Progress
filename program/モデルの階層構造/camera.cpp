//---------------------------
//インクルードファイル
//---------------------------
#include <stdio.h>
#include "camara.h"
#include "keyinput.h"
#include "mouseinput.h"
#include "model.h"

//---------------------------
//グローバル変数
//---------------------------
Camera	g_Camera[MAX_CAMERA];	//カメラ

//--------------------------- 
//初期化処理
//---------------------------
HRESULT InitCamera(void)
{
	g_Camera[0].PosV = (D3DXVECTOR3(0.0f, 25.0f, 5.0f));
	g_Camera[0].PosR = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	g_Camera[0].Rot = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	g_Camera[0].VecU = (D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	g_Camera[0].bUse = true;

	g_Camera[1].PosV = (D3DXVECTOR3(0.0f, 100.0f, -50.0f));
	g_Camera[1].PosR = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	g_Camera[1].Rot = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	g_Camera[1].VecU = (D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	g_Camera[1].bUse = false;

	g_Camera[2].PosV = (D3DXVECTOR3(1000.0f, 1500.0f, -500.0f));
	g_Camera[2].PosR = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	g_Camera[2].Rot = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	g_Camera[2].VecU = (D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	g_Camera[2].bUse = false;

	return S_OK;
}

//---------------------------
//終了処理
//---------------------------
void UninitCamera(void)
{
	
}

//---------------------------
//更新処理
//---------------------------
void UpdateCamera(void)
{
	Player * pPlayer;	//モデルの構造体

	pPlayer = GetPlayer();	//モデルの情報

	//---------------------------
	//使ってるカメラのマウス情報
	//---------------------------
	for (int nCntCm = 0; nCntCm < MAX_CAMERA; nCntCm++)
	{
		if (g_Camera[nCntCm].bUse == true)
		{
			//前回の位置を保存
			g_Camera[nCntCm].Poiold = g_Camera[nCntCm].Pointer;

			//マウス座標の取得
			GetCursorPos(&g_Camera[nCntCm].Pointer);
		}
	}

	//---------------------------
	//TPS視点
	//---------------------------
	g_Camera[1].PosR = pPlayer->PosModel;

	g_Camera[1].PosR.x = pPlayer->PosModel.x + sinf(g_Camera[1].Rot.y + 10.0f) * g_Camera[1].Long;
	g_Camera[1].PosR.z = pPlayer->PosModel.z + cosf(g_Camera[1].Rot.y + 10.0f) * g_Camera[1].Long;
	g_Camera[1].PosR.y = pPlayer->PosModel.y + 5.0f;

	//---------------------------
	//FPS視点
	//---------------------------
	g_Camera[0].PosV = pPlayer->PosModel;

	g_Camera[0].PosV.x = pPlayer->PosModel.x;
	g_Camera[0].PosV.z = pPlayer->PosModel.z;
	g_Camera[0].PosV.y = pPlayer->PosModel.y + 25.0f;

	//---------------------------
	//マウスの座標の位置がどこか
	//---------------------------
	for (int nCntCm = 0; nCntCm < MAX_CAMERA; nCntCm++)
	{
		if (g_Camera[nCntCm].bUse == true)
		{
			if (g_Camera[nCntCm].Poiold.x > g_Camera[nCntCm].Pointer.x)
			{
				g_Camera[nCntCm].Poimove.x = g_Camera[nCntCm].Poiold.x - g_Camera[nCntCm].Pointer.x - 1;
			}
			else if (g_Camera[nCntCm].Poiold.x < g_Camera[nCntCm].Pointer.x)
			{
				g_Camera[nCntCm].Poimove.x = g_Camera[nCntCm].Poiold.x - g_Camera[nCntCm].Pointer.x + 1;
			}
			if (g_Camera[nCntCm].Poiold.y > g_Camera[nCntCm].Pointer.y)
			{
				g_Camera[nCntCm].Poimove.y = g_Camera[nCntCm].Poiold.y - g_Camera[nCntCm].Pointer.y - 1;
			}
			else if (g_Camera[nCntCm].Poiold.y < g_Camera[nCntCm].Pointer.y)
			{
				g_Camera[nCntCm].Poimove.y = g_Camera[nCntCm].Poiold.y - g_Camera[nCntCm].Pointer.y + 1;
			}
		}
	}

	for (int nCntCm = 0; nCntCm < MAX_CAMERA; nCntCm++)
	{
		//カメラと注視点の距離
		g_Camera[nCntCm].Long = CAMERA_DESTAANCE;
	}
	//---------------------------
	//視点注視点移動
	//---------------------------
	for (int nCntCm = 0; nCntCm < MAX_CAMERA; nCntCm++)
	{
		if (g_Camera[nCntCm].bUse == true)
		{
			if (GetKeyboardPress(DIK_W) == true)
			{
				g_Camera[nCntCm].PosV.x = g_Camera[nCntCm].PosV.x + sinf(g_Camera[nCntCm].Rot.y) * CAMERA_MOVE_SPEED;
				g_Camera[nCntCm].PosV.z = g_Camera[nCntCm].PosV.z + cosf(g_Camera[nCntCm].Rot.y) * CAMERA_MOVE_SPEED;

				g_Camera[nCntCm].PosR.x = g_Camera[nCntCm].PosR.x + sinf(g_Camera[nCntCm].Rot.y) * CAMERA_MOVE_SPEED;
				g_Camera[nCntCm].PosR.z = g_Camera[nCntCm].PosR.z + cosf(g_Camera[nCntCm].Rot.y) * CAMERA_MOVE_SPEED;
			}
			if (GetKeyboardPress(DIK_S) == true)
			{
				g_Camera[nCntCm].PosV.x = g_Camera[nCntCm].PosV.x - sinf(g_Camera[nCntCm].Rot.y) * CAMERA_MOVE_SPEED;
				g_Camera[nCntCm].PosV.z = g_Camera[nCntCm].PosV.z - cosf(g_Camera[nCntCm].Rot.y) * CAMERA_MOVE_SPEED;

				g_Camera[nCntCm].PosR.x = g_Camera[nCntCm].PosR.x - sinf(g_Camera[nCntCm].Rot.y) * CAMERA_MOVE_SPEED;
				g_Camera[nCntCm].PosR.z = g_Camera[nCntCm].PosR.z - cosf(g_Camera[nCntCm].Rot.y) * CAMERA_MOVE_SPEED;
			}
			if (GetKeyboardPress(DIK_A) == true)
			{
				g_Camera[nCntCm].PosV.x = g_Camera[nCntCm].PosV.x - cosf(g_Camera[nCntCm].Rot.y) * CAMERA_MOVE_SPEED;
				g_Camera[nCntCm].PosV.z = g_Camera[nCntCm].PosV.z + sinf(g_Camera[nCntCm].Rot.y) * CAMERA_MOVE_SPEED;

				g_Camera[nCntCm].PosR.x = g_Camera[nCntCm].PosR.x - cosf(g_Camera[nCntCm].Rot.y) * CAMERA_MOVE_SPEED;
				g_Camera[nCntCm].PosR.z = g_Camera[nCntCm].PosR.z + sinf(g_Camera[nCntCm].Rot.y) * CAMERA_MOVE_SPEED;
			}
			if (GetKeyboardPress(DIK_D) == true)
			{
				g_Camera[nCntCm].PosV.x = g_Camera[nCntCm].PosV.x + cosf(g_Camera[nCntCm].Rot.y) * CAMERA_MOVE_SPEED;
				g_Camera[nCntCm].PosV.z = g_Camera[nCntCm].PosV.z - sinf(g_Camera[nCntCm].Rot.y) * CAMERA_MOVE_SPEED;

				g_Camera[nCntCm].PosR.x = g_Camera[nCntCm].PosR.x + cosf(g_Camera[nCntCm].Rot.y) * CAMERA_MOVE_SPEED;
				g_Camera[nCntCm].PosR.z = g_Camera[nCntCm].PosR.z - sinf(g_Camera[nCntCm].Rot.y) * CAMERA_MOVE_SPEED;
			}
			//---------------------------
			//注視点横移動
			//---------------------------
			if (g_Camera[nCntCm].Poimove.x > 0 && MouseDowan(MOUSE_LEFT_BOTTON) == true)
			{
				g_Camera[nCntCm].Rot.y -= g_Camera[nCntCm].Poimove.x * 0.01;
				g_Camera[nCntCm].PosR.x = g_Camera[nCntCm].PosV.x + sinf(g_Camera[nCntCm].Rot.y) * g_Camera[nCntCm].Long;
				g_Camera[nCntCm].PosR.z = g_Camera[nCntCm].PosV.z + cosf(g_Camera[nCntCm].Rot.y) * g_Camera[nCntCm].Long;
			}
			else if (g_Camera[nCntCm].Poimove.x < 0 && MouseDowan(MOUSE_LEFT_BOTTON) == true)
			{
				g_Camera[nCntCm].Rot.y += g_Camera[nCntCm].Poimove.x * -0.01;
				g_Camera[nCntCm].PosR.x = g_Camera[nCntCm].PosV.x + sinf(g_Camera[nCntCm].Rot.y) * g_Camera[nCntCm].Long;
				g_Camera[nCntCm].PosR.z = g_Camera[nCntCm].PosV.z + cosf(g_Camera[nCntCm].Rot.y) * g_Camera[nCntCm].Long;
			}
			else if (g_Camera[nCntCm].Poimove.x == 0)
			{
				g_Camera[nCntCm].Rot.y += 0.0;
				g_Camera[nCntCm].PosR.x = g_Camera[nCntCm].PosV.x + sinf(g_Camera[nCntCm].Rot.y) * g_Camera[nCntCm].Long;
				g_Camera[nCntCm].PosR.z = g_Camera[nCntCm].PosV.z + cosf(g_Camera[nCntCm].Rot.y) * g_Camera[nCntCm].Long;
			}
			//---------------------------
			//注視点縦移動
			//---------------------------
			if (g_Camera[nCntCm].Poimove.y > 0 && MouseDowan(MOUSE_LEFT_BOTTON) == true)
			{
				g_Camera[nCntCm].PosR.y += g_Camera[nCntCm].Poimove.y * 3.0f;
			}
			else if (g_Camera[nCntCm].Poimove.y < 0 && MouseDowan(MOUSE_LEFT_BOTTON) == true)
			{
				g_Camera[nCntCm].PosR.y -= g_Camera[nCntCm].Poimove.y * -3.0f;
			}
			else if (g_Camera[nCntCm].Poimove.y == 0)
			{
				g_Camera[nCntCm].PosR.y += 0.0;
			}
			//---------------------------
			//視点横移動
			//---------------------------
			if (g_Camera[nCntCm].Poimove.x > 0 && MouseDowan(MOUSE_WHEEL_BOTTON) == true)
			{
				g_Camera[nCntCm].Rot.y += g_Camera[nCntCm].Poimove.x * 0.01f;
				g_Camera[nCntCm].PosV.x = g_Camera[nCntCm].PosR.x - sinf(g_Camera[nCntCm].Rot.y) * g_Camera[nCntCm].Long;
				g_Camera[nCntCm].PosV.z = g_Camera[nCntCm].PosR.z - cosf(g_Camera[nCntCm].Rot.y) * g_Camera[nCntCm].Long;
			}
			else if (g_Camera[nCntCm].Poimove.x < 0 && MouseDowan(MOUSE_WHEEL_BOTTON) == true)
			{
				g_Camera[nCntCm].Rot.y -= g_Camera[nCntCm].Poimove.x * -0.01f;
				g_Camera[nCntCm].PosV.x = g_Camera[nCntCm].PosR.x - sinf(g_Camera[nCntCm].Rot.y) * g_Camera[nCntCm].Long;
				g_Camera[nCntCm].PosV.z = g_Camera[nCntCm].PosR.z - cosf(g_Camera[nCntCm].Rot.y) * g_Camera[nCntCm].Long;
			}
			//---------------------------
			//視点縦移動
			//---------------------------
			if (g_Camera[nCntCm].Poimove.y > 0 && MouseDowan(MOUSE_RIGHT_BOTTON) == true)
			{
				g_Camera[nCntCm].PosV.y += g_Camera[nCntCm].Poimove.y * 1.0f;
			}
			else if (g_Camera[nCntCm].Poimove.y < 0 && MouseDowan(MOUSE_RIGHT_BOTTON) == true)
			{
				g_Camera[nCntCm].PosV.y -= g_Camera[nCntCm].Poimove.y * -1.0f;
			}
		}
	}

	//---------------------------
	//リセット
	//---------------------------
	if (GetKeyboardPress(DIK_RETURN) == true)
	{
		g_Camera[0].PosV = (D3DXVECTOR3(0.0f, 25.0f, -5.0f));
		g_Camera[0].PosR = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		g_Camera[0].Rot = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		g_Camera[0].VecU = (D3DXVECTOR3(0.0f, 1.0f, 0.0f));

		g_Camera[1].PosV = (D3DXVECTOR3(0.0f, 1000.0f, -1000.0f));
		g_Camera[1].PosR = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		g_Camera[1].Rot = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		g_Camera[1].VecU = (D3DXVECTOR3(0.0f, 1.0f, 0.0f));

		g_Camera[2].PosV = (D3DXVECTOR3(3000.0f, 2000.0f, -3000.0f));
		g_Camera[2].PosR = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		g_Camera[2].Rot = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		g_Camera[2].VecU = (D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	}
	//---------------------------
	//カメラの切り替え
	//---------------------------
	if (GetKeyboardTrigger(DIK_1) == true)
	{
		if (g_Camera[0].bUse == true)
		{
			g_Camera[2].bUse = true;
			g_Camera[0].bUse = false;
		}
		else if (g_Camera[1].bUse == true)
		{
			g_Camera[0].bUse = true;
			g_Camera[1].bUse = false;
		}
		else if (g_Camera[2].bUse == true)
		{
			g_Camera[1].bUse = true;
			g_Camera[2].bUse = false;
		}
	}
	else if (GetKeyboardTrigger(DIK_2) == true)
	{
		if (g_Camera[0].bUse == true)
		{
			g_Camera[1].bUse = true;
			g_Camera[0].bUse = false;
		}
		else if (g_Camera[1].bUse == true)
		{
			g_Camera[2].bUse = true;
			g_Camera[1].bUse = false;
		}
		else if (g_Camera[2].bUse == true)
		{
			g_Camera[0].bUse = true;
			g_Camera[2].bUse = false;
		}
	}
}

//---------------------------
//描画処理
//---------------------------
void SetCamera(void)
{
	LPDIRECT3DDEVICE9	pDevice;			//デバイスのポインタ

	pDevice = GetDevice();					//デバイスを取得する
	for (int nCntCamera = 0; nCntCamera < MAX_CAMERA; nCntCamera++)
	{
		if (g_Camera[nCntCamera].bUse == true)
		{
			//---------------------------
			//マトリックスの設定
			//---------------------------
			D3DXMatrixIdentity(&g_Camera[nCntCamera].mtxProjection);	//マトリックス初期化

															//マトリックスの作成
			D3DXMatrixPerspectiveFovLH(	&g_Camera[nCntCamera].mtxProjection,
										D3DXToRadian(90.0f),	//視野角
										(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
										10.0f,		//カメラの最小描画距離
										30000.0f);	//カメラの最大描画距離

							//プロジェクションマトリックス設定
			pDevice->SetTransform(	D3DTS_PROJECTION,
									&g_Camera[nCntCamera].mtxProjection);

			//ビューマトリックスの初期化
			D3DXMatrixIdentity(&g_Camera[nCntCamera].mtxView);

			//ビューマトリックスの作成
			D3DXMatrixLookAtLH(	&g_Camera[nCntCamera].mtxView,
								&g_Camera[nCntCamera].PosV,
								&g_Camera[nCntCamera].PosR,
								&g_Camera[nCntCamera].VecU);

			//ビューマトリックスの設定
			pDevice->SetTransform(	D3DTS_VIEW,
									&g_Camera[nCntCamera].mtxView);
		}
	}
}

//---------------------------
//カメラの情報
//---------------------------
Camera *GetCamera(void)
{
	return &g_Camera[0];
}

//---------------------------
//カメラ1の情報
//---------------------------
Camera *Get1Camera(void)
{
	return &g_Camera[1];
}