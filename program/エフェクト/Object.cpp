//ーーーーーーーーーーーーーーーーーーーーーーーーー
//モデルの処理(Object.cpp)
//Author：佐藤秀亮
//ーーーーーーーーーーーーーーーーーーーーーーーーー

#include "main.h"
#include "Object.h"
#include "Shadow.h"
#include "camera.h"
#include "Effect.h"

//グローバル変数
LPD3DXMESH g_pMeshObject[MAX_OBJECT] = {};//メッシュへのポインタ
LPD3DXBUFFER g_pBuffMatObject[MAX_OBJECT] = {};//マテリアルへのポインタ
DWORD g_nNumMatObject[MAX_OBJECT] = {};		//マテリアルの数

LPDIRECT3DTEXTURE9 g_pTextueObject[MAX_OBJECT][64] = {};//テクスチャ

Object g_Object[MAX_OBJECT];

//初期化処理
void InitObject(void)
{

	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		g_Object[nCntObject].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Object[nCntObject].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Object[nCntObject].Color = D3DXCOLOR(255, 255, 255, 255);

		g_Object[nCntObject].VtxMaxObject = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Object[nCntObject].VtxMinObject = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		g_Object[nCntObject].ntype = 0;
		g_Object[nCntObject].bUse = false;
	}
	
}

//終了処理
void UninitObject(void)//追加の可能性があるため項目は作っとく
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		//オブジェクトの破棄
		if (g_pMeshObject[nCntObject] != NULL)
		{
			g_pMeshObject[nCntObject]->Release();
			g_pMeshObject[nCntObject] = NULL;
		}
		//頂点バッファも破棄
		if (g_pBuffMatObject[nCntObject] != NULL)
		{
			g_pBuffMatObject[nCntObject]->Release();
			g_pBuffMatObject[nCntObject] = NULL;
		}
	}
	
}

//更新処理
void UpdateObject(void)//追加の可能性があるため項目は作っとく
{

}

//描画処理
void DrawObject(void)
{

	LPDIRECT3DDEVICE9 pDevice;//デバイスのポインタ
	pDevice = GetDevice();//デバイスを取得する
	D3DXMATRIX mtxRot, mtxTrans;//計算用マトリックス

	D3DMATERIAL9 matDef;//現在のマテリアル保存
	D3DXMATERIAL *pMat;//マテリアルデータポインタ

	D3DCOLORVALUE *pMatColor;

	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (g_Object[nCntObject].bUse == true)
		{
			D3DXMatrixIdentity(&g_Object[nCntObject].mtxObject);//ワールドマトリックスの初期化

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Object[nCntObject].rot.y, g_Object[nCntObject].rot.x, g_Object[nCntObject].rot.z);
			D3DXMatrixMultiply(&g_Object[nCntObject].mtxObject, &g_Object[nCntObject].mtxObject, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Object[nCntObject].pos.x, g_Object[nCntObject].pos.y, g_Object[nCntObject].pos.z);
			D3DXMatrixMultiply(&g_Object[nCntObject].mtxObject, &g_Object[nCntObject].mtxObject, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Object[nCntObject].mtxObject);

			//現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			//マテリアルデータの取得
			pMat = (D3DXMATERIAL*)g_pBuffMatObject[nCntObject]->GetBufferPointer();
			pMatColor = (D3DCOLORVALUE*)g_pBuffMatObject[nCntObject]->GetBufferPointer();

			//パーツ分回す
			for (int nCntMat = 0; nCntMat < (int)g_nNumMatObject[nCntObject]; nCntMat++)
			{
				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				//テクスチャの設定
				pDevice->SetTexture(0, g_pTextueObject[nCntObject][nCntMat]);
				
				//モデルパーツの描画
				g_pMeshObject[nCntObject]->DrawSubset(nCntMat);
				
			}
		}
	}
	//保存したマテリアル戻す
	pDevice->SetMaterial(&matDef);

}

