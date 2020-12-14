//---------------------------
//インクルードファイル
//---------------------------
#include <stdio.h>
#include "model.h"
#include "keyinput.h"
#include "camara.h"
#include "mouseinput.h"
#include "shadow.h"
#include "bullet.h"
#include "wall.h"

//---------------------------
//グローバル変数
//---------------------------
LPD3DXMESH				g_pMeshModel = NULL;		//メッシュのポインタ
LPD3DXBUFFER			g_pBuffMatModel = NULL;		//マテリアルのポインタ
Model					g_aModel;					//モデルの構造体

//---------------------------
//初期化処理
//---------------------------
HRESULT InitModel(void)
{
	LPDIRECT3DDEVICE9	pDevice;	//デバイスへのポインタ

	pDevice = GetDevice();			//デバイスの取得

	//位置向き初期化
	g_aModel.PosModel = (D3DXVECTOR3(0.0f, 0.0f, -100.0f));
	g_aModel.RotModel = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	g_aModel.vtxMaxModel = (D3DXVECTOR3(-1000000.0f, -1000000.0f, -1000000.0f));
	g_aModel.vtxMinModel = (D3DXVECTOR3(1000000.0f, 1000000.0f, 1000000.0f));
	g_aModel.nIdex = 0;

	//---------------------------
	//Xファイルの読み込み
	//---------------------------
	D3DXLoadMeshFromX(	"data/Model/guys.x",
						D3DXMESH_SYSTEMMEM,
						pDevice,
						NULL,
						&g_pBuffMatModel,
						NULL,
						&g_aModel.pnNumMatModel,
						&g_pMeshModel);
	//---------------------------
	//頂点座標の抜き出し
	//---------------------------
	int nNumVtx;	//頂点数
	DWORD sizeFVF;	//頂点フォーマットのサイズ
	BYTE *pVtxBuff;	//頂点バッファのポインタ

	//頂点数を取得
	nNumVtx = g_pMeshModel->GetNumVertices();

	//頂点フォーマットのサイズを取得
	sizeFVF = D3DXGetFVFVertexSize(g_pMeshModel->GetFVF());

	//頂点バッファのロック
	g_pMeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//頂点座標の代入

		//頂点数を比較して最小値、最大値を抜く
		//X
		if (g_aModel.vtxMaxModel.x <= vtx.x)
		{
			g_aModel.vtxMaxModel.x = vtx.x;
		}
		if (g_aModel.vtxMinModel.x >= vtx.x)
		{
			g_aModel.vtxMinModel.x = vtx.x;
		}
		//Y
		if (g_aModel.vtxMaxModel.y <= vtx.y)
		{
			g_aModel.vtxMaxModel.y = vtx.y;
		}
		if (g_aModel.vtxMinModel.y >= vtx.y)
		{
			g_aModel.vtxMinModel.y = vtx.y;
		}
		//Z
		if (g_aModel.vtxMaxModel.z <= vtx.z)
		{
			g_aModel.vtxMaxModel.z = vtx.z;
		}
		if (g_aModel.vtxMinModel.z >= vtx.z)
		{
			g_aModel.vtxMinModel.z = vtx.z;
		}

		pVtxBuff += sizeFVF;	//頂点を進める
	}
	//頂点バッファをアンロック
	g_pMeshModel->UnlockVertexBuffer();

	g_aModel.nIdex = SetShadow(g_aModel.PosModel, 50.0f, 50.0f);

	return S_OK;
}

//---------------------------
//終了処理
//---------------------------
void UninitModel(void)
{
	//---------------------------
	//メッシュ破棄
	//---------------------------
	if (g_pMeshModel != NULL)
	{
		g_pMeshModel->Release();
		g_pMeshModel = NULL;
	}

	//---------------------------
	//マテリアル破棄
	//---------------------------
	if (g_pBuffMatModel != NULL)
	{
		g_pBuffMatModel->Release();
		g_pBuffMatModel = NULL;
	}
}

