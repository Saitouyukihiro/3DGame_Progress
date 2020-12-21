//=============================================================================
//
// メイン処理 [main.cpp]
// Author : KAZUTO SAKAI
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "main.h"
#include "keyinput.h"
#include "camara.h"
#include "light.h"
#include "model.h"
#include "shadow.h"
#include "wall.h"
#include "mouseinput.h"
#include "billboard.h"
#include "meshfield.h"
#include "bullet.h"
#include "fixedmodel.h"

#ifdef _DEBUG

#endif  _DEBUG


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CLASS_NAME		"AppClass"			// ウインドウのクラス名
#define WINDOW_NAME		"3Dポリゴンの描画"	// ウインドウのキャプション名

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
#ifdef _DEBUG
void DrawFPS(void);
#endif

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3D9			g_pD3D = NULL;			// Direct3D オブジェクト
LPDIRECT3DDEVICE9	g_pD3DDevice = NULL;	// Deviceオブジェクト(描画に必要)
#ifdef _DEBUG
LPD3DXFONT			g_pFont = NULL;			// フォントへのポインタ
#endif
int					g_nCountFPS;			// FPSカウンタ
MODE				g_mode = MODE_TEST;		//現在のモード
MODE				g_modeold;
RECT				g_rc;					//マウス座標範囲の取得

//=============================================================================
// メイン関数
//=============================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	HWND hWnd;
	MSG msg;
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;

	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	// 指定したクライアント領域を確保するために必要なウィンドウ座標を計算
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	// ウィンドウの作成
	hWnd = CreateWindow(	CLASS_NAME,
							WINDOW_NAME,
							WS_OVERLAPPEDWINDOW,
							CW_USEDEFAULT,
							CW_USEDEFAULT,
							(rect.right - rect.left),
							(rect.bottom - rect.top),
							NULL,
							NULL,
							hInstance,
							NULL);

	// 初期化処理(ウィンドウを作成してから行う)
	if (FAILED(Init(hInstance, hWnd, true)))
	{
		return -1;
	}

	// 分解能を設定
	timeBeginPeriod(1);

	// フレームカウント初期化
	dwExecLastTime =
		dwFPSLastTime = timeGetTime();
	dwCurrentTime =
		dwFrameCount = 0;

	// ウインドウの表示(初期化処理の後に呼ばないと駄目)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{// PostQuitMessage()が呼ばれたらループ終了
				break;
			}
			else
			{
				// メッセージの翻訳とディスパッチ
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{// 0.5秒ごとに実行
				g_nCountFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 144))
			{// 1/144秒経過
				dwExecLastTime = dwCurrentTime;

				// 更新処理
				Update();

				// 描画処理
				Draw();

				dwFrameCount++;
			}
		}
	}

	// 終了処理
	Uninit();

	// 分解能を戻す
	timeEndPeriod(1);

	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//=============================================================================
// ウインドウプロシージャ
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	// Direct3Dオブジェクトの作成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	// 現在のディスプレイモードを取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));					// ワークをゼロクリア
	d3dpp.BackBufferCount = 1;							// バックバッファの数
	d3dpp.BackBufferWidth = SCREEN_WIDTH;				// ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;				// ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat = d3ddm.Format;				// カラーモードの指定
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;			// 映像信号に同期してフリップする
	d3dpp.Windowed = TRUE;								// ウィンドウモード
	d3dpp.EnableAutoDepthStencil = TRUE;						// デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					// デプスバッファとして16bitを使う
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// インターバル

	// デバイスの生成
	// ディスプレイアダプタを表すためのデバイスを作成
	// 描画と頂点処理をハードウェアで行なう
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &g_pD3DDevice)))
	{
		// 上記の設定が失敗したら
		// 描画をハードウェアで行い、頂点処理はCPUで行なう
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &g_pD3DDevice)))
		{
			// 上記の設定が失敗したら
			// 描画と頂点処理をCPUで行なう
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp, &g_pD3DDevice)))
			{
				// 初期化失敗
				return E_FAIL;
			}
		}
	}

	// レンダーステートの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);				// カリングを行わない
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Zバッファを使用
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// αブレンドを行う
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定

	// サンプラーステートの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(U値)を設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(V値)を設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// テクスチャ縮小フィルタモードを設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// テクスチャ拡大フィルタモードを設定

	// テクスチャステージステートの設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

#ifdef _DEBUG
	// デバッグ情報表示用フォントを設定
	D3DXCreateFont(g_pD3DDevice, 50, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &g_pFont);
#endif

	InitKeyboard(hInstance, hWnd);

	InitMouse(hInstance, hWnd);

	InitCamera();

	InitLight();

	//カーソルの有り無し
	ShowCursor(TRUE);

	//ウィンドウ座標を取得
	GetWindowRect(hWnd, &g_rc);

	//マウス座標の設定
	SetCursorPos(g_rc.right / 2, g_rc.bottom / 2);

