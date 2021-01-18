//ーーーーーーーーーーーーーーーーーーーーーーーーー
//壁の処理(Wall.cpp)
//Author：佐藤秀亮
//ーーーーーーーーーーーーーーーーーーーーーーーーー

#include "main.h"
#include "input.h"
#include "wall.h"
#include "Model.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexturewall[1] = {};//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffwall = NULL;//頂点バッファへのポインタ
LPDIRECT3DINDEXBUFFER9 g_pigxBuffMeshWall = NULL;


Wall g_wall[MAX_WALL];

//初期化処理
HRESULT InitWall(void)
{
	int nCntWall;
	LPDIRECT3DDEVICE9 pDevice;//デバイスのポインタ
	pDevice = GetDevice();//デバイスの取得

	for (nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		g_wall[nCntWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_wall[nCntWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_wall[nCntWall].fWhidth = 0;
		g_wall[nCntWall].fHight = 0;
		g_wall[nCntWall].bUse = false;
	}

	D3DXCreateTextureFromFile(pDevice, "date/TEXTURE/wall000.jpg", &g_pTexturewall[0]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 9 * MAX_WALL, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffwall, NULL);

	VERTEX_3D * pVtx;//頂点情報へのポインタ
	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffwall->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		//頂点の座標
		pVtx[0].pos = D3DXVECTOR3(g_wall[nCntWall].pos.x - (0 / 2), g_wall[nCntWall].pos.y + (0)	, g_wall[nCntWall].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_wall[nCntWall].pos.x		  , g_wall[nCntWall].pos.y + (0)	, g_wall[nCntWall].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_wall[nCntWall].pos.x + (0 / 2), g_wall[nCntWall].pos.y + (0)	, g_wall[nCntWall].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_wall[nCntWall].pos.x - (0 / 2), g_wall[nCntWall].pos.y + (0 / 2), g_wall[nCntWall].pos.z);
		pVtx[4].pos = D3DXVECTOR3(g_wall[nCntWall].pos.x		  , g_wall[nCntWall].pos.y + (0 / 2), g_wall[nCntWall].pos.z);
		pVtx[5].pos = D3DXVECTOR3(g_wall[nCntWall].pos.x + (0 / 2), g_wall[nCntWall].pos.y + (0 / 2), g_wall[nCntWall].pos.z);
		pVtx[6].pos = D3DXVECTOR3(g_wall[nCntWall].pos.x - (0 / 2), g_wall[nCntWall].pos.y			, g_wall[nCntWall].pos.z);
		pVtx[7].pos = D3DXVECTOR3(g_wall[nCntWall].pos.x		  , g_wall[nCntWall].pos.y			, g_wall[nCntWall].pos.z);
		pVtx[8].pos = D3DXVECTOR3(g_wall[nCntWall].pos.x + (0 / 2), g_wall[nCntWall].pos.y			, g_wall[nCntWall].pos.z);

		//ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[4].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[5].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[6].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[7].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[8].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//頂点の色
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[8].col = D3DCOLOR_RGBA(255, 255, 255, 255); 

		//テクスチャのUV座標
		pVtx[0].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);

		pVtx[6].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[7].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[8].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 9;
	}
	//頂点バッファをアンロック
	g_pVtxBuffwall->Unlock();

	pDevice->CreateIndexBuffer(sizeof(WORD) * 14, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pigxBuffMeshWall, NULL);

	WORD * pidx;
	g_pigxBuffMeshWall->Lock(0, 0, (void**)&pidx, 0);

	pidx[0] = 7;
	pidx[1] = 6;
	pidx[2] = 4;
	pidx[3] = 3;
	pidx[4] = 1;
	pidx[5] = 0;
	pidx[6] = 0;
	pidx[7] = 8;
	pidx[8] = 8;
	pidx[9] = 7;
	pidx[10] = 5;
	pidx[11] = 4;
	pidx[12] = 2;
	pidx[13] = 1;

	g_pigxBuffMeshWall->Unlock();


	return S_OK;
}

//終了処理
void UninitWall(void)//追加の可能性があるため項目は作っとく
{
	for (int nCntWall = 0; nCntWall < 1; nCntWall++)
	{
		//テクスチャの破棄
		if (g_pTexturewall != NULL)
		{
			g_pTexturewall[nCntWall]->Release();
			g_pTexturewall[nCntWall] = NULL;
		}

		//頂点バッファも破棄
		if (g_pVtxBuffwall != NULL)
		{
			g_pVtxBuffwall->Release();
			g_pVtxBuffwall = NULL;
		}

		//頂点バッファも破棄
		if (g_pigxBuffMeshWall != NULL)
		{
			g_pigxBuffMeshWall->Release();
			g_pigxBuffMeshWall = NULL;
		}
	}
}

