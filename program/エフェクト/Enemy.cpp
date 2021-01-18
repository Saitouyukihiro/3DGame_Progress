//ーーーーーーーーーーーーーーーーーーーーーーーーー
//敵の処理(Enemy.cpp)
//Author：佐藤秀亮
//ーーーーーーーーーーーーーーーーーーーーーーーーー

//インクルードファイル
#include "main.h"
#include "input.h"
#include "Enemy.h"
#include "Shadow.h"
#include "camera.h"
#include "Effect.h"



//グローバル変数

D3DXVECTOR3 g_SaveEnemyRot;

Enemy g_Enemy[MAX_ENEMY];

int g_EnemyMaxParts = 0;

//初期化処理
void InitEnemy(void)
{
	for (int nCntMaxEnemy = 0; nCntMaxEnemy < MAX_ENEMY; nCntMaxEnemy++)
	{
		g_Enemy[nCntMaxEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//位置
		g_Enemy[nCntMaxEnemy].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//回転

		g_Enemy[nCntMaxEnemy].aEnemy[g_EnemyMaxParts];
		g_Enemy[nCntMaxEnemy].nNumEnemy;

		g_Enemy[nCntMaxEnemy].ntype = 0;
		g_Enemy[nCntMaxEnemy].bUse = false;
		g_Enemy[nCntMaxEnemy].nLife = 0;
	}
}

//終了処理
void UninitEnemy(void)//追加の可能性があるため項目は作っとく
{
	for (int nCntMaxEnemy = 0; nCntMaxEnemy < MAX_ENEMY; nCntMaxEnemy++)
	{
		for (int nCntEnemy = 0; nCntEnemy < g_Enemy[nCntEnemy].nNumEnemy; nCntEnemy++)
		{
			//テクスチャの破棄
			if (g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].pMeshEnemy != NULL)
			{
				g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].pMeshEnemy->Release();
				g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].pMeshEnemy = NULL;
			}

			//頂点バッファも破棄
			if (g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].pBuffMatEnemy != NULL)
			{
				g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].pBuffMatEnemy->Release();
				g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].pBuffMatEnemy = NULL;
			}
		}
	}
}

//更新処理
void UpdateEnemy(void)//追加の可能性があるため項目は作っとく
{
	
}

