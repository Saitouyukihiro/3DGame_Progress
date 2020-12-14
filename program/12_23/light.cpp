//---------------------------
//インクルードファイル
//---------------------------
#include "light.h"
#include "keyinput.h"
#include "camara.h"

//---------------------------
//グローバル変数
//---------------------------
D3DLIGHT9		g_Ligt[MAX_LIGHT];	//ライト
LightSelect		g_bUse[MAX_LIGHT];	//選択してるか

//---------------------------
//初期化処理
//---------------------------
HRESULT InitLight(void)
{
	LPDIRECT3DDEVICE9	pDevice;				//デバイスのポインタ
	D3DXVECTOR3			VecDir[MAX_LIGHT];		//ベクトル

	pDevice = GetDevice();			//デバイスを取得する

	g_bUse[0].bUse = true;
	g_bUse[1].bUse = false;
	g_bUse[2].bUse = false;
	for (int nCntLihgt = 0; nCntLihgt < MAX_LIGHT; nCntLihgt++)
	{
		g_bUse[nCntLihgt].bSelect = TRUE;
		g_bUse[nCntLihgt].Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	//---------------------------
	//ライトの設定
	//---------------------------

	for (int nCntLihgt = 0; nCntLihgt < MAX_LIGHT; nCntLihgt++)
	{
		//ライトのクリア
		ZeroMemory(	&g_Ligt[nCntLihgt],
					sizeof(D3DLIGHT9));

		if (nCntLihgt == 0)
		{
			//ライトの種類
			g_Ligt[nCntLihgt].Type = D3DLIGHT_DIRECTIONAL;	//種類

			//ライトの拡散光
			g_Ligt[nCntLihgt].Diffuse = (D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	//色

			//ライトの場所
			g_Ligt[nCntLihgt].Position = (D3DXVECTOR3(-1000.0f, 1000.0f, 1000.0f));

			//ライトの方向
			VecDir[nCntLihgt] = (D3DXVECTOR3(0.2f, -0.8f, 0.6f));

			//正規化する
			D3DXVec3Normalize(	&VecDir[nCntLihgt],
								&VecDir[nCntLihgt]);

			//ライトの方向を入れる
			g_Ligt[nCntLihgt].Direction = VecDir[nCntLihgt];

			//ライトの設定
			pDevice->SetLight(nCntLihgt, &g_Ligt[nCntLihgt]);	//0番目のライトに設定した設定を入れる

			//ライトを有効にする
			pDevice->LightEnable(nCntLihgt, TRUE);	//0番目のライトを付ける
		}
		else if (nCntLihgt == 1)
		{
			//ライトの種類
			g_Ligt[nCntLihgt].Type = D3DLIGHT_DIRECTIONAL;	//種類

			//ライトの拡散光
			g_Ligt[nCntLihgt].Diffuse = (D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	//色

			//ライトの場所
			g_Ligt[nCntLihgt].Position = (D3DXVECTOR3(0.0f, 1000.0f, 0.0f));

			//ライトの方向
			VecDir[nCntLihgt] = (D3DXVECTOR3(0.0f, -1.0f, 0.0f));

			//正規化する
			D3DXVec3Normalize(	&VecDir[nCntLihgt],
								&VecDir[nCntLihgt]);

			//ライトの方向を入れる
			g_Ligt[nCntLihgt].Direction = VecDir[nCntLihgt];

			//ライトの設定
			pDevice->SetLight(nCntLihgt, &g_Ligt[nCntLihgt]);	//1番目のライトに設定した設定を入れる

			//ライトを有効にする
			pDevice->LightEnable(nCntLihgt, TRUE);	//1番目のライトを付ける
		}
		else if (nCntLihgt == 2)
		{
			//ライトの種類
			g_Ligt[nCntLihgt].Type = D3DLIGHT_DIRECTIONAL;	//種類

			//ライトの拡散光
			g_Ligt[nCntLihgt].Diffuse = (D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	//色

			//ライトの場所
			g_Ligt[nCntLihgt].Position = (D3DXVECTOR3(3000.0f, -1000.0f, -3000.0f));

			//ライトの方向
			VecDir[nCntLihgt] = (D3DXVECTOR3(-0.2f, 0.8f, -0.6f));

			//正規化する
			D3DXVec3Normalize(	&VecDir[nCntLihgt],
								&VecDir[nCntLihgt]);

			//ライトの方向を入れる
			g_Ligt[nCntLihgt].Direction = VecDir[nCntLihgt];

			//ライトの設定
			pDevice->SetLight(nCntLihgt, &g_Ligt[nCntLihgt]);	//2番目のライトに設定した設定を入れる

			//ライトを有効にする
			pDevice->LightEnable(nCntLihgt, TRUE);	//2番目のライトを付ける
		}
	}
	return S_OK;
}

//---------------------------
//終了処理
//---------------------------
void UninitLight(void)
{

}

//---------------------------
//更新処理
//---------------------------
void UpdateLight(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスのポインタ
	D3DXVECTOR3	VecDir[MAX_LIGHT];	//ベクトル

	pDevice = GetDevice();			//デバイスを取得する

	//---------------------------
	//ライトの移動
	//---------------------------
	for (int nCntLihgt = 0; nCntLihgt < MAX_LIGHT; nCntLihgt++)
	{
		if (g_bUse[nCntLihgt].bUse == true)
		{
			if (GetKeyboardPress(DIK_UP) == true)
			{
				g_bUse[nCntLihgt].Rot.x += 0.1f;

				//ライトの方向を入れる
				g_Ligt[nCntLihgt].Direction.y = g_Ligt[nCntLihgt].Direction.y += sinf(g_bUse[nCntLihgt].Rot.x) * LIGHT_MOVE_SPEED;
				g_Ligt[nCntLihgt].Direction.z = g_Ligt[nCntLihgt].Direction.z += cosf(g_bUse[nCntLihgt].Rot.x) * LIGHT_MOVE_SPEED;

				//ライトの設定
				pDevice->SetLight(nCntLihgt, &g_Ligt[nCntLihgt]);	//2番目のライトに設定した設定を入れる
			}
			else if (GetKeyboardPress(DIK_DOWN) == true)
			{
				g_bUse[nCntLihgt].Rot.x -= 0.1f;

				//ライトの方向を入れる
				g_Ligt[nCntLihgt].Direction.y = g_Ligt[nCntLihgt].Direction.y += sinf(g_bUse[nCntLihgt].Rot.x) * LIGHT_MOVE_SPEED;
				g_Ligt[nCntLihgt].Direction.z = g_Ligt[nCntLihgt].Direction.z += cosf(g_bUse[nCntLihgt].Rot.x) * LIGHT_MOVE_SPEED;

				//ライトの設定
				pDevice->SetLight(nCntLihgt, &g_Ligt[nCntLihgt]);	//2番目のライトに設定した設定を入れる
			}
			else if (GetKeyboardPress(DIK_LEFT) == true)
			{
				g_bUse[nCntLihgt].Rot.y -= 0.1f;

				//ライトの方向を入れる
				g_Ligt[nCntLihgt].Direction.x = g_Ligt[nCntLihgt].Direction.x += sinf(g_bUse[nCntLihgt].Rot.y) * LIGHT_MOVE_SPEED;
				g_Ligt[nCntLihgt].Direction.z = g_Ligt[nCntLihgt].Direction.z += cosf(g_bUse[nCntLihgt].Rot.y) * LIGHT_MOVE_SPEED;

				//ライトの設定
				pDevice->SetLight(nCntLihgt, &g_Ligt[nCntLihgt]);	//2番目のライトに設定した設定を入れる
			}
			else if (GetKeyboardPress(DIK_RIGHT) == true)
			{

				g_bUse[nCntLihgt].Rot.y += 0.1f;

				//ライトの方向を入れる
				g_Ligt[nCntLihgt].Direction.x = g_Ligt[nCntLihgt].Direction.x += sinf(g_bUse[nCntLihgt].Rot.y) * LIGHT_MOVE_SPEED;
				g_Ligt[nCntLihgt].Direction.z = g_Ligt[nCntLihgt].Direction.z += cosf(g_bUse[nCntLihgt].Rot.y) * LIGHT_MOVE_SPEED;

				//ライトの設定
				pDevice->SetLight(nCntLihgt, &g_Ligt[nCntLihgt]);	//2番目のライトに設定した設定を入れる
			}
			//---------------------------
			//ライトの切り替え
			//---------------------------
			if (GetKeyboardTrigger(DIK_F) == true)
			{
				//ついてたら消す、消えてたら付ける
				g_bUse[nCntLihgt].bSelect = g_bUse[nCntLihgt].bSelect ? FALSE : TRUE;
				//ライトの設定
				pDevice->LightEnable(nCntLihgt, g_bUse[nCntLihgt].bSelect);	//選択番目のライト
			}
		}
	}
	//---------------------------
	//ライトの切り替え
	//---------------------------
	if (GetKeyboardTrigger(DIK_3) == true)
	{
		if (g_bUse[0].bUse == true)
		{
			g_bUse[2].bUse = true;
			g_bUse[0].bUse = false;
		}
		else if (g_bUse[1].bUse == true)
		{
			g_bUse[0].bUse = true;
			g_bUse[1].bUse = false;
		}
		else if (g_bUse[2].bUse == true)
		{
			g_bUse[1].bUse = true;
			g_bUse[2].bUse = false;
		}
	}
	else if (GetKeyboardTrigger(DIK_4) == true)
	{
		if (g_bUse[0].bUse == true)
		{
			g_bUse[1].bUse = true;
			g_bUse[0].bUse = false;
		}
		else if (g_bUse[1].bUse == true)
		{
			g_bUse[2].bUse = true;
			g_bUse[1].bUse = false;
		}
		else if (g_bUse[2].bUse == true)
		{
			g_bUse[3].bUse = true;
			g_bUse[2].bUse = false;
		}
	}
}
//---------------------------
//ライトの情報
//---------------------------
D3DLIGHT9 *GetLight(void)
{
	return &g_Ligt[0];
}
//---------------------------
//ライトの情報
//---------------------------
LightSelect *GetLightSelect(void)
{
	return &g_bUse[0];
}