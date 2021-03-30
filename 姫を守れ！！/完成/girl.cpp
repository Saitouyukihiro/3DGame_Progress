//---------------------------
//インクルードファイル
//---------------------------
#include "girl.h"
#include "shadow.h"
#include "spider.h"
#include "fade.h"
#include "Sound.h"
//---------------------------
//グローバル変数
//---------------------------
LPDIRECT3DTEXTURE9		g_pTextureGirl[MAX_GIRL_TEX];	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGirl = NULL;			//頂点バッファへのポインタ
Girl					g_aGirl[MAX_GIRL];				//ビルボードのポインタ

//---------------------------
//初期化処理
//---------------------------
HRESULT InitGirl(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	pDevice = GetDevice();			//デバイスの取得

	//値の初期化
	for (int nCntGirl = 0; nCntGirl < MAX_GIRL; nCntGirl++)
	{
		g_aGirl[nCntGirl].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aGirl[nCntGirl].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aGirl[nCntGirl].aState = GIRL_STATE_NONE;
		g_aGirl[nCntGirl].fWidth = GIRL_X;
		g_aGirl[nCntGirl].fHeiht = GIRL_Y;
		g_aGirl[nCntGirl].nIdex = 0;
		g_aGirl[nCntGirl].nAnim = 0;
		g_aGirl[nCntGirl].bUse = false;
	}

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/girl_000.png",			//テクスチャ
								&g_pTextureGirl[0]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/girl_001.png",			//テクスチャ
								&g_pTextureGirl[1]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/girl_002.png",			//テクスチャ
								&g_pTextureGirl[2]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/girl_003.png",			//テクスチャ
								&g_pTextureGirl[3]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/girl_004.png",			//テクスチャ
								&g_pTextureGirl[5]);
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(	sizeof(VERTEX_3D) * 4 * MAX_GIRL,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_3D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffGirl,
									NULL);
	//---------------------------
	//頂点情報
	//---------------------------
	VERTEX_3D *pVtx;	//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffGirl->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntGirl = 0; nCntGirl < MAX_GIRL; nCntGirl++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-g_aGirl[nCntGirl].fWidth, -g_aGirl[nCntGirl].fHeiht, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aGirl[nCntGirl].fWidth, -g_aGirl[nCntGirl].fHeiht, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-g_aGirl[nCntGirl].fWidth, g_aGirl[nCntGirl].fHeiht, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aGirl[nCntGirl].fWidth, g_aGirl[nCntGirl].fHeiht, 0.0f);

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
	g_pVtxBuffGirl->Unlock();

	return S_OK;
}

//---------------------------
//終了処理
//---------------------------
void UninitGirl(void)
{
	//---------------------------
	//テクスチャ破棄
	//---------------------------
	for (int nCntTex = 0; nCntTex < MAX_GIRL_TEX; nCntTex++)
	{
		if (g_pTextureGirl[nCntTex] != NULL)
		{
			g_pTextureGirl[nCntTex]->Release();
			g_pTextureGirl[nCntTex] = NULL;
		}
	}

	//---------------------------
	//バッファ破棄
	//---------------------------
	if (g_pVtxBuffGirl != NULL)
	{
		g_pVtxBuffGirl->Release();
		g_pVtxBuffGirl = NULL;
	}
}

//---------------------------
//更新処理
//---------------------------
void UpdateGirl(void)
{
	VERTEX_3D *pVtx;		//頂点情報へのポインタ
	static int nAnimTime;	//アニメーションの更新時間

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffGirl->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntGirl = 0; nCntGirl < MAX_GIRL; nCntGirl++)
	{
		if (g_aGirl[nCntGirl].bUse == true)
		{
			g_aGirl[nCntGirl].posold = g_aGirl[nCntGirl].pos;
			nAnimTime++;
			if (nAnimTime >= 144)
			{
				g_aGirl[nCntGirl].nAnim++;
				nAnimTime = 0;
			}
			pVtx[0].tex = D3DXVECTOR2(0.0f + (0.5 * g_aGirl[nCntGirl].nAnim), 1.0f);
			pVtx[1].tex = D3DXVECTOR2(0.5f + (0.5 * g_aGirl[nCntGirl].nAnim), 1.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + (0.5 * g_aGirl[nCntGirl].nAnim), 0.0f);
			pVtx[3].tex = D3DXVECTOR2(0.5f + (0.5 * g_aGirl[nCntGirl].nAnim), 0.0f);
		}
		pVtx += 4;	//頂点を進める
		if (CollisionSpider(&g_aGirl[nCntGirl].pos, &g_aGirl[nCntGirl].posold, &g_aGirl[nCntGirl].move, g_aGirl[nCntGirl].fWidth, g_aGirl[nCntGirl].fHeiht, COLLISION_GIRL) == true)
		{

		}

		//影の追尾
		SetPointShadow(g_aGirl[nCntGirl].nIdex, D3DXVECTOR3(g_aGirl[nCntGirl].pos.x, 0.0f, g_aGirl[nCntGirl].pos.z), g_aGirl[nCntGirl].fWidth, g_aGirl[nCntGirl].fHeiht / 2);
	}
	//頂点バッファをアンロックする
	g_pVtxBuffGirl->Unlock();
}

