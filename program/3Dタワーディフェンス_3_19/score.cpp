//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "score.h"

//---------------------------
//�O���[�o���ϐ�
//---------------------------
LPDIRECT3DTEXTURE9		g_apTextureScore = NULL;	//�e�N�X�`��
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;		//���_�o�b�t�@�ւ̃|�C���^
Score					g_aScore[MAX_SCOREDIGIT];	//�X�R�A�̍\����
int						g_nScore;					//�X�R�A

//---------------------------
//����������
//---------------------------
HRESULT InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�ւ̃|�C���^
	VERTEX_2D *pVtx; //���_���ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	//�G�̏�����
	for (int nCntScore = 0; nCntScore < MAX_SCOREDIGIT; nCntScore++)
	{
		g_aScore[nCntScore].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/number.png",
								&g_apTextureScore);
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(	sizeof(VERTEX_2D) * 4 * MAX_SCOREDIGIT,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffScore,
									NULL);
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntScore = 0; nCntScore < MAX_SCOREDIGIT; nCntScore++)
	{
		//���_���W
		pVtx[0].pos = D3DXVECTOR3(g_aScore[nCntScore].pos.x + SCORE_X * 2 * nCntScore - SCORE_X, g_aScore[nCntScore].pos.y - SCORE_Y, g_aScore[nCntScore].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aScore[nCntScore].pos.x + SCORE_X * 2 * nCntScore + SCORE_X, g_aScore[nCntScore].pos.y - SCORE_Y, g_aScore[nCntScore].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aScore[nCntScore].pos.x + SCORE_X * 2 * nCntScore - SCORE_X, g_aScore[nCntScore].pos.y + SCORE_Y, g_aScore[nCntScore].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aScore[nCntScore].pos.x + SCORE_X * 2 * nCntScore + SCORE_X, g_aScore[nCntScore].pos.y + SCORE_Y, g_aScore[nCntScore].pos.z);

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
	g_pVtxBuffScore->Unlock();

	return S_OK;
}

//---------------------------
//�I������
//---------------------------
void UninitScore(void)
{
	g_nScore = 0;
	//�e�N�X�`���̔j��
	if (g_apTextureScore != NULL)
	{
		g_apTextureScore->Release();
		g_apTextureScore = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
}

//---------------------------
//�X�V����
//---------------------------
void UpdateScore(void)
{
	VERTEX_2D	*pVtx;		//���_���ւ̃|�C���^
	int			nHeith = 0;	//����

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntScore = 0; nCntScore < MAX_SCOREDIGIT; nCntScore++, nHeith + 50.0f)
	{
		g_aScore[nCntScore].pos = D3DXVECTOR3(1570, 0.0f +35.0f, 0.0f);

		//���_���W
		pVtx[0].pos = D3DXVECTOR3(g_aScore[nCntScore].pos.x + SCORE_X * 2 * nCntScore - SCORE_X, g_aScore[nCntScore].pos.y - SCORE_Y, g_aScore[nCntScore].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aScore[nCntScore].pos.x + SCORE_X * 2 * nCntScore + SCORE_X, g_aScore[nCntScore].pos.y - SCORE_Y, g_aScore[nCntScore].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aScore[nCntScore].pos.x + SCORE_X * 2 * nCntScore - SCORE_X, g_aScore[nCntScore].pos.y + SCORE_Y, g_aScore[nCntScore].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aScore[nCntScore].pos.x + SCORE_X * 2 * nCntScore + SCORE_X, g_aScore[nCntScore].pos.y + SCORE_Y, g_aScore[nCntScore].pos.z);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();
}

//---------------------------
//�`�揈��
//---------------------------
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^

	pDevice = GetDevice();		//�f�o�C�X���擾����
	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(	0,
								g_pVtxBuffScore,
								0,
								sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D); //���_�t�H�[�}�b�g�̐ݒ�

	for (int nCntScore = 0; nCntScore < MAX_SCOREDIGIT; nCntScore++)
	{
		//�e�N�X�`��
		pDevice->SetTexture(0, g_apTextureScore);
		//�|���S���̕`��
		pDevice->DrawPrimitive(	D3DPT_TRIANGLESTRIP, //�v���~�e�B�u�̎��
								nCntScore * 4,
								2);
	}
}

//---------------------------
//�X�R�A�v�Z
//---------------------------
void AddScore(int nVolue)
{
	VERTEX_2D	*pVtx;						//���_���ւ̃|�C���^
	int			aNumber[MAX_SCOREDIGIT];	//�X�R�A�v�Z

	//�X�R�A���Z
	g_nScore += nVolue;

	//�X�R�A�v�Z
	aNumber[0] = g_nScore % 100000 / 10000;
	aNumber[1] = g_nScore % 10000 / 1000;
	aNumber[2] = g_nScore % 1000 / 100;
	aNumber[3] = g_nScore % 100 / 10;
	aNumber[4] = g_nScore % 10 / 1;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntScore = 0; nCntScore < MAX_SCOREDIGIT; nCntScore++)
	{
		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2((aNumber[nCntScore] * 0.1f) + 0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((aNumber[nCntScore] * 0.1f) + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2((aNumber[nCntScore] * 0.1f) + 0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((aNumber[nCntScore] * 0.1f) + 0.1f, 1.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffScore->Unlock();
}

//---------------------------
//�X�R�A����
//---------------------------
int GetScore(void)
{
	return g_nScore;
}