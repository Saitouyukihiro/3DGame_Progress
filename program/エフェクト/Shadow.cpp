//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
//�X�e�[�W�̏���(Shadow.cpp)
//Author�F�����G��
//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[

#include "main.h"
#include "input.h"
#include "Shadow.h"
#include "Model.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureShadow[TYPE_MAX] = {};//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;//���_�o�b�t�@�ւ̃|�C���^

Shadow g_shadow[MAX_SHADOW];

//����������
HRESULT InitShadow(void)
{
	int nCntShadow;
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�̃|�C���^
	pDevice = GetDevice();//�f�o�C�X�̎擾

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		g_shadow[nCntShadow].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_shadow[nCntShadow].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_shadow[nCntShadow].fWhidth = 0;
		g_shadow[nCntShadow].fDepth = 0;
		g_shadow[nCntShadow].ntype = 0;
		g_shadow[nCntShadow].bUse = false;
	}

	D3DXCreateTextureFromFile(pDevice, "date/TEXTURE/shadow000.jpg", &g_pTextureShadow[TYPE_PLAYER]);
	D3DXCreateTextureFromFile(pDevice, "date/TEXTURE/shadow000.jpg", &g_pTextureShadow[TYPE_ENEMY]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_SHADOW, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffShadow, NULL);

	VERTEX_3D * pVtx;//���_���ւ̃|�C���^
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		//���_�̍��W
		pVtx[0].pos = D3DXVECTOR3(g_shadow[nCntShadow].pos.x - (100 / 2), g_shadow[nCntShadow].pos.y, g_shadow[nCntShadow].pos.z + (100 / 2));
		pVtx[1].pos = D3DXVECTOR3(g_shadow[nCntShadow].pos.x + (100 / 2), g_shadow[nCntShadow].pos.y, g_shadow[nCntShadow].pos.z + (100 / 2));
		pVtx[2].pos = D3DXVECTOR3(g_shadow[nCntShadow].pos.x - (100 / 2), g_shadow[nCntShadow].pos.y, g_shadow[nCntShadow].pos.z - (100 / 2));
		pVtx[3].pos = D3DXVECTOR3(g_shadow[nCntShadow].pos.x + (100 / 2), g_shadow[nCntShadow].pos.y, g_shadow[nCntShadow].pos.z - (100 / 2));

		//�x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���_�̐F
		pVtx[0].col = D3DCOLOR_RGBA(0, 0, 0, 0);
		pVtx[1].col = D3DCOLOR_RGBA(0, 0, 0, 0);
		pVtx[2].col = D3DCOLOR_RGBA(0, 0, 0, 0);
		pVtx[3].col = D3DCOLOR_RGBA(0, 0, 0, 0);

		//�e�N�X�`����UV���W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffShadow->Unlock();

	return S_OK;
}

//�I������
void UninitShadow(void)//�ǉ��̉\�������邽�ߍ��ڂ͍���Ƃ�
{
	for (int nCntShadow = 0; nCntShadow < TYPE_MAX; nCntShadow++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureShadow != NULL)
		{
			g_pTextureShadow[nCntShadow]->Release();
			g_pTextureShadow[nCntShadow] = NULL;
		}

		//���_�o�b�t�@���j��
		if (g_pVtxBuffShadow != NULL)
		{
			g_pVtxBuffShadow->Release();
			g_pVtxBuffShadow = NULL;
		}
	}
}