//---------------------------
//描画処理
//---------------------------
void DrawGirl(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ

	pDevice = GetDevice();		//デバイスを取得する

	//---------------------------
	//マトリックスの設定
	//---------------------------
	D3DXMATRIX mtxTrans;	//計算用マトリックス

	for (int nCntGirl = 0; nCntGirl < MAX_GIRL; nCntGirl++)
	{
		if (g_aGirl[nCntGirl].bUse == true)
		{
			//カリング有り
			pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

			pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

			//αテスト
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

			//マトリックス初期化
			D3DXMatrixIdentity(&g_aGirl[nCntGirl].mtxWold);

			//カメラの向きを取得
			pDevice->GetTransform(	D3DTS_VIEW,
									&g_aGirl[nCntGirl].mtxView);
			//カメラの情報を入れて、スケールを反映
			g_aGirl[nCntGirl].mtxWold._11 = g_aGirl[nCntGirl].mtxView._11 * g_aGirl[nCntGirl].fWidth;
			g_aGirl[nCntGirl].mtxWold._12 = g_aGirl[nCntGirl].mtxView._21 * g_aGirl[nCntGirl].fWidth;
			g_aGirl[nCntGirl].mtxWold._13 = g_aGirl[nCntGirl].mtxView._31 * g_aGirl[nCntGirl].fWidth;
			g_aGirl[nCntGirl].mtxWold._21 = g_aGirl[nCntGirl].mtxView._12 * g_aGirl[nCntGirl].fHeiht;
			g_aGirl[nCntGirl].mtxWold._22 = g_aGirl[nCntGirl].mtxView._22 * g_aGirl[nCntGirl].fHeiht;
			g_aGirl[nCntGirl].mtxWold._23 = g_aGirl[nCntGirl].mtxView._32 * g_aGirl[nCntGirl].fHeiht;
			g_aGirl[nCntGirl].mtxWold._31 = g_aGirl[nCntGirl].mtxView._13;
			g_aGirl[nCntGirl].mtxWold._32 = g_aGirl[nCntGirl].mtxView._23;
			g_aGirl[nCntGirl].mtxWold._33 = g_aGirl[nCntGirl].mtxView._33;

			//位置
			D3DXMatrixTranslation(	&mtxTrans,
									g_aGirl[nCntGirl].pos.x,
									g_aGirl[nCntGirl].pos.y,
									g_aGirl[nCntGirl].pos.z);

			D3DXMatrixMultiply(	&g_aGirl[nCntGirl].mtxWold,
								&g_aGirl[nCntGirl].mtxWold,
								&mtxTrans);
			//マトリックスの設定
			pDevice->SetTransform(	D3DTS_WORLD,
									&g_aGirl[nCntGirl].mtxWold);
			//---------------------------
			//描画処理
			//---------------------------
			//バッファの設定をデータストリームに設定
			pDevice->SetStreamSource(	0,
										g_pVtxBuffGirl,
										0,
										sizeof(VERTEX_3D));
			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(	0,
									g_pTextureGirl[g_aGirl[nCntGirl].nType]);
			//ポリゴンの描画
			pDevice->DrawPrimitive(	D3DPT_TRIANGLESTRIP,	//プリミティブの種類
									nCntGirl * 4,			//何番目から描画するか
									2);						//△の数
			//αテスト
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);
		}
	}
}

//---------------------------
//セット
//---------------------------
void SetGirl(D3DXVECTOR3 pos, float fWidth, float fHeight, int nType)
{
	for (int nCntGirl = 0; nCntGirl < MAX_GIRL; nCntGirl++)
	{
		if (g_aGirl[nCntGirl].bUse == false)
		{
			g_aGirl[nCntGirl].pos = pos;		//位置を入れる
			g_aGirl[nCntGirl].fWidth = fWidth;	//幅を入れる
			g_aGirl[nCntGirl].fHeiht = fHeight;	//高さを入れる
			g_aGirl[nCntGirl].nType = nType;	//種類を入れる

			//影を付けて、影の番号を取得
			g_aGirl[nCntGirl].nIdex = SetShadow(pos, fWidth, fHeight / 2);
			g_aGirl[nCntGirl].bUse = true;		//使ってる
			break;
		}
	}
}

//---------------------------
//女の子情報
//---------------------------
Girl *GetGirl(void)
{
	return &g_aGirl[0];
}

//---------------------------
//女の子目線
//---------------------------
void GirlLooking(D3DXVECTOR3 pos)
{
	int nSide;
	for (int nCntGirl = 0; nCntGirl < MAX_GIRL; nCntGirl++)
	{
		if (g_aGirl[nCntGirl].bUse == true)
		{
			if (pos.x >= g_aGirl[nCntGirl].pos.x - g_aGirl[nCntGirl].fLookigX &&
				pos.x <= g_aGirl[nCntGirl].pos.x + g_aGirl[nCntGirl].fLookigX &&
				pos.z <= g_aGirl[nCntGirl].pos.z + g_aGirl[nCntGirl].fLookigZ)
			{
				nSide = rand() % 2;
				switch (nSide)
				{
				case 0:
					g_aGirl[nCntGirl].aState = GIRL_STATE_RIGHT;
					break;
				case 1:
					g_aGirl[nCntGirl].aState = GIRL_STATE_LEFT;
					break;
				}
			}
		}
	}
}

void AddGirl(int nVolue)
{
	for (int nCntGirl = 0; nCntGirl < MAX_GIRL; nCntGirl++)
	{
		if (g_aGirl[nCntGirl].bUse == true)
		{
			g_aGirl[nCntGirl].nHp -= nVolue;
			if (g_aGirl[nCntGirl].nHp <= 0)
			{
				SetFade(MODE_RESULT);
				PlaySound(SOUND_LABEL_aaa);
			}
		}
	}
}