#ifdef _DEBUG
	
#endif _DEBUG

	SetMode(g_mode);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void Uninit(void)
{
#ifdef _DEBUG
	if (g_pFont != NULL)
	{// デバッグ情報表示用フォントを設定
		g_pFont->Release();
		g_pFont = NULL;
	}
#endif
	//省略部分：各種オブジェクトの終了処理
	UninitKeyboard();

	UninitMouse();

	UninitMeshfield();

	UninitModel();

	UninitFixedModel();

	UninitBillboard();

	UninitShadow();

	UninitWall();

	UninitCamera();

	UninitLight();

	//マウス移動範囲の初期化
	ClipCursor(NULL);
	if (g_pD3DDevice != NULL)
	{// デバイスの開放
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	if (g_pD3D != NULL)
	{// Direct3Dオブジェクトの開放
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void Update(void)
{
	//省略部分：各種オブジェクトの更新処理
	UpdateKeyboard();

	UpdateMouse();

	UpdateCamera();

	UpdateLight();

	UpdateMeshfield();

	//ウィンドウ内にマウスを捕える
	ClipCursor(&g_rc);

	switch (g_mode)
	{
	case MODE_TEST:
		UpdateShadow();
		UpdateModel();
		UpdateFixedModel();
		UpdateBullet();
		UpdateBillboard();
		UpdateWall();
		break;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void Draw(void)
{
	// バックバッファ＆Ｚバッファのクリア
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(100, 0, 0, 0), 1.0f, 0);

	// Direct3Dによる描画の開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{

		//省略部分：各種オブジェクトの描画処理
		switch (g_mode)
		{
		case MODE_TEST:
			DrawMeshfield();
			DrawShadow();
			DrawModel();
			DrawFixedModel();
			DrawBullet();
			DrawBillboard();
			DrawWall();
			break;
		}
		SetCamera();
#ifdef _DEBUG
		DrawFPS();
		DrawCmTxt();
		DrawCmInfo();
		LightInfo();
		LightTxt();
		PlayerInfo();
#endif
		// Direct3Dによる描画の終了
		g_pD3DDevice->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=============================================================================
// デバイスを取得
//=============================================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//=============================================================================
// モードの切り替え
//=============================================================================
void SetMode(MODE mode)
{
	g_modeold = g_mode;

	switch (g_mode)
	{
	case MODE_TEST:
		UninitMeshfield();
		UninitModel();
		UninitFixedModel();
		UninitBullet();
		UninitBillboard();
		UninitShadow();
		UninitWall();
		break;
	}

	switch (mode)
	{
	case MODE_TEST:
		InitMeshfield();
		SetField(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1000.0f, 0.0f, 1000.0f, 0, FORM_FLOO);
		SetField(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2000.0f, 0.0f, 0.0f), 1000.0f, 0.0f, 1000.0f, 1, FORM_FLOO);
		SetField(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -2000.0f), 1000.0f, 0.0f, 1000.0f, 2, FORM_FLOO);
		SetField(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2000.0f, 0.0f, -2000.0f), 1000.0f, 0.0f, 1000.0f, 3, FORM_FLOO);

		SetField(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f), 2000.0f, 1000.0f, 0.0f, 3, FORM_WALL);
		SetField(D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(3000.0f, 1000.0f, -1000.0f), 2000.0f, 1000.0f, 0.0f, 1, FORM_WALL);

		SetField(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, 50.0f, 1, FORM_SEMICIRCLE);

		SetField(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-1500.0f, 0.0f, 0.0f), 500.0f, 0.0f, 500.0f, 1, FORM_FLOO);

		InitShadow();
		InitModel();
		InitFixedModel();
		SetFixedModel(D3DXVECTOR3(-500.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODEL_HERTS);
		SetFixedModel(D3DXVECTOR3(500.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODEL_HERTS);
		SetFixedModel(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODEL_CAT);

		InitBullet();

		InitBillboard();
		SetBillboard(D3DXVECTOR3(-200.0f, 200.0f, 0.0f), 100.0f, 100.0f);
		SetBillboard(D3DXVECTOR3(0.0f, 200.0f, 0.0f), 200.0f, 200.0f);
		SetBillboard(D3DXVECTOR3(300.0f, 200.0f, 0.0f), 300.0f, 300.0f);

		InitWall();
		SetWall(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), D3DXVECTOR3(0.0f, 1000.0f, -1000.0f), 2000.0f, 2000.0f);
		SetWall(D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f), D3DXVECTOR3(-1000.0f, 1000.0f, 0.0f), 2000.0f, 2000.0f);
		break;
	}

	g_mode = mode;

}

//=============================================================================
// モード情報の取得
//=============================================================================
MODE GetMode(void)
{
	return g_mode;
}

