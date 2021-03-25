//---------------------------
//インクルードファイル
//---------------------------
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cube.h"
#include "shadow.h"
#include "keyinput.h"

//---------------------------
//グローバル変数
//---------------------------
LPDIRECT3DTEXTURE9		g_pTextureCube[MAX_CUBE][MAX_CUBE_TEX];	//テクスチャへのポインタ
Cube				g_aCube[MAX_CUBE];	//敵の構造体

//---------------------------
//初期化処理
//---------------------------
HRESULT InitCube(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	pDevice = GetDevice();		//デバイスの取得

	for (int nCntCube = 0; nCntCube < MAX_CUBE; nCntCube++)
	{
		g_aCube[nCntCube].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCube[nCntCube].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCube[nCntCube].bCollision = false;
		g_aCube[nCntCube].bUse = false;

		//---------------------------
		//Xファイルの読み込み
		//---------------------------
		D3DXLoadMeshFromX(	"data/Model/cube/cube.x",
							D3DXMESH_SYSTEMMEM,
							pDevice,
							NULL,
							&g_aCube[nCntCube].pBuffMat,
							NULL,
							&g_aCube[nCntCube].pnNumMat,
							&g_aCube[nCntCube].pMesh);
		//---------------------------
		//テクスチャの抜き出し
		//---------------------------
		D3DXMATERIAL *pMat;	//マテリアルのポインタ

							//マテリアル情報のポインタ
		pMat = (D3DXMATERIAL*)g_aCube[nCntCube].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_aCube[nCntCube].pnNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				//テクスチャの読み込み
				D3DXCreateTextureFromFile(	pDevice,
											pMat[nCntMat].pTextureFilename,			//テクスチャ
											&g_pTextureCube[nCntCube][nCntMat]);
			}
		}
		//---------------------------
		//頂点座標の抜き出し
		//---------------------------
		int nNumVtx;	//頂点数
		DWORD sizeFVF;	//頂点フォーマットのサイズ
		BYTE *pVtxBuff;	//頂点バッファのポインタ

						//頂点数を取得
		nNumVtx = g_aCube[nCntCube].pMesh->GetNumVertices();

		//頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(g_aCube[nCntCube].pMesh->GetFVF());

		//頂点バッファのロック
		g_aCube[nCntCube].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//頂点座標の代入

			//頂点数を比較して最小値、最大値を抜く
			//X
			if (g_aCube[nCntCube].vtxMax.x <= vtx.x)
			{
				g_aCube[nCntCube].vtxMax.x = vtx.x;
			}
			if (g_aCube[nCntCube].vtxMin.x >= vtx.x)
			{
				g_aCube[nCntCube].vtxMin.x = vtx.x;
			}
			//Y
			if (g_aCube[nCntCube].vtxMax.y <= vtx.y)
			{
				g_aCube[nCntCube].vtxMax.y = vtx.y;
			}
			if (g_aCube[nCntCube].vtxMin.y >= vtx.y)
			{
				g_aCube[nCntCube].vtxMin.y = vtx.y;
			}
			//Z
			if (g_aCube[nCntCube].vtxMax.z <= vtx.z)
			{
				g_aCube[nCntCube].vtxMax.z = vtx.z;
			}
			if (g_aCube[nCntCube].vtxMin.z >= vtx.z)
			{
				g_aCube[nCntCube].vtxMin.z = vtx.z;
			}

			pVtxBuff += sizeFVF;	//頂点を進める
		}
		//頂点バッファをアンロック
		g_aCube[nCntCube].pMesh->UnlockVertexBuffer();
	}
	return S_OK;
}

//---------------------------
//終了処理
//---------------------------
void UninitCube(void)
{
	for (int nCntCube = 0; nCntCube < MAX_CUBE; nCntCube++)
	{
		//---------------------------
		//メッシュ破棄
		//---------------------------
		if (g_aCube[nCntCube].pMesh != NULL)
		{
			g_aCube[nCntCube].pMesh->Release();
			g_aCube[nCntCube].pMesh = NULL;
		}

		//---------------------------
		//マテリアル破棄
		//---------------------------
		if (g_aCube[nCntCube].pBuffMat != NULL)
		{
			g_aCube[nCntCube].pBuffMat->Release();
			g_aCube[nCntCube].pBuffMat = NULL;
		}
	}
}

//---------------------------
//更新処理
//---------------------------
void UpdateCube(void)
{

}

