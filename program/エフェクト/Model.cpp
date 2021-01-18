//ーーーーーーーーーーーーーーーーーーーーーーーーー
//モデル(プレイヤー)の処理(Model.cpp)
//Author：佐藤秀亮
//ーーーーーーーーーーーーーーーーーーーーーーーーー

//インクルードファイル
#include "main.h"
#include "input.h"
#include "Model.h"
#include "Shadow.h"
#include "camera.h"
#include "Billboard.h"
#include "Bullet.h"
#include "Object.h"
#include "Effect.h"
#include "Enemy.h"

//グローバル変数
D3DXVECTOR3 g_Oldpos;	//当たり判定で必要

//フルオート発射に必要
bool g_bCoolDown;
int g_nCntCoolDown;

D3DXVECTOR3 g_SaveModelRot;

Player g_Player;

int g_EffectTime;//エフェクトの出る間隔

//マクロ
#define MOVE (5.0f)
#define BULLET_COOLDOWN (3) //弾の発射間隔
#define MUGZINE_BULLET (30)//マガジン内弾薬
#define RELOAD_TIME (60) //リロード時間

#define EFFECT_SIZE_X (15)
#define EFFECT_SIZE_Y (15)

#define EFFECT_LIFE (15)
#define EFFECT_COOLDOWN (30)

