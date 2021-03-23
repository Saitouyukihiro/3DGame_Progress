//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[

#include "main.h"
#include "input.h"
#include "Field.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureField[FIELDTYPE_MAX] = {};//�e�N�X�`���ւ̃|�C���^
Field g_Field[MAX_FIELD];

//����������
HRESULT InitField(void)
{

	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�̃|�C���^
	pDevice = GetDevice();//�f�o�C�X�̎擾
	
	for (int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		g_Field[nCntField].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Field[nCntField].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Field[nCntField].pVtxBuffField = NULL;
		g_Field[nCntField].pIdxBuffField = NULL;
		g_Field[nCntField].fWidth = 0.0f;
		g_Field[nCntField].fDepht = 0.0f;
		g_Field[nCntField].ntype = 0;
		g_Field[nCntField].bUse = false;

	}
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/field002.jpg", &g_pTextureField[FIELDTYPE_NOMAL]);

	return S_OK;
}

//�I������
void UninitField(void)//�ǉ��̉\�������邽�ߍ��ڂ͍���Ƃ�
{
	for (int nCntTex = 0; nCntTex < FIELDTYPE_MAX; nCntTex++)
	{
		//�e�N�X�`���j��
		if (g_pTextureField[nCntTex] != NULL)
		{
			g_pTextureField[nCntTex]->Release();
			g_pTextureField[nCntTex] = NULL;
		}
	}

	for (int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		//���_�o�b�t�@�j��
		if (g_Field[nCntField].pVtxBuffField != NULL)
		{
			g_Field[nCntField].pVtxBuffField->Release();
			g_Field[nCntField].pVtxBuffField = NULL;
		}
		//�C���f�b�N�X�j��
		if (g_Field[nCntField].pIdxBuffField != NULL)
		{
			g_Field[nCntField].pIdxBuffField->Release();
			g_Field[nCntField].pIdxBuffField = NULL;
		}
	}
}

//�X�V����
void UpdateField(void)//�ǉ��̉\�������邽�ߍ��ڂ͍���Ƃ�
{

}

//�`�揈��
void DrawField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;

	for (int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		
		if (g_Field[nCntField].bUse == true)
		{

			D3DXMatrixIdentity(&g_Field[nCntField].mtxwold);
			//�X�P�[��
			g_Field[nCntField].mtxwold._11 = g_Field[nCntField].fWidth;

			g_Field[nCntField].mtxwold._33 = g_Field[nCntField].fDepht;

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Field[nCntField].rot.y, g_Field[nCntField].rot.x, g_Field[nCntField].rot.z);
			D3DXMatrixMultiply(&g_Field[nCntField].mtxwold, &g_Field[nCntField].mtxwold, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Field[nCntField].pos.x, g_Field[nCntField].pos.y, g_Field[nCntField].pos.z);
			D3DXMatrixMultiply(&g_Field[nCntField].mtxwold, &g_Field[nCntField].mtxwold, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Field[nCntField].mtxwold);

			//�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_Field[nCntField].pVtxBuffField, 0, sizeof(VERTEX_3D));
			//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetIndices(g_Field[nCntField].pIdxBuffField);

			pDevice->SetFVF(FVF_VERTEX_3D);//���_�t�H�[�}�b�g�̐ݒ�

			pDevice->SetTexture(0, g_pTextureField[g_Field[nCntField].ntype]);//�e�N�X�`���̐ݒ�

			//�|���S���̕`��
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,				//�v���~�e�B�u�̎��
										  0,								//�C���f�b�N�X �o�b�t�@�̊J�n�n�_����ŏ��̃C���f�b�N�X�܂ł̃I�t�Z�b�g
										  nCntField * FLOO_VTX_NUM_MAX,		//�`��Ŏg�p�����ŏ��̒��_�ԍ�
										  FLOO_IDX_NUM_MAX,					//���_�̐�
										  nCntField * FLOO_IDX_NUM_MAX,		//�C���f�b�N�X�z��̓ǂݎ����J�n����ʒu
										  FLOO_POLY_NUM_MAX;				//���̐�
		}
	}
}

void SetField(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fDepht, int ntype)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//�f�o�C�X�̃|�C���^

	for (int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		if (g_Field[nCntField].bUse == false)
		{
			g_Field[nCntField].pos = pos;
			g_Field[nCntField].rot = rot;
			g_Field[nCntField].fWidth = fWidth;
			g_Field[nCntField].fDepht = fDepht;
			g_Field[nCntField].ntype = ntype;

			//���_�o�b�t�@�̐���
			pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * FLOO_VTX_NUM_MAX * MAX_FIELD, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_Field[nCntField].pVtxBuffField, NULL);
			//�C���f�b�N�X�o�b�t�@�쐬
			pDevice->CreateIndexBuffer(sizeof(WORD) * FLOO_IDX_NUM_MAX * MAX_FIELD, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_Field[nCntField].pIdxBuffField, NULL);

			//���_���
			VERTEX_3D*pVtx;//���_���ւ̃|�C���^
			//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
			g_Field[nCntField].pVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);
			for (int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
			{
				int nVtxNum = 0;
				for (int nCntZ = 0; nCntZ < FLOO_MAX_VTX_Z + 1; nCntZ++)
				{
					for (int nCntX = 0; nCntX < FLOO_MAX_VTX_X + 1; nCntX++, nVtxNum++)
					{
						pVtx[nVtxNum].pos = D3DXVECTOR3(-MS_X + (((MS_X * 2) / FLOO_MAX_VTX_X) * nCntX), 0.0f, MS_Z - (((MS_Z * 2) / FLOO_MAX_VTX_Z) * nCntZ));
						pVtx[nVtxNum].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
						pVtx[nVtxNum].col = D3DCOLOR_RGBA(255, 255, 255, 255);
						pVtx[nVtxNum].tex = D3DXVECTOR2(0.0f + (1.0f * nCntX), 0.0f + (1.0f * nCntZ));
					}
				}
				nVtxNum = 0;
				pVtx += FLOO_VTX_NUM_MAX;	//���_��i�߂�
			}

			//���_�o�b�t�@���A�����b�N����
			g_Field[nCntField].pVtxBuffField->Unlock();

			WORD *pIdx;		//�C���f�b�N�X���ւ̃|�C���^

			//�C���f�b�N�X�o�b�t�@�����b�N���A�ԍ��f�[�^�ւ̃|�C���^���擾
			g_Field[nCntField].pIdxBuffField->Lock(0, 0, (void**)&pIdx, 0);

			for (int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
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
			g_Field[nCntField].pIdxBuffField->Unlock();
			g_Field[nCntField].bUse = true;
			break;
		}
	}
}