//オブジェクトの設定処理
void SetObject(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int ntype)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//デバイスのポインタ
	
	int nNumVtx; //頂点数
	DWORD sizeFVF; //頂点フォーマットのサイズ
	BYTE *pVtxBuff; //頂点バッファへのポインタ
	D3DXMATERIAL * pMat;//マテリアルポインタ

	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (g_Object[nCntObject].bUse == false)
		{
			
				g_Object[nCntObject].pos = pos;
				g_Object[nCntObject].ntype = ntype;
				g_Object[nCntObject].rot = rot;

				if (g_Object[nCntObject].ntype == OBJECTTYPE_TANK)
				{
					//xファイルの読み込み
					D3DXLoadMeshFromX("date/Model/Tank.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatObject[nCntObject], NULL, &g_nNumMatObject[nCntObject], &g_pMeshObject[nCntObject]);
				}

				else if (g_Object[nCntObject].ntype == OBJECTTYPE_SANDBAG)
				{
					//xファイルの読み込み
					D3DXLoadMeshFromX("date/Model/Sandbag.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatObject[nCntObject], NULL, &g_nNumMatObject[nCntObject], &g_pMeshObject[nCntObject]);
				}

				else if (g_Object[nCntObject].ntype == OBJECTTYPE_BLOCK00)
				{
					//xファイルの読み込み
					D3DXLoadMeshFromX("date/Model/Block.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatObject[nCntObject], NULL, &g_nNumMatObject[nCntObject], &g_pMeshObject[nCntObject]);
				}

				else if (g_Object[nCntObject].ntype == OBJECTTYPE_BLOCK01)
				{
					//xファイルの読み込み
					D3DXLoadMeshFromX("date/Model/Block01.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatObject[nCntObject], NULL, &g_nNumMatObject[nCntObject], &g_pMeshObject[nCntObject]);
				}

				//マテリアルデータの取得
				pMat = (D3DXMATERIAL*)g_pBuffMatObject[nCntObject]->GetBufferPointer();
				for (int nCantMat = 0; nCantMat < g_nNumMatObject[nCntObject]; nCantMat++)
				{
					if (pMat[nCantMat].pTextureFilename != NULL)
					{
						D3DXCreateTextureFromFile(pDevice, pMat[nCantMat].pTextureFilename, &g_pTextueObject[nCntObject][nCantMat]);
					}
				}

					//頂点数の取得
					nNumVtx = g_pMeshObject[nCntObject]->GetNumVertices();

					//頂点フォーマットのサイズを取得
					sizeFVF = D3DXGetFVFVertexSize(g_pMeshObject[nCntObject]->GetFVF());

					//頂点バッファロック
					g_pMeshObject[nCntObject]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

					//大きさの確認
					for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
					{
						D3DXVECTOR3 Vtx = *(D3DXVECTOR3*)pVtxBuff;//頂点座標代入
	
						//***************************************
						//X軸
						//***************************************
						//比較対象がMaxより大きかったら
						if (Vtx.x > g_Object[nCntObject].VtxMaxObject.x)
						{
							g_Object[nCntObject].VtxMaxObject.x = Vtx.x + MAX_COLLISION;
						}
						//比較対象がMinより小さかったら
						if (Vtx.x < g_Object[nCntObject].VtxMinObject.x)
						{
							g_Object[nCntObject].VtxMinObject.x = Vtx.x - MIN_COLLISION;
						}

						//***************************************
						//Y軸
						//***************************************
						//比較対象がMaxより大きかったら
						if (Vtx.y > g_Object[nCntObject].VtxMaxObject.y)
						{
							g_Object[nCntObject].VtxMaxObject.y = Vtx.y + MAX_COLLISION;
						}
						//比較対象がMinより小さかったら
						if (Vtx.y < g_Object[nCntObject].VtxMinObject.y)
						{
							g_Object[nCntObject].VtxMinObject.y = Vtx.y - MIN_COLLISION;
						}

						//***************************************
						//Z軸
						//***************************************
						//比較対象がMaxより大きかったら
						if (Vtx.z > g_Object[nCntObject].VtxMaxObject.z)
						{
							g_Object[nCntObject].VtxMaxObject.z = Vtx.z + MAX_COLLISION;
						}
						//比較対象がMinより小さかったら
						if (Vtx.z < g_Object[nCntObject].VtxMinObject.z)
						{
							g_Object[nCntObject].VtxMinObject.z = Vtx.z - MIN_COLLISION;
						}

						pVtxBuff += sizeFVF;//比較対象の変更
					}

					//頂点バッファアンロック
					g_pMeshObject[nCntObject]->UnlockVertexBuffer();
					g_Object[nCntObject].bUse = true;
			break;
		}

	}
}

Object *GetObject(void)
{
	return &g_Object[0];
}

//#endif