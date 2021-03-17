//**************************************************************
//UIの処理(UI.cpp)
//**************************************************************

#include "UI.h"

#define FILENAMETEXT "data/UINameRead.txt"	//読み込むスクリプトファイル名


LPDIRECT3DTEXTURE9 g_pTextureGameUI[64] = {};//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGameUI = NULL;//頂点バッファへのポインタ

GAMEUI g_aGameUI[MAX_GAMEUI];
UIserect g_UIserect;

int g_MaxUITexture;
int g_UITexture;
//初期化
void InitGameUI(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//デバイスのポインタ
	int nCntGameUI;

	g_MaxUITexture = 0;
	g_UITexture = 0;

	int Textype = 0;
	D3DXVECTOR3 UIpos = D3DXVECTOR3(0.0, 0.0, 0.0);
	float Width = 0;
	float Heigth = 0;

	char aFile[256];
	bool bSet = false;
	bool bSetGameUI = false;

	FILE *pFile = fopen(FILENAMETEXT, "r");

	if (pFile != NULL)//一度ファイルを読み込んで必要な情報を抜く
	{
		while (true)
		{
			fscanf(pFile, "%s", &aFile[0]);
			if (strcmp(&aFile[0], "NUM_TEXTURE") == 0)	//NUM_TEXTUREの文字列を見つけたら
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d", &g_MaxUITexture);
			}
			if (strcmp(&aFile[0], "TEXTURE_FILENAME") == 0) //TEXTURE_FILENAMEの文字列を見つけたら
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%s", &aFile[0]);
				D3DXCreateTextureFromFile(pDevice, &aFile[0], &g_pTextureGameUI[g_UITexture]);
				g_UITexture++;
			}
			
			if (strcmp(&aFile[0], "END_SCRIPT") == 0) //END_SCRIPTの文字列を見つけたら
			{
				break;
			}
		}
	}
	fclose(pFile);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_GAMEUI, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffGameUI, NULL);
	//それぞれの初期化
	for (nCntGameUI = 0; nCntGameUI < MAX_GAMEUI; nCntGameUI++)
	{
		g_aGameUI[nCntGameUI].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aGameUI[nCntGameUI].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aGameUI[nCntGameUI].color = D3DXCOLOR(255, 255, 255, 255);
		g_aGameUI[nCntGameUI].ntype;
		g_aGameUI[nCntGameUI].bUse = false;
		g_aGameUI[nCntGameUI].fWidth = 0;
		g_aGameUI[nCntGameUI].fHeight = 0;
	}
	g_UIserect.Serect = 0;
	VERTEX_2D*pVtx;//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffGameUI->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntGameUI = 0; nCntGameUI < MAX_GAMEUI; nCntGameUI++)
	{
		for (int nVtxUI = 0; nVtxUI < 4; nVtxUI++)
		{
			//頂点の座標
			pVtx[nVtxUI].pos = D3DXVECTOR3(g_aGameUI[nCntGameUI].pos.x - (0.0f / 2), g_aGameUI[nCntGameUI].pos.y - (0.0f / 2), 0.0f);

			//rhwの設定
			pVtx[nVtxUI].rhw = 1.0f;

			//頂点の色
			pVtx[nVtxUI].col = g_aGameUI[nCntGameUI].color;

			//テクスチャのUV座標
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[3].tex = D3DXVECTOR2(0.0f, 0.0f);
		}
		pVtx += 4;
	}
	//頂点バッファをアンロック
	g_pVtxBuffGameUI->Unlock();
	pFile = fopen(FILENAMETEXT, "r");//二度目の読み込みでセット

	ModeStyle * pStyle = GetModeStyle();

	if (pFile != NULL)//一度ファイルを読み込んで必要な情報を抜く
	{
		while (true)
		{
			fscanf(pFile, "%s", &aFile[0]);
			if (bSetGameUI == true)
			{
				if (bSet == true)
				{
					if (strcmp(&aFile[0], "TYPE") == 0)	//TYPEの文字列を見つけたら
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &Textype);
					}
					if (strcmp(&aFile[0], "POS") == 0)	//POSの文字列を見つけたら
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f%f%f", &UIpos.x, &UIpos.y, &UIpos.z);
					}
					if (strcmp(&aFile[0], "WIDTH") == 0)	//WIDTHの文字列を見つけたら
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f", &Width);
					}
					if (strcmp(&aFile[0], "HEIGTH") == 0)	//HEIGTHの文字列を見つけたら
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f", &Heigth);
					}
				}

				if (strcmp(&aFile[0], "UISET") == 0)	//UISETの文字列を見つけたら
				{
					bSet = true;
				}
				if (strcmp(&aFile[0], "END_UISET") == 0)	//END_UISETの文字列を見つけたら
				{
					bSet = false;
					SetGameUI(UIpos, Width, Heigth, Textype);
				}
			}
			if (strcmp(&aFile[0], "END_SCRIPT") == 0) //END_SCRIPTの文字列を見つけたら
			{
				break;
			}

		}
	}
	fclose(pFile);


}

