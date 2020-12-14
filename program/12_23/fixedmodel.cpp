//---------------------------
//インクルードファイル
//---------------------------
#include "fixedmodel.h"
#include "shadow.h"
#include "model.h"

//---------------------------
//グローバル変数
//---------------------------
LPDIRECT3DTEXTURE9		g_apTextureFixemodel[MAX_FIXED_MODEL][MAX_FIXEMODEL_TEX] = {};	//テクスチャのポインタ
Fixedmodel				g_aFixedmodel[MAX_FIXED_MODEL];	//モデルの構造体

//---------------------------
//初期化処理
//---------------------------
HRESULT InitFixedModel(void)
{
	LPDIRECT3DDEVICE9	pDevice;	//デバイスへのポインタ

	pDevice = GetDevice();			//デバイスの取得

	for (int nCntModel = 0; nCntModel < MAX_FIXED_MODEL; nCntModel++)
	{
		//位置向き初期化
		g_aFixedmodel[nCntModel].PosModel = (D3DXVECTOR3(-500.0f, 0.0f, 0.0f));
		g_aFixedmodel[nCntModel].RotModel = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		g_aFixedmodel[nCntModel].vtxMaxModel = (D3DXVECTOR3(-1000000.0f, -1000000.0f, -1000000.0f));
		g_aFixedmodel[nCntModel].vtxMinModel = (D3DXVECTOR3(1000000.0f, 1000000.0f, 1000000.0f));
		g_aFixedmodel[nCntModel].pMeshFixedmodel = {};
		g_aFixedmodel[nCntModel].pBuffMatFixedmodel = {};
		g_aFixedmodel[nCntModel].nIdex = 0;
		g_aFixedmodel[nCntModel].bUse = false;
	}

	return S_OK;
}

//---------------------------
//終了処理
//---------------------------
void UninitFixedModel(void)
{
	for (int nCntModel = 0; nCntModel < MAX_FIXED_MODEL; nCntModel++)
	{
		//---------------------------
		//メッシュ破棄
		//---------------------------
		if (g_aFixedmodel[nCntModel].pMeshFixedmodel != NULL)
		{
			g_aFixedmodel[nCntModel].pMeshFixedmodel->Release();
			g_aFixedmodel[nCntModel].pMeshFixedmodel = NULL;
		}

		//---------------------------
		//マテリアル破棄
		//---------------------------
		if (g_aFixedmodel[nCntModel].pBuffMatFixedmodel != NULL)
		{
			g_aFixedmodel[nCntModel].pBuffMatFixedmodel->Release();
			g_aFixedmodel[nCntModel].pBuffMatFixedmodel = NULL;
		}
	}
}

//---------------------------
//更新処理
//---------------------------
void UpdateFixedModel(void)
{
	Model *pModel;

	pModel = GetModel();

	for (int nCntModel = 0; nCntModel < MAX_FIXED_MODEL; nCntModel++)
	{
		if (g_aFixedmodel[nCntModel].bUse == true)
		{
			
		}
	}
}

