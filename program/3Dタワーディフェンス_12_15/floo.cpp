//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "floo.h"

//---------------------------
//�O���[�o���ϐ�
//---------------------------
LPDIRECT3DTEXTURE9		g_pTextureField[MAX_FLOO_TEX] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFloo = NULL;				//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9	g_pIdxBuffFloo = NULL;				//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
Field					g_Floo[MAX_FLOO];					//���b�V���t�B�[���h�̍\����

//---------------------------
//����������
//---------------------------
HRESULT InitFloo(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	pDevice = GetDevice();		//�f�o�C�X�̎擾

	for (int nCntFloo = 0; nCntFloo < MAX_FLOO; nCntFloo++)
	{
		g_Floo[nCntFloo].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Floo[nCntFloo].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Floo[nCntFloo].fWidth = 1.0f;
		g_Floo[nCntFloo].fDepht = 1.0f;
		g_Floo[nCntFloo].nTex = 0;
		g_Floo[nCntFloo].bUse = false;
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/field002.jpg",			//�e�N�X�`��
								&g_pTextureField[0]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(	sizeof(VERTEX_3D) * FLOO_VTX_NUM_MAX * MAX_FLOO,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_3D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffFloo,
									NULL);
	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(	sizeof(WORD) * FLOO_IDX_NUM_MAX * MAX_FLOO,
								D3DUSAGE_WRITEONLY,
								D3DFMT_INDEX16,
								D3DPOOL_MANAGED,
								&g_pIdxBuffFloo,
								NULL);
	//---------------------------
	//���_���
	//---------------------------
	VERTEX_3D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffFloo->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntField = 0; nCntField < MAX_FLOO; nCntField++)
	{
		int nVtxNum = 0;
		for (int nCntZ = 0; nCntZ < FLOO_MAX_VTX_Z + 1; nCntZ++)
		{
			for (int nCntX = 0; nCntX < FLOO_MAX_VTX_X + 1; nCntX++, nVtxNum++)
			{
				pVtx[nVtxNum].pos = D3DXVECTOR3(-MS_FLOO_X + (((MS_FLOO_X * 2) / FLOO_MAX_VTX_X) * nCntX), 0.0f, MS_FLOO_Z - (((MS_FLOO_Z * 2) / FLOO_MAX_VTX_Z) * nCntZ));
				pVtx[nVtxNum].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				pVtx[nVtxNum].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[nVtxNum].tex = D3DXVECTOR2(0.0f + (1.0f * nCntX), 0.0f + (1.0f * nCntZ));
			}
		}
		nVtxNum = 0;
		pVtx += FLOO_VTX_NUM_MAX;	//���_��i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffFloo->Unlock();

	//---------------------------
	//�C���f�b�N�X���
	//---------------------------
	WORD *pIdx;		//�C���f�b�N�X���ւ̃|�C���^

	//�C���f�b�N�X�o�b�t�@�����b�N���A�ԍ��f�[�^�ւ̃|�C���^���擾
	g_pIdxBuffFloo->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntField = 0; nCntField < MAX_FLOO; nCntField++)
	{
		//�p�킳��ȊO�̒��_
		for (int nCntZ = 0; nCntZ < FLOO_MAX_VTX_Z; nCntZ++)
		{
			for (int nCntX = 0; nCntX < FLOO_MAX_VTX_X + 1; nCntX++)
			{
				pIdx[(nCntX * 2) + 0 + ((FLOO_MAX_VTX_X + 2) * 2) * nCntZ] = ((FLOO_MAX_VTX_X + 1) + nCntX) + ((FLOO_MAX_VTX_X + 1) * nCntZ);
				pIdx[(nCntX * 2) + 1 + ((FLOO_MAX_VTX_X + 2) * 2) * nCntZ] = (0 + nCntX) + ((FLOO_MAX_VTX_X + 1) * nCntZ);
			}
		}
		//�p�킳��̒��_
		for (int nCntZ = 0; nCntZ < FLOO_MAX_VTX_Z - 1; nCntZ++)
		{
			pIdx[(((FLOO_MAX_VTX_X + 1) * 2 + 0) * (nCntZ + 1)) + (2 * nCntZ)] = FLOO_MAX_VTX_X + ((FLOO_MAX_VTX_X + 1) * nCntZ);
			pIdx[(((FLOO_MAX_VTX_X + 1) * 2 + 1) * (nCntZ + 1)) + (1 * nCntZ)] = (FLOO_MAX_VTX_X * 2 + 2) + ((FLOO_MAX_VTX_X + 1) * nCntZ);
		}
		pIdx += FLOO_IDX_NUM_MAX;	//�C���f�b�N�X��i�߂�
	}

	//�C���f�b�N�X�o�b�t�@���A�����b�N����
	g_pIdxBuffFloo->Unlock();

	return S_OK;
}