//終了処理
void UninitGameUI(void)
{
	int nCntGameUI;
	for (nCntGameUI = 0; nCntGameUI < g_MaxUITexture; nCntGameUI++)
	{
		//テクスチャの破棄
		if (g_pTextureGameUI[nCntGameUI] != NULL)
		{
			g_pTextureGameUI[nCntGameUI]->Release();
			g_pTextureGameUI[nCntGameUI] = NULL;
		}

		//頂点バッファも破棄
		if (g_pVtxBuffGameUI != NULL)
		{
			g_pVtxBuffGameUI->Release();
			g_pVtxBuffGameUI = NULL;
		}
	}
}

//更新処理
void UpdateGameUI(void)
{
	VERTEX_2D*pVtx;//頂点情報へのポインタ
	ModeStyle * pStyle = GetModeStyle();
	

	for (int nCntUI = 0; nCntUI < MAX_GAMEUI; nCntUI++)
	{
		if (g_aGameUI[nCntUI].bUse == true)
		{
			if (g_aGameUI[nCntUI].ntype == 15)
			{
				if (g_aGameUI[nCntUI].pos.y < 200.0f)
				{
					g_aGameUI[nCntUI].pos.y += 5;
				}
				else if (g_aGameUI[nCntUI].pos.y >= 200.0f)
				{
					g_aGameUI[nCntUI].pos.y = 200.0f;
				}

				//頂点バッファをロックし、頂点データへのポインタを取得
				g_pVtxBuffGameUI->Lock(0, 0, (void**)&pVtx, 0);
				pVtx += (nCntUI * 4);

				//頂点の座標
				pVtx[0].pos = D3DXVECTOR3(g_aGameUI[nCntUI].pos.x - (g_aGameUI[nCntUI].fWidth / 2), g_aGameUI[nCntUI].pos.y - (g_aGameUI[nCntUI].fHeight / 2), 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aGameUI[nCntUI].pos.x + (g_aGameUI[nCntUI].fWidth / 2), g_aGameUI[nCntUI].pos.y - (g_aGameUI[nCntUI].fHeight / 2), 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aGameUI[nCntUI].pos.x - (g_aGameUI[nCntUI].fWidth / 2), g_aGameUI[nCntUI].pos.y + (g_aGameUI[nCntUI].fHeight / 2), 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aGameUI[nCntUI].pos.x + (g_aGameUI[nCntUI].fWidth / 2), g_aGameUI[nCntUI].pos.y + (g_aGameUI[nCntUI].fHeight / 2), 0.0f);

				//頂点バッファをアンロック
				g_pVtxBuffGameUI->Unlock();

			}
		}
	}
	
	switch (pStyle->Modestyle)
	{
	case(MODE_TITLE):
		switch (g_UIserect.Serect)
		{
		case(0):
			for (int nCntUI = 0; nCntUI < MAX_GAMEUI; nCntUI++)
			{
				if (g_aGameUI[nCntUI].bUse == true)
				{
					if (g_aGameUI[nCntUI].ntype == GAMEUITYPE_TUTOLIAL)
					{

						//頂点バッファをロックし、頂点データへのポインタを取得
						g_pVtxBuffGameUI->Lock(0, 0, (void**)&pVtx, 0);
						pVtx += (nCntUI * 4);

						//頂点の色
						pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 100);
						pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 100);
						pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 100);
						pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 100);

						//頂点バッファをアンロック
						g_pVtxBuffGameUI->Unlock();
					}

					else if (g_aGameUI[nCntUI].ntype == GAMEUITYPE_GAMESTART)
					{


						//頂点バッファをロックし、頂点データへのポインタを取得
						g_pVtxBuffGameUI->Lock(0, 0, (void**)&pVtx, 0);
						pVtx += (nCntUI * 4);

						//頂点の色
						pVtx[0].col = D3DXCOLOR(255, 255, 255, 255);
						pVtx[1].col = D3DXCOLOR(255, 255, 255, 255);
						pVtx[2].col = D3DXCOLOR(255, 255, 255, 255);
						pVtx[3].col = D3DXCOLOR(255, 255, 255, 255);

						//頂点バッファをアンロック
						g_pVtxBuffGameUI->Unlock();

					}
				}
			}
			break;

		case(1):
			for (int nCntUI = 0; nCntUI < MAX_GAMEUI; nCntUI++)
			{
				if (g_aGameUI[nCntUI].ntype == GAMEUITYPE_GAMESTART)
				{
					if (g_aGameUI[nCntUI].bUse == true)
					{
						//頂点バッファをロックし、頂点データへのポインタを取得
						g_pVtxBuffGameUI->Lock(0, 0, (void**)&pVtx, 0);
						pVtx += (nCntUI * 4);

						//頂点の色
						pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 100);
						pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 100);
						pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 100);
						pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 100);

						//頂点バッファをアンロック
						g_pVtxBuffGameUI->Unlock();
					}
				}
				else if (g_aGameUI[nCntUI].ntype == GAMEUITYPE_TUTOLIAL)
				{
					if (g_aGameUI[nCntUI].bUse == true)
					{
						//頂点バッファをロックし、頂点データへのポインタを取得
						g_pVtxBuffGameUI->Lock(0, 0, (void**)&pVtx, 0);
						pVtx += (nCntUI * 4);

						//頂点の色
						pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
						pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
						pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
						pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

						//頂点バッファをアンロック
						g_pVtxBuffGameUI->Unlock();
					}

				}

			}
			break;
		}
		break;


	case(MODE_GAME):
		switch (g_UIserect.Serect)
		{
		case(0):
			for (int nCntUI = 0; nCntUI < MAX_GAMEUI; nCntUI++)
			{
				if (g_aGameUI[nCntUI].bUse == true)
				{
					if (g_aGameUI[nCntUI].ntype == GAMEUITYPE_QUIT || g_aGameUI[nCntUI].ntype == GAMEUITYPE_RETRY)
					{

						//頂点バッファをロックし、頂点データへのポインタを取得
						g_pVtxBuffGameUI->Lock(0, 0, (void**)&pVtx, 0);
						pVtx += (nCntUI * 4);

						//頂点の色
						pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 100);
						pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 100);
						pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 100);
						pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 100);

						//頂点バッファをアンロック
						g_pVtxBuffGameUI->Unlock();
					}
					else if (g_aGameUI[nCntUI].ntype == GAMEUITYPE_CONTINUE)
					{

						//頂点バッファをロックし、頂点データへのポインタを取得
						g_pVtxBuffGameUI->Lock(0, 0, (void**)&pVtx, 0);
						pVtx += (nCntUI * 4);

						//頂点の色
						pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
						pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
						pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
						pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

						//頂点バッファをアンロック
						g_pVtxBuffGameUI->Unlock();

					}
				}
			}
			break;
		case(1):
			for (int nCntUI = 0; nCntUI < MAX_GAMEUI; nCntUI++)
			{
				if (g_aGameUI[nCntUI].ntype == GAMEUITYPE_CONTINUE || g_aGameUI[nCntUI].ntype == GAMEUITYPE_QUIT)
				{
					if (g_aGameUI[nCntUI].bUse == true)
					{
						//頂点バッファをロックし、頂点データへのポインタを取得
						g_pVtxBuffGameUI->Lock(0, 0, (void**)&pVtx, 0);
						pVtx += (nCntUI * 4);

						//頂点の色
						pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 100);
						pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 100);
						pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 100);
						pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 100);

						//頂点バッファをアンロック
						g_pVtxBuffGameUI->Unlock();
					}
				}
				else if (g_aGameUI[nCntUI].ntype == GAMEUITYPE_RETRY)
				{
					if (g_aGameUI[nCntUI].bUse == true)
					{
						//頂点バッファをロックし、頂点データへのポインタを取得
						g_pVtxBuffGameUI->Lock(0, 0, (void**)&pVtx, 0);
						pVtx += (nCntUI * 4);

						//頂点の色
						pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
						pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
						pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
						pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

						//頂点バッファをアンロック
						g_pVtxBuffGameUI->Unlock();
					}

				}
			}
			break;
		case(2):
			for (int nCntUI = 0; nCntUI < MAX_GAMEUI; nCntUI++)
			{
				if (g_aGameUI[nCntUI].ntype == GAMEUITYPE_CONTINUE || g_aGameUI[nCntUI].ntype == GAMEUITYPE_RETRY)
				{
					if (g_aGameUI[nCntUI].bUse == true)
					{
						//頂点バッファをロックし、頂点データへのポインタを取得
						g_pVtxBuffGameUI->Lock(0, 0, (void**)&pVtx, 0);
						pVtx += (nCntUI * 4);

						//頂点の色
						pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 100);
						pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 100);
						pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 100);
						pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 100);

						//頂点バッファをアンロック
						g_pVtxBuffGameUI->Unlock();
					}
				}
				else if (g_aGameUI[nCntUI].ntype == GAMEUITYPE_QUIT)
				{
					if (g_aGameUI[nCntUI].bUse == true)
					{
						//頂点バッファをロックし、頂点データへのポインタを取得
						g_pVtxBuffGameUI->Lock(0, 0, (void**)&pVtx, 0);

						pVtx += (nCntUI * 4);
						//頂点の色
						pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
						pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
						pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
						pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);


						//頂点バッファをアンロック
						g_pVtxBuffGameUI->Unlock();
					}
				}
			}
			break;
		}
		break;

			case(MODE_TUTORIAL):
				switch (g_UIserect.Serect)
				{
				case(0):
					for (int nCntUI = 0; nCntUI < MAX_GAMEUI; nCntUI++)
					{
						if (g_aGameUI[nCntUI].bUse == true)
						{
							if (g_aGameUI[nCntUI].ntype == GAMEUITYPE_QUIT || g_aGameUI[nCntUI].ntype == GAMEUITYPE_RETRY)
							{

								//頂点バッファをロックし、頂点データへのポインタを取得
								g_pVtxBuffGameUI->Lock(0, 0, (void**)&pVtx, 0);
								pVtx += (nCntUI * 4);

								//頂点の色
								pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 100);
								pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 100);
								pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 100);
								pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 100);

								//頂点バッファをアンロック
								g_pVtxBuffGameUI->Unlock();
							}
							else if (g_aGameUI[nCntUI].ntype == GAMEUITYPE_CONTINUE)
							{

								//頂点バッファをロックし、頂点データへのポインタを取得
								g_pVtxBuffGameUI->Lock(0, 0, (void**)&pVtx, 0);
								pVtx += (nCntUI * 4);

								//頂点の色
								pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
								pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
								pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
								pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

								//頂点バッファをアンロック
								g_pVtxBuffGameUI->Unlock();

							}
						}
					}
					break;
				case(1):
					for (int nCntUI = 0; nCntUI < MAX_GAMEUI; nCntUI++)
					{
						if (g_aGameUI[nCntUI].ntype == GAMEUITYPE_CONTINUE || g_aGameUI[nCntUI].ntype == GAMEUITYPE_QUIT)
						{
							if (g_aGameUI[nCntUI].bUse == true)
							{
								//頂点バッファをロックし、頂点データへのポインタを取得
								g_pVtxBuffGameUI->Lock(0, 0, (void**)&pVtx, 0);
								pVtx += (nCntUI * 4);

								//頂点の色
								pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 100);
								pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 100);
								pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 100);
								pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 100);

								//頂点バッファをアンロック
								g_pVtxBuffGameUI->Unlock();
							}
						}
						else if (g_aGameUI[nCntUI].ntype == GAMEUITYPE_RETRY)
						{
							if (g_aGameUI[nCntUI].bUse == true)
							{
								//頂点バッファをロックし、頂点データへのポインタを取得
								g_pVtxBuffGameUI->Lock(0, 0, (void**)&pVtx, 0);
								pVtx += (nCntUI * 4);

								//頂点の色
								pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
								pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
								pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
								pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

								//頂点バッファをアンロック
								g_pVtxBuffGameUI->Unlock();
							}

						}
					}
					break;
				case(2):
					for (int nCntUI = 0; nCntUI < MAX_GAMEUI; nCntUI++)
					{
						if (g_aGameUI[nCntUI].ntype == GAMEUITYPE_CONTINUE || g_aGameUI[nCntUI].ntype == GAMEUITYPE_RETRY)
						{
							if (g_aGameUI[nCntUI].bUse == true)
							{
								//頂点バッファをロックし、頂点データへのポインタを取得
								g_pVtxBuffGameUI->Lock(0, 0, (void**)&pVtx, 0);
								pVtx += (nCntUI * 4);

								//頂点の色
								pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 100);
								pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 100);
								pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 100);
								pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 100);

								//頂点バッファをアンロック
								g_pVtxBuffGameUI->Unlock();
							}
						}
						else if (g_aGameUI[nCntUI].ntype == GAMEUITYPE_QUIT)
						{
							if (g_aGameUI[nCntUI].bUse == true)
							{
								//頂点バッファをロックし、頂点データへのポインタを取得
								g_pVtxBuffGameUI->Lock(0, 0, (void**)&pVtx, 0);

								pVtx += (nCntUI * 4);
								//頂点の色
								pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
								pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
								pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
								pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);


								//頂点バッファをアンロック
								g_pVtxBuffGameUI->Unlock();
							}
						}
					}
					break;
				}
				break;

	}

}

