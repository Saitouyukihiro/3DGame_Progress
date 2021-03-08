//=============================================================================
//�^�C�g���̏���
//=============================================================================
#include "Main.h"
#include "Title.h"
#include "Input.h"
#include "Fade.h"
#include "Sound.h"

//-----------------------------------------------------------------------------
//�O���[�o���ϐ�
//-----------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 g_pTextureTitle = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;		//�e�N�X�`���ւ̃|�C���^

//-----------------------------------------------------------------------------
//�}�`�̏���������
//-----------------------------------------------------------------------------
void InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;     //�f�o�C�X�ւ̃|�C���^
	pDevice = GetDevice();        //�f�o�C�X�̎擾

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/bg0001.png", &g_pTextureTitle);		//�w�i
	

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffTitle, NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffTitle->Unlock();
}

//-----------------------------------------------------------------------------
//�I������
//-----------------------------------------------------------------------------
void UninitTitle(void)
{
	
		//�e�N�X�`���̔j��
		if (g_pTextureTitle != NULL)
		{
			g_pTextureTitle->Release();
			g_pTextureTitle = NULL;
		}

		if (g_pVtxBuffTitle != NULL)
		{
			g_pVtxBuffTitle->Release();
			g_pVtxBuffTitle = NULL;
		}
	
}


//-----------------------------------------------------------------------------
//�X�V����
//-----------------------------------------------------------------------------
void UpdateTitle(void)
{
	XINPUT_STATE state;
	ZeroMemory(&state, sizeof(XINPUT_STATE));
	DWORD dwResult = XInputGetState(0, &state);

	//���̉�ʂɕς��
	if (GetKeyboardTrigger(DIK_RETURN) == true && *GetFade() != FADE_OUT)
	{
		SetFade(MODE_TITLE);
		PlaySound(SOUND_LABEL_Enter000);
	}
}

//-----------------------------------------------------------------------------
//�`�揈��
//-----------------------------------------------------------------------------
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;  //�f�o�C�X�̃|�C���^
	pDevice = GetDevice();     //�f�o�C�X���擾����
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));  //���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);  //���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetTexture(0, g_pTextureTitle);  //�e�N�X�`���̐ݒ�
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);    //�|���S���̕`��

}