//更新処理
void UpdateWall(void)//追加の可能性があるため項目は作っとく
{
	
}

//描画処理
void DrawWall(void)
{
	int nCntWall;
	LPDIRECT3DDEVICE9 pDevice;//デバイスのポインタ
	D3DXMATRIX mtxRot, mtxTrans;
	pDevice = GetDevice();//デバイスを取得する

	for (nCntWall = 0; nCntWall <= MAX_WALL; nCntWall++)
	{
		if (g_wall[nCntWall].bUse == true)
		{
			D3DXMatrixIdentity(&g_wall[nCntWall].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_wall[nCntWall].rot.y, g_wall[nCntWall].rot.x, g_wall[nCntWall].rot.z);
			D3DXMatrixMultiply(&g_wall[nCntWall].mtxWorld, &g_wall[nCntWall].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_wall[nCntWall].pos.x, g_wall[nCntWall].pos.y, g_wall[nCntWall].pos.z);
			D3DXMatrixMultiply(&g_wall[nCntWall].mtxWorld, &g_wall[nCntWall].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_wall[nCntWall].mtxWorld);

			//頂点バッファをデバイスのデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffwall, 0, sizeof(VERTEX_3D));

			//インデックスバッファデータストリーム
			pDevice->SetIndices(g_pigxBuffMeshWall);

			pDevice->SetFVF(FVF_VERTEX_3D);//頂点フォーマットの設定

			pDevice->SetTexture(0, g_pTexturewall[0]);//テクスチャの設定

			//ポリゴンの描画
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 9, 0, 12);

		}

	}

}

void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWhidth, float fHight, int ntype)
{
	VERTEX_3D*pVtx;//頂点情報へのポインタ
	int nCntWall;

	for (nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_wall[nCntWall].bUse == false)
		{
			g_wall[nCntWall].pos = pos;
			g_wall[nCntWall].rot = rot;

			
			//頂点バッファをロックし、頂点データへのポインタを取得
			g_pVtxBuffwall->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += (nCntWall * 9);

			//頂点の座標
			pVtx[0].pos = D3DXVECTOR3(g_wall[nCntWall].pos.x - (fWhidth / 2), g_wall[nCntWall].pos.y + (fHight)	   , g_wall[nCntWall].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_wall[nCntWall].pos.x				, g_wall[nCntWall].pos.y + (fHight)	   , g_wall[nCntWall].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_wall[nCntWall].pos.x + (fWhidth / 2), g_wall[nCntWall].pos.y + (fHight)	   , g_wall[nCntWall].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_wall[nCntWall].pos.x - (fWhidth / 2), g_wall[nCntWall].pos.y + (fHight / 2), g_wall[nCntWall].pos.z);
			pVtx[4].pos = D3DXVECTOR3(g_wall[nCntWall].pos.x				, g_wall[nCntWall].pos.y + (fHight / 2), g_wall[nCntWall].pos.z);
			pVtx[5].pos = D3DXVECTOR3(g_wall[nCntWall].pos.x + (fWhidth / 2), g_wall[nCntWall].pos.y + (fHight / 2), g_wall[nCntWall].pos.z);
			pVtx[6].pos = D3DXVECTOR3(g_wall[nCntWall].pos.x - (fWhidth / 2), g_wall[nCntWall].pos.y			   , g_wall[nCntWall].pos.z);
			pVtx[7].pos = D3DXVECTOR3(g_wall[nCntWall].pos.x				, g_wall[nCntWall].pos.y			   , g_wall[nCntWall].pos.z);
			pVtx[8].pos = D3DXVECTOR3(g_wall[nCntWall].pos.x + (fWhidth / 2), g_wall[nCntWall].pos.y			   , g_wall[nCntWall].pos.z);

			//ベクトルの設定
			pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[4].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[5].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[6].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[7].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[8].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

			//頂点の色
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[8].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			//テクスチャのUV座標
			pVtx[0].tex = D3DXVECTOR2(1.0f, 2.0f);
			pVtx[1].tex = D3DXVECTOR2(0.0f, 2.0f);
			pVtx[2].tex = D3DXVECTOR2(1.0f, 2.0f);

			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx[4].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[5].tex = D3DXVECTOR2(1.0f, 1.0f);

			pVtx[6].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[7].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[8].tex = D3DXVECTOR2(1.0f, 0.0f);

			//頂点バッファをアンロック
			g_pVtxBuffwall->Unlock();

			g_wall[nCntWall].fWhidth = fWhidth;
			g_wall[nCntWall].fHight = fHight;
			g_wall[nCntWall].bUse = true;

			break;
		}
	}
}

Wall *GetWall(void)
{
	return &g_wall[0];
}