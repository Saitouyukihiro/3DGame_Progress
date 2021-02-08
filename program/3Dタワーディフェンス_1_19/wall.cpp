//---------------------------
//インクルードファイル
//---------------------------
#include "wall.h"
#include "camara.h"

//---------------------------
//グローバル変数
//---------------------------
LPDIRECT3DTEXTURE9		g_pTextureWall[MAX_WALL_TEX] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;				//頂点バッファへのポインタ
Wall					g_aWall[MAX_WALL];					//壁のポインタ

//---------------------------
//初期化処理
//---------------------------
HRESULT InitWall(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	pDevice = GetDevice();		//デバイスの取得

	//値の初期化
	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		g_aWall[nCntWall].pos = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		g_aWall[nCntWall].rot = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		g_aWall[nCntWall].fWidth = WALL_X;
		g_aWall[nCntWall].fHeiht = WALL_Y;
		g_aWall[nCntWall].nType = 0;
		g_aWall[nCntWall].bUse = false;
	}

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/wall_000.jpg",			//テクスチャ
								&g_pTextureWall[0]);
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(	sizeof(VERTEX_3D) * 4 * MAX_WALL,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_3D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffWall,
									NULL);
	//---------------------------
	//頂点情報
	//---------------------------
	VERTEX_3D *pVtx;	//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-g_aWall[nCntWall].fWidth, g_aWall[nCntWall].fHeiht, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aWall[nCntWall].fWidth, g_aWall[nCntWall].fHeiht, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-g_aWall[nCntWall].fWidth, -g_aWall[nCntWall].fHeiht, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aWall[nCntWall].fWidth, -g_aWall[nCntWall].fHeiht, 0.0f);

		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;	//頂点を進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffWall->Unlock();

	return S_OK;
}

//---------------------------
//終了処理
//---------------------------
void UninitWall(void)
{
	//---------------------------
	//テクスチャ破棄
	//---------------------------
	for (int nCntWall = 0; nCntWall < MAX_WALL_TEX; nCntWall++)
	{
		if (g_pTextureWall[nCntWall] != NULL)
		{
			g_pTextureWall[nCntWall]->Release();
			g_pTextureWall[nCntWall] = NULL;
		}
	}

	//---------------------------
	//バッファ破棄
	//---------------------------
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}
}

//---------------------------
//更新処理
//---------------------------
void UpdateWall(void)
{

}

//---------------------------
//描画処理
//---------------------------
void DrawWall(void)
{

	LPDIRECT3DDEVICE9 pDevice;		//デバイスのポインタ

	pDevice = GetDevice();			//デバイスを取得する

	//---------------------------
	//マトリックスの設定
	//---------------------------
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_aWall[nCntWall].bUse == true)
		{
			//カリング有
			pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

			pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

			//マトリックス初期化
			D3DXMatrixIdentity(&g_aWall[nCntWall].mtxWold);

			//スケール
			g_aWall[nCntWall].mtxWold._11 = g_aWall[nCntWall].fWidth;
			g_aWall[nCntWall].mtxWold._22 = g_aWall[nCntWall].fHeiht;

			//向きの設定
			D3DXMatrixRotationYawPitchRoll(	&mtxRot,
											g_aWall[nCntWall].rot.y,
											g_aWall[nCntWall].rot.x,
											g_aWall[nCntWall].rot.z);

			D3DXMatrixMultiply(	&g_aWall[nCntWall].mtxWold,
								&g_aWall[nCntWall].mtxWold,
								&mtxRot);
			//位置
			D3DXMatrixTranslation(	&mtxTrans,
									g_aWall[nCntWall].pos.x,
									g_aWall[nCntWall].pos.y,
									g_aWall[nCntWall].pos.z);
													  
			D3DXMatrixMultiply(	&g_aWall[nCntWall].mtxWold,
								&g_aWall[nCntWall].mtxWold,
								&mtxTrans);
			//マトリックスの設定
			pDevice->SetTransform(	D3DTS_WORLD,
									&g_aWall[nCntWall].mtxWold);
			//---------------------------
			//描画処理
			//---------------------------
			//バッファの設定をデータストリームに設定
			pDevice->SetStreamSource(	0,
										g_pVtxBuffWall,
										0,
										sizeof(VERTEX_3D));
			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(	0,
									g_pTextureWall[g_aWall[nCntWall].nType]);
			//ポリゴンの描画
			pDevice->DrawPrimitive(	D3DPT_TRIANGLESTRIP,	//プリミティブの種類
									nCntWall * 4,			//何番目から描画するか
									2);						//△の数
		}
	}
}

