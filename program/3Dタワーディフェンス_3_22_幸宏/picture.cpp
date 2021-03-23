//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "picture.h"
#include "mouseinput.h"
#include "fade.h"
#include "Sound.h"
//---------------------------
//�O���[�o���ϐ�
//---------------------------
LPDIRECT3DTEXTURE9		g_pTexturePicture[MAX_PICTURE_TEX] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPicture = NULL;			//���_�o�b�t�@�ւ̃|�C���^
Picture					g_aPicture[MAX_PICTURE];			//BG�̍\����
static float			g_fCol = 255.0f;					//�_��
POINT					g_mouse;

//---------------------------
//����������
//---------------------------
HRESULT InitPicture(void)
{
	LPDIRECT3DDEVICE9	pDevice;	//�f�o�C�X�ւ̃|�C���^
	VERTEX_2D			*pVtx;		//���_���ւ̃|�C���^

	pDevice = GetDevice();			//�f�o�C�X�̎擾

	for (int nCntPicture = 0; nCntPicture < MAX_PICTURE; nCntPicture++)
	{
		g_aPicture[nCntPicture].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu
		g_aPicture[nCntPicture].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu
		g_aPicture[nCntPicture].aType = PICTURE_TITLE;				//���
		g_aPicture[nCntPicture].bUse = false;		//�g���Ă邩�ǂ���
		g_aPicture[nCntPicture].bClick = false;
	}
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(	pDevice,	
								"data/Texture/bg001.png",			//�e�N�X�`��
								&g_pTexturePicture[PICTURE_TITLE]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/bg002.png",			//�e�N�X�`��
								&g_pTexturePicture[PICTURE_GAMESTERTS]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/5mode.png",	//�e�N�X�`��
								&g_pTexturePicture[PICTURE_5WAVE]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/Limited mode.png",				//�e�N�X�`��
								&g_pTexturePicture[PICTURE_UNLIMITED]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/Result002.png",				//�e�N�X�`��
								&g_pTexturePicture[PICTURE_RESULT]);
	
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(	sizeof(VERTEX_2D) * 4 * MAX_PICTURE,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffPicture,
									NULL);
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPicture->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntPicture = 0; nCntPicture < MAX_PICTURE; nCntPicture++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].col = D3DXCOLOR(255, 255, 255, 255);
		pVtx[1].col = D3DXCOLOR(255, 255, 255, 255);
		pVtx[2].col = D3DXCOLOR(255, 255, 255, 255);
		pVtx[3].col = D3DXCOLOR(255, 255, 255, 255);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;	//���_��i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPicture->Unlock();

	return S_OK;
}

