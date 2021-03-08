//=============================================================================
//メインの処理
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS

#include "main.h"
#include <stdio.h>
#include "Picture.h"
#include "Sound.h"
#include"Title.h"
#include "Fade.h"

//-----------------------------------------------------------------------------
//マクロ定義
//-----------------------------------------------------------------------------
#define CLASS_NAME "WindowClass"
#define WINDOW_NAME "～迷い森～"

//-----------------------------------------------------------------------------
//プロトタイプ宣言
//-----------------------------------------------------------------------------
LRESULT CALLBACK WindowProc(HWND hwnd, UINT  uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
void DrawTxT(void);
//-----------------------------------------------------------------------------
//グローバル変数
//-----------------------------------------------------------------------------
LPDIRECT3D9 g_pD3D = NULL;
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;
MODE g_mode = MODE_TITLE;                //現在のモード
int g_nCountFPS;
LPD3DXFONT g_pFont = NULL;
//-----------------------------------------------------------------------------
//メイン関数
//-----------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lPCmdLine, int nCmdShow)
{
	//構造体
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),					//WNDCLASSENのメモリサイズの指示
		CS_CLASSDC,							//表示するウィンドウのスタイルを設定
		WindowProc,							//ウィンドウプロシージャのアドレス(関数名)を指定
		0,									//0を指定
		0,									//0を指定
		hInstance,							//Windowsの引数のインスタンスハンドルを指定
		LoadIcon(NULL,IDI_APPLICATION),		//タスクバーに使うアイコンを指定
		LoadCursor(NULL,IDC_ARROW),			//使うマウスカーソルを指定
		(HBRUSH)(COLOR_WINDOW + 1),			//ウィンドウのクライアント領域の背景色を指定
		NULL,								//Windowにつけるメニューを設定
		CLASS_NAME,							//ウィンドウクラスの名前
		LoadIcon(NULL,IDI_APPLICATION)		//ファイルアイコンに使うアイコンを設定
	};

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	HWND hWnd;	//ウィンドウハンドル
	MSG msg;	//メッセージを格納する変数

				//ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	//ウィンドウを生成(作ったウィンドウハンドルに納めて管理する)
	hWnd = CreateWindowEx(0,				//拡張ウィンドウスタイル
		CLASS_NAME,							//ウィンドウクラスの名前
		WINDOW_NAME,						//ウィンドウの名前
		WS_OVERLAPPEDWINDOW,				//ウィンドウスタイル
		CW_USEDEFAULT,						//ウィンドウの左上X座標
		CW_USEDEFAULT,						//ウィンドウの左上Y座標
		(rect.right - rect.left),			//ウィンドウの幅
		(rect.bottom - rect.top),			//ウィンドウの高さ
		NULL,								//親ウィンドウのハンドル
		NULL,								//メニューウィンドウまたは子ウィンドウ
		hInstance,							//インスタンスハンドル
		NULL								//ウィンドウ作成データ
	);



	//初期化処理(ウィンドウ生成してからやる(DirectXの生成)
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}

	//ウィンドウの表示(初期化処理の後に行う)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	DWORD dwExecLastTime;		//処理実行最終時刻
	DWORD dwFPSLastTime;		//FPS計測最終時刻
	DWORD dwCurrentTime;		//現在時刻
	DWORD dwFrameCount;			//フレームカウント

								// フレームカウント初期化
	dwExecLastTime =
		dwFPSLastTime =
		dwCurrentTime = timeGetTime();
	dwFrameCount = 0;

	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)		//メッセージを取得したなら進む
		{
			if (msg.message == WM_QUIT)		//"WM_QUIT"メッセージが送られたらループを抜ける
			{
				break;
			}
			else
			{
				//メッセージ翻訳と送出
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			//DirectXの処理
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{
				// 0.5秒ごとに実行
				g_nCountFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}

			if ((dwCurrentTime - dwExecLastTime) > (1000 / 60))
			{
				// 1/60秒経過
				dwExecLastTime = dwCurrentTime;

				// 更新処理
				Update();

				// 描画処理
				Draw();

				dwFrameCount++;
			}
		}
	}
	//終了処理
	Uninit();

	//ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return(int)msg.wParam;
}

