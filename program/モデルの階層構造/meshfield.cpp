//---------------------------
//インクルードファイル
//---------------------------
#include "meshfield.h"

//---------------------------
//グローバル変数
//---------------------------
LPDIRECT3DTEXTURE9		g_pTextureField[MAX_MESH_TEX] = {};	//テクスチャへのポインタ
Field					g_Field[MAX_FIELD];		//メッシュフィールドの構造体

//---------------------------
//グローバル変数
//---------------------------
HRESULT InitMeshfield(void)
{
	LPDIRECT3DDEVICE9	pDevice;	//デバイスへのポインタ

	pDevice = GetDevice();			//デバイスの取得

	for (int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		g_Field[nCntField].Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Field[nCntField].Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Field[nCntField].pVtxBuffField = NULL;
		g_Field[nCntField].pIdxBuffFoeld = NULL;
		g_Field[nCntField].fWidth = 1.0f;
		g_Field[nCntField].fHeiht = 1.0f;
		g_Field[nCntField].fDepht = 1.0f;
		g_Field[nCntField].nTex = 0;
		g_Field[nCntField].bUse = false;
	}

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/field002.jpg",			//テクスチャ
								&g_pTextureField[0]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/field000.jpg",			//テクスチャ
								&g_pTextureField[1]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/field001.jpg",			//テクスチャ
								&g_pTextureField[2]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/cat01.png",				//テクスチャ
								&g_pTextureField[3]);
	return S_OK;
}

//---------------------------
//終了処理
//---------------------------
void UninitMeshfield(void)
{
	//---------------------------
	//テクスチャ破棄
	//---------------------------
	for (int nCntTex = 0; nCntTex < MAX_MESH_TEX; nCntTex++)
	{
		if (g_pTextureField[nCntTex] != NULL)
		{
			g_pTextureField[nCntTex]->Release();
			g_pTextureField[nCntTex] = NULL;
		}
	}

	for (int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		//---------------------------
		//バッファ破棄
		//---------------------------
		if (g_Field[nCntField].pVtxBuffField != NULL)
		{
			g_Field[nCntField].pVtxBuffField->Release();
			g_Field[nCntField].pVtxBuffField = NULL;
		}

		//---------------------------
		//インデックスバッファ破棄
		//---------------------------
		if (g_Field[nCntField].pIdxBuffFoeld != NULL)
		{
			g_Field[nCntField].pIdxBuffFoeld->Release();
			g_Field[nCntField].pIdxBuffFoeld = NULL;
		}
	}
}

//---------------------------
//更新処理
//---------------------------
void UpdateMeshfield(void)
{
	
}	

