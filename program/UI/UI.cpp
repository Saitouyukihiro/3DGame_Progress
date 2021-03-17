//**************************************************************
//UI�̏���(UI.cpp)
//**************************************************************

#include "UI.h"

#define FILENAMETEXT "data/UINameRead.txt"	//�ǂݍ��ރX�N���v�g�t�@�C����


LPDIRECT3DTEXTURE9 g_pTextureGameUI[64] = {};//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGameUI = NULL;//���_�o�b�t�@�ւ̃|�C���^

GAMEUI g_aGameUI[MAX_GAMEUI];
UIserect g_UIserect;

int g_MaxUITexture;
int g_UITexture;
//������
void InitGameUI(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//�f�o�C�X�̃|�C���^
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

	if (pFile != NULL)//��x�t�@�C����ǂݍ���ŕK�v�ȏ��𔲂�
	{
		while (true)
		{
			fscanf(pFile, "%s", &aFile[0]);
			if (strcmp(&aFile[0], "NUM_TEXTURE") == 0)	//NUM_TEXTURE�̕��������������
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d", &g_MaxUITexture);
			}
			if (strcmp(&aFile[0], "TEXTURE_FILENAME") == 0) //TEXTURE_FILENAME�̕��������������
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%s", &aFile[0]);
				D3DXCreateTextureFromFile(pDevice, &aFile[0], &g_pTextureGameUI[g_UITexture]);
				g_UITexture++;
			}
			
			if (strcmp(&aFile[0], "END_SCRIPT") == 0) //END_SCRIPT�̕��������������
			{
				break;
			}
		}
	}
	fclose(pFile);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_GAMEUI, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffGameUI, NULL);
	//���ꂼ��̏�����
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
	VERTEX_2D*pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffGameUI->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntGameUI = 0; nCntGameUI < MAX_GAMEUI; nCntGameUI++)
	{
		for (int nVtxUI = 0; nVtxUI < 4; nVtxUI++)
		{
			//���_�̍��W
			pVtx[nVtxUI].pos = D3DXVECTOR3(g_aGameUI[nCntGameUI].pos.x - (0.0f / 2), g_aGameUI[nCntGameUI].pos.y - (0.0f / 2), 0.0f);

			//rhw�̐ݒ�
			pVtx[nVtxUI].rhw = 1.0f;

			//���_�̐F
			pVtx[nVtxUI].col = g_aGameUI[nCntGameUI].color;

			//�e�N�X�`����UV���W
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[3].tex = D3DXVECTOR2(0.0f, 0.0f);
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffGameUI->Unlock();
	pFile = fopen(FILENAMETEXT, "r");//��x�ڂ̓ǂݍ��݂ŃZ�b�g

	ModeStyle * pStyle = GetModeStyle();

	if (pFile != NULL)//��x�t�@�C����ǂݍ���ŕK�v�ȏ��𔲂�
	{
		while (true)
		{
			fscanf(pFile, "%s", &aFile[0]);
			if (bSetGameUI == true)
			{
				if (bSet == true)
				{
					if (strcmp(&aFile[0], "TYPE") == 0)	//TYPE�̕��������������
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &Textype);
					}
					if (strcmp(&aFile[0], "POS") == 0)	//POS�̕��������������
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f%f%f", &UIpos.x, &UIpos.y, &UIpos.z);
					}
					if (strcmp(&aFile[0], "WIDTH") == 0)	//WIDTH�̕��������������
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f", &Width);
					}
					if (strcmp(&aFile[0], "HEIGTH") == 0)	//HEIGTH�̕��������������
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f", &Heigth);
					}
				}

				if (strcmp(&aFile[0], "UISET") == 0)	//UISET�̕��������������
				{
					bSet = true;
				}
				if (strcmp(&aFile[0], "END_UISET") == 0)	//END_UISET�̕��������������
				{
					bSet = false;
					SetGameUI(UIpos, Width, Heigth, Textype);
				}
			}
			if (strcmp(&aFile[0], "END_SCRIPT") == 0) //END_SCRIPT�̕��������������
			{
				break;
			}

		}
	}
	fclose(pFile);


}