//---------------------------
//描画処理
//---------------------------
void DrawCube(void)
{
	LPDIRECT3DDEVICE9	pDevice;			//デバイスのポインタ

	pDevice = GetDevice();					//デバイスを取得する

	for (int nCntCube = 0; nCntCube < MAX_CUBE; nCntCube++)
	{
		if (g_aCube[nCntCube].bUse == true)
		{
			//-------------------------------
			//プレイヤー(原点)のマトリックスの設定
			//-------------------------------
			D3DXMATRIX			mtxRot, mtxTrans;	//計算用マトリックス

			if (g_aCube[nCntCube].bCollision == false)
			{
				pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
			}
			else
			{
				pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
			}

			D3DXMatrixIdentity(&g_aCube[nCntCube].mtxWold);	//マトリックス初期化

			//向きの設定
			D3DXMatrixRotationYawPitchRoll(	&mtxRot,
											g_aCube[nCntCube].rot.y,
											g_aCube[nCntCube].rot.x,
											g_aCube[nCntCube].rot.z);

			D3DXMatrixMultiply(	&g_aCube[nCntCube].mtxWold,
								&g_aCube[nCntCube].mtxWold,
								&mtxRot);
			//位置
			D3DXMatrixTranslation(	&mtxTrans,
									g_aCube[nCntCube].pos.x,
									g_aCube[nCntCube].pos.y,
									g_aCube[nCntCube].pos.z);

			D3DXMatrixMultiply(	&g_aCube[nCntCube].mtxWold,
								&g_aCube[nCntCube].mtxWold,
								&mtxTrans);
			//マトリックスの設定
			pDevice->SetTransform(	D3DTS_WORLD,
									&g_aCube[nCntCube].mtxWold);

			//---------------------------
			//描画処理
			//---------------------------
			D3DMATERIAL9		matDef;				//マテリアルの一時保存
			D3DXMATERIAL		*pMat;				//マテリアルデータのポインタ

			//現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			//マテリアルデータのポインタ
			pMat = (D3DXMATERIAL*)g_aCube[nCntCube].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aCube[nCntCube].pnNumMat; nCntMat++)
			{
				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//テクスチャの設定
				pDevice->SetTexture(	0,
										g_pTextureCube[nCntCube][nCntMat]);

				//モデルパーツの描画
				g_aCube[nCntCube].pMesh->DrawSubset(nCntMat);
			}
			//一時保存してたやつをもどす
			pDevice->SetMaterial(&matDef);
		}
	}
}

//---------------------------
//セット
//---------------------------
void SetCube(int nIdx, D3DXVECTOR3 rot, D3DXVECTOR3 pos, bool bCollision)
{
	g_aCube[nIdx].pos = pos;
	g_aCube[nIdx].rot = rot;
	g_aCube[nIdx].bCollision = bCollision;
}

int SetCubeUse(D3DXVECTOR3 rot, D3DXVECTOR3 pos, bool bCollision)
{
	int nIndex = -1;

	for (int nCntCube = 0; nCntCube < MAX_CUBE; nCntCube++)
	{
		if (g_aCube[nCntCube].bUse == false)
		{
			g_aCube[nCntCube].pos = pos;
			g_aCube[nCntCube].rot = rot;
			g_aCube[nCntCube].bCollision = bCollision;

			g_aCube[nCntCube].bUse = true;
			nIndex = nCntCube;
			break;
		}
	}
	return nIndex;
}

Cube *GetCube(void)
{
	return &g_aCube[0];
}

bool CollisionCude(D3DXVECTOR3 *pos, D3DXVECTOR3 *posold, D3DXVECTOR3 *move, float fWidth, float fHeight)
{
	bool bCollision = false;
	D3DXVECTOR3 posdfrc;
	D3DXVECTOR3 efectmove;
	float nGuysR = 50.0f;
	float fposdfrcX;

	posdfrc = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	for (int nCntCube = 0; nCntCube < MAX_CUBE; nCntCube++)
	{
		if (g_aCube[nCntCube].bUse == true)
		{
			posdfrc.x = g_aCube[nCntCube].pos.x - pos->x;
			posdfrc.z = g_aCube[nCntCube].pos.z - pos->z;

			posdfrc.x = posdfrc.x * posdfrc.x;
			posdfrc.z = posdfrc.z * posdfrc.z;

			fposdfrcX = posdfrc.x + posdfrc.z;

			fposdfrcX = sqrtf(fposdfrcX);

			if (g_aCube[nCntCube].pos.y <= pos->y + fHeight / 2 &&
				g_aCube[nCntCube].pos.y + g_aCube[nCntCube].fHight >= pos->y - fHeight / 2 &&
				fposdfrcX < nGuysR)
			{
				bCollision = true;
			}
		}
	}
	return bCollision;
}