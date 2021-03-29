//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "rank.h"
#include "score.h"

//---------------------------
//�O���[�o���ϐ�
//---------------------------
LPDIRECT3DTEXTURE9		g_apTextureRank = NULL;				//�e�N�X�`��
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRank = NULL;				//���_�o�b�t�@�ւ̃|�C���^
RANK					g_aRank[MAX_RANK][MAX_SCOREDIGIT];	//�X�R�A�̍\����
int						g_nRankScore[MAX_RANK + 1];			//��ׂ�X�R�A
bool					g_bRuse;								//��񂾂��ۑ�
int						g_nCnt;

//---------------------------
//����������
//---------------------------
HRESULT InitRank(void)
{
	LPDIRECT3DDEVICE9 pDevice;  //�f�o�C�X�ւ̃|�C���^
	VERTEX_2D		  *pVtx;	//���_���ւ̃|�C���^
	FILE			  *pFile;	//�t�@�C���J��

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//������
	for (int nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		for (int nCntRank2 = 0; nCntRank2 < MAX_SCOREDIGIT; nCntRank2++)
		{
			g_aRank[nCntRank][nCntRank2].pos = D3DXVECTOR3(((SCREEN_WIDTH / 2) - (RANK_X * 3)) + (RANK_X * nCntRank2), (SCREEN_HEIGHT / (2 + 1)) + ((SCREEN_HEIGHT / (5 + 1)) * nCntRank), 0.0f);
		}
		g_nRankScore[nCntRank] = 0;
	}
	g_nRankScore[MAX_RANK] = 0;
	g_bRuse = true;
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/number.png",
								&g_apTextureRank);
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(	sizeof(VERTEX_2D) * 4 * MAX_SCOREDIGIT * MAX_RANK,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffRank,
									NULL);
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		for (int nCntRank2 = 0; nCntRank2 < MAX_SCOREDIGIT; nCntRank2++)
		{
			//���_���W
			pVtx[0].pos = D3DXVECTOR3(g_aRank[nCntRank][nCntRank2].pos.x - RANK_X / 2, g_aRank[nCntRank][nCntRank2].pos.y - RANK_X / 2, g_aRank[nCntRank][nCntRank2].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aRank[nCntRank][nCntRank2].pos.x + RANK_X / 2, g_aRank[nCntRank][nCntRank2].pos.y - RANK_X / 2, g_aRank[nCntRank][nCntRank2].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_aRank[nCntRank][nCntRank2].pos.x - RANK_X / 2, g_aRank[nCntRank][nCntRank2].pos.y + RANK_X / 2, g_aRank[nCntRank][nCntRank2].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aRank[nCntRank][nCntRank2].pos.x + RANK_X / 2, g_aRank[nCntRank][nCntRank2].pos.y + RANK_X / 2, g_aRank[nCntRank][nCntRank2].pos.z);

			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			pVtx[0].col = D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f);
			pVtx[1].col = D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f);
			pVtx[2].col = D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f);
			pVtx[3].col = D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f);

			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

			pVtx += 4;
		}
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRank->Unlock();

	//�t�@�C���J��
	pFile = fopen("data/rank/rank_5wave.bin", "rb");

	//�Ȃ񂩓����Ă���
	if (pFile != NULL)
	{
		for (int nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
		{
			//�����L���O����
			fscanf(pFile, "%d\n", &g_nRankScore[nCntRank]);
		}
		//����
		fclose(pFile);
	}
	else
	{
		printf("�ǂݎ��Ȃ���");
	}
	return S_OK;
}

//---------------------------
//�I������
//---------------------------
void UninitRank(void)
{
	FILE			  *pFile;	//�t�@�C���J��
	//�t�@�C���J��
	pFile = fopen("data/rank/rank_5wave.bin", "wb");

	//�Ȃ񂩓����Ă���
	if (pFile != NULL)
	{
		for (int nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
		{
			//�����L���O�ۑ�
			fprintf(pFile, "%d\n", g_nRankScore[nCntRank]);
		}
		//����
		fclose(pFile);
	}
	else
	{
		printf("�ǂݎ��Ȃ���");
	}
	g_nCnt = 0;
	//�e�N�X�`���̔j��
	if (g_apTextureRank != NULL)
	{
		g_apTextureRank->Release();
		g_apTextureRank = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffRank != NULL)
	{
		g_pVtxBuffRank->Release();
		g_pVtxBuffRank = NULL;
	}
}

//---------------------------
//�X�V����
//---------------------------
void UpdateRank(void)
{
	FILE			  *pFile;	//�t�@�C���J��
	VERTEX_2D	*pVtx;						//���_���ւ̃|�C���^
	int			aNumber[MAX_SCOREDIGIT];	//�X�R�A�v�Z
	int			nSubdata;					//�s��

	if (g_bRuse == true)
	{
		g_nRankScore[3] = GetScore();	//���Ɏ����̃X�R�A
	}

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);

	//���U���g���
	if (GetMode() == MODE_RESULT)
	{
		for (int nRank = 0; nRank < MAX_RANK + 1; nRank++)
		{
			for (int nRank = 0; nRank < MAX_RANK + 1; nRank++)
			{
				if (g_nRankScore[nRank] < g_nRankScore[nRank + 1])
				{
					nSubdata = g_nRankScore[nRank];
					g_nRankScore[nRank] = g_nRankScore[nRank + 1];
					g_nRankScore[nRank + 1] = nSubdata;
				}
			}
		}
		for (int nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
		{
			//�X�R�A�v�Z
			aNumber[0] = g_nRankScore[nCntRank] % 100000 / 10000;
			aNumber[1] = g_nRankScore[nCntRank] % 10000 / 1000;
			aNumber[2] = g_nRankScore[nCntRank] % 1000 / 100;
			aNumber[3] = g_nRankScore[nCntRank] % 100 / 10;
			aNumber[4] = g_nRankScore[nCntRank] % 10 / 1;

			for (int nCntScore = 0; nCntScore < MAX_SCOREDIGIT; nCntScore++)
			{
				//�e�N�X�`�����W
				pVtx[0].tex = D3DXVECTOR2((aNumber[nCntScore] * 0.1f) + 0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2((aNumber[nCntScore] * 0.1f) + 0.1f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2((aNumber[nCntScore] * 0.1f) + 0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2((aNumber[nCntScore] * 0.1f) + 0.1f, 1.0f);

				pVtx += 4;
			}
		}
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRank->Unlock();
}

//---------------------------
//�`�揈��
//---------------------------
void DrawRank(void)
{
	LPDIRECT3DDEVICE9	pDevice;	//�f�o�C�X�̃|�C���^
	int					nNum = 0;

	pDevice = GetDevice();		//�f�o�C�X���擾����
	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(	0,
								g_pVtxBuffRank,
								0,
								sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D); //���_�t�H�[�}�b�g�̐ݒ�

	for (int nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		for (int nCntRank2 = 0; nCntRank2 < MAX_SCOREDIGIT; nCntRank2++)
		{
			//�e�N�X�`��
			pDevice->SetTexture(0, g_apTextureRank);
			//�|���S���̕`��
			pDevice->DrawPrimitive(	D3DPT_TRIANGLESTRIP, //�v���~�e�B�u�̎��
									nNum * 4,			 //�`����J�n���钸�_�̃C���f�b�N�X
									2);
			nNum++;
		}
	}
}