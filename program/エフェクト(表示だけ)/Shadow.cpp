//ーーーーーーーーーーーーーーーーーーーーーーーーー
//ステージの処理(Shadow.cpp)
//Author：佐藤秀亮
//ーーーーーーーーーーーーーーーーーーーーーーーーー

#include "main.h"
#include "input.h"
#include "Shadow.h"
#include "Model.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureShadow[TYPE_MAX] = {};//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;//頂点バッファへのポインタ

Shadow g_shadow[MAX_SHADOW];

//初期化処理
HRESULT InitShadow(void)
{
	int nCntShadow;
	LPDIRECT3DDEVICE9 pDevice;//デバイスのポインタ
	pDevice = GetDevice();//デバイスの取得

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		g_shadow[nCntShadow].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_shadow[nCntShadow].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_shadow[nCntShadow].fWhidth = 0;
		g_shadow[nCntShadow].fDepth = 0;
		g_shadow[nCntShadow].ntype = 0;
		g_shadow[nCntShadow].bUse = false;
	}

	D3DXCreateTextureFromFile(pDevice, "date/TEXTURE/shadow000.jpg", &g_pTextureShadow[TYPE_PLAYER]);
	D3DXCreateTextureFromFile(pDevice, "date/TEXTURE/shadow000.jpg", &g_pTextureShadow[TYPE_ENEMY]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_SHADOW, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffShadow, NULL);

	VERTEX_3D * pVtx;//頂点情報へのポインタ
	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		//頂点の座標
		pVtx[0].pos = D3DXVECTOR3(g_shadow[nCntShadow].pos.x - (100 / 2), g_shadow[nCntShadow].pos.y, g_shadow[nCntShadow].pos.z + (100 / 2));
		pVtx[1].pos = D3DXVECTOR3(g_shadow[nCntShadow].pos.x + (100 / 2), g_shadow[nCntShadow].pos.y, g_shadow[nCntShadow].pos.z + (100 / 2));
		pVtx[2].pos = D3DXVECTOR3(g_shadow[nCntShadow].pos.x - (100 / 2), g_shadow[nCntShadow].pos.y, g_shadow[nCntShadow].pos.z - (100 / 2));
		pVtx[3].pos = D3DXVECTOR3(g_shadow[nCntShadow].pos.x + (100 / 2), g_shadow[nCntShadow].pos.y, g_shadow[nCntShadow].pos.z - (100 / 2));

		//ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//頂点の色
		pVtx[0].col = D3DCOLOR_RGBA(0, 0, 0, 0);
		pVtx[1].col = D3DCOLOR_RGBA(0, 0, 0, 0);
		pVtx[2].col = D3DCOLOR_RGBA(0, 0, 0, 0);
		pVtx[3].col = D3DCOLOR_RGBA(0, 0, 0, 0);

		//テクスチャのUV座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロック
	g_pVtxBuffShadow->Unlock();

	return S_OK;
}

//終了処理
void UninitShadow(void)//追加の可能性があるため項目は作っとく
{
	for (int nCntShadow = 0; nCntShadow < TYPE_MAX; nCntShadow++)
	{
		//テクスチャの破棄
		if (g_pTextureShadow != NULL)
		{
			g_pTextureShadow[nCntShadow]->Release();
			g_pTextureShadow[nCntShadow] = NULL;
		}

		//頂点バッファも破棄
		if (g_pVtxBuffShadow != NULL)
		{
			g_pVtxBuffShadow->Release();
			g_pVtxBuffShadow = NULL;
		}
	}
}