//�I������
void UninitGameUI(void)
{
	int nCntGameUI;
	for (nCntGameUI = 0; nCntGameUI < g_MaxUITexture; nCntGameUI++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureGameUI[nCntGameUI] != NULL)
		{
			g_pTextureGameUI[nCntGameUI]->Release();
			g_pTextureGameUI[nCntGameUI] = NULL;
		}

		//���_�o�b�t�@���j��
		if (g_pVtxBuffGameUI != NULL)
		{
			g_pVtxBuffGameUI->Release();
			g_pVtxBuffGameUI = NULL;
		}
	}
}

//�X�V����
void UpdateGameUI(void)
{
	VERTEX_2D*pVtx;//���_���ւ̃|�C���^
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

				//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
				g_pVtxBuffGameUI->Lock(0, 0, (void**)&pVtx, 0);
				pVtx += (nCntUI * 4);

				//���_�̍��W
				pVtx[0].pos = D3DXVECTOR3(g_aGameUI[nCntUI].pos.x - (g_aGameUI[nCntUI].fWidth / 2), g_aGameUI[nCntUI].pos.y - (g_aGameUI[nCntUI].fHeight / 2), 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aGameUI[nCntUI].pos.x + (g_aGameUI[nCntUI].fWidth / 2), g_aGameUI[nCntUI].pos.y - (g_aGameUI[nCntUI].fHeight / 2), 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aGameUI[nCntUI].pos.x - (g_aGameUI[nCntUI].fWidth / 2), g_aGameUI[nCntUI].pos.y + (g_aGameUI[nCntUI].fHeight / 2), 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aGameUI[nCntUI].pos.x + (g_aGameUI[nCntUI].fWidth / 2), g_aGameUI[nCntUI].pos.y + (g_aGameUI[nCntUI].fHeight / 2), 0.0f);

				//���_�o�b�t�@���A�����b�N
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

						//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
						g_pVtxBuffGameUI->Lock(0, 0, (void**)&pVtx, 0);
						pVtx += (nCntUI * 4);

						//���_�̐F
						pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 100);
						pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 100);
						pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 100);
						pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 100);

						//���_�o�b�t�@���A�����b�N
						g_pVtxBuffGameUI->Unlock();
					}

					else if (g_aGameUI[nCntUI].ntype == GAMEUITYPE_GAMESTART)
					{


						//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
						g_pVtxBuffGameUI->Lock(0, 0, (void**)&pVtx, 0);
						pVtx += (nCntUI * 4);

						//���_�̐F
						pVtx[0].col = D3DXCOLOR(255, 255, 255, 255);
						pVtx[1].col = D3DXCOLOR(255, 255, 255, 255);
						pVtx[2].col = D3DXCOLOR(255, 255, 255, 255);
						pVtx[3].col = D3DXCOLOR(255, 255, 255, 255);

						//���_�o�b�t�@���A�����b�N
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
						//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
						g_pVtxBuffGameUI->Lock(0, 0, (void**)&pVtx, 0);
						pVtx += (nCntUI * 4);

						//���_�̐F
						pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 100);
						pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 100);
						pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 100);
						pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 100);

						//���_�o�b�t�@���A�����b�N
						g_pVtxBuffGameUI->Unlock();
					}
				}
				else if (g_aGameUI[nCntUI].ntype == GAMEUITYPE_TUTOLIAL)
				{
					if (g_aGameUI[nCntUI].bUse == true)
					{
						//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
						g_pVtxBuffGameUI->Lock(0, 0, (void**)&pVtx, 0);
						pVtx += (nCntUI * 4);

						//���_�̐F
						pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
						pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
						pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
						pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

						//���_�o�b�t�@���A�����b�N
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

						//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
						g_pVtxBuffGameUI->Lock(0, 0, (void**)&pVtx, 0);
						pVtx += (nCntUI * 4);

						//���_�̐F
						pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 100);
						pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 100);
						pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 100);
						pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 100);

						//���_�o�b�t�@���A�����b�N
						g_pVtxBuffGameUI->Unlock();
					}
					else if (g_aGameUI[nCntUI].ntype == GAMEUITYPE_CONTINUE)
					{

						//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
						g_pVtxBuffGameUI->Lock(0, 0, (void**)&pVtx, 0);
						pVtx += (nCntUI * 4);

						//���_�̐F
						pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
						pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
						pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
						pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

						//���_�o�b�t�@���A�����b�N
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
						//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
						g_pVtxBuffGameUI->Lock(0, 0, (void**)&pVtx, 0);
						pVtx += (nCntUI * 4);

						//���_�̐F
						pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 100);
						pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 100);
						pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 100);
						pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 100);

						//���_�o�b�t�@���A�����b�N
						g_pVtxBuffGameUI->Unlock();
					}
				}
				else if (g_aGameUI[nCntUI].ntype == GAMEUITYPE_RETRY)
				{
					if (g_aGameUI[nCntUI].bUse == true)
					{
						//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
						g_pVtxBuffGameUI->Lock(0, 0, (void**)&pVtx, 0);
						pVtx += (nCntUI * 4);

						//���_�̐F
						pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
						pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
						pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
						pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

						//���_�o�b�t�@���A�����b�N
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
						//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
						g_pVtxBuffGameUI->Lock(0, 0, (void**)&pVtx, 0);
						pVtx += (nCntUI * 4);

						//���_�̐F
						pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 100);
						pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 100);
						pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 100);
						pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 100);

						//���_�o�b�t�@���A�����b�N
						g_pVtxBuffGameUI->Unlock();
					}
				}
				else if (g_aGameUI[nCntUI].ntype == GAMEUITYPE_QUIT)
				{
					if (g_aGameUI[nCntUI].bUse == true)
					{
						//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
						g_pVtxBuffGameUI->Lock(0, 0, (void**)&pVtx, 0);

						pVtx += (nCntUI * 4);
						//���_�̐F
						pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
						pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
						pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
						pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);


						//���_�o�b�t�@���A�����b�N
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

								//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
								g_pVtxBuffGameUI->Lock(0, 0, (void**)&pVtx, 0);
								pVtx += (nCntUI * 4);

								//���_�̐F
								pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 100);
								pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 100);
								pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 100);
								pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 100);

								//���_�o�b�t�@���A�����b�N
								g_pVtxBuffGameUI->Unlock();
							}
							else if (g_aGameUI[nCntUI].ntype == GAMEUITYPE_CONTINUE)
							{

								//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
								g_pVtxBuffGameUI->Lock(0, 0, (void**)&pVtx, 0);
								pVtx += (nCntUI * 4);

								//���_�̐F
								pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
								pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
								pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
								pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

								//���_�o�b�t�@���A�����b�N
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
								//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
								g_pVtxBuffGameUI->Lock(0, 0, (void**)&pVtx, 0);
								pVtx += (nCntUI * 4);

								//���_�̐F
								pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 100);
								pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 100);
								pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 100);
								pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 100);

								//���_�o�b�t�@���A�����b�N
								g_pVtxBuffGameUI->Unlock();
							}
						}
						else if (g_aGameUI[nCntUI].ntype == GAMEUITYPE_RETRY)
						{
							if (g_aGameUI[nCntUI].bUse == true)
							{
								//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
								g_pVtxBuffGameUI->Lock(0, 0, (void**)&pVtx, 0);
								pVtx += (nCntUI * 4);

								//���_�̐F
								pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
								pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
								pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
								pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

								//���_�o�b�t�@���A�����b�N
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
								//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
								g_pVtxBuffGameUI->Lock(0, 0, (void**)&pVtx, 0);
								pVtx += (nCntUI * 4);

								//���_�̐F
								pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 100);
								pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 100);
								pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 100);
								pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 100);

								//���_�o�b�t�@���A�����b�N
								g_pVtxBuffGameUI->Unlock();
							}
						}
						else if (g_aGameUI[nCntUI].ntype == GAMEUITYPE_QUIT)
						{
							if (g_aGameUI[nCntUI].bUse == true)
							{
								//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
								g_pVtxBuffGameUI->Lock(0, 0, (void**)&pVtx, 0);

								pVtx += (nCntUI * 4);
								//���_�̐F
								pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
								pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
								pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
								pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);


								//���_�o�b�t�@���A�����b�N
								g_pVtxBuffGameUI->Unlock();
							}
						}
					}
					break;
				}
				break;

	}

}