//---------------------------
//描画処理
//---------------------------
void DrawFixedModel(void)
{
	LPDIRECT3DDEVICE9	pDevice;			//デバイスのポインタ

	pDevice = GetDevice();					//デバイスを取得する

	//---------------------------
	//マトリックスの設定
	//---------------------------
	D3DXMATRIX			mtxRot, mtxTrans;	//計算用マトリックス

	for (int nCntModel = 0; nCntModel < MAX_FIXED_MODEL; nCntModel++)
	{
		if (g_aFixedmodel[nCntModel].bUse == true)
		{
			//αテスト
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

			D3DXMatrixIdentity(&g_aFixedmodel[nCntModel].mtxWoldModel);	//マトリックス初期化

			//向きの設定
			D3DXMatrixRotationYawPitchRoll(	&mtxRot,
											g_aFixedmodel[nCntModel].RotModel.y,
											g_aFixedmodel[nCntModel].RotModel.x,
											g_aFixedmodel[nCntModel].RotModel.z);

			D3DXMatrixMultiply(	&g_aFixedmodel[nCntModel].mtxWoldModel,
								&g_aFixedmodel[nCntModel].mtxWoldModel,
								&mtxRot);
			//位置
			D3DXMatrixTranslation(	&mtxTrans,
									g_aFixedmodel[nCntModel].PosModel.x,
									g_aFixedmodel[nCntModel].PosModel.y,
									g_aFixedmodel[nCntModel].PosModel.z);

			D3DXMatrixMultiply(	&g_aFixedmodel[nCntModel].mtxWoldModel,
								&g_aFixedmodel[nCntModel].mtxWoldModel,
								&mtxTrans);
			//マトリックスの設定
			pDevice->SetTransform(	D3DTS_WORLD,
									&g_aFixedmodel[nCntModel].mtxWoldModel);
			//---------------------------
			//描画処理
			//---------------------------
			D3DMATERIAL9		matDef;				//マテリアルの一時保存
			D3DXMATERIAL		*pMat;				//マテリアルデータのポインタ

													//現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			//マテリアルデータのポインタ
			pMat = (D3DXMATERIAL*)g_aFixedmodel[nCntModel].pBuffMatFixedmodel->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aFixedmodel[nCntModel].pnNumMatModel; nCntMat++)
			{
				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//テクスチャの設定
				pDevice->SetTexture(	0,
										g_apTextureFixemodel[nCntModel][nCntMat]);

				//モデルパーツの描画
				g_aFixedmodel[nCntModel].pMeshFixedmodel->DrawSubset(nCntMat);
			}
			//一時保存してたやつをもどす
			pDevice->SetMaterial(&matDef);

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
void SetFixedModel(D3DXVECTOR3 PosModel, D3DXVECTOR3 RotModel, MODEL_TYPE Type)
{
	LPDIRECT3DDEVICE9	pDevice;	//デバイスへのポインタ

	pDevice = GetDevice();			//デバイスの取得

	for (int nCntModel = 0; nCntModel < MAX_FIXED_MODEL; nCntModel++)
	{
		if (g_aFixedmodel[nCntModel].bUse == false)
		{
			g_aFixedmodel[nCntModel].PosModel = PosModel;
			g_aFixedmodel[nCntModel].RotModel = RotModel;
			g_aFixedmodel[nCntModel].aType = Type;

			if (g_aFixedmodel[nCntModel].aType == MODEL_HERTS)
			{
				//---------------------------
				//Xファイルの読み込み
				//---------------------------
				D3DXLoadMeshFromX(	"data/Model/Herts.x",
									D3DXMESH_SYSTEMMEM,
									pDevice,
									NULL,
									&g_aFixedmodel[nCntModel].pBuffMatFixedmodel,
									NULL,
									&g_aFixedmodel[nCntModel].pnNumMatModel,
									&g_aFixedmodel[nCntModel].pMeshFixedmodel);
			}
			else if (g_aFixedmodel[nCntModel].aType == MODEL_CAT)
			{
				//---------------------------
				//Xファイルの読み込み
				//---------------------------
				D3DXLoadMeshFromX(	"data/Model/Cat.x",
									D3DXMESH_SYSTEMMEM,
									pDevice,
									NULL,
									&g_aFixedmodel[nCntModel].pBuffMatFixedmodel,
									NULL,
									&g_aFixedmodel[nCntModel].pnNumMatModel,
									&g_aFixedmodel[nCntModel].pMeshFixedmodel);
			}
			//---------------------------
			//テクスチャの抜き出し
			//---------------------------
			D3DXMATERIAL *pMat;	//マテリアルのポインタ

			//マテリアル情報のポインタ
			pMat = (D3DXMATERIAL*)g_aFixedmodel[nCntModel].pBuffMatFixedmodel->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aFixedmodel[nCntModel].pnNumMatModel; nCntMat++)
			{
				if (pMat[nCntMat].pTextureFilename != NULL)
				{
					//テクスチャの読み込み
					D3DXCreateTextureFromFile(	pDevice,
												pMat[nCntMat].pTextureFilename,			//テクスチャ
												&g_apTextureFixemodel[nCntModel][nCntMat]);
				}
			}

			//---------------------------
			//頂点座標の抜き出し
			//---------------------------
			int nNumVtx;	//頂点数
			DWORD sizeFVF;	//頂点フォーマットのサイズ
			BYTE *pVtxBuff;	//頂点バッファのポインタ

			//頂点数を取得
			nNumVtx = g_aFixedmodel[nCntModel].pMeshFixedmodel->GetNumVertices();

			//頂点フォーマットのサイズを取得
			sizeFVF = D3DXGetFVFVertexSize(g_aFixedmodel[nCntModel].pMeshFixedmodel->GetFVF());

			//頂点バッファのロック
			g_aFixedmodel[nCntModel].pMeshFixedmodel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
			{
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//頂点座標の代入

				//頂点数を比較して最小値、最大値を抜く
				//X
				if (g_aFixedmodel[nCntModel].vtxMaxModel.x <= vtx.x)
				{
					g_aFixedmodel[nCntModel].vtxMaxModel.x = vtx.x;
				}
				if (g_aFixedmodel[nCntModel].vtxMinModel.x >= vtx.x)
				{
					g_aFixedmodel[nCntModel].vtxMinModel.x = vtx.x;
				}
				//Y
				if (g_aFixedmodel[nCntModel].vtxMaxModel.y <= vtx.y)
				{
					g_aFixedmodel[nCntModel].vtxMaxModel.y = vtx.y;
				}
				if (g_aFixedmodel[nCntModel].vtxMinModel.y >= vtx.y)
				{
					g_aFixedmodel[nCntModel].vtxMinModel.y = vtx.y;
				}
				//Z
				if (g_aFixedmodel[nCntModel].vtxMaxModel.z <= vtx.z)
				{
					g_aFixedmodel[nCntModel].vtxMaxModel.z = vtx.z;
				}
				if (g_aFixedmodel[nCntModel].vtxMinModel.z >= vtx.z)
				{
					g_aFixedmodel[nCntModel].vtxMinModel.z = vtx.z;
				}

				pVtxBuff += sizeFVF;	//頂点を進める
			}
			//頂点バッファをアンロック
			g_aFixedmodel[nCntModel].pMeshFixedmodel->UnlockVertexBuffer();
			g_aFixedmodel[nCntModel].nIdex = SetShadow(g_aFixedmodel[nCntModel].PosModel, g_aFixedmodel[nCntModel].vtxMaxModel.x * 4, g_aFixedmodel[nCntModel].vtxMaxModel.z * 4);
			g_aFixedmodel[nCntModel].bUse = true;
			break;
		}
	}
}