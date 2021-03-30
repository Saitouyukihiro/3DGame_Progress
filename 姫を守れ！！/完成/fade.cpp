//---------------------------------
// �C���N���[�h�t�@�C��
//---------------------------------
#include "fade.h"

//---------------------------------
// �O���[�o���ϐ�
//----------------------------------
LPDIRECT3DTEXTURE9 g_pTextureFade = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFade = NULL;	//���_�o�b�t�@�ւ̃|�C���^
FADE g_fade;									//�t�F�[�h�̏��
MODE g_modeNext;								//���̃t�F�[�h
D3DXCOLOR g_colorfade;							//�t�F�[�h�̐F

//---------------------------------
// ����������
//---------------------------------
void InitFade(MODE modeNext)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^
	g_fade = FADE_IN;
	g_modeNext = g_modeNext;
	g_colorfade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	pDevice = GetDevice();		//�f�o�C�X�̎擾

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/brack.png",	//�g���e�N�X�`��
								&g_pTextureFade);
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(	sizeof(VERTEX_2D) * 4,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffFade,
									NULL);

	//---------------------------
	//���_���
	//---------------------------
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f + SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f + SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f + SCREEN_WIDTH, 0.0f + SCREEN_HEIGHT, 0.0f);
	
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	
	pVtx[0].col = D3DCOLOR_RGBA(0, 0, 0, 255);							
	pVtx[1].col = D3DCOLOR_RGBA(0, 0, 0, 255);							
	pVtx[2].col = D3DCOLOR_RGBA(0, 0, 0, 255);							
	pVtx[3].col = D3DCOLOR_RGBA(0, 0, 0, 255);							
																		
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);										
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);										
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);									
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);								
																					
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffFade->Unlock();
}
//---------------------------------
//�@�I������
//---------------------------------
void UninitFade(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureFade != NULL)
	{
		g_pTextureFade->Release();
		g_pTextureFade = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffFade != NULL)
	{
		g_pVtxBuffFade->Release();
		g_pVtxBuffFade = NULL;
	}
}
//---------------------------------
// �X�V����
//---------------------------------
void UpdateFade(void)
{
	VERTEX_2D *pVtx;

	if (g_fade != FADE_NONE)
	{
		if (g_fade == FADE_IN)
		{
			g_colorfade.a -= 0.01f;		//�t�F�[�h�̑���
			if (g_colorfade.a <= 0.0f)
			{
				g_colorfade.a = 0.0f;
				g_fade = FADE_NONE;
			}
		}
		else if (g_fade == FADE_OUT)
		{
			g_colorfade.a += 0.01f;		//�t�F�[�h�̑���
			if (g_colorfade.a >= 1.0f)
			{
				g_colorfade.a = 1.0f;
				g_fade = FADE_IN;
				SetMode(g_modeNext);
			}
		}
		g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

		pVtx[0].col = g_colorfade;
		pVtx[1].col = g_colorfade;
		pVtx[2].col = g_colorfade;
		pVtx[3].col = g_colorfade;

		g_pVtxBuffFade->Unlock();
	}
}
//---------------------------------
// �`�揈��
//---------------------------------
void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^

	pDevice = GetDevice();	//�f�o�C�X���擾����

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(	0,
								g_pVtxBuffFade,
								0,
								sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);					//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetTexture(0, g_pTextureFade);			//�e�N�X�`���̐ݒ�
	//�|���S���̕`��
	pDevice->DrawPrimitive(	D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
							0,
							2);
}

//---------------------------------
// �t�F�[�h�̃Z�b�g
//---------------------------------
void SetFade(MODE modeNext)
{
	g_fade = FADE_OUT;
	g_modeNext = modeNext;
	g_colorfade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

//---------------------------------
//�t�F�[�h�̏����擾
//---------------------------------
FADE GetFade(void)
{
	return g_fade;
}