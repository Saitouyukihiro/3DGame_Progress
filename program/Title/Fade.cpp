//=============================================================================
//�t�F�[�h�̏���
//=============================================================================

#include "Main.h"
#include "Fade.h"

//-----------------------------------------------------------------------------
//�O���[�o���ϐ�
//-----------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 g_pTexturefade = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufffade = NULL;		//�e�N�X�`���ւ̃|�C���^
FADE g_fade;										//�t�F�[�h�̏��
MODE g_modeNext;									//���̉��(���[�h)
D3DXCOLOR g_colorFade;								//�t�F�[�h�̐F

//-----------------------------------------------------------------------------
//�t�F�[�h�̏���������
//-----------------------------------------------------------------------------
void InitFade(MODE modeNext)
{
	LPDIRECT3DDEVICE9 pDevice;     //�f�o�C�X�ւ̃|�C���^
	pDevice = GetDevice();        //�f�o�C�X�̎擾

	g_fade = FADE_IN;
	g_modeNext = modeNext;
	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);    //3�ڂ��������(�s����)


	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBufffade, NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBufffade->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0, 0.0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[:0�`255
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBufffade->Unlock();
}

//-----------------------------------------------------------------------------
//�t�F�[�h�̏I������
//-----------------------------------------------------------------------------
void UninitFade(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexturefade != NULL)
	{
		g_pTexturefade->Release();
		g_pTexturefade = NULL;
	}

	if (g_pVtxBufffade != NULL)
	{
		g_pVtxBufffade->Release();
		g_pVtxBufffade = NULL;
	}
}

//-----------------------------------------------------------------------------
//�t�F�[�h�̍X�V����
//-----------------------------------------------------------------------------
void UpdateFade(void)
{
	if (g_fade != FADE_NONE)
	{
		if (g_fade == FADE_IN)
		{
			g_colorFade.a -= 0.01f;       //�t�F�[�h�̃X�s�[�h��ς���

			if (g_colorFade.a <= 0.0f)
			{
				g_colorFade.a = 0.01f;
				g_fade = FADE_NONE;
			}
		}

		else if (g_fade == FADE_OUT)
		{
			g_colorFade.a += 0.01f;
			if (g_colorFade.a >= 1.0f)
			{
				g_colorFade.a = 1.0f;
				g_fade = FADE_IN;

				//���[�h�̐ݒ�
				SetMode(g_modeNext);
			}
		}

		LPDIRECT3DDEVICE9 pDevice;     //�f�o�C�X�ւ̃|�C���^
		pDevice = GetDevice();        //�f�o�C�X�̎擾
									  //���_�o�b�t�@�̐���
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBufffade, NULL);

		//���_���ւ̃|�C���^
		VERTEX_2D*pVtx;
		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBufffade->Lock(0, 0, (void**)&pVtx, 0);

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0, 0.0, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0, SCREEN_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[:0�`255
		pVtx[0].col = g_colorFade;
		pVtx[1].col = g_colorFade;
		pVtx[2].col = g_colorFade;
		pVtx[3].col = g_colorFade;

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//���_�o�b�t�@���A�����b�N
		g_pVtxBufffade->Unlock();
	}
}

//-----------------------------------------------------------------------------
//�t�F�[�h�̕`�揈��
//-----------------------------------------------------------------------------
void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDevice;  //�f�o�C�X�̃|�C���^
	pDevice = GetDevice();     //�f�o�C�X���擾����
	pDevice->SetStreamSource(0, g_pVtxBufffade, 0, sizeof(VERTEX_2D));  //���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);  //���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetTexture(0, g_pTexturefade);  //�e�N�X�`���̐ݒ�
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);    //�|���S���̕`��
}

//-----------------------------------------------------------------------------
//�t�F�[�h�̐ݒ菈��
//-----------------------------------------------------------------------------
void SetFade(MODE modeNext)
{
	g_fade = FADE_OUT;
	g_modeNext = modeNext;
	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

//-----------------------------------------------------------------------------
//�t�F�[�h�̎擾����
//-----------------------------------------------------------------------------
FADE *GetFade(void)
{
	return &g_fade;
}