//�`�揈��
void DrawGameUI(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�̃|�C���^
	pDevice = GetDevice();//�f�o�C�X���擾����

						  //���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffGameUI, 0, sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);//���_�t�H�[�}�b�g�̐ݒ�
	for (int nCntGameUI = 0; nCntGameUI < MAX_GAMEUI; nCntGameUI++)
	{
		if (g_aGameUI[nCntGameUI].bUse == true)
		{
			pDevice->SetTexture(0, g_pTextureGameUI[g_aGameUI[nCntGameUI].ntype]);//�e�N�X�`���̐ݒ�
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntGameUI * 4, 2);//�|���S���̕`��
		}
	}

}

//UI�̐ݒ菈��
void SetGameUI(D3DXVECTOR3 pos, float fWidth, float fHeight, int ntype)
{
	VERTEX_2D*pVtx;//���_���ւ̃|�C���^


	int nCntGameUI;
	for (nCntGameUI = 0; nCntGameUI < MAX_GAMEUI; nCntGameUI++)
	{
		if (g_aGameUI[nCntGameUI].bUse == false)
		{
			g_aGameUI[nCntGameUI].pos = pos;//���W�����
			g_aGameUI[nCntGameUI].ntype = ntype;//�^�C�v������
			g_aGameUI[nCntGameUI].fWidth = fWidth;
			g_aGameUI[nCntGameUI].fHeight = fHeight;
			//���_�o�b�t�@�����b�N
			g_pVtxBuffGameUI->Lock(0, 0, (void**)&pVtx, 0);
			for (int nVtxUI = 0; nVtxUI <= 4; nVtxUI++)
			{
				pVtx += (nCntGameUI * 4);
				//���_�̍��W
				pVtx[0].pos = D3DXVECTOR3(g_aGameUI[nCntGameUI].pos.x - (g_aGameUI[nCntGameUI].fWidth / 2), g_aGameUI[nCntGameUI].pos.y - (g_aGameUI[nCntGameUI].fHeight / 2), 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aGameUI[nCntGameUI].pos.x + (g_aGameUI[nCntGameUI].fWidth / 2), g_aGameUI[nCntGameUI].pos.y - (g_aGameUI[nCntGameUI].fHeight / 2), 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aGameUI[nCntGameUI].pos.x - (g_aGameUI[nCntGameUI].fWidth / 2), g_aGameUI[nCntGameUI].pos.y + (g_aGameUI[nCntGameUI].fHeight / 2), 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aGameUI[nCntGameUI].pos.x + (g_aGameUI[nCntGameUI].fWidth / 2), g_aGameUI[nCntGameUI].pos.y + (g_aGameUI[nCntGameUI].fHeight / 2), 0.0f);

				//rhw�̐ݒ�
				pVtx[nVtxUI].rhw = 1.0f;

				//���_�̐F
				pVtx[nVtxUI].col = g_aGameUI[nCntGameUI].color;

				//�e�N�X�`����UV���W
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			}
			
			//�A�����b�N
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