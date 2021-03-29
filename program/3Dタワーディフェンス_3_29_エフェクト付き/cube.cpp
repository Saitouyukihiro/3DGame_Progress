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
#include "camara.h"

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
		g_aCube[nCntCube].g_bLoop = true;

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

		g_aCube[nCntCube].vertexpos[0] = D3DXVECTOR3(-g_aCube[nCntCube].vtxMax.x, g_aCube[nCntCube].vtxMax.y, g_aCube[nCntCube].vtxMax.z);
		g_aCube[nCntCube].vertexpos[1] = D3DXVECTOR3(g_aCube[nCntCube].vtxMax.x, g_aCube[nCntCube].vtxMax.y, g_aCube[nCntCube].vtxMax.z);
		g_aCube[nCntCube].vertexpos[2] = D3DXVECTOR3(-g_aCube[nCntCube].vtxMax.x, g_aCube[nCntCube].vtxMax.y, -g_aCube[nCntCube].vtxMax.z);
		g_aCube[nCntCube].vertexpos[3] = D3DXVECTOR3(g_aCube[nCntCube].vtxMax.x, g_aCube[nCntCube].vtxMax.y, -g_aCube[nCntCube].vtxMax.z);
		g_aCube[nCntCube].vertexpos[4] = D3DXVECTOR3(-g_aCube[nCntCube].vtxMax.x, -g_aCube[nCntCube].vtxMax.y, g_aCube[nCntCube].vtxMax.z);
		g_aCube[nCntCube].vertexpos[5] = D3DXVECTOR3(g_aCube[nCntCube].vtxMax.x, -g_aCube[nCntCube].vtxMax.y, g_aCube[nCntCube].vtxMax.z);
		g_aCube[nCntCube].vertexpos[6] = D3DXVECTOR3(-g_aCube[nCntCube].vtxMax.x, -g_aCube[nCntCube].vtxMax.y, -g_aCube[nCntCube].vtxMax.z);
		g_aCube[nCntCube].vertexpos[7] = D3DXVECTOR3(g_aCube[nCntCube].vtxMax.x, -g_aCube[nCntCube].vtxMax.y, -g_aCube[nCntCube].vtxMax.z);
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
				pDevice->SetTexture(0,
					g_pTextureCube[nCntCube][nCntMat]);

				//モデルパーツの描画
				g_aCube[nCntCube].pMesh->DrawSubset(nCntMat);
			}
			//一時保存してたやつをもどす
			pDevice->SetMaterial(&matDef);

			for (int nCntVtx = 0; nCntVtx < 8; nCntVtx++)
			{
				D3DXMATRIX			mtxvtxRot, mtxvtxTrans;	//計算用マトリックス
				D3DXMATRIX			mtxParent;

				D3DXMatrixIdentity(&g_aCube[nCntCube].vertexmtxWold[nCntVtx]);	//マトリックス初期化

				//向きの設定
				D3DXMatrixRotationYawPitchRoll(&mtxvtxRot,
					g_aCube[nCntCube].vertexrot[nCntVtx].y,
					g_aCube[nCntCube].vertexrot[nCntVtx].x,
					g_aCube[nCntCube].vertexrot[nCntVtx].z);

				D3DXMatrixMultiply(&g_aCube[nCntCube].vertexmtxWold[nCntVtx],
					&g_aCube[nCntCube].vertexmtxWold[nCntVtx],
					&mtxvtxRot);
				//位置
				D3DXMatrixTranslation(&mtxvtxTrans,
					g_aCube[nCntCube].vertexpos[nCntVtx].x,
					g_aCube[nCntCube].vertexpos[nCntVtx].y,
					g_aCube[nCntCube].vertexpos[nCntVtx].z);

				D3DXMatrixMultiply(&g_aCube[nCntCube].vertexmtxWold[nCntVtx],
					&g_aCube[nCntCube].vertexmtxWold[nCntVtx],
					&mtxvtxTrans);

				//パーツのワールドマトリックスと親のワールドマトリックスを掛け合わせる
				D3DXMatrixMultiply(&g_aCube[nCntCube].vertexmtxWold[nCntVtx],
					&g_aCube[nCntCube].vertexmtxWold[nCntVtx],
					&g_aCube[nCntCube].mtxWold);

				mtxParent = g_aCube[nCntCube].mtxWold;

				//マトリックスの設定
				pDevice->SetTransform(D3DTS_WORLD,
					&g_aCube[nCntCube].vertexmtxWold[nCntVtx]);
			}
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

