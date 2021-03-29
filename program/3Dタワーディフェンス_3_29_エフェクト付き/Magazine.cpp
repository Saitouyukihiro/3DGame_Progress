//**************************************************************
//�c�e���\���̏���
//Author�F�����G��
//**************************************************************

#include "Magazine.h"
#include "keyinput.h"
#include "mouseinput.h"
#include "bullet.h"
#include "camara.h"
#include "player.h"

//�}�N����`
#define MAX_MAGAZINE (2)

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureMagazine = NULL;//�e�N�X�`���ւ̃|�C���^

											   //���_�o�b�t�@�̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMagazine = NULL; //�o�b�t�@�ւ̃|�C���^
int g_nMagazineBullet;//�v�Z�p
int g_nCntBullet = 30;//�u�v�Ɍ��݂̒e���̏��������

Magazine g_aMagazine[MAX_MAGAZINE];
Equipment g_aEquipment;

//����������
void InitMagazine(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�̃|�C���^
	int nCntMagazine;
	pDevice = GetDevice();//�f�o�C�X�̎擾

	for (nCntMagazine = 0; nCntMagazine < MAX_MAGAZINE; nCntMagazine++)
	{
		g_aMagazine[nCntMagazine].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	g_aEquipment.state = TYPE_ASSULT;//�����łƂ肠�����A�T���g

	g_nCntBullet = 30;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/Texture/number.png", &g_pTextureMagazine);
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_MAGAZINE, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffMagazine, NULL);
	VERTEX_2D*pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffMagazine->Lock(0, 0, (void**)&pVtx, 0);


	for (nCntMagazine = 0; nCntMagazine < MAX_MAGAZINE; nCntMagazine++)
	{
		g_aMagazine[nCntMagazine].pos = D3DXVECTOR3(1670.0f + 30.0f * nCntMagazine, 1020.0f, 0.0f);//�X�R�A�\���ꏊ

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
void UninitMagazine(void)
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

	if (g_nCntBullet <= 0)//�c�e��0��
	{
		nCntReload++;
		switch (g_aEquipment.state)//�������Ă�e�̃^�C�v�ōő吔���ς��悤��
		{
		case(TYPE_ASSULT)://�A�T���g
			{
				if (nCntReload > 144)
				{
					g_nCntBullet = 30;
					nCntReload = 0;
				}
				nCntMagazineBlt = 30;
				break;
			}
		case(TYPE_HANDGUN)://�n���h�K��
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




	VERTEX_2D*pVtx;//���_���ւ̃|�C���^

	aMagazineBullet[0] = g_nMagazineBullet % 100 / 10;
	aMagazineBullet[1] = g_nMagazineBullet % 10 / 1;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffMagazine->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntMagazineBullet = 0; nCntMagazineBullet < MAX_MAGAZINE; nCntMagazineBullet++)
	{
		//���_�̍��W
		pVtx[0].pos = D3DXVECTOR3(g_aMagazine[nCntMagazineBullet].pos.x - (30.0f / 2), g_aMagazine[nCntMagazineBullet].pos.y - (30.0f / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aMagazine[nCntMagazineBullet].pos.x + (30.0f / 2), g_aMagazine[nCntMagazineBullet].pos.y - (30.0f / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aMagazine[nCntMagazineBullet].pos.x - (30.0f / 2), g_aMagazine[nCntMagazineBullet].pos.y + (30.0f / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aMagazine[nCntMagazineBullet].pos.x + (30.0f / 2), g_aMagazine[nCntMagazineBullet].pos.y + (30.0f / 2), 0.0f);

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
		//���e�X�g
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 110);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntMagazine * 4, 2);

		//���e�X�g
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

