//---------------------------
//インクルードファイル
//---------------------------
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "turret.h"
#include "shadow.h"
#include "keyinput.h"
#include "girl.h"

//---------------------------
//グローバル変数
//---------------------------
Turret				g_aTurret[MAX_TURRET];	//敵の構造体

//---------------------------
//初期化処理
//---------------------------
HRESULT InitTurret(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	pDevice = GetDevice();		//デバイスの取得

	for (int nCntTurret = 0; nCntTurret < MAX_TURRET; nCntTurret++)
	{
		g_aTurret[nCntTurret].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTurret[nCntTurret].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTurret[nCntTurret].bCollision = false;
		g_aTurret[nCntTurret].bUse = false;

		//---------------------------
		//Xファイルの読み込み
		//---------------------------
		D3DXLoadMeshFromX(	"data/Model/turret/turret.x",
							D3DXMESH_SYSTEMMEM,
							pDevice,
							NULL,
							&g_aTurret[nCntTurret].pBuffMat,
							NULL,
							&g_aTurret[nCntTurret].pnNumMat,
							&g_aTurret[nCntTurret].pMesh);
		//---------------------------
		//頂点座標の抜き出し
		//---------------------------
		int nNumVtx;	//頂点数
		DWORD sizeFVF;	//頂点フォーマットのサイズ
		BYTE *pVtxBuff;	//頂点バッファのポインタ

		//頂点数を取得
		nNumVtx = g_aTurret[nCntTurret].pMesh->GetNumVertices();

		//頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(g_aTurret[nCntTurret].pMesh->GetFVF());

		//頂点バッファのロック
		g_aTurret[nCntTurret].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//頂点座標の代入

			//頂点数を比較して最小値、最大値を抜く
			//X
			if (g_aTurret[nCntTurret].vtxMax.x <= vtx.x)
			{
				g_aTurret[nCntTurret].vtxMax.x = vtx.x;
			}
			if (g_aTurret[nCntTurret].vtxMin.x >= vtx.x)
			{
				g_aTurret[nCntTurret].vtxMin.x = vtx.x;
			}
			//Y
			if (g_aTurret[nCntTurret].vtxMax.y <= vtx.y)
			{
				g_aTurret[nCntTurret].vtxMax.y = vtx.y;
			}
			if (g_aTurret[nCntTurret].vtxMin.y >= vtx.y)
			{
				g_aTurret[nCntTurret].vtxMin.y = vtx.y;
			}
			//Z
			if (g_aTurret[nCntTurret].vtxMax.z <= vtx.z)
			{
				g_aTurret[nCntTurret].vtxMax.z = vtx.z;
			}
			if (g_aTurret[nCntTurret].vtxMin.z >= vtx.z)
			{
				g_aTurret[nCntTurret].vtxMin.z = vtx.z;
			}

			pVtxBuff += sizeFVF;	//頂点を進める
		}
		//頂点バッファをアンロック
		g_aTurret[nCntTurret].pMesh->UnlockVertexBuffer();
	}
	return S_OK;
}

//---------------------------
//終了処理
//---------------------------
void UninitTurret(void)
{
	for (int nCntTurret = 0; nCntTurret < MAX_TURRET; nCntTurret++)
	{
		//---------------------------
		//メッシュ破棄
		//---------------------------
		if (g_aTurret[nCntTurret].pMesh != NULL)
		{
			g_aTurret[nCntTurret].pMesh->Release();
			g_aTurret[nCntTurret].pMesh = NULL;
		}

		//---------------------------
		//マテリアル破棄
		//---------------------------
		if (g_aTurret[nCntTurret].pBuffMat != NULL)
		{
			g_aTurret[nCntTurret].pBuffMat->Release();
			g_aTurret[nCntTurret].pBuffMat = NULL;
		}
	}
}

//---------------------------
//更新処理
//---------------------------
void UpdateTurret(void)
{

}

//---------------------------
//描画処理
//---------------------------
void DrawTurret(void)
{
	LPDIRECT3DDEVICE9	pDevice;			//デバイスのポインタ

	pDevice = GetDevice();					//デバイスを取得する

	for (int nCntTurret = 0; nCntTurret < MAX_TURRET; nCntTurret++)
	{
		if (g_aTurret[nCntTurret].bUse == true)
		{
			//-------------------------------
			//プレイヤー(原点)のマトリックスの設定
			//-------------------------------
			D3DXMATRIX			mtxRot, mtxTrans;	//計算用マトリックス

			if (g_aTurret[nCntTurret].bCollision == false)
			{
				pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
			}
			else
			{
				pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
			}

			D3DXMatrixIdentity(&g_aTurret[nCntTurret].mtxWold);	//マトリックス初期化

			//向きの設定
			D3DXMatrixRotationYawPitchRoll(	&mtxRot,
											g_aTurret[nCntTurret].rot.y,
											g_aTurret[nCntTurret].rot.x,
											g_aTurret[nCntTurret].rot.z);

			D3DXMatrixMultiply(	&g_aTurret[nCntTurret].mtxWold,
								&g_aTurret[nCntTurret].mtxWold,
								&mtxRot);
			//位置
			D3DXMatrixTranslation(	&mtxTrans,
									g_aTurret[nCntTurret].pos.x,
									g_aTurret[nCntTurret].pos.y,
									g_aTurret[nCntTurret].pos.z);

			D3DXMatrixMultiply(	&g_aTurret[nCntTurret].mtxWold,
								&g_aTurret[nCntTurret].mtxWold,
								&mtxTrans);
			//マトリックスの設定
			pDevice->SetTransform(	D3DTS_WORLD,
									&g_aTurret[nCntTurret].mtxWold);

			//---------------------------
			//描画処理
			//---------------------------
			D3DMATERIAL9		matDef;				//マテリアルの一時保存
			D3DXMATERIAL		*pMat;				//マテリアルデータのポインタ

			//現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			//マテリアルデータのポインタ
			pMat = (D3DXMATERIAL*)g_aTurret[nCntTurret].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aTurret[nCntTurret].pnNumMat; nCntMat++)
			{
				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//テクスチャの設定
				pDevice->SetTexture(	0,
										NULL);

				//モデルパーツの描画
				g_aTurret[nCntTurret].pMesh->DrawSubset(nCntMat);
			}
			//一時保存してたやつをもどす
			pDevice->SetMaterial(&matDef);
		}
	}
}

//---------------------------
//セット
//---------------------------
void SetTurret(int nIdx, D3DXVECTOR3 rot, D3DXVECTOR3 pos, bool bCollision)
{
	g_aTurret[nIdx].pos = pos;
	g_aTurret[nIdx].rot = rot;
	g_aTurret[nIdx].bCollision = bCollision;
}

int SetTurretUse(D3DXVECTOR3 rot, D3DXVECTOR3 pos, bool bCollision)
{
	int nIndex = -1;

	for (int nCntTurret = 0; nCntTurret < MAX_TURRET; nCntTurret++)
	{
		if (g_aTurret[nCntTurret].bUse == false)
		{
			g_aTurret[nCntTurret].pos = pos;
			g_aTurret[nCntTurret].rot = rot;
			g_aTurret[nCntTurret].bCollision = bCollision;

			g_aTurret[nCntTurret].bUse = true;
			nIndex = nCntTurret;
			break;
		}
	}
	return nIndex;
}

Turret *GetTurret(void)
{
	return &g_aTurret[0];
}

bool ColisionTurret(D3DXVECTOR3 *pos, D3DXVECTOR3 *posold, D3DXVECTOR3 *move, float fWidth, float fHeight, float fDepht, int nType)
{
	return true;
}