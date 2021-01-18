//=========================================================================================================================
// DirectX_Sample [main.cpp]
// Author:satou syusuke
//=========================================================================================================================
#include "main.h"
#include "input.h"
#include "Polygon.h"
#include "camera.h"
#include "ligth.h"
#include "Model.h"
#include "Shadow.h"
#include "wall.h"
#include "Billboard.h"
#include "Bullet.h"
#include "Object.h"
#include "Effect.h"
#include "Enemy.h"

//=========================================================================================================================
// マクロ定義
//=========================================================================================================================
#define CLASS_NAME "WindowClass"	// ウィンドウクラスの名前
#define WINDOW_NAME "3D雛形"		// ウィンドウの名前
#define WINDOW_COLOR_R	(255)		// ウィンドウの色(赤)
#define WINDOW_COLOR_G	(0)			// ウィンドウの色(緑)
#define WINDOW_COLOR_B	(0)			// ウィンドウの色(青)
#define WINDOW_COLOR_A	(0)			// ウィンドウの色(透明度)

//=========================================================================================================================
// プロトタイプ宣言
//=========================================================================================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);	// ウィンドウプロシージャ
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);							// 初期化処理
void Uninit(void);																	// 終了処理
void Update(void);																	// 更新処理
void Draw(void);																	// 描画処理
void DrawFPS(void);																	// 
void DrawTxT(void);