//�X�V����
void UpdateShadow(void)//�ǉ��̉\�������邽�ߍ��ڂ͍���Ƃ�
{
	int nCntShadow;

	Player *pPlayer;
	pPlayer = GetModel();

	VERTEX_3D*pVtx;//���_���ւ̃|�C���^

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_shadow[nCntShadow].bUse == true)
		{
			g_shadow[nCntShadow].pos = pPlayer->pos / 2;

			//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
			g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += (nCntShadow * 4);

			//���_�̍��W
			pVtx[0].pos = D3DXVECTOR3(g_shadow[nCntShadow].pos.x - (g_shadow[nCntShadow].fWhidth / 2), g_shadow[nCntShadow].pos.y, g_shadow[nCntShadow].pos.z + (g_shadow[nCntShadow].fDepth / 2));
			pVtx[1].pos = D3DXVECTOR3(g_shadow[nCntShadow].pos.x + (g_shadow[nCntShadow].fWhidth / 2), g_shadow[nCntShadow].pos.y, g_shadow[nCntShadow].pos.z + (g_shadow[nCntShadow].fDepth / 2));
			pVtx[2].pos = D3DXVECTOR3(g_shadow[nCntShadow].pos.x - (g_shadow[nCntShadow].fWhidth / 2), g_shadow[nCntShadow].pos.y, g_shadow[nCntShadow].pos.z - (g_shadow[nCntShadow].fDepth / 2));
			pVtx[3].pos = D3DXVECTOR3(g_shadow[nCntShadow].pos.x + (g_shadow[nCntShadow].fWhidth / 2), g_shadow[nCntShadow].pos.y, g_shadow[nCntShadow].pos.z - (g_shadow[nCntShadow].fDepth / 2));

			//�x�N�g���̐ݒ�
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//���_�̐F
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 75);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 75);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 75);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 75);

			//�e�N�X�`����UV���W
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			//���_�o�b�t�@���A�����b�N
			g_pVtxBuffShadow->Unlock();
		}
	}
}

void SetShadow(D3DXVECTOR3 pos, float fWhidth, float fDepth ,int ntype)
{
	VERTEX_3D*pVtx;//���_���ւ̃|�C���^
	int nCntShadow;

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW;nCntShadow++)
	{
		if (g_shadow[nCntShadow].bUse == false)
		{
			g_shadow[nCntShadow].pos = pos;
			g_shadow[nCntShadow].ntype = ntype;

			//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
			g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += (nCntShadow * 4);

			//���_�̍��W
			pVtx[0].pos = D3DXVECTOR3(g_shadow[nCntShadow].pos.x - (fWhidth / 2), g_shadow[nCntShadow].pos.y, g_shadow[nCntShadow].pos.z + (fDepth / 2));
			pVtx[1].pos = D3DXVECTOR3(g_shadow[nCntShadow].pos.x + (fWhidth / 2), g_shadow[nCntShadow].pos.y, g_shadow[nCntShadow].pos.z + (fDepth / 2));
			pVtx[2].pos = D3DXVECTOR3(g_shadow[nCntShadow].pos.x - (fWhidth / 2), g_shadow[nCntShadow].pos.y, g_shadow[nCntShadow].pos.z - (fDepth / 2));
			pVtx[3].pos = D3DXVECTOR3(g_shadow[nCntShadow].pos.x + (fWhidth / 2), g_shadow[nCntShadow].pos.y, g_shadow[nCntShadow].pos.z - (fDepth / 2));

			//�x�N�g���̐ݒ�
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//���_�̐F
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 75);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 75);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 75);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 75);

			//�e�N�X�`����UV���W
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			
			//���_�o�b�t�@���A�����b�N
			g_pVtxBuffShadow->Unlock();

			g_shadow[nCntShadow].fWhidth = fWhidth;
			g_shadow[nCntShadow].fDepth = fDepth;

			g_shadow[nCntShadow].bUse = true;

			break;
		}
	}
}

//�`�揈��
void DrawShadow(void)
{
	int nCntShadow;
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;
	pDevice = GetDevice();//�f�o�C�X���擾����

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_shadow[nCntShadow].bUse == true)
		{
			//���Z����
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

			D3DXMatrixIdentity(&g_shadow[nCntShadow].mtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_shadow[nCntShadow].rot.y, g_shadow[nCntShadow].rot.x, g_shadow[nCntShadow].rot.z);
			D3DXMatrixMultiply(&g_shadow[nCntShadow].mtxWorld, &g_shadow[nCntShadow].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_shadow[nCntShadow].pos.x, g_shadow[nCntShadow].pos.y, g_shadow[nCntShadow].pos.z);
			D3DXMatrixMultiply(&g_shadow[nCntShadow].mtxWorld, &g_shadow[nCntShadow].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_shadow[nCntShadow].mtxWorld);

			//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

			pDevice->SetFVF(FVF_VERTEX_3D);//���_�t�H�[�}�b�g�̐ݒ�

			pDevice->SetTexture(0, g_pTextureShadow[g_shadow[nCntShadow].ntype]);//�e�N�X�`���̐ݒ�

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntShadow * 4, 2);

			//�ʏ퍇���ɖ߂�
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		}
		
	}
	
}