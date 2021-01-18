//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
//�ǂ̏���(Wall.cpp)
//Author�F�����G��
//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[

#include "main.h"
#include "input.h"
#include "wall.h"
#include "Model.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexturewall[1] = {};//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffwall = NULL;//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pigxBuffMeshWall = NULL;


Wall g_wall[MAX_WALL];

//����������
HRESULT InitWall(void)
{
	int nCntWall;
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�̃|�C���^
	pDevice = GetDevice();//�f�o�C�X�̎擾

	for (nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		g_wall[nCntWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_wall[nCntWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_wall[nCntWall].fWhidth = 0;
		g_wall[nCntWall].fHight = 0;
		g_wall[nCntWall].bUse = false;
	}

	D3DXCreateTextureFromFile(pDevice, "date/TEXTURE/wall000.jpg", &g_pTexturewall[0]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 9 * MAX_WALL, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffwall, NULL);

	VERTEX_3D * pVtx;//���_���ւ̃|�C���^
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffwall->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		//���_�̍��W
		pVtx[0].pos = D3DXVECTOR3(g_wall[nCntWall].pos.x - (0 / 2), g_wall[nCntWall].pos.y + (0)	, g_wall[nCntWall].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_wall[nCntWall].pos.x		  , g_wall[nCntWall].pos.y + (0)	, g_wall[nCntWall].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_wall[nCntWall].pos.x + (0 / 2), g_wall[nCntWall].pos.y + (0)	, g_wall[nCntWall].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_wall[nCntWall].pos.x - (0 / 2), g_wall[nCntWall].pos.y + (0 / 2), g_wall[nCntWall].pos.z);
		pVtx[4].pos = D3DXVECTOR3(g_wall[nCntWall].pos.x		  , g_wall[nCntWall].pos.y + (0 / 2), g_wall[nCntWall].pos.z);
		pVtx[5].pos = D3DXVECTOR3(g_wall[nCntWall].pos.x + (0 / 2), g_wall[nCntWall].pos.y + (0 / 2), g_wall[nCntWall].pos.z);
		pVtx[6].pos = D3DXVECTOR3(g_wall[nCntWall].pos.x - (0 / 2), g_wall[nCntWall].pos.y			, g_wall[nCntWall].pos.z);
		pVtx[7].pos = D3DXVECTOR3(g_wall[nCntWall].pos.x		  , g_wall[nCntWall].pos.y			, g_wall[nCntWall].pos.z);
		pVtx[8].pos = D3DXVECTOR3(g_wall[nCntWall].pos.x + (0 / 2), g_wall[nCntWall].pos.y			, g_wall[nCntWall].pos.z);

		//�x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[4].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[5].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[6].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[7].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[8].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//���_�̐F
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[8].col = D3DCOLOR_RGBA(255, 255, 255, 255); 

		//�e�N�X�`����UV���W
		pVtx[0].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);

		pVtx[6].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[7].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[8].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 9;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffwall->Unlock();

	pDevice->CreateIndexBuffer(sizeof(WORD) * 14, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pigxBuffMeshWall, NULL);

	WORD * pidx;
	g_pigxBuffMeshWall->Lock(0, 0, (void**)&pidx, 0);

	pidx[0] = 7;
	pidx[1] = 6;
	pidx[2] = 4;
	pidx[3] = 3;
	pidx[4] = 1;
	pidx[5] = 0;
	pidx[6] = 0;
	pidx[7] = 8;
	pidx[8] = 8;
	pidx[9] = 7;
	pidx[10] = 5;
	pidx[11] = 4;
	pidx[12] = 2;
	pidx[13] = 1;

	g_pigxBuffMeshWall->Unlock();


	return S_OK;
}

//�I������
void UninitWall(void)//�ǉ��̉\�������邽�ߍ��ڂ͍���Ƃ�
{
	for (int nCntWall = 0; nCntWall < 1; nCntWall++)
	{
		//�e�N�X�`���̔j��
		if (g_pTexturewall != NULL)
		{
			g_pTexturewall[nCntWall]->Release();
			g_pTexturewall[nCntWall] = NULL;
		}

		//���_�o�b�t�@���j��
		if (g_pVtxBuffwall != NULL)
		{
			g_pVtxBuffwall->Release();
			g_pVtxBuffwall = NULL;
		}

		//���_�o�b�t�@���j��
		if (g_pigxBuffMeshWall != NULL)
		{
			g_pigxBuffMeshWall->Release();
			g_pigxBuffMeshWall = NULL;
		}
	}
}

//�X�V����
void UpdateWall(void)//�ǉ��̉\�������邽�ߍ��ڂ͍���Ƃ�
{
	
}

//�`�揈��
void DrawWall(void)
{
	int nCntWall;
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;
	pDevice = GetDevice();//�f�o�C�X���擾����

	for (nCntWall = 0; nCntWall <= MAX_WALL; nCntWall++)
	{
		if (g_wall[nCntWall].bUse == true)
		{
			D3DXMatrixIdentity(&g_wall[nCntWall].mtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_wall[nCntWall].rot.y, g_wall[nCntWall].rot.x, g_wall[nCntWall].rot.z);
			D3DXMatrixMultiply(&g_wall[nCntWall].mtxWorld, &g_wall[nCntWall].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_wall[nCntWall].pos.x, g_wall[nCntWall].pos.y, g_wall[nCntWall].pos.z);
			D3DXMatrixMultiply(&g_wall[nCntWall].mtxWorld, &g_wall[nCntWall].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_wall[nCntWall].mtxWorld);

			//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffwall, 0, sizeof(VERTEX_3D));

			//�C���f�b�N�X�o�b�t�@�f�[�^�X�g���[��
			pDevice->SetIndices(g_pigxBuffMeshWall);

			pDevice->SetFVF(FVF_VERTEX_3D);//���_�t�H�[�}�b�g�̐ݒ�

			pDevice->SetTexture(0, g_pTexturewall[0]);//�e�N�X�`���̐ݒ�

			//�|���S���̕`��
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 9, 0, 12);

		}

	}

}