//---------------------------
//�I������
//---------------------------
void UninitFloo(void)
{
	//---------------------------
	//�e�N�X�`���j��
	//---------------------------
	for (int nCntTex = 0; nCntTex < MAX_FLOO_TEX; nCntTex++)
	{
		if (g_pTextureField[nCntTex] != NULL)
		{
			g_pTextureField[nCntTex]->Release();
			g_pTextureField[nCntTex] = NULL;
		}
	}

	//---------------------------
	//�o�b�t�@�j��
	//---------------------------
	if (g_pVtxBuffFloo != NULL)
	{
		g_pVtxBuffFloo->Release();
		g_pVtxBuffFloo = NULL;
	}

	//---------------------------
	//�C���f�b�N�X�o�b�t�@�j��
	//---------------------------
	if (g_pIdxBuffFloo != NULL)
	{
		g_pIdxBuffFloo->Release();
		g_pIdxBuffFloo = NULL;
	}
}

//---------------------------
//�X�V����
//---------------------------
void UpdateFloo(void)
{

}

//---------------------------
//�`�揈��
//---------------------------
void DrawFloo(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^

	pDevice = GetDevice();		//�f�o�C�X���擾����

	//---------------------------
	//�}�g���b�N�X�̐ݒ�
	//---------------------------
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	for (int nCntFloo = 0; nCntFloo < MAX_FLOO; nCntFloo++)
	{
		if (g_Floo[nCntFloo].bUse == true)
		{
			//�J�����O�L
			pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

			//���e�X�g
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

			D3DXMatrixIdentity(&g_Floo[nCntFloo].mtxWold);	//�}�g���b�N�X������

			//�X�P�[��
			g_Floo[nCntFloo].mtxWold._11 = g_Floo[nCntFloo].fWidth;
			g_Floo[nCntFloo].mtxWold._33 = g_Floo[nCntFloo].fDepht;

			//�����̐ݒ�
			D3DXMatrixRotationYawPitchRoll(	&mtxRot,
											g_Floo[nCntFloo].rot.y,
											g_Floo[nCntFloo].rot.x,
											g_Floo[nCntFloo].rot.z);

			D3DXMatrixMultiply(	&g_Floo[nCntFloo].mtxWold,
								&g_Floo[nCntFloo].mtxWold,
								&mtxRot);
			//�ʒu
			D3DXMatrixTranslation(	&mtxTrans,
									g_Floo[nCntFloo].pos.x,
									g_Floo[nCntFloo].pos.y,
									g_Floo[nCntFloo].pos.z);

			D3DXMatrixMultiply(	&g_Floo[nCntFloo].mtxWold,
								&g_Floo[nCntFloo].mtxWold,
								&mtxTrans);
			//�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(	D3DTS_WORLD,
									&g_Floo[nCntFloo].mtxWold);
			//---------------------------
			//�`�揈��
			//---------------------------
			//�o�b�t�@�̐ݒ���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(	0,
										g_pVtxBuffFloo,
										0,
										sizeof(VERTEX_3D));
			//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetIndices(g_pIdxBuffFloo);

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(	0,
									g_pTextureField[g_Floo[nCntFloo].nTex]);
			//�|���S���̕`��
			pDevice->DrawIndexedPrimitive(	D3DPT_TRIANGLESTRIP,			//�v���~�e�B�u�̎��
											0,								//�C���f�b�N�X �o�b�t�@�̊J�n�n�_����ŏ��̃C���f�b�N�X�܂ł̃I�t�Z�b�g
											nCntFloo * FLOO_VTX_NUM_MAX,	//�`��Ŏg�p�����ŏ��̒��_�ԍ�
											FLOO_IDX_NUM_MAX,				//���_�̐�
											nCntFloo * FLOO_IDX_NUM_MAX,	//�C���f�b�N�X�z��̓ǂݎ����J�n����ʒu
											FLOO_POLY_NUM_MAX;				//���̐�
		}
		//���e�X�g
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);
	}
}

//---------------------------
//���̃Z�b�g
//---------------------------
void SetFloo(D3DXVECTOR3 rot, D3DXVECTOR3 pos, float fWidth, float fDepht, int nTex)
{
	for (int nCntFloo = 0; nCntFloo < MAX_FLOO; nCntFloo++)
	{
		if (g_Floo[nCntFloo].bUse == false)
		{
			g_Floo[nCntFloo].pos = pos;			//�ʒu������
			g_Floo[nCntFloo].rot = rot;			//����������
			g_Floo[nCntFloo].fWidth = fWidth;	//��������
			g_Floo[nCntFloo].fDepht = fDepht;	//���s������
			g_Floo[nCntFloo].nTex = nTex;		//�e�N�X�`���̎��

			g_Floo[nCntFloo].bUse = true;		//�g���Ă�
			break;
		}
	}
}