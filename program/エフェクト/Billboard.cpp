//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
//�r���{�[�h�̏���(Billboard.cpp)
//Author�F�����G��
//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[

#include "main.h"
#include "input.h"
#include "Billboard.h"
#include "Model.h"

#define MOVE_Y (3.0f)

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureBillboard[TYPE_BILLBOARMAX] = {};//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillboard = NULL;//���_�o�b�t�@�ւ̃|�C���^

Billboard g_Billboard[MAX_BILLBOARD];



//����������
HRESULT InitBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�̃|�C���^
	int nCntBillboard;
	pDevice = GetDevice();//�f�o�C�X�̎擾

	//������
	for (nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		g_Billboard[nCntBillboard].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Billboard[nCntBillboard].fHight = 30;
		g_Billboard[nCntBillboard].fWhidth = 30;

		g_Billboard[nCntBillboard].bUse = false;
		g_Billboard[nCntBillboard].nlife = 0;
		g_Billboard[nCntBillboard].ntype = NULL;
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "date/TEXTURE/�͂�.png", &g_pTextureBillboard[TYPE_BILLBOARDPLAYER]);
	D3DXCreateTextureFromFile(pDevice, "date/TEXTURE/wall000.jpg", &g_pTextureBillboard[TYPE_BILLBOARDFIRE]);


	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BILLBOARD, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffBillboard, NULL);

	return S_OK;
}

//�I������
void UninitBillboard(void)//�ǉ��̉\�������邽�ߍ��ڂ͍���Ƃ�
{
	for (int nCntBillboard = 0; nCntBillboard < TYPE_BILLBOARMAX; nCntBillboard++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureBillboard != NULL)
		{
			g_pTextureBillboard[nCntBillboard]->Release();
			g_pTextureBillboard[nCntBillboard] = NULL;
		}

		//���_�o�b�t�@���j��
		if (g_pVtxBuffBillboard != NULL)
		{
			g_pVtxBuffBillboard->Release();
			g_pVtxBuffBillboard = NULL;
		}
	}
}

//�X�V����
void UpdateBillboard(void)//�ǉ��̉\�������邽�ߍ��ڂ͍���Ƃ�
{
	
}

//�`�揈��
void DrawBillboard(void)
{
	int nCntBillboard;
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxView;
	D3DXMATRIX mtxTrans;
	pDevice = GetDevice();//�f�o�C�X���擾����

	for (nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		if (g_Billboard[nCntBillboard].bUse == true)
		{
			//�A���t�@�e�X�g�֌W
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0);		

			//�}�g���b�N�X������
			D3DXMatrixIdentity(&g_Billboard[nCntBillboard].mtxWorld);
			//�r���[�}�g���b�N�X�̎擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�|���S�����J�����ɑ΂��Đ��ʂ�
			D3DXMatrixInverse(&g_Billboard[nCntBillboard].mtxWorld, NULL, &mtxView);

			g_Billboard[nCntBillboard].mtxWorld._41 = 0.0f;
			g_Billboard[nCntBillboard].mtxWorld._42 = 0.0f;
			g_Billboard[nCntBillboard].mtxWorld._43 = 0.0f;

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Billboard[nCntBillboard].pos.x, g_Billboard[nCntBillboard].pos.y, g_Billboard[nCntBillboard].pos.z);
			D3DXMatrixMultiply(&g_Billboard[nCntBillboard].mtxWorld, &g_Billboard[nCntBillboard].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Billboard[nCntBillboard].mtxWorld);

			//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffBillboard, 0, sizeof(VERTEX_3D));

			pDevice->SetFVF(FVF_VERTEX_3D);//���_�t�H�[�}�b�g�̐ݒ�

			pDevice->SetTexture(0, g_pTextureBillboard[g_Billboard[nCntBillboard].ntype]);//�e�N�X�`���̐ݒ�

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBillboard * 4, 2);

			//�A���t�@�e�X�g�֌W
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);
		}

	}

}

void SetBillboard(D3DXVECTOR3 pos, float fWhidth, float fHight, int ntype)
{
	VERTEX_3D*pVtx;//���_���ւ̃|�C���^

	int nCntBillboard;
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		if (g_Billboard[nCntBillboard].bUse == false)
		{
			g_Billboard[nCntBillboard].pos = pos;

			g_Billboard[nCntBillboard].fWhidth = fWhidth;
			g_Billboard[nCntBillboard].fHight = fHight;

			//���_�̍��W
			pVtx[0].pos = D3DXVECTOR3(-g_Billboard[nCntBillboard].fWhidth / 2, +g_Billboard[nCntBillboard].fHight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(+g_Billboard[nCntBillboard].fWhidth / 2, +g_Billboard[nCntBillboard].fHight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-g_Billboard[nCntBillboard].fWhidth / 2,0.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(+g_Billboard[nCntBillboard].fWhidth / 2,0.0f, 0.0f);

			//�x�N�g���̐ݒ�
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//���_�̐F
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			//�e�N�X�`����UV���W
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			g_Billboard[nCntBillboard].ntype = ntype;

			g_Billboard[nCntBillboard].bUse = true;

			break;
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBillboard->Unlock();
}

Billboard *GetBillboard(void)
{
	return &g_Billboard[0];
}