//=============================================================================
// 前回のモード情報の取得
//=============================================================================
MODE GetModeold(void)
{
	return g_modeold;
}

#ifdef _DEBUG
//=============================================================================
// カメラの情報
//=============================================================================
void DrawCmInfo(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	Camera *pCamera;
	char aStr[256];

	pCamera = GetCamera();

	for (int nCntCamera = 0; nCntCamera < MAX_CAMERA; nCntCamera++, pCamera++)
	{
		if (pCamera->bUse == true)
		{
			int nNum = sprintf(&aStr[0], "----カメラ[%d]-----\n視点X:%.2f\n視点Y:%.2f\n視点Z:%.2f\n", nCntCamera, pCamera->PosV.x, pCamera->PosV.y, pCamera->PosV.z);
			nNum += sprintf(&aStr[nNum], "注視点X:%.2f\n注視点Y:%.2f\n注視点Z:%.2f\n------------------", pCamera->PosR.x, pCamera->PosR.y, pCamera->PosR.z);
		}
	}
	pCamera -= MAX_CAMERA;

	// テキスト描画
	g_pFont->DrawText(NULL, aStr, -1, &rect, DT_RIGHT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}

//=============================================================================
// ライトの情報
//=============================================================================
void LightInfo(void)
{
	RECT rect = { 0, 350, SCREEN_WIDTH, SCREEN_HEIGHT };
	D3DLIGHT9		*pLight;
	LightSelect		*pbLight;
	char aStrL[256];

	pLight = GetLight();
	pbLight = GetLightSelect();

	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++, pLight++, pbLight++)
	{
		if (pbLight->bUse == true)
		{
			if (pbLight->bSelect == true)
			{
				int nNum = sprintf(&aStrL[0], "----ライト[%d]-----\n向きX:%.2f\n向きY:%.2f\n向きZ:%.2f\nライトの情報:ON\n------------------", nCntLight, pLight->Direction.x, pLight->Direction.y, pLight->Direction.z);
			}
			else if (pbLight->bSelect == false)
			{
				int nNum = sprintf(&aStrL[0], "----ライト[%d]-----\n向きX:%.2f\n向きY:%.2f\n向きZ:%.2f\nライトの情報:OFF\n------------------", nCntLight, pLight->Direction.x, pLight->Direction.y, pLight->Direction.z);
			}
		}
	}
	pLight -= MAX_LIGHT;
	pbLight -= MAX_LIGHT;

	// テキスト描画
	g_pFont->DrawText(NULL, aStrL, -1, &rect, DT_RIGHT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}

//=============================================================================
// カメラの操作方法
//=============================================================================
void DrawCmTxt(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char aStr[256];

	int nNum = sprintf(&aStr[0], "-----------カメラ操作方法-----------\nWASD (四方向移動)\n");
	nNum += sprintf(&aStr[nNum], "視点縦:右クリック + マウス移動\n");
	nNum += sprintf(&aStr[nNum], "視点横:ホイールクリック + マウス移動\n");
	nNum += sprintf(&aStr[nNum], "注視点:左クリック + マウス移動\n");
	nNum += sprintf(&aStr[nNum], "カメラ選択:1[前のカメラ]2[次のカメラ]\n-------------------------------------");

	// テキスト描画
	g_pFont->DrawText(NULL, aStr, -1, &rect, DT_BOTTOM, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}

//=============================================================================
// カメラの操作方法
//=============================================================================
void LightTxt(void)
{
	RECT rect = { 750, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char aStrLI[256];

	int nNum = sprintf(&aStrLI[0], "---ライト操作方法---\n↑↓→← (向き移動)\n");
	nNum += sprintf(&aStrLI[nNum], "ライトの選択:3[前のライト]4[次のライト]\n");
	nNum += sprintf(&aStrLI[nNum], "ライトのON : OFF:F\n--------------------");

	// テキスト描画
	g_pFont->DrawText(NULL, aStrLI, -1, &rect, DT_BOTTOM, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}

//=============================================================================
// カメラの情報
//=============================================================================
void PlayerInfo(void)
{
	RECT rect = { 0, 600, SCREEN_WIDTH, SCREEN_HEIGHT };
	Player *pPlayer;
	char aStrM[256];

	pPlayer = GetPlayer();

	int nNum = sprintf(&aStrM[0], "-------モデル-------\n位置X:%.2f\n位置Y:%.2f\n位置Z:%.2f\n--------------------", pPlayer->PosModel.x, pPlayer->PosModel.y, pPlayer->PosModel.z);

	// テキスト描画
	g_pFont->DrawText(NULL, aStrM, -1, &rect, DT_RIGHT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}

//=============================================================================
// FPS表示処理
//=============================================================================
void DrawFPS(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char str[256];

	wsprintf(str, "FPS:%d\n", g_nCountFPS);

	// テキスト描画
	g_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}
#endif