//更新処理
void UpdateShadow(void)//追加の可能性があるため項目は作っとく
{
	int nCntShadow;

	Player *pPlayer;
	pPlayer = GetModel();

	VERTEX_3D*pVtx;//頂点情報へのポインタ

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_shadow[nCntShadow].bUse == true)
		{
			g_shadow[nCntShadow].pos = pPlayer->pos / 2;

			//頂点バッファをロックし、頂点データへのポインタを取得
			g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += (nCntShadow * 4);

			//頂点の座標
			pVtx[0].pos = D3DXVECTOR3(g_shadow[nCntShadow].pos.x - (g_shadow[nCntShadow].fWhidth / 2), g_shadow[nCntShadow].pos.y, g_shadow[nCntShadow].pos.z + (g_shadow[nCntShadow].fDepth / 2));
			pVtx[1].pos = D3DXVECTOR3(g_shadow[nCntShadow].pos.x + (g_shadow[nCntShadow].fWhidth / 2), g_shadow[nCntShadow].pos.y, g_shadow[nCntShadow].pos.z + (g_shadow[nCntShadow].fDepth / 2));
			pVtx[2].pos = D3DXVECTOR3(g_shadow[nCntShadow].pos.x - (g_shadow[nCntShadow].fWhidth / 2), g_shadow[nCntShadow].pos.y, g_shadow[nCntShadow].pos.z - (g_shadow[nCntShadow].fDepth / 2));
			pVtx[3].pos = D3DXVECTOR3(g_shadow[nCntShadow].pos.x + (g_shadow[nCntShadow].fWhidth / 2), g_shadow[nCntShadow].pos.y, g_shadow[nCntShadow].pos.z - (g_shadow[nCntShadow].fDepth / 2));

			//ベクトルの設定
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//頂点の色
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 75);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 75);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 75);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 75);

			//テクスチャのUV座標
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			//頂点バッファをアンロック
			g_pVtxBuffShadow->Unlock();
		}
	}
}

void SetShadow(D3DXVECTOR3 pos, float fWhidth, float fDepth ,int ntype)
{
	VERTEX_3D*pVtx;//頂点情報へのポインタ
	int nCntShadow;

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW;nCntShadow++)
	{
		if (g_shadow[nCntShadow].bUse == false)
		{
			g_shadow[nCntShadow].pos = pos;
			g_shadow[nCntShadow].ntype = ntype;

			//頂点バッファをロックし、頂点データへのポインタを取得
			g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += (nCntShadow * 4);

			//頂点の座標
			pVtx[0].pos = D3DXVECTOR3(g_shadow[nCntShadow].pos.x - (fWhidth / 2), g_shadow[nCntShadow].pos.y, g_shadow[nCntShadow].pos.z + (fDepth / 2));
			pVtx[1].pos = D3DXVECTOR3(g_shadow[nCntShadow].pos.x + (fWhidth / 2), g_shadow[nCntShadow].pos.y, g_shadow[nCntShadow].pos.z + (fDepth / 2));
			pVtx[2].pos = D3DXVECTOR3(g_shadow[nCntShadow].pos.x - (fWhidth / 2), g_shadow[nCntShadow].pos.y, g_shadow[nCntShadow].pos.z - (fDepth / 2));
			pVtx[3].pos = D3DXVECTOR3(g_shadow[nCntShadow].pos.x + (fWhidth / 2), g_shadow[nCntShadow].pos.y, g_shadow[nCntShadow].pos.z - (fDepth / 2));

			//ベクトルの設定
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//頂点の色
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 75);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 75);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 75);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 75);

			//テクスチャのUV座標
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			
			//頂点バッファをアンロック
			g_pVtxBuffShadow->Unlock();

			g_shadow[nCntShadow].fWhidth = fWhidth;
			g_shadow[nCntShadow].fDepth = fDepth;

			g_shadow[nCntShadow].bUse = true;

			break;
		}
	}
}

//描画処理
void DrawShadow(void)
{
	int nCntShadow;
	LPDIRECT3DDEVICE9 pDevice;//デバイスのポインタ
	D3DXMATRIX mtxRot, mtxTrans;
	pDevice = GetDevice();//デバイスを取得する

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_shadow[nCntShadow].bUse == true)
		{
			//減算合成
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

			D3DXMatrixIdentity(&g_shadow[nCntShadow].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_shadow[nCntShadow].rot.y, g_shadow[nCntShadow].rot.x, g_shadow[nCntShadow].rot.z);
			D3DXMatrixMultiply(&g_shadow[nCntShadow].mtxWorld, &g_shadow[nCntShadow].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_shadow[nCntShadow].pos.x, g_shadow[nCntShadow].pos.y, g_shadow[nCntShadow].pos.z);
			D3DXMatrixMultiply(&g_shadow[nCntShadow].mtxWorld, &g_shadow[nCntShadow].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_shadow[nCntShadow].mtxWorld);

			//頂点バッファをデバイスのデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

			pDevice->SetFVF(FVF_VERTEX_3D);//頂点フォーマットの設定

			pDevice->SetTexture(0, g_pTextureShadow[g_shadow[nCntShadow].ntype]);//テクスチャの設定

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntShadow * 4, 2);

			//通常合成に戻す
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		}
		
	}
	
}