void SetCube(D3DXVECTOR3 rot, D3DXVECTOR3 pos)
{
	for (int nCntCube = 0; nCntCube < MAX_CUBE; nCntCube++)
	{
		if (g_aCube[nCntCube].bUse == false)
		{
			g_aCube[nCntCube].pos = pos;
			g_aCube[nCntCube].rot = rot;

			g_aCube[nCntCube].bUse = true;
			g_aCube[nCntCube].bCollision = true;
			break;
		}
	}
}

bool CollisionCude(D3DXVECTOR3 *pos, D3DXVECTOR3 *posold, D3DXVECTOR3 *move, float fRadiou)
{
	Camera *pCamera = GetCamera();
	Cube *pCube = GetCube();
	D3DXVECTOR3 vec[4];
	D3DXVECTOR3 pvec[4];
	D3DXVECTOR3 poldvec[4];
	LPDIRECT3DDEVICE9	pDevice; //デバイスのポインタ
	float fask[4];
	float faskold[4];

	pDevice = GetDevice();	//デバイスを取得する

	for (int nCnt4 = 0; nCnt4 < 4; nCnt4++)
	{
		vec[nCnt4] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pvec[nCnt4] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		poldvec[nCnt4] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		fask[nCnt4] = 0.0f;
	}

	for (int nCntCube = 0; nCntCube < MAX_CUBE; nCntCube++, pCube++)
	{
		if (g_aCube[nCntCube].bUse == true)
		{	
			if (g_aCube[nCntCube].g_bLoop == true)
			{
				g_aCube[nCntCube].vertexpos[0].x -= fRadiou;
				g_aCube[nCntCube].vertexpos[0].z += fRadiou;

				g_aCube[nCntCube].vertexpos[1].x += fRadiou;
				g_aCube[nCntCube].vertexpos[1].z += fRadiou;

				g_aCube[nCntCube].vertexpos[2].x -= fRadiou;
				g_aCube[nCntCube].vertexpos[2].z -= fRadiou;

				g_aCube[nCntCube].vertexpos[3].x += fRadiou;
				g_aCube[nCntCube].vertexpos[3].z -= fRadiou;

				g_aCube[nCntCube].vertexpos[4].x -= fRadiou;
				g_aCube[nCntCube].vertexpos[4].z += fRadiou;

				g_aCube[nCntCube].vertexpos[5].x += fRadiou;
				g_aCube[nCntCube].vertexpos[5].z += fRadiou;

				g_aCube[nCntCube].vertexpos[6].x -= fRadiou;
				g_aCube[nCntCube].vertexpos[6].z -= fRadiou;

				g_aCube[nCntCube].vertexpos[7].x += fRadiou;
				g_aCube[nCntCube].vertexpos[7].z -= fRadiou;

				g_aCube[nCntCube].g_bLoop = false;
			}

			for (int nCntVtx = 0; nCntVtx < 8; nCntVtx++)
			{
				D3DXMATRIX			mtxvtxRot, mtxvtxTrans;	//計算用マトリックス
				D3DXMATRIX			mtxParent;

				D3DXMatrixIdentity(&g_aCube[nCntCube].vertexmtxWold[nCntVtx]);	//マトリックス初期化

				//向きの設定
				D3DXMatrixRotationYawPitchRoll(	&mtxvtxRot,
												g_aCube[nCntCube].vertexrot[nCntVtx].y,
												g_aCube[nCntCube].vertexrot[nCntVtx].x,
												g_aCube[nCntCube].vertexrot[nCntVtx].z);

				D3DXMatrixMultiply(	&g_aCube[nCntCube].vertexmtxWold[nCntVtx],
									&g_aCube[nCntCube].vertexmtxWold[nCntVtx],
									&mtxvtxRot);
				//位置
				D3DXMatrixTranslation(	&mtxvtxTrans,
										g_aCube[nCntCube].vertexpos[nCntVtx].x,
										g_aCube[nCntCube].vertexpos[nCntVtx].y,
										g_aCube[nCntCube].vertexpos[nCntVtx].z);

				D3DXMatrixMultiply(	&g_aCube[nCntCube].vertexmtxWold[nCntVtx],
									&g_aCube[nCntCube].vertexmtxWold[nCntVtx],
									&mtxvtxTrans);

				mtxParent = g_aCube[nCntCube].mtxWold;

				//パーツのワールドマトリックスと親のワールドマトリックスを掛け合わせる
				D3DXMatrixMultiply(	&g_aCube[nCntCube].vertexmtxWold[nCntVtx],
									&g_aCube[nCntCube].vertexmtxWold[nCntVtx],
									&mtxParent);

				//マトリックスの設定
				pDevice->SetTransform(	D3DTS_WORLD,
										&g_aCube[nCntCube].vertexmtxWold[nCntVtx]);
			}

			//---------------------------
			//外積
			//---------------------------
			//頂点から頂点のベクトル(次 - 前)		※ワールドマトリックスでやる
			vec[0].x = pCube->vertexmtxWold[5]._41 - pCube->vertexmtxWold[4]._41;
			vec[0].z = pCube->vertexmtxWold[5]._43 - pCube->vertexmtxWold[4]._43;

			vec[1].x = pCube->vertexmtxWold[7]._41 - pCube->vertexmtxWold[5]._41;
			vec[1].z = pCube->vertexmtxWold[7]._43 - pCube->vertexmtxWold[5]._43;

			vec[2].x = pCube->vertexmtxWold[6]._41 - pCube->vertexmtxWold[7]._41;
			vec[2].z = pCube->vertexmtxWold[6]._43 - pCube->vertexmtxWold[7]._43;

			vec[3].x = pCube->vertexmtxWold[4]._41 - pCube->vertexmtxWold[6]._41;
			vec[3].z = pCube->vertexmtxWold[4]._43 - pCube->vertexmtxWold[6]._43;

			//頂点と当たるやつのベクトル(当たるやつ - 頂点)		※ワールドマトリックスでやる
			pvec[0].x = pos->x - pCube->vertexmtxWold[4]._41;
			pvec[0].z = pos->z - pCube->vertexmtxWold[4]._43;

			pvec[1].x = pos->x - pCube->vertexmtxWold[5]._41;
			pvec[1].z = pos->z - pCube->vertexmtxWold[5]._43;

			pvec[2].x = pos->x - pCube->vertexmtxWold[7]._41;
			pvec[2].z = pos->z - pCube->vertexmtxWold[7]._43;

			pvec[3].x = pos->x - pCube->vertexmtxWold[6]._41;
			pvec[3].z = pos->z - pCube->vertexmtxWold[6]._43;

			//頂点と前回の当たるやつのベクトル(当たるやつ - 頂点)		※ワールドマトリックスでやる
			poldvec[0].x = posold->x - pCube->vertexmtxWold[4]._41;
			poldvec[0].z = posold->z - pCube->vertexmtxWold[4]._43;

			poldvec[1].x = posold->x - pCube->vertexmtxWold[5]._41;
			poldvec[1].z = posold->z - pCube->vertexmtxWold[5]._43;

			poldvec[2].x = posold->x - pCube->vertexmtxWold[7]._41;
			poldvec[2].z = posold->z - pCube->vertexmtxWold[7]._43;

			poldvec[3].x = posold->x - pCube->vertexmtxWold[6]._41;
			poldvec[3].z = posold->z - pCube->vertexmtxWold[6]._43;

			//今の外積
			fask[0] = (vec[0].x * pvec[0].z) - (pvec[0].x * vec[0].z);
			fask[1] = (vec[1].x * pvec[1].z) - (pvec[1].x * vec[1].z);
			fask[2] = (vec[2].x * pvec[2].z) - (pvec[2].x * vec[2].z);
			fask[3] = (vec[3].x * pvec[3].z) - (pvec[3].x * vec[3].z);

			//前回の外積
			faskold[0] = (vec[0].x * poldvec[0].z) - (poldvec[0].x * vec[0].z);
			faskold[1] = (vec[1].x * poldvec[1].z) - (poldvec[1].x * vec[1].z);
			faskold[2] = (vec[2].x * poldvec[2].z) - (poldvec[2].x * vec[2].z);
			faskold[3] = (vec[3].x * poldvec[3].z) - (poldvec[3].x * vec[3].z);

			//
			if ((fask[0] < 0.0f && fask[1] < 0.0f && fask[2] < 0.0f && fask[3] < 0.0f) &&
				(faskold[0] >= 0.0f || faskold[1] >= 0.0f || faskold[2] >= 0.0f || faskold[3] >= 0.0f))
			{
				pos->x = posold->x;
				pos->z = posold->z;
			}
		}
	}
	pCube -= MAX_CUBE;
	return true;
}

Cube *GetCube(void)
{
	return &g_aCube[0];
}