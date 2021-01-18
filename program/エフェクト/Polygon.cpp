//ーーーーーーーーーーーーーーーーーーーーーーーーー

#include "main.h"
#include "input.h"
#include "Polygon.h"

#define POLYGON_SIZE_X (1000)
#define POLYGON_SIZE_Z (1000)

#define POLYGON_VRTEX (9)
#define POLYGON_INDEXBUFFER (14)

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexturePolygon = NULL;//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygon = NULL;//頂点バッファへのポインタ
LPDIRECT3DINDEXBUFFER9 g_pigxBuffMeshFeild = NULL;

D3DXVECTOR3 g_posPolygon;
D3DXVECTOR3 g_movepolygon;

D3DXVECTOR3 g_rotPolygon;
D3DXVECTOR3 g_rotmovePolygon;

D3DXMATRIX g_mtxWorldPolygon;

//初期化処理
HRESULT InitPolygon(void)
{

	LPDIRECT3DDEVICE9 pDevice;//デバイスのポインタ
	pDevice = GetDevice();//デバイスの取得
	
	g_posPolygon = D3DXVECTOR3(0.0f, -0.0f, 0.0f);
	g_movepolygon = D3DXVECTOR3(2.0f, 2.0f, 2.0f);

	g_rotPolygon = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotmovePolygon = D3DXVECTOR3(0.02f, 0.02f, 0.02f);
	D3DXCreateTextureFromFile(pDevice, "date/TEXTURE/field002.jpg", &g_pTexturePolygon);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * POLYGON_VRTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffPolygon, NULL);

	VERTEX_3D*pVtx;//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

	//頂点の座標
	pVtx[0].pos = D3DXVECTOR3(g_posPolygon.x - (POLYGON_SIZE_X / 2), g_posPolygon.y, g_posPolygon.z + (POLYGON_SIZE_Z / 2));
	pVtx[1].pos = D3DXVECTOR3(g_posPolygon.x					   , g_posPolygon.y, g_posPolygon.z + (POLYGON_SIZE_Z / 2));
	pVtx[2].pos = D3DXVECTOR3(g_posPolygon.x + (POLYGON_SIZE_X / 2), g_posPolygon.y, g_posPolygon.z + (POLYGON_SIZE_Z / 2));
	pVtx[3].pos = D3DXVECTOR3(g_posPolygon.x - (POLYGON_SIZE_X / 2), g_posPolygon.y, g_posPolygon.z);
	pVtx[4].pos = D3DXVECTOR3(g_posPolygon.x					   , g_posPolygon.y, g_posPolygon.z);
	pVtx[5].pos = D3DXVECTOR3(g_posPolygon.x + (POLYGON_SIZE_X / 2), g_posPolygon.y, g_posPolygon.z);
	pVtx[6].pos = D3DXVECTOR3(g_posPolygon.x - (POLYGON_SIZE_X / 2), g_posPolygon.y, g_posPolygon.z - (POLYGON_SIZE_Z / 2));
	pVtx[7].pos = D3DXVECTOR3(g_posPolygon.x					   , g_posPolygon.y, g_posPolygon.z - (POLYGON_SIZE_Z / 2));
	pVtx[8].pos = D3DXVECTOR3(g_posPolygon.x + (POLYGON_SIZE_X / 2), g_posPolygon.y, g_posPolygon.z - (POLYGON_SIZE_Z / 2));

	//ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVtx[4].nor = D3DXVECTOR3(0.0f,1.0f, 0.0f);
	pVtx[5].nor = D3DXVECTOR3(0.0f,1.0f, 0.0f);
	pVtx[6].nor = D3DXVECTOR3(0.0f,1.0f, 0.0f);
	pVtx[7].nor = D3DXVECTOR3(0.0f,1.0f, 0.0f);
	pVtx[8].nor = D3DXVECTOR3(0.0f,1.0f, 0.0f);

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

	//頂点バッファをアンロック
	g_pVtxBuffPolygon->Unlock();

	//インデックスバッファ作成
	pDevice->CreateIndexBuffer(sizeof(WORD) * POLYGON_INDEXBUFFER, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pigxBuffMeshFeild,NULL);

	WORD * pidx;
	g_pigxBuffMeshFeild->Lock(0, 0, (void**)&pidx, 0);

	pidx[0] = 3;
	pidx[1] = 0;
	pidx[2] = 4;
	pidx[3] = 1;
	pidx[4] = 5;
	pidx[5] = 2;
	pidx[6] = 2;
	pidx[7] = 6;
	pidx[8] = 6;
	pidx[9] = 3;
	pidx[10] = 7;
	pidx[11] = 4;
	pidx[12] = 8;
	pidx[13] = 5;

	g_pigxBuffMeshFeild->Unlock();

	return S_OK;
}

//終了処理
void UninitPolygon(void)//追加の可能性があるため項目は作っとく
{
	
	//テクスチャの破棄
	if (g_pTexturePolygon != NULL)
	{
		g_pTexturePolygon->Release();
		g_pTexturePolygon = NULL;
	}

	//頂点バッファも破棄
	if (g_pVtxBuffPolygon != NULL)
	{
		g_pVtxBuffPolygon->Release();
		g_pVtxBuffPolygon = NULL;
	}
	
	if (g_pigxBuffMeshFeild != NULL)
	{
		g_pigxBuffMeshFeild->Release();
		g_pigxBuffMeshFeild = NULL;
	}

}

//更新処理
void UpdatePolygon(void)//追加の可能性があるため項目は作っとく
{

}

//描画処理
void DrawPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスのポインタ
	D3DXMATRIX mtxRot, mtxTrans;
	pDevice = GetDevice();//デバイスを取得する

	D3DXMatrixIdentity (&g_mtxWorldPolygon);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot,g_rotPolygon.y,g_rotPolygon.x,g_rotPolygon.z);
	D3DXMatrixMultiply(&g_mtxWorldPolygon, &g_mtxWorldPolygon, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posPolygon.x, g_posPolygon.y, g_posPolygon.z);
	D3DXMatrixMultiply(&g_mtxWorldPolygon, &g_mtxWorldPolygon, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPolygon);

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPolygon, 0, sizeof(VERTEX_3D));
	//インデックスバッファデータストリーム
	pDevice->SetIndices(g_pigxBuffMeshFeild);

	pDevice->SetFVF(FVF_VERTEX_3D);//頂点フォーマットの設定

	pDevice->SetTexture(0, g_pTexturePolygon);//テクスチャの設定

	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, POLYGON_VRTEX, 0, POLYGON_INDEXBUFFER - 2);

}