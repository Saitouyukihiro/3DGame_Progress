//---------------------------
//インクルードファイル
//---------------------------
#include "enemycount.h"
#include "spider.h"

//---------------------------
//グローバル変数
//---------------------------
LPDIRECT3DTEXTURE9		g_apTextureEnemyCount = NULL;	//テクスチャ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemyCount = NULL;		//頂点バッファへのポインタ
Enemycount				g_aEnemyCount[MAX_ENEMY_COUNT_DIGIT];	//スコアの構造体
int						g_nEnemyCount;					//スコア
int g_nCountSpider = 0;

//---------------------------
//初期化処理
//---------------------------
HRESULT InitCount(void)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ
	VERTEX_2D *pVtx; //頂点情報へのポインタ

					 //デバイスの取得
	pDevice = GetDevice();
	//敵の初期化
	for (int nCntEnemyCount = 0; nCntEnemyCount < MAX_ENEMY_COUNT_DIGIT; nCntEnemyCount++)
	{
		g_aEnemyCount[nCntEnemyCount].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/number.png",
								&g_apTextureEnemyCount);
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(	sizeof(VERTEX_2D) * 4 * MAX_ENEMY_COUNT_DIGIT,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffEnemyCount,
									NULL);
	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffEnemyCount->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEnemyCount = 0; nCntEnemyCount < MAX_ENEMY_COUNT_DIGIT; nCntEnemyCount++)
	{
		//頂点座標
		pVtx[0].pos = D3DXVECTOR3(g_aEnemyCount[nCntEnemyCount].pos.x + ENEMY_COUNT_X * 2 * nCntEnemyCount - ENEMY_COUNT_X, g_aEnemyCount[nCntEnemyCount].pos.y - ENEMY_COUNT_Y, g_aEnemyCount[nCntEnemyCount].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aEnemyCount[nCntEnemyCount].pos.x + ENEMY_COUNT_X * 2 * nCntEnemyCount + ENEMY_COUNT_X, g_aEnemyCount[nCntEnemyCount].pos.y - ENEMY_COUNT_Y, g_aEnemyCount[nCntEnemyCount].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aEnemyCount[nCntEnemyCount].pos.x + ENEMY_COUNT_X * 2 * nCntEnemyCount - ENEMY_COUNT_X, g_aEnemyCount[nCntEnemyCount].pos.y + ENEMY_COUNT_Y, g_aEnemyCount[nCntEnemyCount].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aEnemyCount[nCntEnemyCount].pos.x + ENEMY_COUNT_X * 2 * nCntEnemyCount + ENEMY_COUNT_X, g_aEnemyCount[nCntEnemyCount].pos.y + ENEMY_COUNT_Y, g_aEnemyCount[nCntEnemyCount].pos.z);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].col = D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f);
		pVtx[1].col = D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f);
		pVtx[2].col = D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f);
		pVtx[3].col = D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffEnemyCount->Unlock();

	return S_OK;
}

//---------------------------
//終了処理
//---------------------------
void UninitCount(void)
{
	g_nEnemyCount = 0;
	g_nCountSpider = 0;
	//テクスチャの破棄
	if (g_apTextureEnemyCount != NULL)
	{
		g_apTextureEnemyCount->Release();
		g_apTextureEnemyCount = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffEnemyCount != NULL)
	{
		g_pVtxBuffEnemyCount->Release();
		g_pVtxBuffEnemyCount = NULL;
	}
}

//---------------------------
//更新処理
//---------------------------
void UpdateCount(void)
{
	VERTEX_2D	*pVtx;		//頂点情報へのポインタ
	int			nHeith = 0;	//差分

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffEnemyCount->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEnemyCount = 0; nCntEnemyCount < MAX_ENEMY_COUNT_DIGIT; nCntEnemyCount++, nHeith + 50.0f)
	{
		g_aEnemyCount[nCntEnemyCount].pos = D3DXVECTOR3(1170, 0.0f + 35.0f, 0.0f);

		//頂点座標
		pVtx[0].pos = D3DXVECTOR3(g_aEnemyCount[nCntEnemyCount].pos.x + ENEMY_COUNT_X * 2 * nCntEnemyCount - ENEMY_COUNT_X, g_aEnemyCount[nCntEnemyCount].pos.y - ENEMY_COUNT_Y, g_aEnemyCount[nCntEnemyCount].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aEnemyCount[nCntEnemyCount].pos.x + ENEMY_COUNT_X * 2 * nCntEnemyCount + ENEMY_COUNT_X, g_aEnemyCount[nCntEnemyCount].pos.y - ENEMY_COUNT_Y, g_aEnemyCount[nCntEnemyCount].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aEnemyCount[nCntEnemyCount].pos.x + ENEMY_COUNT_X * 2 * nCntEnemyCount - ENEMY_COUNT_X, g_aEnemyCount[nCntEnemyCount].pos.y + ENEMY_COUNT_Y, g_aEnemyCount[nCntEnemyCount].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aEnemyCount[nCntEnemyCount].pos.x + ENEMY_COUNT_X * 2 * nCntEnemyCount + ENEMY_COUNT_X, g_aEnemyCount[nCntEnemyCount].pos.y + ENEMY_COUNT_Y, g_aEnemyCount[nCntEnemyCount].pos.z);

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffEnemyCount->Unlock();

	int			aNumber[MAX_ENEMY_COUNT_DIGIT];	//スコア計算

	Spider *pSpider;

	pSpider = GetSpider();

	for (int nCntSpider = 0; nCntSpider < MAX_SPIDER_MODEL; nCntSpider++, pSpider++)
	{
		if (pSpider->bUse == true)
		{
			g_nCountSpider += 1;
		}
	}

	pSpider -= MAX_SPIDER_MODEL;

	//スコア換算
	g_nEnemyCount = g_nCountSpider;

	//スコア計算
	aNumber[0] = g_nEnemyCount % 100 / 10;
	aNumber[1] = g_nEnemyCount % 10 / 1;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffEnemyCount->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEnemyCount = 0; nCntEnemyCount < MAX_ENEMY_COUNT_DIGIT; nCntEnemyCount++, nHeith + 50.0f)
	{
		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2((aNumber[nCntEnemyCount] * 0.1f) + 0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((aNumber[nCntEnemyCount] * 0.1f) + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2((aNumber[nCntEnemyCount] * 0.1f) + 0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((aNumber[nCntEnemyCount] * 0.1f) + 0.1f, 1.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffEnemyCount->Unlock();
	g_nCountSpider = 0;
}

//---------------------------
//描画処理
//---------------------------
void DrawCount(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ

	pDevice = GetDevice();		//デバイスを取得する
								//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(	0,
								g_pVtxBuffEnemyCount,
								0,
								sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D); //頂点フォーマットの設定

	for (int nCntEnemyCount = 0; nCntEnemyCount < MAX_ENEMY_COUNT_DIGIT; nCntEnemyCount++)
	{
		//αテスト
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 110);

		//テクスチャ
		pDevice->SetTexture(0, g_apTextureEnemyCount);
		//ポリゴンの描画
		pDevice->DrawPrimitive(	D3DPT_TRIANGLESTRIP, //プリミティブの種類
								nCntEnemyCount * 4,
								2);
		//αテスト
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);
	}
}

//---------------------------
//スコア入手
//---------------------------
int GetCount(void)
{
	return g_nEnemyCount;
}