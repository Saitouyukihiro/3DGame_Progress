//ーーーーーーーーーーーーーーーーーーーーーーーーー
//エフェクトの処理(Effect.cpp)
//ーーーーーーーーーーーーーーーーーーーーーーーーー

#include "main.h"
#include "input.h"
#include "Effect.h"
#include "Model.h"

#define MOVE_Y (3.0f)

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureEffect[EFFECTTYPE_MAX] = {};//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;//頂点バッファへのポインタ

Effect g_Effect[MAX_EFFECT];



//初期化処理
void InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスのポインタ
	int nCntEffect;
	pDevice = GetDevice();//デバイスの取得

	//エフェクトの初期化
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		g_Effect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Effect[nCntEffect].color = D3DXCOLOR(0, 0, 0, 0);

		g_Effect[nCntEffect].fHight = 0;
		g_Effect[nCntEffect].fWhidth = 0;

		g_Effect[nCntEffect].bUse = true;
		g_Effect[nCntEffect].nlife = 0;
		g_Effect[nCntEffect].ntype = 0;
	}

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "date/TEXTURE/はね.png", &g_pTextureEffect[EFFECTTYTPE_PLAYER]);


	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EFFECT, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffEffect, NULL);

	

}

//終了処理
void UninitEffect(void)//追加の可能性があるため項目は作っとく
{
	for (int nCntEffect = 0; nCntEffect < EFFECTTYPE_MAX; nCntEffect++)
	{
		//テクスチャの破棄
		if (g_pTextureEffect != NULL)
		{
			g_pTextureEffect[nCntEffect]->Release();
			g_pTextureEffect[nCntEffect] = NULL;
		}

		//頂点バッファも破棄
		if (g_pVtxBuffEffect != NULL)
		{
			g_pVtxBuffEffect->Release();
			g_pVtxBuffEffect = NULL;
		}
	}
}

//更新処理
void UpdateEffect(void)//追加の可能性があるため項目は作っとく
{
	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_Effect[nCntEffect].bUse == true)
		{
			g_Effect[nCntEffect].nlife--;

			if (g_Effect[nCntEffect].nlife <= 0)
			{
				g_Effect[nCntEffect].bUse = false;
			}
		}
	}
}

void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR color, float fWhidth, float fHight, int ntype, int nLife)
{
	int nCntEffect;
	VERTEX_3D*pVtx;//頂点情報へのポインタ

	 //頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_Effect[nCntEffect].bUse == false)
		{
			g_Effect[nCntEffect].pos = pos;

			g_Effect[nCntEffect].fWhidth = fWhidth;
			g_Effect[nCntEffect].fHight = fHight;
			g_Effect[nCntEffect].ntype = ntype;
			
			//頂点の座標
			pVtx[0].pos = D3DXVECTOR3(g_Effect[nCntEffect].pos.x - (g_Effect[nCntEffect].fWhidth / 2), g_Effect[nCntEffect].pos.y + (g_Effect[nCntEffect].fHight), g_Effect[nCntEffect].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_Effect[nCntEffect].pos.x + (g_Effect[nCntEffect].fWhidth / 2), g_Effect[nCntEffect].pos.y + (g_Effect[nCntEffect].fHight), g_Effect[nCntEffect].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_Effect[nCntEffect].pos.x - (g_Effect[nCntEffect].fWhidth / 2), g_Effect[nCntEffect].pos.y, g_Effect[nCntEffect].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_Effect[nCntEffect].pos.x + (g_Effect[nCntEffect].fWhidth / 2), g_Effect[nCntEffect].pos.y, g_Effect[nCntEffect].pos.z);

			//ベクトルの設定
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//頂点の色
			pVtx[0].col = color; 
			pVtx[1].col = color;
			pVtx[2].col = color;
			pVtx[3].col = color;

			//テクスチャのUV座標
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		

			g_Effect[nCntEffect].nlife = nLife;
			g_Effect[nCntEffect].bUse = true;

			break;
		}
		pVtx += 4;
	}
	//頂点バッファをアンロック
	g_pVtxBuffEffect->Unlock();
}

Effect *GetEffect(void)
{
	return &g_Effect[0];
}

//描画処理
void DrawEffect(void)
{
	int nCntEffect;
	LPDIRECT3DDEVICE9 pDevice;//デバイスのポインタ
	D3DXMATRIX mtxView;
	D3DXMATRIX mtxTrans;
	pDevice = GetDevice();//デバイスを取得する

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_Effect[nCntEffect].bUse == true)
		{

			//アルファテスト関係
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

			//加算合成関係
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

			//マトリックス初期化
			D3DXMatrixIdentity(&g_Effect[nCntEffect].mtxWorld);
			//ビューマトリックスの取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//ポリゴンをカメラに対して正面に
			D3DXMatrixInverse(&g_Effect[nCntEffect].mtxWorld, NULL, &mtxView);

			g_Effect[nCntEffect].mtxWorld._41 = 0.0f;
			g_Effect[nCntEffect].mtxWorld._42 = 0.0f;
			g_Effect[nCntEffect].mtxWorld._43 = 0.0f;

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Effect[nCntEffect].pos.x, g_Effect[nCntEffect].pos.y, g_Effect[nCntEffect].pos.z);
			D3DXMatrixMultiply(&g_Effect[nCntEffect].mtxWorld, &g_Effect[nCntEffect].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Effect[nCntEffect].mtxWorld);

			//頂点バッファをデバイスのデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_3D));

			pDevice->SetFVF(FVF_VERTEX_3D);//頂点フォーマットの設定

			pDevice->SetTexture(0, g_pTextureEffect[g_Effect[nCntEffect].ntype]);//テクスチャの設定

																				 //ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEffect * 4, 2);

			//通常合成に戻す(加算合成)
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

			//アルファテスト関係
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);
		}

	}

}