//初期化処理
void InitModel(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスのポインタ
	pDevice = GetDevice();//デバイスの取得
	//ーーーーーーーーーーーーーーーーーーーーーーーーー
	//構造体初期化
	//ーーーーーーーーーーーーーーーーーーーーーーーーー
	g_Player.nNumModel = MAX_MODEL;//パーツ数を入れる
	g_Player.state = PLAYERSTATE_NOMAL;
	g_Player.MugzineBullet = MUGZINE_BULLET;
	g_Player.ReloadTime = RELOAD_TIME;
	//ーーーーーーーーーーーーーーーーーーーーーーーーー

	g_EffectTime = 0;
	g_Oldpos = g_Player.pos;//初期位置をとりあえず保存

	//xファイルの読み込み
	D3DXLoadMeshFromX("date/Model/LMG/100_sityu.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[0].pBuffMatModel, NULL, &g_Player.aModel[0].nNumMatmodel, &g_Player.aModel[0].pMeshModel);
	//xファイルの読み込み
	D3DXLoadMeshFromX("date/Model/LMG/101_gun.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[1].pBuffMatModel, NULL, &g_Player.aModel[1].nNumMatmodel, &g_Player.aModel[1].pMeshModel);
	//xファイルの読み込み
	D3DXLoadMeshFromX("date/Model/LMG/102_reg.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[2].pBuffMatModel, NULL, &g_Player.aModel[2].nNumMatmodel, &g_Player.aModel[2].pMeshModel);

	//０番目のパーツのオフセット等
	g_Player.aModel[0].nIndxModelParent = -1;
	g_Player.aModel[0].pos = D3DXVECTOR3(0.0, 10.0, 0.0);
	g_Player.aModel[0].rot = D3DXVECTOR3(0.0, D3DX_PI * 1, 0.0);

	//1番目のパーツのオフセット等
	g_Player.aModel[1].nIndxModelParent = 0;
	g_Player.aModel[1].pos = D3DXVECTOR3(0.0, 20.0, 0.0);
	g_Player.aModel[1].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

	//2番目のパーツのオフセット等
	g_Player.aModel[2].nIndxModelParent = 0;
	g_Player.aModel[2].pos = D3DXVECTOR3(0.0, 0.0, 0.0);
	g_Player.aModel[2].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

	g_Player.pos = D3DXVECTOR3(0.0, 0.0, 0.0);
	g_Player.rot = D3DXVECTOR3(0.0, 0.0, 0.0);

	g_SaveModelRot = g_Player.aModel[1].rot;

	int nNumVtx; //頂点数
	DWORD sizeFVF; //頂点フォーマットのサイズ
	BYTE *pVtxBuff; //頂点バッファへのポインタ

	for (int nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
	{
		//頂点数の取得
		nNumVtx = g_Player.aModel[nCntModel].pMeshModel->GetNumVertices();
		//頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(g_Player.aModel[nCntModel].pMeshModel->GetFVF());
		//頂点バッファロック
		g_Player.aModel[nCntModel].pMeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 Vtx = *(D3DXVECTOR3*)pVtxBuff;//頂点座標代入

			//***************************************
			//X軸
			//***************************************
			//比較対象がMaxより大きかったら
			if (Vtx.x > g_Player.aModel[nCntModel].VtxMaxModel.x)
			{
				g_Player.aModel[nCntModel].VtxMaxModel.x = Vtx.x;
			}
			//比較対象がMinより小さかったら
			if (Vtx.x < g_Player.aModel[nCntModel].VtxMinModel.x)
			{
				g_Player.aModel[nCntModel].VtxMinModel.x = Vtx.x;
			}

			//***************************************
			//Y軸
			//***************************************
			//比較対象がMaxより大きかったら
			if (Vtx.y > g_Player.aModel[nCntModel].VtxMaxModel.y)
			{
				g_Player.aModel[nCntModel].VtxMaxModel.y = Vtx.y;
			}
			//比較対象がMinより小さかったら
			if (Vtx.y < g_Player.aModel[nCntModel].VtxMinModel.y)
			{
				g_Player.aModel[nCntModel].VtxMinModel.y = Vtx.y;
			}

			//***************************************
			//Z軸
			//***************************************
			//比較対象がMaxより大きかったら
			if (Vtx.z > g_Player.aModel[nCntModel].VtxMaxModel.z)
			{
				g_Player.aModel[nCntModel].VtxMaxModel.z = Vtx.z;
			}
			//比較対象がMinより小さかったら
			if (Vtx.z < g_Player.aModel[nCntModel].VtxMinModel.z)
			{
				g_Player.aModel[nCntModel].VtxMinModel.z = Vtx.z;
			}

			pVtxBuff += sizeFVF;//比較対象の変更
		}
		//頂点バッファアンロック
		g_Player.aModel[nCntModel].pMeshModel->UnlockVertexBuffer();
	}
	

	//フルオート発射に必要
	g_bCoolDown = false;
	g_nCntCoolDown = BULLET_COOLDOWN;

	//影のセット
	InitShadow();
	SetShadow(g_Player.pos, 100.0f, 100.0f, TYPE_PLAYER);

	
}

//終了処理
void UninitModel(void)//追加の可能性があるため項目は作っとく
{
	UninitShadow();
	for (int nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
	{
		//テクスチャの破棄
		if (g_Player.aModel[nCntModel].pMeshModel != NULL)
		{
			g_Player.aModel[nCntModel].pMeshModel->Release();
			g_Player.aModel[nCntModel].pMeshModel = NULL;
		}

		//頂点バッファも破棄
		if (g_Player.aModel[nCntModel].pBuffMatModel != NULL)
		{
			g_Player.aModel[nCntModel].pBuffMatModel->Release();
			g_Player.aModel[nCntModel].pBuffMatModel = NULL;
		}
	}

}

//更新処理
void UpdateModel(void)//追加の可能性があるため項目は作っとく
{
	Camera * pCamera;
	pCamera = GetCamera();
	bool RecoilControl = true;

	switch(g_Player.state)
	{ 
	case(PLAYERSTATE_NOMAL):
	{
		//一回だけ通るようにしてX回転量を保存
		if (GetKeyboardTrigger(DIK_SPACE) == true && RecoilControl == false)
		{
			g_SaveModelRot.x = g_Player.aModel[1].rot.x;
		}

		//弾の射出
		if (GetKeyboardPress(DIK_SPACE) == true && g_bCoolDown == false)
		{
			SetBullet(D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y + 30, g_Player.pos.z), D3DXVECTOR3(g_Player.aModel[1].rot.x, g_Player.aModel[1].rot.y, g_Player.rot.z), BULLETTYPE_PLAYER);
			g_bCoolDown = true;
			g_nCntCoolDown = BULLET_COOLDOWN;

			g_Player.aModel[1].rot.x += 0.005;

			pCamera->ShotBullet = true;
			RecoilControl = true;

			g_Player.MugzineBullet--;

			if (g_Player.aModel[1].rot.x >= sinf(D3DX_PI * 0.1))
			{
				g_Player.aModel[1].rot.x = sinf(D3DX_PI * 0.1);
			}
		}
		if (GetKeyboardRelese(DIK_SPACE) == true)
		{
			pCamera->ShotBullet = false;
		}
		//フルオート発射
		if (g_bCoolDown = true)
		{
			g_nCntCoolDown--;
			if (g_nCntCoolDown < 0)
			{
				g_bCoolDown = false;
			}
		}
		//反動で上がった銃を下げる処理
		if (pCamera->ShotBullet == false && RecoilControl == true)
		{
			g_Player.aModel[1].rot.x -= 0.01;

			if (g_Player.aModel[1].rot.x <= g_SaveModelRot.x)
			{
				g_Player.aModel[1].rot.x = g_SaveModelRot.x;
				RecoilControl = false;
			}
		}

		if (GetKeyboardTrigger(DIK_L) == TRUE || g_Player.MugzineBullet <= 0)
		{
			g_Player.state = PLAYERSTATE_RELOAD;
			g_Player.ReloadTime = RELOAD_TIME;
		}
		break;
	}
	case(PLAYERSTATE_RELOAD):
	{
		g_Player.ReloadTime--;
		if (g_Player.ReloadTime <= 0)
		{
			g_Player.MugzineBullet = MUGZINE_BULLET;
			g_Player.state = PLAYERSTATE_NOMAL;
		}
		break;
	}
		
	}
	

	//****************************************
	//移動処理
	//****************************************
	if (GetKeyboardPress(DIK_UP) == true)
	{
		g_Player.pos.z += cosf(pCamera->rot.y) * MOVE;
		g_Player.pos.x += sinf(pCamera->rot.y) * MOVE;
		SetEffect(g_Player.pos, D3DXCOLOR(0, 0, 255, 255), EFFECT_SIZE_X, EFFECT_SIZE_Y, EFFECTTYPE_PLAYER, EFFECT_LIFE);

	}
	else if (GetKeyboardPress(DIK_DOWN) == true)
	{
		g_Player.pos.z -= cosf(pCamera->rot.y) * MOVE;
		g_Player.pos.x -= sinf(pCamera->rot.y) * MOVE;

		SetEffect(g_Player.pos, D3DXCOLOR(0, 0, 255, 255), EFFECT_SIZE_X, EFFECT_SIZE_Y, EFFECTTYPE_PLAYER, EFFECT_LIFE);
	
	}
	if (GetKeyboardPress(DIK_LEFT) == true)
	{
		g_Player.pos.x -= cosf(pCamera->rot.y) * MOVE;
		g_Player.pos.z += sinf(pCamera->rot.y) * MOVE;
		SetEffect(g_Player.pos, D3DXCOLOR(0, 0, 255, 255), EFFECT_SIZE_X, EFFECT_SIZE_Y, EFFECTTYPE_PLAYER, EFFECT_LIFE);

	}
	else if (GetKeyboardPress(DIK_RIGHT) == true)
	{
		g_Player.pos.x += cosf(pCamera->rot.y) * MOVE;
		g_Player.pos.z -= sinf(pCamera->rot.y) * MOVE;

		SetEffect(g_Player.pos, D3DXCOLOR(0, 0, 255, 255), EFFECT_SIZE_X, EFFECT_SIZE_Y, EFFECTTYPE_PLAYER, EFFECT_LIFE);
	}

	//****************************************
	//エフェクト関係
	//****************************************
	if (g_EffectTime <= 0)
	{
		SetEffect(g_Player.pos, D3DXCOLOR(0, 255, 0, 255), EFFECT_SIZE_X, EFFECT_SIZE_Y, EFFECTTYPE_FOLL_ST, EFFECT_LIFE);
		SetEffect(g_Player.pos, D3DXCOLOR(0, 255, 255, 255), EFFECT_SIZE_X, EFFECT_SIZE_Y, EFFECTTYPE_FOLL_L, EFFECT_LIFE * 2);
		SetEffect(g_Player.pos, D3DXCOLOR(255, 255, 0, 255), EFFECT_SIZE_X, EFFECT_SIZE_Y, EFFECTTYPE_FOLL_R, EFFECT_LIFE * 2);

		SetEffect(g_Player.pos, D3DXCOLOR(0, 255, 0, 255), EFFECT_SIZE_X, EFFECT_SIZE_Y, EFFECTTYPE_UP_ST, EFFECT_LIFE);
		SetEffect(g_Player.pos, D3DXCOLOR(0, 255, 255, 255), EFFECT_SIZE_X, EFFECT_SIZE_Y, EFFECTTYPE_UP_L, EFFECT_LIFE * 2);
		SetEffect(g_Player.pos, D3DXCOLOR(255, 255, 0, 255), EFFECT_SIZE_X, EFFECT_SIZE_Y, EFFECTTYPE_UP_R, EFFECT_LIFE * 2);

		g_EffectTime = EFFECT_COOLDOWN;
	}
	else if (g_EffectTime >= 0)
	{
		g_EffectTime--;
	}

	//****************************************
	//当たり判定
	//****************************************
	Object *pObject;
	pObject = GetObject();

	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (pObject[nCntObject].bUse == true)
		{
			if (g_Player.pos.x >= pObject[nCntObject].pos.x + (pObject[nCntObject].VtxMinObject.x) && g_Player.pos.x <= pObject[nCntObject].pos.x + (pObject[nCntObject].VtxMaxObject.x) &&
				g_Player.pos.y >= pObject[nCntObject].pos.y + (pObject[nCntObject].VtxMinObject.y) && g_Player.pos.y <= pObject[nCntObject].pos.y + (pObject[nCntObject].VtxMaxObject.y) &&
				g_Player.pos.z >= pObject[nCntObject].pos.z + (pObject[nCntObject].VtxMinObject.z) && g_Player.pos.z <= pObject[nCntObject].pos.z + (pObject[nCntObject].VtxMaxObject.z))
			{
				g_Player.pos = g_Oldpos;
			}
		}
	}
	g_Oldpos = g_Player.pos;

	UpdateShadow();

}

//描画処理
void DrawModel(void)
{

	LPDIRECT3DDEVICE9 pDevice;//デバイスのポインタ
	pDevice = GetDevice();//デバイスを取得する
	D3DXMATRIX mtxRot, mtxTrans;//計算用マトリックス

	D3DMATERIAL9 matDef;//現在のマテリアル保存
	D3DXMATERIAL *pMat;//マテリアルデータポインタ

	D3DXMatrixIdentity(&g_Player.mtxWorldPlayer);//ワールドマトリックスの初期化

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);
	D3DXMatrixMultiply(&g_Player.mtxWorldPlayer, &g_Player.mtxWorldPlayer, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
	D3DXMatrixMultiply(&g_Player.mtxWorldPlayer, &g_Player.mtxWorldPlayer, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_Player.mtxWorldPlayer);

	//パーツ１つ１つに設定をする
	for (int nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
	{
		D3DXMATRIX mtxRotModel, mtxTransModel;//計算用マトリックス
		D3DXMATRIX mtxParent;//親のマトリックス

		D3DXMatrixIdentity(&g_Player.aModel[nCntModel].mtxWorldModel);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_Player.aModel[nCntModel].rot.y, g_Player.aModel[nCntModel].rot.x, g_Player.aModel[nCntModel].rot.z);
		D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorldModel, &g_Player.aModel[nCntModel].mtxWorldModel, &mtxRotModel);

		//位置を反映
		D3DXMatrixTranslation(&mtxTransModel, g_Player.aModel[nCntModel].pos.x, g_Player.aModel[nCntModel].pos.y, g_Player.aModel[nCntModel].pos.z);
		D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorldModel, &g_Player.aModel[nCntModel].mtxWorldModel, &mtxTransModel);

		//親のマトリックスを反映
		if (g_Player.aModel[nCntModel].nIndxModelParent != -1)
		{
			mtxParent = g_Player.aModel[g_Player.aModel[nCntModel].nIndxModelParent].mtxWorldModel;
		}
		else
		{
			mtxParent = g_Player.mtxWorldPlayer;
		}
		//算出した各パーツのマトリックスと親のマトリックを掛け合わせる
		D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorldModel, &g_Player.aModel[nCntModel].mtxWorldModel, &mtxParent);

		//マトリックスをセット
		pDevice->SetTransform(D3DTS_WORLD, &g_Player.aModel[nCntModel].mtxWorldModel);

		//現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);

		//マテリアルデータの取得
		pMat = (D3DXMATERIAL*)g_Player.aModel[nCntModel].pBuffMatModel->GetBufferPointer();

		//パーツ分回す
		for (int nCntMat = 0; nCntMat < (int)g_Player.aModel[nCntModel].nNumMatmodel; nCntMat++)
		{
			//マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
			//テクスチャの設定
			pDevice->SetTexture(0, NULL);
			//モデルパーツの描画
			g_Player.aModel[nCntModel].pMeshModel->DrawSubset(nCntMat);
		}

	}
	//保存したマテリアル戻す
	pDevice->SetMaterial(&matDef);
}

Player *GetModel(void)
{
	return &g_Player;
}