//---------------------------
//描画処理
//---------------------------
void DrawMeshfield(void)
{
	LPDIRECT3DDEVICE9	pDevice;			//デバイスのポインタ

	pDevice = GetDevice();					//デバイスを取得する

	//---------------------------
	//マトリックスの設定
	//---------------------------
	D3DXMATRIX			mtxRot, mtxTrans;	//計算用マトリックス

	for (int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		if (g_Field[nCntField].bUse == true)
		{
			//カリング有
			pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

			//αテスト
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

			D3DXMatrixIdentity(&g_Field[nCntField].mtxWold);	//マトリックス初期化

			//スケール
			g_Field[nCntField].mtxWold._11 = g_Field[nCntField].fWidth;
			g_Field[nCntField].mtxWold._22 = g_Field[nCntField].fHeiht;
			g_Field[nCntField].mtxWold._33 = g_Field[nCntField].fDepht;

			//向きの設定
			D3DXMatrixRotationYawPitchRoll(	&mtxRot,
											g_Field[nCntField].Rot.y,
											g_Field[nCntField].Rot.x,
											g_Field[nCntField].Rot.z);

			D3DXMatrixMultiply(	&g_Field[nCntField].mtxWold,
								&g_Field[nCntField].mtxWold,
								&mtxRot);
			//位置
			D3DXMatrixTranslation(	&mtxTrans,
									g_Field[nCntField].Pos.x,
									g_Field[nCntField].Pos.y,
									g_Field[nCntField].Pos.z);

			D3DXMatrixMultiply(	&g_Field[nCntField].mtxWold,
								&g_Field[nCntField].mtxWold,
								&mtxTrans);
			//マトリックスの設定
			pDevice->SetTransform(	D3DTS_WORLD,
									&g_Field[nCntField].mtxWold);
			//---------------------------
			//描画処理
			//---------------------------
			//バッファの設定をデータストリームに設定
			pDevice->SetStreamSource(	0,
				g_Field[nCntField].pVtxBuffField,
										0,
										sizeof(VERTEX_3D));
			//インデックスバッファをデータストリームに設定
			pDevice->SetIndices(g_Field[nCntField].pIdxBuffFoeld);

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(	0,
									g_pTextureField[g_Field[nCntField].nTex]);
			if (g_Field[nCntField].aState == FORM_FLOO)
			{
				//ポリゴンの描画
				pDevice->DrawIndexedPrimitive(	D3DPT_TRIANGLESTRIP,			//プリミティブの種類
												0,								//インデックス バッファの開始地点から最初のインデックスまでのオフセット
												nCntField * FLOO_VTX_NUM_MAX,	//描画で使用される最小の頂点番号
												FLOO_IDX_NUM_MAX,				//頂点の数
												nCntField * FLOO_IDX_NUM_MAX,	//インデックス配列の読み取りを開始する位置
												FLOO_POLY_NUM_MAX;				//△の数
			}
			else if (g_Field[nCntField].aState == FORM_WALL)
			{
				//ポリゴンの描画		
				pDevice->DrawIndexedPrimitive(	D3DPT_TRIANGLESTRIP,			//プリミティブの種類
												0,								//インデックス バッファの開始地点から最初のインデックスまでのオフセット
												nCntField * WALL_VTX_NUM_MAX,	//描画で使用される最小の頂点番号
												WALL_IDX_NUM_MAX,				//頂点の数
												nCntField * WALL_IDX_NUM_MAX,	//インデックス配列の読み取りを開始する位置
												WALL_POLY_NUM_MAX;				//△の数
			}
			else if (g_Field[nCntField].aState == FORM_SEMICIRCLE)
			{
				//ポリゴンの描画
				pDevice->DrawIndexedPrimitive(	D3DPT_TRIANGLEFAN,					//プリミティブの種類
												0,									//インデックス バッファの開始地点から最初のインデックスまでのオフセット
												nCntField * SEMICIRCLE_VTX_NUM_MAX,	//描画で使用される最小の頂点番号
												SEMICIRCLE_IDX_NUM_MAX,				//頂点の数
												nCntField * SEMICIRCLE_IDX_NUM_MAX,	//インデックス配列の読み取りを開始する位置
												SEMICIRCLE_POLY_NUM_MAX;			//△の数
			}
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
void SetField(D3DXVECTOR3 rot, D3DXVECTOR3 pos, float fWidth, float fHeight, float fDepht, int nTex, MESH_FORM aState)
{
	LPDIRECT3DDEVICE9	pDevice;	//デバイスへのポインタ

	pDevice = GetDevice();			//デバイスの取得

	for (int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		if (g_Field[nCntField].bUse == false)
		{
			g_Field[nCntField].Pos = pos;			//位置
			g_Field[nCntField].Rot = rot;			//向き
			g_Field[nCntField].fWidth = fWidth;		//幅
			g_Field[nCntField].fHeiht = fHeight;	//高さ
			g_Field[nCntField].fDepht = fDepht;		//奥行
			g_Field[nCntField].nTex = nTex;			//テクスチャ
			g_Field[nCntField].aState = aState;		//形

			if (g_Field[nCntField].aState == FORM_FLOO)
			{
				//頂点バッファの生成
				pDevice->CreateVertexBuffer(	sizeof(VERTEX_3D) * FLOO_VTX_NUM_MAX * MAX_FIELD,
												D3DUSAGE_WRITEONLY,
												FVF_VERTEX_3D,
												D3DPOOL_MANAGED,
												&g_Field[nCntField].pVtxBuffField,
												NULL);
				//インデックスバッファの生成
				pDevice->CreateIndexBuffer(	sizeof(WORD) * FLOO_IDX_NUM_MAX * MAX_FIELD,
											D3DUSAGE_WRITEONLY,
											D3DFMT_INDEX16,
											D3DPOOL_MANAGED,
											&g_Field[nCntField].pIdxBuffFoeld,
											NULL);
				//---------------------------
				//頂点情報
				//---------------------------
				VERTEX_3D *pVtx;		//頂点情報へのポインタ

				//頂点バッファをロックし、頂点データへのポインタを取得
				g_Field[nCntField].pVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);

				for (int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
				{
					int nVtxNum = 0;
					for (int nCntZ = 0; nCntZ < FLOO_MAX_VTX_Z + 1; nCntZ++)
					{
						for (int nCntX = 0; nCntX < FLOO_MAX_VTX_X + 1; nCntX++, nVtxNum++)
						{
							pVtx[nVtxNum].pos = D3DXVECTOR3(-MS_X + (((MS_X * 2) / FLOO_MAX_VTX_X) * nCntX), 0.0f, MS_Z - (((MS_Z * 2) / FLOO_MAX_VTX_Z) * nCntZ));
							pVtx[nVtxNum].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
							pVtx[nVtxNum].col = D3DCOLOR_RGBA(255, 255, 255, 255);
							pVtx[nVtxNum].tex = D3DXVECTOR2(0.0f + (1.0f * nCntX), 0.0f + (1.0f * nCntZ));
						}
					}
					nVtxNum = 0;
					pVtx += FLOO_VTX_NUM_MAX;	//頂点を進める
				}

				//頂点バッファをアンロックする
				g_Field[nCntField].pVtxBuffField->Unlock();

				//---------------------------
				//インデックス情報
				//---------------------------
				WORD *pIdx;		//インデックス情報へのポインタ

				//インデックスバッファをロックし、番号データへのポインタを取得
				g_Field[nCntField].pIdxBuffFoeld->Lock(0, 0, (void**)&pIdx, 0);

				for (int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
				{
					//角被さり以外の頂点
					for (int nCntZ = 0; nCntZ < FLOO_MAX_VTX_Z; nCntZ++)
					{
						for (int nCntX = 0; nCntX < FLOO_MAX_VTX_X + 1; nCntX++)
						{
							pIdx[(nCntX * 2) + 0 + ((FLOO_MAX_VTX_X + 2) * 2) * nCntZ] = ((FLOO_MAX_VTX_X + 1) + nCntX) + ((FLOO_MAX_VTX_X + 1) * nCntZ);
							pIdx[(nCntX * 2) + 1 + ((FLOO_MAX_VTX_X + 2) * 2) * nCntZ] = (0 + nCntX) + ((FLOO_MAX_VTX_X + 1) * nCntZ);
						}
					}
					//角被さりの頂点
					for (int nCntZ = 0; nCntZ < FLOO_MAX_VTX_Z - 1; nCntZ++)
					{
						pIdx[(((FLOO_MAX_VTX_X + 1) * 2 + 0) * (nCntZ + 1)) + (2 * nCntZ)] = FLOO_MAX_VTX_X + ((FLOO_MAX_VTX_X + 1) * nCntZ);
						pIdx[(((FLOO_MAX_VTX_X + 1) * 2 + 1) * (nCntZ + 1)) + (1 * nCntZ)] = (FLOO_MAX_VTX_X * 2 + 2) + ((FLOO_MAX_VTX_X + 1) * nCntZ);
					}
					pIdx += FLOO_IDX_NUM_MAX;	//インデックスを進める
				}

				//インデックスバッファをアンロックする
				g_Field[nCntField].pIdxBuffFoeld->Unlock();
			}
			else if (g_Field[nCntField].aState == FORM_WALL)
			{
				//頂点バッファの生成
				pDevice->CreateVertexBuffer(	sizeof(VERTEX_3D) * WALL_VTX_NUM_MAX * MAX_FIELD,
												D3DUSAGE_WRITEONLY,
												FVF_VERTEX_3D,
												D3DPOOL_MANAGED,
												&g_Field[nCntField].pVtxBuffField,
												NULL);
				//インデックスバッファの生成
				pDevice->CreateIndexBuffer(	sizeof(WORD) * WALL_IDX_NUM_MAX * MAX_FIELD,
											D3DUSAGE_WRITEONLY,
											D3DFMT_INDEX16,
											D3DPOOL_MANAGED,
											&g_Field[nCntField].pIdxBuffFoeld,
											NULL);
				//---------------------------
				//頂点情報
				//---------------------------
				VERTEX_3D *pVtx;		//頂点情報へのポインタ

				//頂点バッファをロックし、頂点データへのポインタを取得
				g_Field[nCntField].pVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);

				for (int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
				{
					int nVtxNum = 0;
					for (int nCntY = 0; nCntY < WALL_MAX_VTX_Y + 1; nCntY++)
					{
						for (int nCntX = 0; nCntX < WALL_MAX_VTX_X + 1; nCntX++, nVtxNum++)
						{
							pVtx[nVtxNum].pos = D3DXVECTOR3(-MS_X + (((MS_X * 2) / WALL_MAX_VTX_X) * nCntX), MS_Z - (((MS_Z * 2) / WALL_MAX_VTX_Y) * nCntY), 0.0f);
							pVtx[nVtxNum].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
							pVtx[nVtxNum].col = D3DCOLOR_RGBA(255, 255, 255, 255);
							pVtx[nVtxNum].tex = D3DXVECTOR2(0.0f + (1.0f * nCntX), 0.0f + (1.0f * nCntY));
						}
					}
					nVtxNum = 0;
					pVtx += WALL_VTX_NUM_MAX;	//頂点を進める
				}

				//頂点バッファをアンロックする
				g_Field[nCntField].pVtxBuffField->Unlock();

				//---------------------------
				//インデックス情報
				//---------------------------
				WORD *pIdx;		//インデックス情報へのポインタ

				//インデックスバッファをロックし、番号データへのポインタを取得
				g_Field[nCntField].pIdxBuffFoeld->Lock(0, 0, (void**)&pIdx, 0);

				for (int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
				{
					//角被さり以外の頂点
					for (int nCntY = 0; nCntY < WALL_MAX_VTX_Y; nCntY++)
					{
						for (int nCntX = 0; nCntX < WALL_MAX_VTX_X + 1; nCntX++)
						{
							pIdx[(nCntX * 2) + 0 + ((WALL_MAX_VTX_X + 2) * 2) * nCntY] = ((WALL_MAX_VTX_X + 1) + nCntX) + ((WALL_MAX_VTX_X + 1) * nCntY);
							pIdx[(nCntX * 2) + 1 + ((WALL_MAX_VTX_X + 2) * 2) * nCntY] = (0 + nCntX) + ((WALL_MAX_VTX_X + 1) * nCntY);
						}
					}
					//角被さりの頂点
					for (int nCntY = 0; nCntY < WALL_MAX_VTX_Y - 1; nCntY++)
					{
						pIdx[(((WALL_MAX_VTX_X + 1) * 2 + 0) * (nCntY + 1)) + (2 * nCntY)] = WALL_MAX_VTX_X + ((WALL_MAX_VTX_X + 1) * nCntY);
						pIdx[(((WALL_MAX_VTX_X + 1) * 2 + 1) * (nCntY + 1)) + (1 * nCntY)] = (WALL_MAX_VTX_X * 2 + 2) + ((WALL_MAX_VTX_X + 1) * nCntY);
					}
					pIdx += WALL_IDX_NUM_MAX;	//インデックスを進める
				}

				//インデックスバッファをアンロックする
				g_Field[nCntField].pIdxBuffFoeld->Unlock();
			}
			else if (g_Field[nCntField].aState == FORM_SEMICIRCLE)
			{
				
			}
			g_Field[nCntField].bUse = true;
			break;
		}
	}
}

//---------------------------
//当たり判定
//---------------------------
bool ColisionFeild(D3DXVECTOR3 *pos, D3DXVECTOR3 *posold, D3DXVECTOR3 *move, float fWidth, float fHeight, float fDepht, int nType)
{
	bool bLand = false;
	Field *pField;

	pField = GetField();

	for (int nCntField = 0; nCntField < MAX_FIELD; nCntField++, pField++)
	{
		if (pField->bUse == true)
		{
			if (pField->aState == FORM_FLOO)
			{
				if (pos->x + fWidth >= pField->Pos.x - pField->fWidth &&
					pos->x - fWidth <= pField->Pos.x + pField->fWidth)
				{
					if (pos->y <= pField->Pos.y)
					{
						move->y = 0.0f;
						pos->y = pField->Pos.y;
						bLand = true;
					}
				}
			}
		}
	}
	return bLand;
}

//---------------------------
//メッシュフィールドの情報
//---------------------------
Field *GetField(void)
{
	return &g_Field[0];
}