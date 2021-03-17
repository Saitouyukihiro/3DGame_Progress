//**************************************************************
//�c�e���\���̏���
//Author�F�����G��
//**************************************************************

#include "Magazine.h"

//�}�N����`
#define MAX_MAGAZINE (2)

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureMagazine = NULL;//�e�N�X�`���ւ̃|�C���^

											   //���_�o�b�t�@�̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMagazine = NULL; //�o�b�t�@�ւ̃|�C���^
int g_nMagazineBullet;//�v�Z�p

Magazine g_aMagazine[MAX_MAGAZINE];
Equipment g_aEquipment;

//����������
void InitMagazineBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�̃|�C���^
	int nCntMagazine;
	pDevice = GetDevice();//�f�o�C�X�̎擾

	for (nCntMagazine = 0; nCntMagazine < MAX_MAGAZINE; nCntMagazine++)
	{
		g_aMagazineBullet[nCntMagazine].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	g_aEquipment.state = TYPE_ASSULT;//�����łƂ肠�����A�T���g

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/number000.png", &g_pTextureMagazine);
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_MAGAZINE, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffMagazine, NULL);
	VERTEX_2D*pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffMagazine->Lock(0, 0, (void**)&pVtx, 0);


	for (nCntMagazine = 0; nCntMagazine < MAX_MAGAZINE; nCntMagazine++)
	{
		g_aMagazineBullet[nCntMagazine].pos = D3DXVECTOR3(180.0f + 30.0f * nCntMagazine, 680.0f, 0.0f);//�X�R�A�\���ꏊ

																												//���_�̍��W
		pVtx[0].pos = D3DXVECTOR3(700.0f + 40.0f * nCntMagazine, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(750.0f + 40.0f * nCntMagazine, 0.0f, 0.0);
		pVtx[2].pos = D3DXVECTOR3(700.0f + 40.0f * nCntMagazine, 50.0f, 0.0);
		pVtx[3].pos = D3DXVECTOR3(750.0f + 40.0f * nCntMagazine, 50.0f, 0.0);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;


		//���_�̐F
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`����UV���W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;
	}


	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffMagazine->Unlock();

}

//�I������
void UninitMagazineBullet(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureMagazine != NULL)
	{
		g_pTextureMagazine->Release();
		g_pTextureMagazine = NULL;
	}

	//���_�o�b�t�@���j��
	if (g_pVtxBuffMagazine != NULL)
	{
		g_pVtxBuffMagazine->Release();
		g_pVtxBuffMagazine = NULL;
	}
}

//�X�V����
void UpdateMagazineBullet(void)
{

	int aMagazineBullet[MAX_MAGAZINE];
	int nCntMagazine;

	int nCntBullet = �u�v;//�u�v�Ɍ��݂̒e���̏��������
	int nCntMagazineBlt;


	if (nCntBullet <= 0)//�c�e��0��
	{
		switch (g_aEquipment.state)//�������Ă�e�̃^�C�v�ōő吔���ς��悤��
		{
		case(TYPE_ASSULT)://�A�T���g
		{
			nCntMagazineBlt = 30;
			break;
		}
		case(TYPE_HANDGUN)://�n���h�K��
		{
			nCntMagazineBlt = 10;
			break;
		}

		}

		nCntBullet = nCntMagazineBlt;
	}


	g_nMagazineBullet = nCntBullet;




	VERTEX_2D*pVtx;//���_���ւ̃|�C���^

	aMagazineBullet[0] = g_nMagazineBullet % 100 / 10;
	aMagazineBullet[1] = g_nMagazineBullet % 10 / 1;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffMagazine->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntMagazineBullet = 0; nCntMagazineBullet < MAX_MAGAZINE; nCntMagazineBullet++)
	{
		//���_�̍��W
		pVtx[0].pos = D3DXVECTOR3(g_aMagazineBullet[nCntMagazineBullet].pos.x - (30.0f / 2), g_aMagazineBullet[nCntMagazineBullet].pos.y - (30.0f / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aMagazineBullet[nCntMagazineBullet].pos.x + (30.0f / 2), g_aMagazineBullet[nCntMagazineBullet].pos.y - (30.0f / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aMagazineBullet[nCntMagazineBullet].pos.x - (30.0f / 2), g_aMagazineBullet[nCntMagazineBullet].pos.y + (30.0f / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aMagazineBullet[nCntMagazineBullet].pos.x + (30.0f / 2), g_aMagazineBullet[nCntMagazineBullet].pos.y + (30.0f / 2), 0.0f);

		//�e�N�X�`����UV���W
		pVtx[0].tex = D3DXVECTOR2(aMagazineBullet[nCntMagazineBullet] * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(aMagazineBullet[nCntMagazineBullet] * 0.1f + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(aMagazineBullet[nCntMagazineBullet] * 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(aMagazineBullet[nCntMagazineBullet] * 0.1f + 0.1f, 1.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffMagazine->Unlock();
}

//�`�揈��
void DrawMagazine(void)
{

	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�̃|�C���^
	pDevice = GetDevice();//�f�o�C�X���擾����

						  //���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMagazine, 0, sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetTexture(0, g_pTextureMagazine);//�e�N�X�`���̐ݒ�

	for (int nCntMagazine = 0; nCntMagazine < MAX_MAGAZINE; nCntMagazine++)
	{

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntMagazine * 4, 2);

	}
}

void AddMagazine(int nValue)
{
	g_nMagazine += nValue;
}

Magazine *GetMagazine(void)
{
	return &g_aMagazine[0];
}

