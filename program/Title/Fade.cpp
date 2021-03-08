//=============================================================================
//フェードの処理
//=============================================================================

#include "Main.h"
#include "Fade.h"

//-----------------------------------------------------------------------------
//グローバル変数
//-----------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 g_pTexturefade = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufffade = NULL;		//テクスチャへのポインタ
FADE g_fade;										//フェードの状態
MODE g_modeNext;									//次の画面(モード)
D3DXCOLOR g_colorFade;								//フェードの色

//-----------------------------------------------------------------------------
//フェードの初期化処理
//-----------------------------------------------------------------------------
void InitFade(MODE modeNext)
{
	LPDIRECT3DDEVICE9 pDevice;     //デバイスへのポインタ
	pDevice = GetDevice();        //デバイスの取得

	g_fade = FADE_IN;
	g_modeNext = modeNext;
	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);    //3目が黒い画面(不透明)


	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBufffade, NULL);

	//頂点情報へのポインタ
	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBufffade->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBufffade->Unlock();
}

//-----------------------------------------------------------------------------
//フェードの終了処理
//-----------------------------------------------------------------------------
void UninitFade(void)
{
	//テクスチャの破棄
	if (g_pTexturefade != NULL)
	{
		g_pTexturefade->Release();
		g_pTexturefade = NULL;
	}

	if (g_pVtxBufffade != NULL)
	{
		g_pVtxBufffade->Release();
		g_pVtxBufffade = NULL;
	}
}

//-----------------------------------------------------------------------------
//フェードの更新処理
//-----------------------------------------------------------------------------
void UpdateFade(void)
{
	if (g_fade != FADE_NONE)
	{
		if (g_fade == FADE_IN)
		{
			g_colorFade.a -= 0.01f;       //フェードのスピードを変える

			if (g_colorFade.a <= 0.0f)
			{
				g_colorFade.a = 0.01f;
				g_fade = FADE_NONE;
			}
		}

		else if (g_fade == FADE_OUT)
		{
			g_colorFade.a += 0.01f;
			if (g_colorFade.a >= 1.0f)
			{
				g_colorFade.a = 1.0f;
				g_fade = FADE_IN;

				//モードの設定
				SetMode(g_modeNext);
			}
		}

		LPDIRECT3DDEVICE9 pDevice;     //デバイスへのポインタ
		pDevice = GetDevice();        //デバイスの取得
									  //頂点バッファの生成
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBufffade, NULL);

		//頂点情報へのポインタ
		VERTEX_2D*pVtx;
		//頂点バッファをロックし、頂点データへのポインタを取得
		g_pVtxBufffade->Lock(0, 0, (void**)&pVtx, 0);

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
		pVtx[0].col = g_colorFade;
		pVtx[1].col = g_colorFade;
		pVtx[2].col = g_colorFade;
		pVtx[3].col = g_colorFade;

		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//頂点バッファをアンロック
		g_pVtxBufffade->Unlock();
	}
}

//-----------------------------------------------------------------------------
//フェードの描画処理
//-----------------------------------------------------------------------------
void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDevice;  //デバイスのポインタ
	pDevice = GetDevice();     //デバイスを取得する
	pDevice->SetStreamSource(0, g_pVtxBufffade, 0, sizeof(VERTEX_2D));  //頂点バッファをデバイスのデータストリームに設定
	pDevice->SetFVF(FVF_VERTEX_2D);  //頂点フォーマットの設定
	pDevice->SetTexture(0, g_pTexturefade);  //テクスチャの設定
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);    //ポリゴンの描画
}

//-----------------------------------------------------------------------------
//フェードの設定処理
//-----------------------------------------------------------------------------
void SetFade(MODE modeNext)
{
	g_fade = FADE_OUT;
	g_modeNext = modeNext;
	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

//-----------------------------------------------------------------------------
//フェードの取得処理
//-----------------------------------------------------------------------------
FADE *GetFade(void)
{
	return &g_fade;
}