//描画処理
void DrawEnemy(void)
{

	LPDIRECT3DDEVICE9 pDevice;//デバイスのポインタ
	pDevice = GetDevice();//デバイスを取得する
	D3DXMATRIX mtxRot, mtxTrans;//計算用マトリックス

	D3DMATERIAL9 matDef;//現在のマテリアル保存
	D3DXMATERIAL *pMat;//マテリアルデータポインタ
	for (int nCntMaxEnemy = 0; nCntMaxEnemy < MAX_ENEMY; nCntMaxEnemy++)
	{
		D3DXMatrixIdentity(&g_Enemy[nCntMaxEnemy].mtxWorldEnemy);//ワールドマトリックスの初期化

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Enemy[nCntMaxEnemy].rot.y, g_Enemy[nCntMaxEnemy].rot.x, g_Enemy[nCntMaxEnemy].rot.z);
		D3DXMatrixMultiply(&g_Enemy[nCntMaxEnemy].mtxWorldEnemy, &g_Enemy[nCntMaxEnemy].mtxWorldEnemy, &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_Enemy[nCntMaxEnemy].pos.x, g_Enemy[nCntMaxEnemy].pos.y, g_Enemy[nCntMaxEnemy].pos.z);
		D3DXMatrixMultiply(&g_Enemy[nCntMaxEnemy].mtxWorldEnemy, &g_Enemy[nCntMaxEnemy].mtxWorldEnemy, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Enemy[nCntMaxEnemy].mtxWorldEnemy);

		//パーツ１つ１つに設定をする
		for (int nCntEnemy = 0; nCntEnemy < g_Enemy[nCntEnemy].nNumEnemy; nCntEnemy++)
		{
			D3DXMATRIX mtxRotEnemy, mtxTransEnemy;//計算用マトリックス
			D3DXMATRIX mtxParent;//親のマトリックス

			D3DXMatrixIdentity(&g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].mtxWorldEnemy);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRotEnemy, g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].rot.y, g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].rot.x, g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].rot.z);
			D3DXMatrixMultiply(&g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].mtxWorldEnemy, &g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].mtxWorldEnemy, &mtxRotEnemy);

			//位置を反映
			D3DXMatrixTranslation(&mtxTransEnemy, g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].pos.x, g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].pos.y, g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].pos.z);
			D3DXMatrixMultiply(&g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].mtxWorldEnemy, &g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].mtxWorldEnemy, &mtxTransEnemy);

			//親のマトリックスを反映
			if (g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].nIndxModelParent != -1)
			{
				mtxParent = g_Enemy[nCntMaxEnemy].aEnemy[g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].nIndxModelParent].mtxWorldEnemy;
			}
			else
			{
				mtxParent = g_Enemy[nCntMaxEnemy].mtxWorldEnemy;
			}
			//算出した各パーツのマトリックスと親のマトリックを掛け合わせる
			D3DXMatrixMultiply(&g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].mtxWorldEnemy, &g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].mtxWorldEnemy, &mtxParent);

			//マトリックスをセット
			pDevice->SetTransform(D3DTS_WORLD, &g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].mtxWorldEnemy);

			//現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			//マテリアルデータの取得
			pMat = (D3DXMATERIAL*)g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].pBuffMatEnemy->GetBufferPointer();

			//パーツ分回す
			for (int nCntMat = 0; nCntMat < (int)g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].nNumMatEnemy; nCntMat++)
			{
				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				//テクスチャの設定
				pDevice->SetTexture(0, NULL);
				//モデルパーツの描画
				g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].pMeshEnemy->DrawSubset(nCntMat);
			}

		}
	}
	//保存したマテリアル戻す
	pDevice->SetMaterial(&matDef);
}

