//ーーーーーーーーーーーーーーーーーーーーーーーーー
//ビルボードの処理(Billboard.cpp)
//Author：佐藤秀亮
//ーーーーーーーーーーーーーーーーーーーーーーーーー

#include "main.h"
#include "input.h"
#include "Billboard.h"
#include "Model.h"

#define MOVE_Y (3.0f)

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureBillboard[TYPE_BILLBOARMAX] = {};//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillboard = NULL;//頂点バッファへのポインタ

Billboard g_Billboard[MAX_BILLBOARD];



//初期化処理
HRESULT InitBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスのポインタ
	int nCntBillboard;
	pDevice = GetDevice();//デバイスの取得

	//初期化
	for (nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		g_Billboard[nCntBillboard].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Billboard[nCntBillboard].fHight = 30;
		g_Billboard[nCntBillboard].fWhidth = 30;

		g_Billboard[nCntBillboard].bUse = false;
		g_Billboard[nCntBillboard].nlife = 0;
		g_Billboard[nCntBillboard].ntype = NULL;
	}

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "date/TEXTURE/はね.png", &g_pTextureBillboard[TYPE_BILLBOARDPLAYER]);
	D3DXCreateTextureFromFile(pDevice, "date/TEXTURE/wall000.jpg", &g_pTextureBillboard[TYPE_BILLBOARDFIRE]);


	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BILLBOARD, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffBillboard, NULL);

	return S_OK;
}

//終了処理
void UninitBillboard(void)//追加の可能性があるため項目は作っとく
{
	for (int nCntBillboard = 0; nCntBillboard < TYPE_BILLBOARMAX; nCntBillboard++)
	{
		//テクスチャの破棄
		if (g_pTextureBillboard != NULL)
		{
			g_pTextureBillboard[nCntBillboard]->Release();
			g_pTextureBillboard[nCntBillboard] = NULL;
		}

		//頂点バッファも破棄
		if (g_pVtxBuffBillboard != NULL)
		{
			g_pVtxBuffBillboard->Release();
			g_pVtxBuffBillboard = NULL;
		}
	}
}

//更新処理
void UpdateBillboard(void)//追加の可能性があるため項目は作っとく
{
	
}

//描画処理
void DrawBillboard(void)
{
	int nCntBillboard;
	LPDIRECT3DDEVICE9 pDevice;//デバイスのポインタ
	D3DXMATRIX mtxView;
	D3DXMATRIX mtxTrans;
	pDevice = GetDevice();//デバイスを取得する

	for (nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		if (g_Billboard[nCntBillboard].bUse == true)
		{
			//アルファテスト関係
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0);		

			//マトリックス初期化
			D3DXMatrixIdentity(&g_Billboard[nCntBillboard].mtxWorld);
			//ビューマトリックスの取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//ポリゴンをカメラに対して正面に
			D3DXMatrixInverse(&g_Billboard[nCntBillboard].mtxWorld, NULL, &mtxView);

			g_Billboard[nCntBillboard].mtxWorld._41 = 0.0f;
			g_Billboard[nCntBillboard].mtxWorld._42 = 0.0f;
			g_Billboard[nCntBillboard].mtxWorld._43 = 0.0f;

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Billboard[nCntBillboard].pos.x, g_Billboard[nCntBillboard].pos.y, g_Billboard[nCntBillboard].pos.z);
			D3DXMatrixMultiply(&g_Billboard[nCntBillboard].mtxWorld, &g_Billboard[nCntBillboard].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Billboard[nCntBillboard].mtxWorld);

			//頂点バッファをデバイスのデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffBillboard, 0, sizeof(VERTEX_3D));

			pDevice->SetFVF(FVF_VERTEX_3D);//頂点フォーマットの設定

			pDevice->SetTexture(0, g_pTextureBillboard[g_Billboard[nCntBillboard].ntype]);//テクスチャの設定

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBillboard * 4, 2);

			//アルファテスト関係
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);
		}

	}

}

void SetBillboard(D3DXVECTOR3 pos, float fWhidth, float fHight, int ntype)
{
	VERTEX_3D*pVtx;//頂点情報へのポインタ

	int nCntBillboard;
	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		if (g_Billboard[nCntBillboard].bUse == false)
		{
			g_Billboard[nCntBillboard].pos = pos;

			g_Billboard[nCntBillboard].fWhidth = fWhidth;
			g_Billboard[nCntBillboard].fHight = fHight;

			//頂点の座標
			pVtx[0].pos = D3DXVECTOR3(-g_Billboard[nCntBillboard].fWhidth / 2, +g_Billboard[nCntBillboard].fHight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(+g_Billboard[nCntBillboard].fWhidth / 2, +g_Billboard[nCntBillboard].fHight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-g_Billboard[nCntBillboard].fWhidth / 2,0.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(+g_Billboard[nCntBillboard].fWhidth / 2,0.0f, 0.0f);

			//ベクトルの設定
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//頂点の色
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			//テクスチャのUV座標
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			g_Billboard[nCntBillboard].ntype = ntype;

			g_Billboard[nCntBillboard].bUse = true;

			break;
		}
		pVtx += 4;
	}
	//頂点バッファをアンロック
	g_pVtxBuffBillboard->Unlock();
}

Billboard *GetBillboard(void)
{
	return &g_Billboard[0];
}