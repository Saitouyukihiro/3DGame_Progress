//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "enemycount.h"
#include "spider.h"

//---------------------------
//�O���[�o���ϐ�
//---------------------------
LPDIRECT3DTEXTURE9		g_apTextureEnemyCount = NULL;	//�e�N�X�`��
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemyCount = NULL;		//���_�o�b�t�@�ւ̃|�C���^
Enemycount				g_aEnemyCount[MAX_ENEMY_COUNT_DIGIT];	//�X�R�A�̍\����
int						g_nEnemyCount;					//�X�R�A
int g_nCountSpider = 0;

//---------------------------
//����������
//---------------------------
HRESULT InitCount(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�ւ̃|�C���^
	VERTEX_2D *pVtx; //���_���ւ̃|�C���^

					 //�f�o�C�X�̎擾
	pDevice = GetDevice();
	//�G�̏�����
	for (int nCntEnemyCount = 0; nCntEnemyCount < MAX_ENEMY_COUNT_DIGIT; nCntEnemyCount++)
	{
		g_aEnemyCount[nCntEnemyCount].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/number.png",
								&g_apTextureEnemyCount);
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(	sizeof(VERTEX_2D) * 4 * MAX_ENEMY_COUNT_DIGIT,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffEnemyCount,
									NULL);
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEnemyCount->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEnemyCount = 0; nCntEnemyCount < MAX_ENEMY_COUNT_DIGIT; nCntEnemyCount++)
	{
		//���_���W
		pVtx[0].pos = D3DXVECTOR3(g_aEnemyCount[nCntEnemyCount].pos.x + ENEMY_COUNT_X * 2 * nCntEnemyCount - ENEMY_COUNT_X, g_aEnemyCount[nCntEnemyCount].pos.y - ENEMY_COUNT_Y, g_aEnemyCount[nCntEnemyCount].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aEnemyCount[nCntEnemyCount].pos.x + ENEMY_COUNT_X * 2 * nCntEnemyCount + ENEMY_COUNT_X, g_aEnemyCount[nCntEnemyCount].pos.y - ENEMY_COUNT_Y, g_aEnemyCount[nCntEnemyCount].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aEnemyCount[nCntEnemyCount].pos.x + ENEMY_COUNT_X * 2 * nCntEnemyCount - ENEMY_COUNT_X, g_aEnemyCount[nCntEnemyCount].pos.y + ENEMY_COUNT_Y, g_aEnemyCount[nCntEnemyCount].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aEnemyCount[nCntEnemyCount].pos.x + ENEMY_COUNT_X * 2 * nCntEnemyCount + ENEMY_COUNT_X, g_aEnemyCount[nCntEnemyCount].pos.y + ENEMY_COUNT_Y, g_aEnemyCount[nCntEnemyCount].pos.z);

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
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemyCount->Unlock();

	return S_OK;
}

//---------------------------
//�I������
//---------------------------
void UninitCount(void)
{
	g_nEnemyCount = 0;
	g_nCountSpider = 0;
	//�e�N�X�`���̔j��
	if (g_apTextureEnemyCount != NULL)
	{
		g_apTextureEnemyCount->Release();
		g_apTextureEnemyCount = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffEnemyCount != NULL)
	{
		g_pVtxBuffEnemyCount->Release();
		g_pVtxBuffEnemyCount = NULL;
	}
}

//---------------------------
//�X�V����
//---------------------------
void UpdateCount(void)
{
	VERTEX_2D	*pVtx;		//���_���ւ̃|�C���^
	int			nHeith = 0;	//����

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEnemyCount->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEnemyCount = 0; nCntEnemyCount < MAX_ENEMY_COUNT_DIGIT; nCntEnemyCount++, nHeith + 50.0f)
	{
		g_aEnemyCount[nCntEnemyCount].pos = D3DXVECTOR3(1170, 0.0f + 35.0f, 0.0f);

		//���_���W
		pVtx[0].pos = D3DXVECTOR3(g_aEnemyCount[nCntEnemyCount].pos.x + ENEMY_COUNT_X * 2 * nCntEnemyCount - ENEMY_COUNT_X, g_aEnemyCount[nCntEnemyCount].pos.y - ENEMY_COUNT_Y, g_aEnemyCount[nCntEnemyCount].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aEnemyCount[nCntEnemyCount].pos.x + ENEMY_COUNT_X * 2 * nCntEnemyCount + ENEMY_COUNT_X, g_aEnemyCount[nCntEnemyCount].pos.y - ENEMY_COUNT_Y, g_aEnemyCount[nCntEnemyCount].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aEnemyCount[nCntEnemyCount].pos.x + ENEMY_COUNT_X * 2 * nCntEnemyCount - ENEMY_COUNT_X, g_aEnemyCount[nCntEnemyCount].pos.y + ENEMY_COUNT_Y, g_aEnemyCount[nCntEnemyCount].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aEnemyCount[nCntEnemyCount].pos.x + ENEMY_COUNT_X * 2 * nCntEnemyCount + ENEMY_COUNT_X, g_aEnemyCount[nCntEnemyCount].pos.y + ENEMY_COUNT_Y, g_aEnemyCount[nCntEnemyCount].pos.z);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemyCount->Unlock();

	int			aNumber[MAX_ENEMY_COUNT_DIGIT];	//�X�R�A�v�Z

	Spider *pSpider;

	pSpider = GetSpider();

	for (int nCntSpider = 0; nCntSpider < MAX_SPIDER_MODEL; nCntSpider++, pSpider++)
	{
		if (pSpider->bUse == true)
		{
			g_nCountSpider += 1;
		}
	}

	pSpider -= MAX_SPIDER_MODEL;

	//�X�R�A���Z
	g_nEnemyCount = g_nCountSpider;

	//�X�R�A�v�Z
	aNumber[0] = g_nEnemyCount % 100 / 10;
	aNumber[1] = g_nEnemyCount % 10 / 1;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEnemyCount->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEnemyCount = 0; nCntEnemyCount < MAX_ENEMY_COUNT_DIGIT; nCntEnemyCount++, nHeith + 50.0f)
	{
		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2((aNumber[nCntEnemyCount] * 0.1f) + 0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((aNumber[nCntEnemyCount] * 0.1f) + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2((aNumber[nCntEnemyCount] * 0.1f) + 0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((aNumber[nCntEnemyCount] * 0.1f) + 0.1f, 1.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemyCount->Unlock();
	g_nCountSpider = 0;
}

//---------------------------
//�`�揈��
//---------------------------
void DrawCount(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^

	pDevice = GetDevice();		//�f�o�C�X���擾����
								//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(	0,
								g_pVtxBuffEnemyCount,
								0,
								sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D); //���_�t�H�[�}�b�g�̐ݒ�

	for (int nCntEnemyCount = 0; nCntEnemyCount < MAX_ENEMY_COUNT_DIGIT; nCntEnemyCount++)
	{
		//���e�X�g
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 110);

		//�e�N�X�`��
		pDevice->SetTexture(0, g_apTextureEnemyCount);
		//�|���S���̕`��
		pDevice->DrawPrimitive(	D3DPT_TRIANGLESTRIP, //�v���~�e�B�u�̎��
								nCntEnemyCount * 4,
								2);
		//���e�X�g
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);
	}
}

//---------------------------
//�X�R�A����
//---------------------------
int GetCount(void)
{
	return g_nEnemyCount;
}