void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife, int ntype)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスのポインタ
	pDevice = GetDevice();//デバイスを取得する

	int nNumVtx[MAX_ENEMY]; //頂点数
	DWORD sizeFVF; //頂点フォーマットのサイズ
	BYTE *pVtxBuff; //頂点バッファへのポインタ

	for (int nCntMaxEnemy = 0; nCntMaxEnemy < MAX_ENEMY; nCntMaxEnemy++)
	{
		if (g_Enemy[nCntMaxEnemy].bUse == false)
		{
			g_Enemy[nCntMaxEnemy].pos = pos;
			g_Enemy[nCntMaxEnemy].rot = rot;
			g_Enemy[nCntMaxEnemy].ntype = ntype;

			switch (g_Enemy[nCntMaxEnemy].ntype)//敵のタイプでそれぞれを読み込ませる
		case(ENEMYTYPE_LMG):
			{

				g_Enemy[nCntMaxEnemy].aEnemy[MAX_PARTS];

				g_Enemy[nCntMaxEnemy].nNumEnemy = MAX_PARTS;//パーツ数を入れる

				//xファイルの読み込み
				D3DXLoadMeshFromX("date/Enemy/LMG/100_sityu.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Enemy[nCntMaxEnemy].aEnemy[0].pBuffMatEnemy, NULL, &g_Enemy[nCntMaxEnemy].aEnemy[0].nNumMatEnemy, &g_Enemy[nCntMaxEnemy].aEnemy[0].pMeshEnemy);
				//xファイルの読み込み
				D3DXLoadMeshFromX("date/Enemy/LMG/101_gun.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Enemy[nCntMaxEnemy].aEnemy[1].pBuffMatEnemy, NULL, &g_Enemy[nCntMaxEnemy].aEnemy[1].nNumMatEnemy, &g_Enemy[nCntMaxEnemy].aEnemy[1].pMeshEnemy);
				//xファイルの読み込み
				D3DXLoadMeshFromX("date/Enemy/LMG/102_reg.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Enemy[nCntMaxEnemy].aEnemy[2].pBuffMatEnemy, NULL, &g_Enemy[nCntMaxEnemy].aEnemy[2].nNumMatEnemy, &g_Enemy[nCntMaxEnemy].aEnemy[2].pMeshEnemy);

				//０番目のパーツのオフセット等
				g_Enemy[nCntMaxEnemy].aEnemy[0].nIndxModelParent = -1;
				g_Enemy[nCntMaxEnemy].aEnemy[0].pos = D3DXVECTOR3(0.0, 10.0, 0.0);
				g_Enemy[nCntMaxEnemy].aEnemy[0].rot = D3DXVECTOR3(0.0, D3DX_PI * 1, 0.0);

				//1番目のパーツのオフセット等
				g_Enemy[nCntMaxEnemy].aEnemy[1].nIndxModelParent = 0;
				g_Enemy[nCntMaxEnemy].aEnemy[1].pos = D3DXVECTOR3(0.0, 20.0, 0.0);
				g_Enemy[nCntMaxEnemy].aEnemy[1].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

				//2番目のパーツのオフセット等
				g_Enemy[nCntMaxEnemy].aEnemy[2].nIndxModelParent = 0;
				g_Enemy[nCntMaxEnemy].aEnemy[2].pos = D3DXVECTOR3(0.0, 0.0, 0.0);
				g_Enemy[nCntMaxEnemy].aEnemy[2].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

				g_Enemy[nCntMaxEnemy].pos = D3DXVECTOR3(0.0, 0.0, 0.0);
				g_Enemy[nCntMaxEnemy].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

				

				for (int nCntEnemy = 0; nCntEnemy < g_Enemy[nCntMaxEnemy].nNumEnemy; nCntEnemy++)
				{

					//頂点数の取得
					nNumVtx[nCntEnemy] = g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].pMeshEnemy->GetNumVertices();
					//頂点フォーマットのサイズを取得
					sizeFVF = D3DXGetFVFVertexSize(g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].pMeshEnemy->GetFVF());
					//頂点バッファロック
					g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].pMeshEnemy->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

					for (int nCntVtx = 0; nCntVtx < nNumVtx[nCntEnemy]; nCntVtx++)
					{
						D3DXVECTOR3 Vtx = *(D3DXVECTOR3*)pVtxBuff;//頂点座標代入

						//***************************************
						//X軸
						//***************************************
						//比較対象がMaxより大きかったら
						if (Vtx.x > g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].VtxMaxEnemy.x)
						{
							g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].VtxMaxEnemy.x = Vtx.x;
						}
						//比較対象がMinより小さかったら
						if (Vtx.x < g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].VtxMinEnemy.x)
						{
							g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].VtxMinEnemy.x = Vtx.x;
						}

						//***************************************
						//Y軸
						//***************************************
						//比較対象がMaxより大きかったら
						if (Vtx.y > g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].VtxMaxEnemy.y)
						{
							g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].VtxMaxEnemy.y = Vtx.y;
						}
						//比較対象がMinより小さかったら
						if (Vtx.y < g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].VtxMinEnemy.y)
						{
							g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].VtxMinEnemy.y = Vtx.y;
						}

						//***************************************
						//Z軸
						//***************************************
						//比較対象がMaxより大きかったら
						if (Vtx.z > g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].VtxMaxEnemy.z)
						{
							g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].VtxMaxEnemy.z = Vtx.z;
						}
						//比較対象がMinより小さかったら
						if (Vtx.z < g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].VtxMinEnemy.z)
						{
							g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].VtxMinEnemy.z = Vtx.z;
						}

						pVtxBuff += sizeFVF;//比較対象の変更
					}
					//頂点バッファアンロック
					g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].pMeshEnemy->UnlockVertexBuffer();
				}
			}
			//影のセット
			SetShadow(g_Enemy[nCntMaxEnemy].pos, 100.0f, 100.0f, TYPE_PLAYER);

			g_Enemy[nCntMaxEnemy].bUse = true;

			break;
		}
	}
}


Enemy *GetEnemy(void)
{
	return &g_Enemy[0];
}