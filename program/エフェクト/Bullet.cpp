#include "main.h"
#include "bullet.h"
#include "Model.h"
#include "camera.h"
#include "Object.h"
#include "Effect.h"
#include "wall.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureBullet[BULLETTYPE_MAX] = {};//テクスチャへのポインタ

//頂点バッファのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL; //頂点バッファへのポインタ

Bullet g_aBullet[MAX_BULLET];

//初期化処理
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスのポインタ
	int nCntBullet;
	pDevice = GetDevice();//デバイスの取得

	//弾の初期化
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		g_aBullet[nCntBullet].bUse = false;
		g_aBullet[nCntBullet].nlife = 0;
		g_aBullet[nCntBullet].ntype = 0;
	}

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "date/TEXTURE/はね.png", &g_pTextureBullet[BULLETTYPE_PLAYER]);


	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BULLET, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffBullet, NULL);

	VERTEX_3D*pVtx;//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);


	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//頂点の座標
		pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - (MAX_BULLET_SIZE_X / 2), g_aBullet[nCntBullet].pos.y + (MAX_BULLET_SIZE_Y / 2), g_aBullet[nCntBullet].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + (MAX_BULLET_SIZE_X / 2), g_aBullet[nCntBullet].pos.y + (MAX_BULLET_SIZE_Y / 2), g_aBullet[nCntBullet].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - (MAX_BULLET_SIZE_X / 2), g_aBullet[nCntBullet].pos.y, g_aBullet[nCntBullet].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + (MAX_BULLET_SIZE_X / 2), g_aBullet[nCntBullet].pos.y, g_aBullet[nCntBullet].pos.z);

		//ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//頂点の色
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャのUV座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}


	//頂点バッファをアンロック
	g_pVtxBuffBullet->Unlock();
}

//終了処理
void UninitBullet(void)
{
	int nCntBullet;
	for (nCntBullet = 0; nCntBullet == BULLETTYPE_MAX; nCntBullet++)
	{
		//テクスチャの破棄
		if (g_pTextureBullet[nCntBullet] != NULL)
		{
			g_pTextureBullet[nCntBullet]->Release();
			g_pTextureBullet[nCntBullet] = NULL;
		}

		//頂点バッファも破棄
		if (g_pVtxBuffBullet != NULL)
		{
			g_pVtxBuffBullet->Release();
			g_pVtxBuffBullet = NULL;
		}
	}
}

//更新処理
void UpdateBullet(void)
{
	int nCntBullet;
	Object * pObject = GetObject();

	Wall * pWall = GetWall();

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			g_aBullet[nCntBullet].pos.x += sinf(g_aBullet[nCntBullet].rot.y) * 6;
			g_aBullet[nCntBullet].pos.z += cosf(g_aBullet[nCntBullet].rot.y) * 6;
			g_aBullet[nCntBullet].pos.y += tanf(g_aBullet[nCntBullet].rot.x) * 6;

			g_aBullet[nCntBullet].nlife--;

			//オブジェクトと弾の当たり判定
			for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
			{
				if (pObject[nCntObject].bUse == true)
				{
					if (g_aBullet[nCntBullet].pos.x >= pObject[nCntObject].pos.x + (pObject[nCntObject].VtxMinObject.x) && g_aBullet[nCntBullet].pos.x <= pObject[nCntObject].pos.x + (pObject[nCntObject].VtxMaxObject.x) &&
						g_aBullet[nCntBullet].pos.y >= pObject[nCntObject].pos.y + (pObject[nCntObject].VtxMinObject.y) && g_aBullet[nCntBullet].pos.y <= pObject[nCntObject].pos.y + (pObject[nCntObject].VtxMaxObject.y) &&
						g_aBullet[nCntBullet].pos.z >= pObject[nCntObject].pos.z + (pObject[nCntObject].VtxMinObject.z) && g_aBullet[nCntBullet].pos.z <= pObject[nCntObject].pos.z + (pObject[nCntObject].VtxMaxObject.z))
					{
						g_aBullet[nCntBullet].bUse = false;
					}
				}
			}
			/*for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
			{
				if (pWall[nCntWall].bUse == true)
				{
					if (g_aBullet[nCntBullet].pos.x > pWall[nCntWall].pos.x - (pWall[nCntWall].fWhidth) &&
						g_aBullet[nCntBullet].pos.x < pWall[nCntWall].pos.x + (pWall[nCntWall].fWhidth)&&
						g_aBullet[nCntBullet].pos.y > pWall[nCntWall].pos.y - (pWall[nCntWall].fHight) &&
						g_aBullet[nCntBullet].pos.y < pWall[nCntWall].pos.y + (pWall[nCntWall].fHight))
					{
						
						g_aBullet[nCntBullet].bUse = false;
					}
				}
			}*/

			SetEffect(g_aBullet[nCntBullet].pos, D3DXCOLOR(255, 0, 255, 255), 8, 8, EFFECTTYPE_PLAYER, 7);

			//射程圏外になったら消す
			if (g_aBullet[nCntBullet].nlife <= 0)
			{
				g_aBullet[nCntBullet].bUse = false;
			}
		}

	}

}

//描画処理
void DrawBullet(void)
{
	int nCntBullet;
	LPDIRECT3DDEVICE9 pDevice;//デバイスのポインタ
	D3DXMATRIX mtxView;
	D3DXMATRIX mtxTrans;
	pDevice = GetDevice();//デバイスを取得する

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			//Zテスト関係
			/*pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);*/

			//アルファテスト関係
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

			//マトリックス初期化
			D3DXMatrixIdentity(&g_aBullet[nCntBullet].mtxWorld);
			//ビューマトリックスの取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//ポリゴンをカメラに対して正面に
			D3DXMatrixInverse(&g_aBullet[nCntBullet].mtxWorld, NULL, &mtxView);

			g_aBullet[nCntBullet].mtxWorld._41 = 0.0f;
			g_aBullet[nCntBullet].mtxWorld._42 = 0.0f;
			g_aBullet[nCntBullet].mtxWorld._43 = 0.0f;

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aBullet[nCntBullet].pos.x, g_aBullet[nCntBullet].pos.y, g_aBullet[nCntBullet].pos.z);
			D3DXMatrixMultiply(&g_aBullet[nCntBullet].mtxWorld, &g_aBullet[nCntBullet].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aBullet[nCntBullet].mtxWorld);

			//頂点バッファをデバイスのデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));

			pDevice->SetFVF(FVF_VERTEX_3D);//頂点フォーマットの設定

			pDevice->SetTexture(0, g_pTextureBullet[0]);//テクスチャの設定

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBullet * 4, 2);

			//Zテスト関係
			/*pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);*/

			//アルファテスト関係
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);
		}

	}
}

//弾の設定処理
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int ntype)
{
	int nCntBullet;


	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{
			g_aBullet[nCntBullet].pos = pos;
			g_aBullet[nCntBullet].ntype = ntype;

			g_aBullet[nCntBullet].rot = rot;
			g_aBullet[nCntBullet].nlife = 100;
			g_aBullet[nCntBullet].bUse = true;

			break;
		}
		
	}
}

Bullet *GetBullet(void)
{
	return &g_aBullet[0];
}