//描画処理
void DrawGameUI(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスのポインタ
	pDevice = GetDevice();//デバイスを取得する

						  //頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffGameUI, 0, sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);//頂点フォーマットの設定
	for (int nCntGameUI = 0; nCntGameUI < MAX_GAMEUI; nCntGameUI++)
	{
		if (g_aGameUI[nCntGameUI].bUse == true)
		{
			pDevice->SetTexture(0, g_pTextureGameUI[g_aGameUI[nCntGameUI].ntype]);//テクスチャの設定
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntGameUI * 4, 2);//ポリゴンの描画
		}
	}

}

//UIの設定処理
void SetGameUI(D3DXVECTOR3 pos, float fWidth, float fHeight, int ntype)
{
	VERTEX_2D*pVtx;//頂点情報へのポインタ


	int nCntGameUI;
	for (nCntGameUI = 0; nCntGameUI < MAX_GAMEUI; nCntGameUI++)
	{
		if (g_aGameUI[nCntGameUI].bUse == false)
		{
			g_aGameUI[nCntGameUI].pos = pos;//座標入れる
			g_aGameUI[nCntGameUI].ntype = ntype;//タイプを入れる
			g_aGameUI[nCntGameUI].fWidth = fWidth;
			g_aGameUI[nCntGameUI].fHeight = fHeight;
			//頂点バッファをロック
			g_pVtxBuffGameUI->Lock(0, 0, (void**)&pVtx, 0);
			for (int nVtxUI = 0; nVtxUI <= 4; nVtxUI++)
			{
				pVtx += (nCntGameUI * 4);
				//頂点の座標
				pVtx[0].pos = D3DXVECTOR3(g_aGameUI[nCntGameUI].pos.x - (g_aGameUI[nCntGameUI].fWidth / 2), g_aGameUI[nCntGameUI].pos.y - (g_aGameUI[nCntGameUI].fHeight / 2), 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aGameUI[nCntGameUI].pos.x + (g_aGameUI[nCntGameUI].fWidth / 2), g_aGameUI[nCntGameUI].pos.y - (g_aGameUI[nCntGameUI].fHeight / 2), 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aGameUI[nCntGameUI].pos.x - (g_aGameUI[nCntGameUI].fWidth / 2), g_aGameUI[nCntGameUI].pos.y + (g_aGameUI[nCntGameUI].fHeight / 2), 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aGameUI[nCntGameUI].pos.x + (g_aGameUI[nCntGameUI].fWidth / 2), g_aGameUI[nCntGameUI].pos.y + (g_aGameUI[nCntGameUI].fHeight / 2), 0.0f);

				//rhwの設定
				pVtx[nVtxUI].rhw = 1.0f;

				//頂点の色
				pVtx[nVtxUI].col = g_aGameUI[nCntGameUI].color;

				//テクスチャのUV座標
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			}
			
			//アンロック
			g_pVtxBuffGameUI->Unlock();

			g_aGameUI[nCntGameUI].bUse = true;

			break;
		}

	}
}

GAMEUI *GetGameUI(void)
{
	return &g_aGameUI[0];
}

UIserect *GetUIserect(void)
{
	return &g_UIserect;
}