void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWhidth, float fHight, int ntype)
{
	VERTEX_3D*pVtx;//���_���ւ̃|�C���^
	int nCntWall;

	for (nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_wall[nCntWall].bUse == false)
		{
			g_wall[nCntWall].pos = pos;
			g_wall[nCntWall].rot = rot;

			
			//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
			g_pVtxBuffwall->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += (nCntWall * 9);

			//���_�̍��W
			pVtx[0].pos = D3DXVECTOR3(g_wall[nCntWall].pos.x - (fWhidth / 2), g_wall[nCntWall].pos.y + (fHight)	   , g_wall[nCntWall].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_wall[nCntWall].pos.x				, g_wall[nCntWall].pos.y + (fHight)	   , g_wall[nCntWall].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_wall[nCntWall].pos.x + (fWhidth / 2), g_wall[nCntWall].pos.y + (fHight)	   , g_wall[nCntWall].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_wall[nCntWall].pos.x - (fWhidth / 2), g_wall[nCntWall].pos.y + (fHight / 2), g_wall[nCntWall].pos.z);
			pVtx[4].pos = D3DXVECTOR3(g_wall[nCntWall].pos.x				, g_wall[nCntWall].pos.y + (fHight / 2), g_wall[nCntWall].pos.z);
			pVtx[5].pos = D3DXVECTOR3(g_wall[nCntWall].pos.x + (fWhidth / 2), g_wall[nCntWall].pos.y + (fHight / 2), g_wall[nCntWall].pos.z);
			pVtx[6].pos = D3DXVECTOR3(g_wall[nCntWall].pos.x - (fWhidth / 2), g_wall[nCntWall].pos.y			   , g_wall[nCntWall].pos.z);
			pVtx[7].pos = D3DXVECTOR3(g_wall[nCntWall].pos.x				, g_wall[nCntWall].pos.y			   , g_wall[nCntWall].pos.z);
			pVtx[8].pos = D3DXVECTOR3(g_wall[nCntWall].pos.x + (fWhidth / 2), g_wall[nCntWall].pos.y			   , g_wall[nCntWall].pos.z);

			//�x�N�g���̐ݒ�
			pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[4].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[5].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[6].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[7].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[8].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

			//���_�̐F
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[8].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			//�e�N�X�`����UV���W
			pVtx[0].tex = D3DXVECTOR2(1.0f, 2.0f);
			pVtx[1].tex = D3DXVECTOR2(0.0f, 2.0f);
			pVtx[2].tex = D3DXVECTOR2(1.0f, 2.0f);

			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx[4].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[5].tex = D3DXVECTOR2(1.0f, 1.0f);

			pVtx[6].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[7].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[8].tex = D3DXVECTOR2(1.0f, 0.0f);

			//���_�o�b�t�@���A�����b�N
			g_pVtxBuffwall->Unlock();

			g_wall[nCntWall].fWhidth = fWhidth;
			g_wall[nCntWall].fHight = fHight;
			g_wall[nCntWall].bUse = true;

			break;
		}
	}
}

Wall *GetWall(void)
{
	return &g_wall[0];
}