//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "girl.h"
#include "shadow.h"
#include "spider.h"
#include "fade.h"
#include "Sound.h"
//---------------------------
//�O���[�o���ϐ�
//---------------------------
LPDIRECT3DTEXTURE9		g_pTextureGirl[MAX_GIRL_TEX];	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGirl = NULL;			//���_�o�b�t�@�ւ̃|�C���^
Girl					g_aGirl[MAX_GIRL];				//�r���{�[�h�̃|�C���^

//---------------------------
//����������
//---------------------------
HRESULT InitGirl(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	pDevice = GetDevice();			//�f�o�C�X�̎擾

	//�l�̏�����
	for (int nCntGirl = 0; nCntGirl < MAX_GIRL; nCntGirl++)
	{
		g_aGirl[nCntGirl].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aGirl[nCntGirl].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aGirl[nCntGirl].aState = GIRL_STATE_NONE;
		g_aGirl[nCntGirl].fWidth = GIRL_X;
		g_aGirl[nCntGirl].fHeiht = GIRL_Y;
		g_aGirl[nCntGirl].nIdex = 0;
		g_aGirl[nCntGirl].nAnim = 0;
		g_aGirl[nCntGirl].bUse = false;
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/girl_000.png",			//�e�N�X�`��
								&g_pTextureGirl[0]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/girl_001.png",			//�e�N�X�`��
								&g_pTextureGirl[1]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/girl_002.png",			//�e�N�X�`��
								&g_pTextureGirl[2]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/girl_003.png",			//�e�N�X�`��
								&g_pTextureGirl[3]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/girl_004.png",			//�e�N�X�`��
								&g_pTextureGirl[5]);
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(	sizeof(VERTEX_3D) * 4 * MAX_GIRL,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_3D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffGirl,
									NULL);
	//---------------------------
	//���_���
	//---------------------------
	VERTEX_3D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffGirl->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntGirl = 0; nCntGirl < MAX_GIRL; nCntGirl++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-g_aGirl[nCntGirl].fWidth, -g_aGirl[nCntGirl].fHeiht, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aGirl[nCntGirl].fWidth, -g_aGirl[nCntGirl].fHeiht, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-g_aGirl[nCntGirl].fWidth, g_aGirl[nCntGirl].fHeiht, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aGirl[nCntGirl].fWidth, g_aGirl[nCntGirl].fHeiht, 0.0f);

		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		pVtx[0].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[3].tex = D3DXVECTOR2(0.0f, 0.0f);

		pVtx += 4;	//���_��i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffGirl->Unlock();

	return S_OK;
}

//---------------------------
//�I������
//---------------------------
void UninitGirl(void)
{
	//---------------------------
	//�e�N�X�`���j��
	//---------------------------
	for (int nCntTex = 0; nCntTex < MAX_GIRL_TEX; nCntTex++)
	{
		if (g_pTextureGirl[nCntTex] != NULL)
		{
			g_pTextureGirl[nCntTex]->Release();
			g_pTextureGirl[nCntTex] = NULL;
		}
	}

	//---------------------------
	//�o�b�t�@�j��
	//---------------------------
	if (g_pVtxBuffGirl != NULL)
	{
		g_pVtxBuffGirl->Release();
		g_pVtxBuffGirl = NULL;
	}
}

//---------------------------
//�X�V����
//---------------------------
void UpdateGirl(void)
{
	VERTEX_3D *pVtx;		//���_���ւ̃|�C���^
	static int nAnimTime;	//�A�j���[�V�����̍X�V����

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffGirl->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntGirl = 0; nCntGirl < MAX_GIRL; nCntGirl++)
	{
		if (g_aGirl[nCntGirl].bUse == true)
		{
			g_aGirl[nCntGirl].posold = g_aGirl[nCntGirl].pos;
			nAnimTime++;
			if (nAnimTime >= 144)
			{
				g_aGirl[nCntGirl].nAnim++;
				nAnimTime = 0;
			}
			pVtx[0].tex = D3DXVECTOR2(0.0f + (0.5 * g_aGirl[nCntGirl].nAnim), 1.0f);
			pVtx[1].tex = D3DXVECTOR2(0.5f + (0.5 * g_aGirl[nCntGirl].nAnim), 1.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + (0.5 * g_aGirl[nCntGirl].nAnim), 0.0f);
			pVtx[3].tex = D3DXVECTOR2(0.5f + (0.5 * g_aGirl[nCntGirl].nAnim), 0.0f);
		}
		pVtx += 4;	//���_��i�߂�
		if (CollisionSpider(&g_aGirl[nCntGirl].pos, &g_aGirl[nCntGirl].posold, &g_aGirl[nCntGirl].move, g_aGirl[nCntGirl].fWidth, g_aGirl[nCntGirl].fHeiht, COLLISION_GIRL) == true)
		{

		}

		//�e�̒ǔ�
		SetPointShadow(g_aGirl[nCntGirl].nIdex, D3DXVECTOR3(g_aGirl[nCntGirl].pos.x, 0.0f, g_aGirl[nCntGirl].pos.z), g_aGirl[nCntGirl].fWidth, g_aGirl[nCntGirl].fHeiht / 2);
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffGirl->Unlock();
}