//---------------------------
//�I������
//---------------------------
void UninitPicture(void)
{
	for (int nCnTex = 0; nCnTex < MAX_PICTURE_TEX; nCnTex++)
	{
		//�e�N�X�`���̔j��
		if (g_pTexturePicture[nCnTex] != NULL)
		{
			g_pTexturePicture[nCnTex]->Release();
			g_pTexturePicture[nCnTex] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPicture != NULL)
	{
		g_pVtxBuffPicture->Release();
		g_pVtxBuffPicture = NULL;
	}
}

//---------------------------
//�X�V����
//---------------------------
void UpdatePicture(void)
{
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^
	static int nCnt;

	nCnt++;
	//��b��������
	if (nCnt >= 72)
	{
		//�����x0
		if (g_fCol == 0.0f)
		{
			//�����x255
			g_fCol = 255.0f;
		}
		//�����x255
		else if (g_fCol == 255.0f)
		{
			//�����x0
			g_fCol = 0.0f;
		}
		nCnt = 0;
	}

	GetCursorPos(&g_mouse);

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPicture->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntPicture = 0; nCntPicture < MAX_PICTURE; nCntPicture++)
	{
		if (g_aPicture[nCntPicture].aType == PICTURE_GAMESTERTS)
		{

		}
		else if (g_aPicture[nCntPicture].aType == PICTURE_5WAVE || g_aPicture[nCntPicture].aType == PICTURE_UNLIMITED)
		{
			if (g_aPicture[nCntPicture].pos.x - g_aPicture[nCntPicture].fWidth / 2 < g_mouse.x &&
				g_aPicture[nCntPicture].pos.x + g_aPicture[nCntPicture].fWidth / 2 > g_mouse.x &&
				g_aPicture[nCntPicture].pos.y - g_aPicture[nCntPicture].fHeight / 2 < g_mouse.y &&
				g_aPicture[nCntPicture].pos.y + g_aPicture[nCntPicture].fHeight / 2 > g_mouse.y)
			{
				g_aPicture[nCntPicture].bClick = true;
			}
			else
			{
				g_aPicture[nCntPicture].bClick = false;
			}
		}
		if (g_aPicture[nCntPicture].bClick == true)
		{
			if (MouseDowan(MOUSE_LEFT_BOTTON) == true)
			{
				if (g_aPicture[nCntPicture].aType == PICTURE_5WAVE && GetFade() == FADE_NONE)
				{
					SetFade(MODE_5WAVE);
					PlaySound(SOUND_LABEL_Enter000);
				}
				else if (g_aPicture[nCntPicture].aType == PICTURE_UNLIMITED && GetFade() == FADE_NONE)
				{
					
				}
			}
		}
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPicture->Unlock();
}

//---------------------------
//�`�揈��
//---------------------------
void DrawPicture(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^
	pDevice = GetDevice();		//�f�o�C�X���擾����

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(	0,
								g_pVtxBuffPicture,
								0,
								sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);	//���_�t�H�[�}�b�g�̐ݒ�

	for (int nCntPicture = 0; nCntPicture < MAX_PICTURE; nCntPicture++)
	{
		if (g_aPicture[nCntPicture].bUse == true)
		{
			//���e�X�g
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 110);

			pDevice->SetTexture(0, g_pTexturePicture[g_aPicture[nCntPicture].aType]);		//�e�N�X�`���̐ݒ�
			//�|���S���̕`��
			pDevice->DrawPrimitive(	D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
									nCntPicture * 4,
									2);

			//���e�X�g
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);
		}
	}
}

//---------------------------
//BG�̃Z�b�g
//---------------------------
void SetPicture(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWigth, float fHeight, PICTURE_TYPE aType)
{
	VERTEX_2D *pVtx; //���_���ւ̃|�C���^
	int nNum = 0;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPicture->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntPicture = 0; nCntPicture < MAX_PICTURE; nCntPicture++)
	{
		if (g_aPicture[nCntPicture].bUse == false)
		{
			nNum = nCntPicture;
			g_aPicture[nCntPicture].pos = pos;				//�����Ă����ʒu����
			g_aPicture[nCntPicture].move = move;			//�����Ă����ړ��ʂ���
			g_aPicture[nCntPicture].fWidth = fWigth;		//�����Ă�����
			g_aPicture[nCntPicture].fHeight = fHeight;		//�����Ă�������
			g_aPicture[nCntPicture].aType = aType;			//�����Ă������

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aPicture[nCntPicture].pos.x - g_aPicture[nCntPicture].fWidth / 2, g_aPicture[nCntPicture].pos.y - g_aPicture[nCntPicture].fHeight / 2, g_aPicture[nCntPicture].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aPicture[nCntPicture].pos.x + g_aPicture[nCntPicture].fWidth / 2, g_aPicture[nCntPicture].pos.y - g_aPicture[nCntPicture].fHeight / 2, g_aPicture[nCntPicture].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_aPicture[nCntPicture].pos.x - g_aPicture[nCntPicture].fWidth / 2, g_aPicture[nCntPicture].pos.y + g_aPicture[nCntPicture].fHeight / 2, g_aPicture[nCntPicture].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aPicture[nCntPicture].pos.x + g_aPicture[nCntPicture].fWidth / 2, g_aPicture[nCntPicture].pos.y + g_aPicture[nCntPicture].fHeight / 2, g_aPicture[nCntPicture].pos.z);

			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			pVtx[0].col = D3DXCOLOR(255, 255, 255, 255);
			pVtx[1].col = D3DXCOLOR(255, 255, 255, 255);
			pVtx[2].col = D3DXCOLOR(255, 255, 255, 255);
			pVtx[3].col = D3DXCOLOR(255, 255, 255, 255);

			g_aPicture[nCntPicture].bUse = true;
			break;
		}
		pVtx += 4;	//���_��i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPicture->Unlock();
}