//=========================================================================================================================
// グローバル変数
//=========================================================================================================================
LPDIRECT3D9 g_pD3D = NULL;													// Direct3Dオブジェクトへのポインタ
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;										// Direct3Dデバイスへのポインタ(描画処理に必要)
LPD3DXFONT g_pFont = NULL;													// フォントへのポインタ
int g_nCountFPS;															// FPSカウンタ
//=========================================================================================================================
// メイン関数
//=========================================================================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstace, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WindowProc,
		0,
		0,
		hInstance,
		LoadIcon(NULL, IDI_APPLICATION),
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		LoadIcon(NULL, IDI_APPLICATION)
	};
	HWND hWnd;		// ウィンドウハンドル(識別子)
	MSG  msg;		// メッセージを格納する
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGTH };


	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);
	
	
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	

	// ウィンドウの生成
	hWnd = CreateWindowEx(
		0,
		CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		rect.right,
		rect.bottom,
		NULL,
		NULL,
		hInstance,
		NULL);

	// 初期化処理
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}

	// ウィンドウの表示
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	DWORD dwExecLastTime;	// 処理実行最終時刻
	DWORD dwFPSLastTime;	// FPS計測最終時刻
	DWORD dwCurrentTime;	// 現在時刻
	DWORD dwFrameCount;		// フレームカウント

	dwExecLastTime = timeGetTime();
	dwFPSLastTime = timeGetTime();
	dwCurrentTime = timeGetTime();
	dwFrameCount = 0;

	//メッセージループ
	while (1)
	{	// Windowsの処理
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{// メッセージを取得しなかった場合 "0" を返す
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				// メッセージの翻訳と送出
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{// DirectXの処理
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{// 0.5秒経過
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}

			if ((dwCurrentTime - dwExecLastTime) > (1000 / 60))
			{
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

	// ウィンドウクラスの登録解除
	UnregisterClass(
		CLASS_NAME,
		wcex.hInstance);

	return (int)msg.wParam;
	return 0;
}

//=========================================================================================================================
// ウィンドウプロシージャ
//=========================================================================================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	const RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGTH };

	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);	// WM_QUITメッセージを返す
		break;
	case WM_CLOSE:
		
			DestroyWindow(hWnd);	// WM_DESTROYメッセージを返すl
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			
			DestroyWindow(hWnd);	// WM_DESTROYメッセージを返す

			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//=========================================================================================================================
// 初期化処理
//=========================================================================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;

	// DIrect3Dオブジェクトの生成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	// ディスプレイモードの取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = SCREEN_WIDTH;		// スクリーンの幅
	d3dpp.BackBufferHeight = SCREEN_HEIGTH;		// スクリーンの高さ
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.Windowed = bWindow;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	// Direct3Dデバイスの生成
	if (FAILED(g_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		if (FAILED(g_pD3D->CreateDevice(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			if (FAILED(g_pD3D->CreateDevice(
				D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	// レンダーステートの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// カリングの設定
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// αブレンド(α値の合成)の設定
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);			// ソース(描画元)の合成方法の設定
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// デスティネーション(描画先)の合成方法の設定

	// サンプラーステートの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// 縮小時 補間
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// 拡大時 補間
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// U値 繰り返し
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// V値 繰り返し

	// テクスチャステージステートの設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// α値の合成
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// α値の合成
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// α値の合成

	//テキスト処理
	D3DXCreateFont(g_pD3DDevice, 20, 0, 0, 0,//大きさ
		FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH, "Terminal", &g_pFont);


	// 入力の初期化
	InitKeyboard(hInstance, hWnd);


	InitCamera();
	InitLigth();

	InitPolygon();
	InitModel();
	InitWall();

	InitBillboard();
	InitEffect();

	InitBullet();
	InitObject();

	InitEnemy();
	Player * pPlayer = GetModel();


	SetWall(D3DXVECTOR3(0.0f, -10.0f, 240.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1000.0f, 300.0f, 0);
	SetWall(D3DXVECTOR3(240.0f, -10.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5, 0.0f), 1000.0f, 300.0f, 0);
	SetWall(D3DXVECTOR3(-240.0f, -10.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * -0.5, 0.0f), 1000.0f, 300.0f, 0);
	SetWall(D3DXVECTOR3(0.0f, -10.0f, -240.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), 1000.0f, 300.0f, 0);

	SetObject(D3DXVECTOR3(-240.0f, -5.0f, -240.0f), D3DXVECTOR3(0.0f, 0.0, 0.0f), OBJECTTYPE_TANK);
	SetObject(D3DXVECTOR3(240.0f, -5.0f, -240.0f), D3DXVECTOR3(0.0f, 0.0, 0.0f), OBJECTTYPE_SANDBAG);

	SetObject(D3DXVECTOR3(100.0f, 25.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0, 0.0f), OBJECTTYPE_BLOCK00);
	SetObject(D3DXVECTOR3(-100.0f, 50.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0, 0.0f), OBJECTTYPE_BLOCK01);

	SetBillboard(D3DXVECTOR3(0.0f, 0.0f, -120.0f), 50.0f, 100.0f, TYPE_BILLBOARDPLAYER);
	SetBillboard(D3DXVECTOR3(200.0f, 0.0f, -120.0f), 100.0f, 10.0f, TYPE_BILLBOARDFIRE);



	return S_OK;

}

//=========================================================================================================================
// 終了処理
//=========================================================================================================================
void Uninit(void)
{
	UninitLigth();

	UninitKeyboard();
	UninitPolygon();
	UninitModel();
	UninitCamera();
	UninitWall();
	UninitBillboard();
	UninitBullet();
	UninitObject();
	UninitEffect();
	UninitEnemy();


	// Direct3Dデバイスの開放
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	// Direct3Dオブジェクトの開放
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}

	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}
}

//=========================================================================================================================
// 更新処理
//=========================================================================================================================
void Update(void)
{
	UpdateCamera();
	UpdateEffect();

	UpdateLigth();
	UpdateKeyboard();
	UpdateModel();
	UpdatePolygon();
	UpdateWall();
	UpdateBullet();
	UpdateObject();
	UpdateEnemy();
	Player * pPlayer = GetModel();
	//SetEffect(pPlayer->pos, D3DXCOLOR(255, 0, 0, 255), 20, 20, EFFECTTYTPE_FOLL, 30);

}

//=========================================================================================================================
// 描画処理
//=========================================================================================================================
void Draw(void)
{

	// バックバッファ&Zバッファのクリア(画面クリア)
	g_pD3DDevice->Clear(
		0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(WINDOW_COLOR_R, WINDOW_COLOR_G, WINDOW_COLOR_B, WINDOW_COLOR_A),
		1.0f,
		0);

	// 描画の開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		SetCamera();

		DrawModel();
		DrawPolygon();
		DrawShadow();

		DrawBullet();
		DrawWall();

		DrawEffect();

		DrawObject();
		DrawBillboard();


		DrawEnemy();

		DrawFPS();
		DrawTxT();

		// 描画の終了
		g_pD3DDevice->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);

	
}

//=========================================================================================================================
// デバイスの取得
//=========================================================================================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//=========================================================================================================================
// FPSの描画
//=========================================================================================================================
void DrawFPS(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGTH };
	char aStr[256];

	wsprintf(&aStr[0], "FPS:%d\n", g_nCountFPS);

	// テキストの描画
	g_pFont->DrawText(
		NULL,
		&aStr[0],
		-1,
		&rect,
		DT_LEFT,
		D3DCOLOR_RGBA(255, 255, 255, 255));
}

void DrawTxT(void)
{
	

	RECT rect = { 0, 20, SCREEN_WIDTH, SCREEN_HEIGTH };
	char aStr[256];

	Camera * pCamera;
	pCamera = GetCamera();

	Player * pPlayer;
	pPlayer = GetModel();

	int nNum = sprintf(&aStr[0], "カメラ視点:(%.1f : %.1f : %.1f)\n", pCamera->posV.x, pCamera->posV.y, pCamera->posV.z);
	nNum += sprintf(&aStr[nNum], "カメラ注視点:(%.1f : %.1f : %.1f)\n", pCamera->posR.x, pCamera->posR.y, pCamera->posR.z);
	nNum += sprintf(&aStr[nNum], "モデル座標:(%.1f : %.1f : %.1f)\n", pPlayer->pos.x, pPlayer->pos.y, pPlayer->pos.z);
	nNum += sprintf(&aStr[nNum], "モデル回転:(%.1f : %.1f : %.1f)\n", pPlayer->rot.x,pPlayer->rot.y, pPlayer->rot.z);
	nNum += sprintf(&aStr[nNum], "カメラ回転:(%.1f)\n\n", pCamera->rot.y);

	nNum += sprintf(&aStr[nNum], "残弾数:(%d)\n", pPlayer->MugzineBullet);
	nNum += sprintf(&aStr[nNum], "状態:(%d)\n", pPlayer->state);
	if (pPlayer->state == PLAYERSTATE_RELOAD)
	{
		nNum += sprintf(&aStr[nNum], "リロード終了まで：%d\n", pPlayer->ReloadTime);
	}
	nNum += sprintf(&aStr[nNum], "状態１でリロード中\n");
	nNum += sprintf(&aStr[nNum], "\n\n");
	nNum += sprintf(&aStr[nNum], "スペース:弾発射 L:リロード\n");


	// テキストの描画
	g_pFont->DrawText(
		NULL,
		&aStr[0],
		-1,
		&rect,
		DT_LEFT,
		D3DCOLOR_RGBA(255, 255, 255, 255));
}