//---------------------------
//セット
//---------------------------
void SetWall(D3DXVECTOR3 rot, D3DXVECTOR3 pos, float fWith, float fHeight, int nType)
{
	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_aWall[nCntWall].bUse == false)
		{
			g_aWall[nCntWall].rot = rot;		//向きを入れる
			g_aWall[nCntWall].pos = pos;		//位置を入れる
			g_aWall[nCntWall].fWidth = fWith;	//幅を入れる
			g_aWall[nCntWall].fHeiht = fHeight;	//高さを入れる
			g_aWall[nCntWall].nType = nType;	//種類を入れる

			g_aWall[nCntWall].bUse = true;		//使ってる
			break;
		}
	}
}

//---------------------------
//壁の当たり判定
//---------------------------
bool ColisionWall(D3DXVECTOR3 *pos, D3DXVECTOR3 *posold, D3DXVECTOR3 *move, float fWidth, float fHeight, float fDepht, int nType)
{
	bool bLand = false;	//壁についてるか
	Wall *pWall;
	Camera *pCamera;

	pWall = GetWall();
	pCamera = GetCamera();

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++, pWall++)
	{
		if (pWall->bUse == true)
		{
			if (pos->x <= pWall->pos.x + pWall->fWidth / 2 &&
				pos->x >= pWall->pos.x - pWall->fWidth / 2 &&
				pos->y <= pWall->pos.y + pWall->fHeiht / 2 &&
				pos->y >= pWall->pos.y - pWall->fHeiht / 2)
			{
				if (pWall->rot.y == 0.0f)
				{
					if (posold->z + fDepht <= pWall->pos.z &&
						pos->z + fDepht >= pWall->pos.z)
					{
						pCamera->PosV.z = pWall->pos.z - (fDepht + 0.1f);	//壁に合わせる
						bLand = true;			//壁についてる
					}
				}
				else if (pWall->rot.y == -D3DX_PI)
				{
					if (posold->z - fDepht >= pWall->pos.z &&
						pos->z - fDepht <= pWall->pos.z)
					{
						pCamera->PosV.z = pWall->pos.z + (fDepht + 0.1f);	//壁に合わせる
						bLand = true;			//壁についてる
					}
				}
			}
			else if (pos->z <= pWall->pos.z + pWall->fWidth / 2 &&
					 pos->z >= pWall->pos.z - pWall->fWidth / 2 &&
					 pos->y <= pWall->pos.y + pWall->fHeiht / 2 &&
					 pos->y >= pWall->pos.y - pWall->fHeiht / 2)
			{
				if (pWall->rot.y == D3DX_PI / 2)
				{
					if (posold->x + fWidth <= pWall->pos.x &&
						pos->x + fWidth >= pWall->pos.x)
					{
						pCamera->PosV.x = pWall->pos.x - (fWidth + 0.1f);	//壁に合わせる
						bLand = true;			//壁についてる
					}
				}
				else if (pWall->rot.y == -D3DX_PI)
				{
					if (posold->z - fDepht >= pWall->pos.z &&
						pos->z - fDepht <= pWall->pos.z)
					{
						pCamera->PosV.z = pWall->pos.z + (fDepht + 0.1f);	//壁に合わせる
						bLand = true;			//壁についてる
					}
				}
			}
		}
	}
	pWall -= MAX_WALL;

	return bLand;
}

//---------------------------
//壁の情報
//---------------------------
Wall *GetWall(void)
{
	return &g_aWall[0];
}