//ウィンドウプロシージャ
LRESULT CALLBACK WindowProc(HWND hWnd, UINT  uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:					//ウィンドウ破棄のメッセージ
		PostQuitMessage(0);				//WM_QUITメッセージを返す
		break;

	case WM_KEYDOWN:					//何かキーが押下された
		switch (wParam)
		{
		case VK_ESCAPE:					//[ESC]キーが押下された
			DestroyWindow(hWnd);		//ウィンドウ破棄(WM_DESTROYメッセージを送る)
		}
		break;

	case WM_CLOSE:						//右上のバツ
		DestroyWindow(hWnd);			//ウィンドウ破棄(WM_DESTROYメッセージを送る)
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//-----------------------------------------------------------------------------
//初期化処理
//-----------------------------------------------------------------------------
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;


	//DirectXオブジェクトの生成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//現在のディスプレイモードを取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));								//ワークをゼロクリア
	d3dpp.BackBufferCount = 1;										//バックバッファの数
	d3dpp.BackBufferWidth = SCREEN_WIDTH;							//ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;							//ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat = d3ddm.Format;							//カラーモードの指定
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;						//映像信号に同期してフリップする
	d3dpp.Windowed = bWindow;											//ウィンドウモード	false	bWindow
	d3dpp.EnableAutoDepthStencil = TRUE;							//デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;						//デプスバッファとして16bitを使う
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		//リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		//インターバル

																	//デバイスの生成
																	//ディスプレイアダプタを表すためのデバイスを作成
																	//描画と頂点処理をハードウェアで行なう
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &g_pD3DDevice)))
	{
		//上記の設定が失敗したら
		//描画をハードウェアで行い、頂点処理はCPUで行なう
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &g_pD3DDevice)))
		{
			//上記の設定が失敗したら
			//描画と頂点処理をCPUで行なう
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp, &g_pD3DDevice)))
			{
				//初期化失敗
				return E_FAIL;
			}
		}
	}

	//レンダーステートの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				//カリングを行わない
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						//Zバッファを使用
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				//αブレンドを行う
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		//αソースカラーの指定
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	//αデスティネーションカラーの指定

																			//サンプラーステートの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	//テクスチャアドレッシング方法(U値)を設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	//テクスチャアドレッシング方法(V値)を設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	//テクスチャ縮小フィルタモードを設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	//テクスチャ拡大フィルタモードを設定

																			//テクスチャステージステートの設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	D3DXCreateFont(g_pD3DDevice, 30, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Teminal", &g_pFont);

	SetMode(g_mode);
	InitFade(g_mode);
	InitSound(hWnd);
	return S_OK;
}

//-----------------------------------------------------------------------------
//終了処理
//-----------------------------------------------------------------------------
void Uninit(void)
{
	UninitTitle();
	UninitFade();
	UninitSound();

	//Direct3Dデバイスの開放
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	//Direct3Dオブジェクトの開放
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//-----------------------------------------------------------------------------
//更新処理
//-----------------------------------------------------------------------------
void Update(void)
{
#if(1)
	//各種オブジェクト更新処理
	switch (g_mode)
	{
	case MODE_TITLE:
		UpdateTitle();
		break;
	}
	UpdateFade();

#endif
}

//-----------------------------------------------------------------------------
//描画処理
//-----------------------------------------------------------------------------
void Draw(void)
{

	//backバッファ、Zバッファのクリア
	g_pD3DDevice->Clear(0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);


#if(1)//カメラの数分、繰り返す
	//描画開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		DrawTxT();
		switch (g_mode)
		{
		case MODE_TITLE:
			DrawTitle();
			break;
		}

		D3DVIEWPORT9 viewportDef;
		//現在のビューポートを取得
		g_pD3DDevice->GetViewport(&viewportDef);
		DrawFade();
		//カメラの設定
		//SetCamera();


		//ビューポートを元に戻す
		g_pD3DDevice->SetViewport(&viewportDef);


		//描画終了
		g_pD3DDevice->EndScene();
	}
#endif
	//バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//-----------------------------------------------------------------------------
//モードの設定
//-----------------------------------------------------------------------------
void SetMode(MODE mode)
{
#if(1)
	switch (g_mode)
	{
	case MODE_TITLE:
		UninitTitle();
		break;
	}

	switch (mode)
	{
	case MODE_TITLE:
		InitTitle();
		break;
	}
	g_mode = mode;
#endif
}

//-----------------------------------------------------------------------------
//描写処理
//-----------------------------------------------------------------------------
MODE *GetMode(void)
{
	return &g_mode;
}

//-----------------------------------------------------------------------------
//座標設定
//-----------------------------------------------------------------------------
void DrawTxT(void)
{
#if(0)
	Camera *pcamera;
	pcamera = GetCamera();

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

	char aStr[512];
	int nNUm = sprintf(&aStr[0], "FPS:%d\n", g_nCountFPS);
	nNUm += sprintf(&aStr[nNUm], "カメラの位置:  %0.1f,  %0.1f,  %0.1f\n", pcamera->posV.x, pcamera->posV.y, pcamera->posV.z);
	nNUm += sprintf(&aStr[nNUm], "注視点の位置:  %0.1f,  %0.1f,  %0.1f", pcamera->posR.x, pcamera->posR.y, pcamera->posR.z);

	//テキスト
	g_pFont->DrawTextA(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
#endif
}

//-----------------------------------------------------------------------------
//描写処理
//-----------------------------------------------------------------------------
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}