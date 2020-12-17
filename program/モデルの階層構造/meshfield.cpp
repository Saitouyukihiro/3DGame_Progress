//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "meshfield.h"

//---------------------------
//�O���[�o���ϐ�
//---------------------------
LPDIRECT3DTEXTURE9		g_pTextureField[MAX_MESH_TEX] = {};	//�e�N�X�`���ւ̃|�C���^
Field					g_Field[MAX_FIELD];		//���b�V���t�B�[���h�̍\����

//---------------------------
//�O���[�o���ϐ�
//---------------------------
HRESULT InitMeshfield(void)
{
	LPDIRECT3DDEVICE9	pDevice;	//�f�o�C�X�ւ̃|�C���^

	pDevice = GetDevice();			//�f�o�C�X�̎擾

	for (int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		g_Field[nCntField].Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Field[nCntField].Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Field[nCntField].pVtxBuffField = NULL;
		g_Field[nCntField].pIdxBuffFoeld = NULL;
		g_Field[nCntField].fWidth = 1.0f;
		g_Field[nCntField].fHeiht = 1.0f;
		g_Field[nCntField].fDepht = 1.0f;
		g_Field[nCntField].nTex = 0;
		g_Field[nCntField].bUse = false;
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/field002.jpg",			//�e�N�X�`��
								&g_pTextureField[0]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/field000.jpg",			//�e�N�X�`��
								&g_pTextureField[1]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/field001.jpg",			//�e�N�X�`��
								&g_pTextureField[2]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/cat01.png",				//�e�N�X�`��
								&g_pTextureField[3]);
	return S_OK;
}

//---------------------------
//�I������
//---------------------------
void UninitMeshfield(void)
{
	//---------------------------
	//�e�N�X�`���j��
	//---------------------------
	for (int nCntTex = 0; nCntTex < MAX_MESH_TEX; nCntTex++)
	{
		if (g_pTextureField[nCntTex] != NULL)
		{
			g_pTextureField[nCntTex]->Release();
			g_pTextureField[nCntTex] = NULL;
		}
	}

	for (int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		//---------------------------
		//�o�b�t�@�j��
		//---------------------------
		if (g_Field[nCntField].pVtxBuffField != NULL)
		{
			g_Field[nCntField].pVtxBuffField->Release();
			g_Field[nCntField].pVtxBuffField = NULL;
		}

		//---------------------------
		//�C���f�b�N�X�o�b�t�@�j��
		//---------------------------
		if (g_Field[nCntField].pIdxBuffFoeld != NULL)
		{
			g_Field[nCntField].pIdxBuffFoeld->Release();
			g_Field[nCntField].pIdxBuffFoeld = NULL;
		}
	}
}

//---------------------------
//�X�V����
//---------------------------
void UpdateMeshfield(void)
{
	
}	

