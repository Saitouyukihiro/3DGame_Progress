//**************************************************************
//残弾数表示の処理
//Author：佐藤秀亮
//**************************************************************

#include "Magazine.h"
#include "keyinput.h"
#include "mouseinput.h"
#include "bullet.h"
#include "camara.h"
#include "player.h"

//マクロ定義
#define MAX_MAGAZINE (2)

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureMagazine = NULL;//テクスチャへのポインタ

											   //頂点バッファのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMagazine = NULL; //バッファへのポインタ
int g_nMagazineBullet;//計算用
int g_nCntBullet = 30;//「」に現在の弾数の情報をいれる

Magazine g_aMagazine[MAX_MAGAZINE];
Equipment g_aEquipment;

//初期化処理
void InitMagazine(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスのポインタ
	int nCntMagazine;
	pDevice = GetDevice();//デバイスの取得

	for (nCntMagazine = 0; nCntMagazine < MAX_MAGAZINE; nCntMagazine++)
	{
		g_aMagazine[nCntMagazine].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	g_aEquipment.state = TYPE_ASSULT;//初期でとりあえずアサルト

	g_nCntBullet = 30;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/Texture/number.png", &g_pTextureMagazine);
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_MAGAZINE, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffMagazine, NULL);
	VERTEX_2D*pVtx;//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffMagazine->Lock(0, 0, (void**)&pVtx, 0);


	for (nCntMagazine = 0; nCntMagazine < MAX_MAGAZINE; nCntMagazine++)
	{
		g_aMagazine[nCntMagazine].pos = D3DXVECTOR3(1670.0f + 30.0f * nCntMagazine, 1020.0f, 0.0f);//スコア表示場所

		//頂点の座標
		pVtx[0].pos = D3DXVECTOR3(700.0f + 40.0f * nCntMagazine, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(750.0f + 40.0f * nCntMagazine, 0.0f, 0.0);
		pVtx[2].pos = D3DXVECTOR3(700.0f + 40.0f * nCntMagazine, 50.0f, 0.0);
		pVtx[3].pos = D3DXVECTOR3(750.0f + 40.0f * nCntMagazine, 50.0f, 0.0);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;


		//頂点の色
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャのUV座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;
	}


	//頂点バッファをアンロック
	g_pVtxBuffMagazine->Unlock();

}

//終了処理
void UninitMagazine(void)
{
	//テクスチャの破棄
	if (g_pTextureMagazine != NULL)
	{
		g_pTextureMagazine->Release();
		g_pTextureMagazine = NULL;
	}

	//頂点バッファも破棄
	if (g_pVtxBuffMagazine != NULL)
	{
		g_pVtxBuffMagazine->Release();
		g_pVtxBuffMagazine = NULL;
	}
}

//更新処理
void UpdateMagazine(void)
{
	Player *pPlayer;
	Camera *pCamera;
	pCamera = GetCamera();
	pPlayer = GetPlayer();
	int aMagazineBullet[MAX_MAGAZINE];
	int nCntMagazine;
	static int nCntSpan;
	static int nCntReload;

	int nCntMagazineBlt;

	nCntSpan++;

	if (MouseDowan(MOUSE_LEFT_BOTTON) == true && nCntSpan > BULLET_SPAN)
	{
		SetBullet(D3DXVECTOR3(pPlayer->pos.x, pPlayer->pos.y + 25.0f, pPlayer->pos.z), pCamera->Rot, D3DXVECTOR3(sinf(pCamera->Rot.y) * BULLET_MOVE_SPEED, sinf(pCamera->Rot.x) * BULLET_MOVE_SPEED, cosf(pCamera->Rot.y) * BULLET_MOVE_SPEED), BULlET_SCALE_X, BULLET_SCALE_Y, BULLET_ASULT);
		g_nCntBullet = g_nCntBullet - 1;
		nCntSpan = 0;
	}

	if (g_nCntBullet <= 0)//残弾数0で
	{
		nCntReload++;
		switch (g_aEquipment.state)//装備してる銃のタイプで最大数が変わるように
		{
		case(TYPE_ASSULT)://アサルト
			{
				if (nCntReload > 144)
				{
					g_nCntBullet = 30;
					nCntReload = 0;
				}
				nCntMagazineBlt = 30;
				break;
			}
		case(TYPE_HANDGUN)://ハンドガン
			{
				nCntMagazineBlt = 10;
				break;
			}

		}
		g_nCntBullet = nCntMagazineBlt;
	}

	if (GetKeyboardTrigger(DIK_R) == true)
	{
		g_nCntBullet = 30;
	}

	g_nMagazineBullet = g_nCntBullet;




	VERTEX_2D*pVtx;//頂点情報へのポインタ

	aMagazineBullet[0] = g_nMagazineBullet % 100 / 10;
	aMagazineBullet[1] = g_nMagazineBullet % 10 / 1;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffMagazine->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntMagazineBullet = 0; nCntMagazineBullet < MAX_MAGAZINE; nCntMagazineBullet++)
	{
		//頂点の座標
		pVtx[0].pos = D3DXVECTOR3(g_aMagazine[nCntMagazineBullet].pos.x - (30.0f / 2), g_aMagazine[nCntMagazineBullet].pos.y - (30.0f / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aMagazine[nCntMagazineBullet].pos.x + (30.0f / 2), g_aMagazine[nCntMagazineBullet].pos.y - (30.0f / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aMagazine[nCntMagazineBullet].pos.x - (30.0f / 2), g_aMagazine[nCntMagazineBullet].pos.y + (30.0f / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aMagazine[nCntMagazineBullet].pos.x + (30.0f / 2), g_aMagazine[nCntMagazineBullet].pos.y + (30.0f / 2), 0.0f);

		//テクスチャのUV座標
		pVtx[0].tex = D3DXVECTOR2(aMagazineBullet[nCntMagazineBullet] * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(aMagazineBullet[nCntMagazineBullet] * 0.1f + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(aMagazineBullet[nCntMagazineBullet] * 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(aMagazineBullet[nCntMagazineBullet] * 0.1f + 0.1f, 1.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロック
	g_pVtxBuffMagazine->Unlock();
}

//描画処理
void DrawMagazine(void)
{

	LPDIRECT3DDEVICE9 pDevice;//デバイスのポインタ
	pDevice = GetDevice();//デバイスを取得する

						  //頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMagazine, 0, sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);//頂点フォーマットの設定
	pDevice->SetTexture(0, g_pTextureMagazine);//テクスチャの設定

	for (int nCntMagazine = 0; nCntMagazine < MAX_MAGAZINE; nCntMagazine++)
	{
		//αテスト
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 110);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntMagazine * 4, 2);

		//αテスト
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);
	}
}

void AddMagazine(int nValue)
{
	g_nMagazineBullet += nValue;
}

Magazine *GetMagazine(void)
{
	return &g_aMagazine[0];
}

