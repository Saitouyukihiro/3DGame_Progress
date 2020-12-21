//---------------------------
//インクルードファイル
//---------------------------
#include "bullet.h"
#include "shadow.h"

//---------------------------
//グローバル変数
//---------------------------
LPDIRECT3DTEXTURE9		g_pTextureBullet = NULL;		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;		//頂点バッファへのポインタ
Bullet					g_aBullet[MAX_BULLET];			//ビルボードのポインタ

//---------------------------
//グローバル変数
//---------------------------
HRESULT InitBullet(void)
{
	LPDIRECT3DDEVICE9	pDevice;	//デバイスへのポインタ

	pDevice = GetDevice();			//デバイスの取得

	//値の初期化
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].fWidth = BULLET_X;
		g_aBullet[nCntBullet].fHeight = BULLET_Y;
		g_aBullet[nCntBullet].nIdex = 0;
		g_aBullet[nCntBullet].nType = 0;
		g_aBullet[nCntBullet].bUse = false;
	}

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/bullet01.png",			//テクスチャ
								&g_pTextureBullet);
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(	sizeof(VERTEX_3D) * 4 * MAX_BULLET,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_3D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffBullet,
									NULL);
	//---------------------------
	//頂点情報
	//---------------------------
	VERTEX_3D *pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-g_aBullet[nCntBullet].fWidth / 2, -g_aBullet[nCntBullet].fHeight / 2, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].fWidth / 2, -g_aBullet[nCntBullet].fHeight / 2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-g_aBullet[nCntBullet].fWidth / 2, g_aBullet[nCntBullet].fHeight / 2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].fWidth / 2, g_aBullet[nCntBullet].fHeight / 2, 0.0f);

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
	g_pVtxBuffBullet->Unlock();

	return S_OK;
}

//---------------------------
//終了処理
//---------------------------
void UninitBullet(void)
{
	//---------------------------
	//テクスチャ破棄
	//---------------------------
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	//---------------------------
	//バッファ破棄
	//---------------------------
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//---------------------------
//更新処理
//---------------------------
void UpdateBullet(void)
{
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			g_aBullet[nCntBullet].Move.x = g_aBullet[nCntBullet].Move.x + sinf(g_aBullet[nCntBullet].rot.y) * BULLET_MOVE_SPEED;
			g_aBullet[nCntBullet].Move.z = g_aBullet[nCntBullet].Move.z + cosf(g_aBullet[nCntBullet].rot.y) * BULLET_MOVE_SPEED;
			//g_aBullet[nCntBullet].Move.y = g_aBullet[nCntBullet].Move.y + cosf(g_aBullet[nCntBullet].rot.x) * BULLET_MOVE_SPEED;

			g_aBullet[nCntBullet].Pos += g_aBullet[nCntBullet].Move;

			//自分の影
			SetPointShadow(g_aBullet[nCntBullet].nIdex, g_aBullet[nCntBullet].Pos, g_aBullet[nCntBullet].fWidth, g_aBullet[nCntBullet].fHeight);
		}
	}
}

//---------------------------
//描画処理
//---------------------------
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9	pDevice;			//デバイスのポインタ

	pDevice = GetDevice();					//デバイスを取得する

	//---------------------------
	//マトリックスの設定
	//---------------------------
	D3DXMATRIX			 mtxTrans;	//計算用マトリックス

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			//カリング有り
			pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

			//αテスト
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

			//マトリックス初期化
			D3DXMatrixIdentity(	&g_aBullet[nCntBullet].mtxWold);

			//カメラの向きを取得
			pDevice->GetTransform(	D3DTS_VIEW,
									&g_aBullet[nCntBullet].mtxView);
			//カメラの情報を入れて、スケールを反映
			g_aBullet[nCntBullet].mtxWold._11 = g_aBullet[nCntBullet].mtxView._11 * g_aBullet[nCntBullet].fWidth;
			g_aBullet[nCntBullet].mtxWold._12 = g_aBullet[nCntBullet].mtxView._21 * g_aBullet[nCntBullet].fWidth;
			g_aBullet[nCntBullet].mtxWold._13 = g_aBullet[nCntBullet].mtxView._31 * g_aBullet[nCntBullet].fWidth;
			g_aBullet[nCntBullet].mtxWold._21 = g_aBullet[nCntBullet].mtxView._12 * g_aBullet[nCntBullet].fHeight;
			g_aBullet[nCntBullet].mtxWold._22 = g_aBullet[nCntBullet].mtxView._22 * g_aBullet[nCntBullet].fHeight;
			g_aBullet[nCntBullet].mtxWold._23 = g_aBullet[nCntBullet].mtxView._32 * g_aBullet[nCntBullet].fHeight;
			g_aBullet[nCntBullet].mtxWold._31 = g_aBullet[nCntBullet].mtxView._13;
			g_aBullet[nCntBullet].mtxWold._32 = g_aBullet[nCntBullet].mtxView._23;
			g_aBullet[nCntBullet].mtxWold._33 = g_aBullet[nCntBullet].mtxView._33;

			//位置
			D3DXMatrixTranslation(	&mtxTrans,
									g_aBullet[nCntBullet].Pos.x,
									g_aBullet[nCntBullet].Pos.y,
									g_aBullet[nCntBullet].Pos.z);

			D3DXMatrixMultiply(	&g_aBullet[nCntBullet].mtxWold,
								&g_aBullet[nCntBullet].mtxWold,
								&mtxTrans);
			//マトリックスの設定
			pDevice->SetTransform(	D3DTS_WORLD,
									&g_aBullet[nCntBullet].mtxWold);
			//---------------------------
			//描画処理
			//---------------------------
			//バッファの設定をデータストリームに設定
			pDevice->SetStreamSource(	0,
										g_pVtxBuffBullet,
										0,
										sizeof(VERTEX_3D));
			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(	0,
									g_pTextureBullet);
			//ポリゴンの描画
			pDevice->DrawPrimitive(	D3DPT_TRIANGLESTRIP,	//プリミティブの種類
									nCntBullet * 4,			//何番目から描画するか
									2);						//△の数
			//αテスト
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);
		}
	}
}

//---------------------------
//弾のセット
//---------------------------
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight, int nType)
{
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{
			g_aBullet[nCntBullet].Pos = pos;			//持ってきた位置を代入
			g_aBullet[nCntBullet].rot = rot;			//持ってきた向きを代入
			g_aBullet[nCntBullet].fWidth = fWidth;		//持ってきた幅を代入
			g_aBullet[nCntBullet].fHeight = fHeight;	//持ってきた高さを代入
			g_aBullet[nCntBullet].nType = nType;		//持ってきた種類を代入

			g_aBullet[nCntBullet].bUse = true;

			//影のセット
			g_aBullet[nCntBullet].nIdex = SetShadow(pos, fWidth, fHeight);
			break;
		}
	}
}

//---------------------------
//弾の情報を取得
//---------------------------
Bullet *GetBullet(void)
{
	return &g_aBullet[0];
}