//---------------------------
//�`�揈��
//---------------------------
void DrawMeshfield(void)
{
	LPDIRECT3DDEVICE9	pDevice;			//�f�o�C�X�̃|�C���^

	pDevice = GetDevice();					//�f�o�C�X���擾����

	//---------------------------
	//�}�g���b�N�X�̐ݒ�
	//---------------------------
	D3DXMATRIX			mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	for (int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		if (g_Field[nCntField].bUse == true)
		{
			//�J�����O�L
			pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

			//���e�X�g
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

			D3DXMatrixIdentity(&g_Field[nCntField].mtxWold);	//�}�g���b�N�X������

			//�X�P�[��
			g_Field[nCntField].mtxWold._11 = g_Field[nCntField].fWidth;
			g_Field[nCntField].mtxWold._22 = g_Field[nCntField].fHeiht;
			g_Field[nCntField].mtxWold._33 = g_Field[nCntField].fDepht;

			//�����̐ݒ�
			D3DXMatrixRotationYawPitchRoll(	&mtxRot,
											g_Field[nCntField].Rot.y,
											g_Field[nCntField].Rot.x,
											g_Field[nCntField].Rot.z);

			D3DXMatrixMultiply(	&g_Field[nCntField].mtxWold,
								&g_Field[nCntField].mtxWold,
								&mtxRot);
			//�ʒu
			D3DXMatrixTranslation(	&mtxTrans,
									g_Field[nCntField].Pos.x,
									g_Field[nCntField].Pos.y,
									g_Field[nCntField].Pos.z);

			D3DXMatrixMultiply(	&g_Field[nCntField].mtxWold,
								&g_Field[nCntField].mtxWold,
								&mtxTrans);
			//�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(	D3DTS_WORLD,
									&g_Field[nCntField].mtxWold);
			//---------------------------
			//�`�揈��
			//---------------------------
			//�o�b�t�@�̐ݒ���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(	0,
				g_Field[nCntField].pVtxBuffField,
										0,
										sizeof(VERTEX_3D));
			//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetIndices(g_Field[nCntField].pIdxBuffFoeld);

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(	0,
									g_pTextureField[g_Field[nCntField].nTex]);
			if (g_Field[nCntField].aState == FORM_FLOO)
			{
				//�|���S���̕`��
				pDevice->DrawIndexedPrimitive(	D3DPT_TRIANGLESTRIP,			//�v���~�e�B�u�̎��
												0,								//�C���f�b�N�X �o�b�t�@�̊J�n�n�_����ŏ��̃C���f�b�N�X�܂ł̃I�t�Z�b�g
												nCntField * FLOO_VTX_NUM_MAX,	//�`��Ŏg�p�����ŏ��̒��_�ԍ�
												FLOO_IDX_NUM_MAX,				//���_�̐�
												nCntField * FLOO_IDX_NUM_MAX,	//�C���f�b�N�X�z��̓ǂݎ����J�n����ʒu
												FLOO_POLY_NUM_MAX;				//���̐�
			}
			else if (g_Field[nCntField].aState == FORM_WALL)
			{
				//�|���S���̕`��		
				pDevice->DrawIndexedPrimitive(	D3DPT_TRIANGLESTRIP,			//�v���~�e�B�u�̎��
												0,								//�C���f�b�N�X �o�b�t�@�̊J�n�n�_����ŏ��̃C���f�b�N�X�܂ł̃I�t�Z�b�g
												nCntField * WALL_VTX_NUM_MAX,	//�`��Ŏg�p�����ŏ��̒��_�ԍ�
												WALL_IDX_NUM_MAX,				//���_�̐�
												nCntField * WALL_IDX_NUM_MAX,	//�C���f�b�N�X�z��̓ǂݎ����J�n����ʒu
												WALL_POLY_NUM_MAX;				//���̐�
			}
			else if (g_Field[nCntField].aState == FORM_SEMICIRCLE)
			{
				//�|���S���̕`��
				pDevice->DrawIndexedPrimitive(	D3DPT_TRIANGLEFAN,					//�v���~�e�B�u�̎��
												0,									//�C���f�b�N�X �o�b�t�@�̊J�n�n�_����ŏ��̃C���f�b�N�X�܂ł̃I�t�Z�b�g
												nCntField * SEMICIRCLE_VTX_NUM_MAX,	//�`��Ŏg�p�����ŏ��̒��_�ԍ�
												SEMICIRCLE_IDX_NUM_MAX,				//���_�̐�
												nCntField * SEMICIRCLE_IDX_NUM_MAX,	//�C���f�b�N�X�z��̓ǂݎ����J�n����ʒu
												SEMICIRCLE_POLY_NUM_MAX;			//���̐�
			}
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
void SetField(D3DXVECTOR3 rot, D3DXVECTOR3 pos, float fWidth, float fHeight, float fDepht, int nTex, MESH_FORM aState)
{
	LPDIRECT3DDEVICE9	pDevice;	//�f�o�C�X�ւ̃|�C���^

	pDevice = GetDevice();			//�f�o�C�X�̎擾

	for (int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		if (g_Field[nCntField].bUse == false)
		{
			g_Field[nCntField].Pos = pos;			//�ʒu
			g_Field[nCntField].Rot = rot;			//����
			g_Field[nCntField].fWidth = fWidth;		//��
			g_Field[nCntField].fHeiht = fHeight;	//����
			g_Field[nCntField].fDepht = fDepht;		//���s
			g_Field[nCntField].nTex = nTex;			//�e�N�X�`��
			g_Field[nCntField].aState = aState;		//�`

			if (g_Field[nCntField].aState == FORM_FLOO)
			{
				//���_�o�b�t�@�̐���
				pDevice->CreateVertexBuffer(	sizeof(VERTEX_3D) * FLOO_VTX_NUM_MAX * MAX_FIELD,
												D3DUSAGE_WRITEONLY,
												FVF_VERTEX_3D,
												D3DPOOL_MANAGED,
												&g_Field[nCntField].pVtxBuffField,
												NULL);
				//�C���f�b�N�X�o�b�t�@�̐���
				pDevice->CreateIndexBuffer(	sizeof(WORD) * FLOO_IDX_NUM_MAX * MAX_FIELD,
											D3DUSAGE_WRITEONLY,
											D3DFMT_INDEX16,
											D3DPOOL_MANAGED,
											&g_Field[nCntField].pIdxBuffFoeld,
											NULL);
				//---------------------------
				//���_���
				//---------------------------
				VERTEX_3D *pVtx;		//���_���ւ̃|�C���^

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

				//---------------------------
				//�C���f�b�N�X���
				//---------------------------
				WORD *pIdx;		//�C���f�b�N�X���ւ̃|�C���^

				//�C���f�b�N�X�o�b�t�@�����b�N���A�ԍ��f�[�^�ւ̃|�C���^���擾
				g_Field[nCntField].pIdxBuffFoeld->Lock(0, 0, (void**)&pIdx, 0);

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
				g_Field[nCntField].pIdxBuffFoeld->Unlock();
			}
			else if (g_Field[nCntField].aState == FORM_WALL)
			{
				//���_�o�b�t�@�̐���
				pDevice->CreateVertexBuffer(	sizeof(VERTEX_3D) * WALL_VTX_NUM_MAX * MAX_FIELD,
												D3DUSAGE_WRITEONLY,
												FVF_VERTEX_3D,
												D3DPOOL_MANAGED,
												&g_Field[nCntField].pVtxBuffField,
												NULL);
				//�C���f�b�N�X�o�b�t�@�̐���
				pDevice->CreateIndexBuffer(	sizeof(WORD) * WALL_IDX_NUM_MAX * MAX_FIELD,
											D3DUSAGE_WRITEONLY,
											D3DFMT_INDEX16,
											D3DPOOL_MANAGED,
											&g_Field[nCntField].pIdxBuffFoeld,
											NULL);
				//---------------------------
				//���_���
				//---------------------------
				VERTEX_3D *pVtx;		//���_���ւ̃|�C���^

				//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
				g_Field[nCntField].pVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);

				for (int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
				{
					int nVtxNum = 0;
					for (int nCntY = 0; nCntY < WALL_MAX_VTX_Y + 1; nCntY++)
					{
						for (int nCntX = 0; nCntX < WALL_MAX_VTX_X + 1; nCntX++, nVtxNum++)
						{
							pVtx[nVtxNum].pos = D3DXVECTOR3(-MS_X + (((MS_X * 2) / WALL_MAX_VTX_X) * nCntX), MS_Z - (((MS_Z * 2) / WALL_MAX_VTX_Y) * nCntY), 0.0f);
							pVtx[nVtxNum].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
							pVtx[nVtxNum].col = D3DCOLOR_RGBA(255, 255, 255, 255);
							pVtx[nVtxNum].tex = D3DXVECTOR2(0.0f + (1.0f * nCntX), 0.0f + (1.0f * nCntY));
						}
					}
					nVtxNum = 0;
					pVtx += WALL_VTX_NUM_MAX;	//���_��i�߂�
				}

				//���_�o�b�t�@���A�����b�N����
				g_Field[nCntField].pVtxBuffField->Unlock();

				//---------------------------
				//�C���f�b�N�X���
				//---------------------------
				WORD *pIdx;		//�C���f�b�N�X���ւ̃|�C���^

				//�C���f�b�N�X�o�b�t�@�����b�N���A�ԍ��f�[�^�ւ̃|�C���^���擾
				g_Field[nCntField].pIdxBuffFoeld->Lock(0, 0, (void**)&pIdx, 0);

				for (int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
				{
					//�p�킳��ȊO�̒��_
					for (int nCntY = 0; nCntY < WALL_MAX_VTX_Y; nCntY++)
					{
						for (int nCntX = 0; nCntX < WALL_MAX_VTX_X + 1; nCntX++)
						{
							pIdx[(nCntX * 2) + 0 + ((WALL_MAX_VTX_X + 2) * 2) * nCntY] = ((WALL_MAX_VTX_X + 1) + nCntX) + ((WALL_MAX_VTX_X + 1) * nCntY);
							pIdx[(nCntX * 2) + 1 + ((WALL_MAX_VTX_X + 2) * 2) * nCntY] = (0 + nCntX) + ((WALL_MAX_VTX_X + 1) * nCntY);
						}
					}
					//�p�킳��̒��_
					for (int nCntY = 0; nCntY < WALL_MAX_VTX_Y - 1; nCntY++)
					{
						pIdx[(((WALL_MAX_VTX_X + 1) * 2 + 0) * (nCntY + 1)) + (2 * nCntY)] = WALL_MAX_VTX_X + ((WALL_MAX_VTX_X + 1) * nCntY);
						pIdx[(((WALL_MAX_VTX_X + 1) * 2 + 1) * (nCntY + 1)) + (1 * nCntY)] = (WALL_MAX_VTX_X * 2 + 2) + ((WALL_MAX_VTX_X + 1) * nCntY);
					}
					pIdx += WALL_IDX_NUM_MAX;	//�C���f�b�N�X��i�߂�
				}

				//�C���f�b�N�X�o�b�t�@���A�����b�N����
				g_Field[nCntField].pIdxBuffFoeld->Unlock();
			}
			else if (g_Field[nCntField].aState == FORM_SEMICIRCLE)
			{
				
			}
			g_Field[nCntField].bUse = true;
			break;
		}
	}
}

//---------------------------
//�����蔻��
//---------------------------
bool ColisionFeild(D3DXVECTOR3 *pos, D3DXVECTOR3 *posold, D3DXVECTOR3 *move, float fWidth, float fHeight, float fDepht, int nType)
{
	bool bLand = false;
	Field *pField;

	pField = GetField();

	for (int nCntField = 0; nCntField < MAX_FIELD; nCntField++, pField++)
	{
		if (pField->bUse == true)
		{
			if (pField->aState == FORM_FLOO)
			{
				if (pos->x + fWidth >= pField->Pos.x - pField->fWidth &&
					pos->x - fWidth <= pField->Pos.x + pField->fWidth)
				{
					if (pos->y <= pField->Pos.y)
					{
						move->y = 0.0f;
						pos->y = pField->Pos.y;
						bLand = true;
					}
				}
			}
		}
	}
	return bLand;
}

//---------------------------
//���b�V���t�B�[���h�̏��
//---------------------------
Field *GetField(void)
{
	return &g_Field[0];
}