//---------------------------
//更新処理
//---------------------------
void UpdateModel(void)
{
	Camera *pCamera;		//カメラの構造体のポインタ
	Camera *p1Camera;		//0番(FPS)カメラ
	static int nSpan;		//クールタイム

	pCamera = GetCamera();		//カメラの情報を取得
	p1Camera = Get1Camera();	//0番(FPS)カメラ

	//---------------------------
	//四方向移動量
	//---------------------------
	for (int nCntCamera = 0; nCntCamera < MAX_CAMERA - 1; nCntCamera++, pCamera++)
	{
		if (pCamera->bUse == true)
		{
			if (GetKeyboardPress(DIK_W) == true)
			{
				g_aModel.PosModel.x = g_aModel.PosModel.x + sinf(pCamera->Rot.y) * CAMERA_MOVE_SPEED;
				g_aModel.PosModel.z = g_aModel.PosModel.z + cosf(pCamera->Rot.y) * CAMERA_MOVE_SPEED;

				//カメラの向きに転換
				g_aModel.RotModel.y = pCamera->Rot.y + -D3DX_PI;
			}
			if (GetKeyboardPress(DIK_S) == true)
			{
				g_aModel.PosModel.x = g_aModel.PosModel.x - sinf(pCamera->Rot.y) * CAMERA_MOVE_SPEED;
				g_aModel.PosModel.z = g_aModel.PosModel.z - cosf(pCamera->Rot.y) * CAMERA_MOVE_SPEED;

				//カメラの向きに転換
				g_aModel.RotModel.y = pCamera->Rot.y;
			}
			if (GetKeyboardPress(DIK_A) == true)
			{
				g_aModel.PosModel.x = g_aModel.PosModel.x - cosf(pCamera->Rot.y) * CAMERA_MOVE_SPEED;
				g_aModel.PosModel.z = g_aModel.PosModel.z + sinf(pCamera->Rot.y) * CAMERA_MOVE_SPEED;

				//カメラの向きに転換
				g_aModel.RotModel.y = pCamera->Rot.y + D3DX_PI / 2;
			}
			if (GetKeyboardPress(DIK_D) == true)
			{
				g_aModel.PosModel.x = g_aModel.PosModel.x + cosf(pCamera->Rot.y) * CAMERA_MOVE_SPEED;
				g_aModel.PosModel.z = g_aModel.PosModel.z - sinf(pCamera->Rot.y) * CAMERA_MOVE_SPEED;

				//カメラの向きに転換
				g_aModel.RotModel.y = pCamera->Rot.y + -D3DX_PI / 2;
			}
			if (GetKeyboardPress(DIK_I) == true)
			{
				g_aModel.PosModel.y += 1.0f;
			}
			if (GetKeyboardPress(DIK_K) == true)
			{
				g_aModel.PosModel.y -= 1.0f;
			}
		}
	}
	pCamera-= (MAX_CAMERA - 1);

	//---------------------------
	//リセット
	//---------------------------
	if (GetKeyboardPress(DIK_RETURN) == true)
	{
		g_aModel.PosModel = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		g_aModel.RotModel = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
	//---------------------------
	//弾の発射
	//---------------------------
	nSpan++;
	if (GetKeyboardPress(DIK_Q) == true && nSpan > BULLET_SPAN)
	{
		for (int nCntCm = 0; nCntCm < MAX_CAMERA; nCntCm++, pCamera++)
		{
			if (pCamera->bUse == true)
			{
				SetBullet(D3DXVECTOR3(g_aModel.PosModel.x, g_aModel.PosModel.y + 25.0f, g_aModel.PosModel.z + 25.0f), D3DXVECTOR3(pCamera->Rot.x, pCamera->Rot.y, 0.0f), 25.0f, 25.0f, 0);
				nSpan = 0;
			}
		}
		pCamera -= MAX_CAMERA;
	}

	//自分の影
	SetPointShadow(g_aModel.nIdex, g_aModel.PosModel, 50.0f, 50.0f);
}

//---------------------------
//描画処理
//---------------------------
void DrawModel(void)
{
	LPDIRECT3DDEVICE9	pDevice;			//デバイスのポインタ

	pDevice = GetDevice();					//デバイスを取得する

	//---------------------------
	//マトリックスの設定
	//---------------------------
	D3DXMATRIX			mtxRot, mtxTrans;	//計算用マトリックス

	D3DXMatrixIdentity(&g_aModel.mtxWoldModel);	//マトリックス初期化

	//向きの設定
	D3DXMatrixRotationYawPitchRoll(	&mtxRot,
									g_aModel.RotModel.y,
									g_aModel.RotModel.x,
									g_aModel.RotModel.z);

	D3DXMatrixMultiply(	&g_aModel.mtxWoldModel,
						&g_aModel.mtxWoldModel,
						&mtxRot);
	//位置
	D3DXMatrixTranslation(	&mtxTrans,
							g_aModel.PosModel.x,
							g_aModel.PosModel.y,
							g_aModel.PosModel.z);

	D3DXMatrixMultiply(	&g_aModel.mtxWoldModel,
						&g_aModel.mtxWoldModel,
						&mtxTrans);
	//マトリックスの設定
	pDevice->SetTransform(	D3DTS_WORLD,
							&g_aModel.mtxWoldModel);
	//---------------------------
	//描画処理
	//---------------------------
	D3DMATERIAL9		matDef;				//マテリアルの一時保存
	D3DXMATERIAL		*pMat;				//マテリアルデータのポインタ

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータのポインタ
	pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_aModel.pnNumMatModel; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0,
							NULL);

		//モデルパーツの描画
		g_pMeshModel->DrawSubset(nCntMat);
	}
	//一時保存してたやつをもどす
	pDevice->SetMaterial(&matDef);
}

//---------------------------
//モデル情報取得
//---------------------------
Model *GetModel(void)
{
	return &g_aModel;
}