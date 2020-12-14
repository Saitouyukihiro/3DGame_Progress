//---------------------------
//インクルードファイル
//---------------------------
#include "billboard.h"
#include "shadow.h"

//---------------------------
//グローバル変数
//---------------------------
LPDIRECT3DTEXTURE9		g_pTextureBillboard = NULL;		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillboard = NULL;		//頂点バッファへのポインタ
Billboard				g_aBillboard[MAX_BILLBOARD];	//ビルボードのポインタ

//---------------------------
//グローバル変数
//---------------------------
HRESULT InitBillboard(void)
{
	LPDIRECT3DDEVICE9	pDevice;	//デバイスへのポインタ

	pDevice = GetDevice();			//デバイスの取得

	//値の初期化
	for (int nCntBill = 0; nCntBill < MAX_BILLBOARD; nCntBill++)
	{
		g_aBillboard[nCntBill].Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBillboard[nCntBill].Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBillboard[nCntBill].fWidth = BILLBOARD_X;
		g_aBillboard[nCntBill].fHeiht = BILLBOARD_Y;
		g_aBillboard[nCntBill].nIdex = 0;
		g_aBillboard[nCntBill].bUse = false;
	}

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/cat01.png",			//テクスチャ
								&g_pTextureBillboard);
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(	sizeof(VERTEX_3D) * 4 * MAX_BILLBOARD,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_3D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffBillboard,
									NULL);
	//---------------------------
	//頂点情報
	//---------------------------
	VERTEX_3D *pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBill = 0; nCntBill < MAX_BILLBOARD; nCntBill++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-g_aBillboard[nCntBill].fWidth / 2, - g_aBillboard[nCntBill].fHeiht / 2, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBillboard[nCntBill].fWidth / 2, - g_aBillboard[nCntBill].fHeiht / 2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-g_aBillboard[nCntBill].fWidth / 2, g_aBillboard[nCntBill].fHeiht / 2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBillboard[nCntBill].fWidth / 2, g_aBillboard[nCntBill].fHeiht / 2, 0.0f);

		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		pVtx[0].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[3].tex = D3DXVECTOR2(0.0f, 0.0f);

		pVtx += 4;	//頂点を進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffBillboard->Unlock();

	return S_OK;
}

//---------------------------
//終了処理
//---------------------------
void UninitBillboard(void)
{
	//---------------------------
	//テクスチャ破棄
	//---------------------------
	if (g_pTextureBillboard != NULL)
	{
		g_pTextureBillboard->Release();
		g_pTextureBillboard = NULL;
	}

	//---------------------------
	//バッファ破棄
	//---------------------------
	if (g_pVtxBuffBillboard != NULL)
	{
		g_pVtxBuffBillboard->Release();
		g_pVtxBuffBillboard = NULL;
	}
}

//---------------------------
//更新処理
//---------------------------
void UpdateBillboard(void)
{
	
}

//---------------------------
//描画処理
//---------------------------
void DrawBillboard(void)
{
	LPDIRECT3DDEVICE9	pDevice;			//デバイスのポインタ

	pDevice = GetDevice();					//デバイスを取得する

	//---------------------------
	//マトリックスの設定
	//---------------------------
	D3DXMATRIX			 mtxTrans;	//計算用マトリックス

	for (int nCntBill = 0; nCntBill < MAX_BILLBOARD; nCntBill++)
	{
		if (g_aBillboard[nCntBill].bUse == true)
		{
			//カリング有り
			pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

			//αテスト
			pDevice->SetRenderState(	D3DRS_ALPHATESTENABLE, TRUE);
			pDevice->SetRenderState(	D3DRS_ALPHAFUNC, D3DCMP_GREATER);
			pDevice->SetRenderState(	D3DRS_ALPHAREF, 0);

			//マトリックス初期化
			D3DXMatrixIdentity(&g_aBillboard[nCntBill].mtxWold);

			//カメラの向きを取得
			pDevice->GetTransform(	D3DTS_VIEW,
									&g_aBillboard[nCntBill].mtxView);
			//カメラの情報を入れて、スケールを反映
			g_aBillboard[nCntBill].mtxWold._11 = g_aBillboard[nCntBill].mtxView._11 * g_aBillboard[nCntBill].fWidth;
			g_aBillboard[nCntBill].mtxWold._12 = g_aBillboard[nCntBill].mtxView._21 * g_aBillboard[nCntBill].fWidth;
			g_aBillboard[nCntBill].mtxWold._13 = g_aBillboard[nCntBill].mtxView._31 * g_aBillboard[nCntBill].fWidth;
			g_aBillboard[nCntBill].mtxWold._21 = g_aBillboard[nCntBill].mtxView._12 * g_aBillboard[nCntBill].fHeiht;
			g_aBillboard[nCntBill].mtxWold._22 = g_aBillboard[nCntBill].mtxView._22 * g_aBillboard[nCntBill].fHeiht;
			g_aBillboard[nCntBill].mtxWold._23 = g_aBillboard[nCntBill].mtxView._32 * g_aBillboard[nCntBill].fHeiht;
			g_aBillboard[nCntBill].mtxWold._31 = g_aBillboard[nCntBill].mtxView._13;
			g_aBillboard[nCntBill].mtxWold._32 = g_aBillboard[nCntBill].mtxView._23;
			g_aBillboard[nCntBill].mtxWold._33 = g_aBillboard[nCntBill].mtxView._33;

			//位置
			D3DXMatrixTranslation(	&mtxTrans,
									g_aBillboard[nCntBill].Pos.x,
									g_aBillboard[nCntBill].Pos.y,
									g_aBillboard[nCntBill].Pos.z);

			D3DXMatrixMultiply(	&g_aBillboard[nCntBill].mtxWold,
								&g_aBillboard[nCntBill].mtxWold,
								&mtxTrans);
			//マトリックスの設定
			pDevice->SetTransform(	D3DTS_WORLD,
									&g_aBillboard[nCntBill].mtxWold);
			//---------------------------
			//描画処理
			//---------------------------
			//バッファの設定をデータストリームに設定
			pDevice->SetStreamSource(	0,
										g_pVtxBuffBillboard,
										0,
										sizeof(VERTEX_3D));
			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(	0,
									g_pTextureBillboard);
			//ポリゴンの描画
			pDevice->DrawPrimitive(	D3DPT_TRIANGLESTRIP,	//プリミティブの種類
									nCntBill * 4,			//何番目から描画するか
									2);						//△の数
			//αテスト
			pDevice->SetRenderState(	D3DRS_ALPHATESTENABLE, FALSE);
			pDevice->SetRenderState(	D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
			pDevice->SetRenderState(	D3DRS_ALPHAREF, 0x00);
		}
	}
}

//---------------------------
//ビルボード
//---------------------------
void SetBillboard(D3DXVECTOR3 Pos, float fWidth, float fHeight)
{
	for (int nCntBill = 0; nCntBill < MAX_BILLBOARD; nCntBill++)
	{
		if (g_aBillboard[nCntBill].bUse == false)
		{
			g_aBillboard[nCntBill].Pos = Pos;			//ビルボードの位置
			g_aBillboard[nCntBill].fWidth = fWidth;		//ビルボードの幅
			g_aBillboard[nCntBill].fHeiht = fHeight;	//ビルボードの高さ

			g_aBillboard[nCntBill].bUse = true;

			//影のセット
			g_aBillboard[nCntBill].nIdex = SetShadow(g_aBillboard[nCntBill].Pos, fWidth, fHeight);
			break;
		}
	}
}