//---------------------------
//�`�揈��
//---------------------------
void DrawGirl(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^

	pDevice = GetDevice();		//�f�o�C�X���擾����

	//---------------------------
	//�}�g���b�N�X�̐ݒ�
	//---------------------------
	D3DXMATRIX mtxTrans;	//�v�Z�p�}�g���b�N�X

	for (int nCntGirl = 0; nCntGirl < MAX_GIRL; nCntGirl++)
	{
		if (g_aGirl[nCntGirl].bUse == true)
		{
			//�J�����O�L��
			pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

			pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

			//���e�X�g
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

			//�}�g���b�N�X������
			D3DXMatrixIdentity(&g_aGirl[nCntGirl].mtxWold);

			//�J�����̌������擾
			pDevice->GetTransform(	D3DTS_VIEW,
									&g_aGirl[nCntGirl].mtxView);
			//�J�����̏������āA�X�P�[���𔽉f
			g_aGirl[nCntGirl].mtxWold._11 = g_aGirl[nCntGirl].mtxView._11 * g_aGirl[nCntGirl].fWidth;
			g_aGirl[nCntGirl].mtxWold._12 = g_aGirl[nCntGirl].mtxView._21 * g_aGirl[nCntGirl].fWidth;
			g_aGirl[nCntGirl].mtxWold._13 = g_aGirl[nCntGirl].mtxView._31 * g_aGirl[nCntGirl].fWidth;
			g_aGirl[nCntGirl].mtxWold._21 = g_aGirl[nCntGirl].mtxView._12 * g_aGirl[nCntGirl].fHeiht;
			g_aGirl[nCntGirl].mtxWold._22 = g_aGirl[nCntGirl].mtxView._22 * g_aGirl[nCntGirl].fHeiht;
			g_aGirl[nCntGirl].mtxWold._23 = g_aGirl[nCntGirl].mtxView._32 * g_aGirl[nCntGirl].fHeiht;
			g_aGirl[nCntGirl].mtxWold._31 = g_aGirl[nCntGirl].mtxView._13;
			g_aGirl[nCntGirl].mtxWold._32 = g_aGirl[nCntGirl].mtxView._23;
			g_aGirl[nCntGirl].mtxWold._33 = g_aGirl[nCntGirl].mtxView._33;

			//�ʒu
			D3DXMatrixTranslation(	&mtxTrans,
									g_aGirl[nCntGirl].pos.x,
									g_aGirl[nCntGirl].pos.y,
									g_aGirl[nCntGirl].pos.z);

			D3DXMatrixMultiply(	&g_aGirl[nCntGirl].mtxWold,
								&g_aGirl[nCntGirl].mtxWold,
								&mtxTrans);
			//�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(	D3DTS_WORLD,
									&g_aGirl[nCntGirl].mtxWold);
			//---------------------------
			//�`�揈��
			//---------------------------
			//�o�b�t�@�̐ݒ���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(	0,
										g_pVtxBuffGirl,
										0,
										sizeof(VERTEX_3D));
			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(	0,
									g_pTextureGirl[g_aGirl[nCntGirl].nType]);
			//�|���S���̕`��
			pDevice->DrawPrimitive(	D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
									nCntGirl * 4,			//���Ԗڂ���`�悷�邩
									2);						//���̐�
			//���e�X�g
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);
		}
	}
}

//---------------------------
//�Z�b�g
//---------------------------
void SetGirl(D3DXVECTOR3 pos, float fWidth, float fHeight, int nType)
{
	for (int nCntGirl = 0; nCntGirl < MAX_GIRL; nCntGirl++)
	{
		if (g_aGirl[nCntGirl].bUse == false)
		{
			g_aGirl[nCntGirl].pos = pos;		//�ʒu������
			g_aGirl[nCntGirl].fWidth = fWidth;	//��������
			g_aGirl[nCntGirl].fHeiht = fHeight;	//����������
			g_aGirl[nCntGirl].nType = nType;	//��ނ�����

			//�e��t���āA�e�̔ԍ����擾
			g_aGirl[nCntGirl].nIdex = SetShadow(pos, fWidth, fHeight / 2);
			g_aGirl[nCntGirl].bUse = true;		//�g���Ă�
			break;
		}
	}
}

//---------------------------
//���̎q���
//---------------------------
Girl *GetGirl(void)
{
	return &g_aGirl[0];
}

//---------------------------
//���̎q�ڐ�
//---------------------------
void GirlLooking(D3DXVECTOR3 pos)
{
	int nSide;
	for (int nCntGirl = 0; nCntGirl < MAX_GIRL; nCntGirl++)
	{
		if (g_aGirl[nCntGirl].bUse == true)
		{
			if (pos.x >= g_aGirl[nCntGirl].pos.x - g_aGirl[nCntGirl].fLookigX &&
				pos.x <= g_aGirl[nCntGirl].pos.x + g_aGirl[nCntGirl].fLookigX &&
				pos.z <= g_aGirl[nCntGirl].pos.z + g_aGirl[nCntGirl].fLookigZ)
			{
				nSide = rand() % 2;
				switch (nSide)
				{
				case 0:
					g_aGirl[nCntGirl].aState = GIRL_STATE_RIGHT;
					break;
				case 1:
					g_aGirl[nCntGirl].aState = GIRL_STATE_LEFT;
					break;
				}
			}
		}
	}
}

void AddGirl(int nVolue)
{
	for (int nCntGirl = 0; nCntGirl < MAX_GIRL; nCntGirl++)
	{
		if (g_aGirl[nCntGirl].bUse == true)
		{
			g_aGirl[nCntGirl].nHp -= nVolue;
			if (g_aGirl[nCntGirl].nHp <= 0)
			{
				SetFade(MODE_RESULT);
				PlaySound(SOUND_LABEL_aaa);
			}
		}
	}
}