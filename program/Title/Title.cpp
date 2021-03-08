//=============================================================================
//タイトルの処理
//=============================================================================
#include "Main.h"
#include "Title.h"
#include "Input.h"
#include "Fade.h"
#include "Sound.h"

//-----------------------------------------------------------------------------
//グローバル変数
//-----------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 g_pTextureTitle = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;		//テクスチャへのポインタ

//-----------------------------------------------------------------------------
//図形の初期化処理
//-----------------------------------------------------------------------------
void InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;     //デバイスへのポインタ
	pDevice = GetDevice();        //デバイスの取得

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/bg0001.png", &g_pTextureTitle);		//背景
	

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffTitle, NULL);

	//頂点情報へのポインタ
	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0, 0.0, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0, SCREEN_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラー:0～255
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロック
	g_pVtxBuffTitle->Unlock();
}

//-----------------------------------------------------------------------------
//終了処理
//-----------------------------------------------------------------------------
void UninitTitle(void)
{
	
		//テクスチャの破棄
		if (g_pTextureTitle != NULL)
		{
			g_pTextureTitle->Release();
			g_pTextureTitle = NULL;
		}

		if (g_pVtxBuffTitle != NULL)
		{
			g_pVtxBuffTitle->Release();
			g_pVtxBuffTitle = NULL;
		}
	
}


//-----------------------------------------------------------------------------
//更新処理
//-----------------------------------------------------------------------------
void UpdateTitle(void)
{
	XINPUT_STATE state;
	ZeroMemory(&state, sizeof(XINPUT_STATE));
	DWORD dwResult = XInputGetState(0, &state);

	//次の画面に変わる
	if (GetKeyboardTrigger(DIK_RETURN) == true && *GetFade() != FADE_OUT)
	{
		SetFade(MODE_TITLE);
		PlaySound(SOUND_LABEL_Enter000);
	}
}

//-----------------------------------------------------------------------------
//描画処理
//-----------------------------------------------------------------------------
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;  //デバイスのポインタ
	pDevice = GetDevice();     //デバイスを取得する
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));  //頂点バッファをデバイスのデータストリームに設定
	pDevice->SetFVF(FVF_VERTEX_2D);  //頂点フォーマットの設定
	pDevice->SetTexture(0, g_pTextureTitle);  //テクスチャの設定
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);    //ポリゴンの描画

}