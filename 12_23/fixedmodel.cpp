//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "fixedmodel.h"
#include "shadow.h"
#include "model.h"

//---------------------------
//�O���[�o���ϐ�
//---------------------------
LPDIRECT3DTEXTURE9		g_apTextureFixemodel[MAX_FIXED_MODEL][MAX_FIXEMODEL_TEX] = {};	//�e�N�X�`���̃|�C���^
Fixedmodel				g_aFixedmodel[MAX_FIXED_MODEL];	//���f���̍\����

//---------------------------
//����������
//---------------------------
HRESULT InitFixedModel(void)
{
	LPDIRECT3DDEVICE9	pDevice;	//�f�o�C�X�ւ̃|�C���^

	pDevice = GetDevice();			//�f�o�C�X�̎擾

	for (int nCntModel = 0; nCntModel < MAX_FIXED_MODEL; nCntModel++)
	{
		//�ʒu����������
		g_aFixedmodel[nCntModel].PosModel = (D3DXVECTOR3(-500.0f, 0.0f, 0.0f));
		g_aFixedmodel[nCntModel].RotModel = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		g_aFixedmodel[nCntModel].vtxMaxModel = (D3DXVECTOR3(-1000000.0f, -1000000.0f, -1000000.0f));
		g_aFixedmodel[nCntModel].vtxMinModel = (D3DXVECTOR3(1000000.0f, 1000000.0f, 1000000.0f));
		g_aFixedmodel[nCntModel].pMeshFixedmodel = {};
		g_aFixedmodel[nCntModel].pBuffMatFixedmodel = {};
		g_aFixedmodel[nCntModel].nIdex = 0;
		g_aFixedmodel[nCntModel].bUse = false;
	}

	return S_OK;
}

//---------------------------
//�I������
//---------------------------
void UninitFixedModel(void)
{
	for (int nCntModel = 0; nCntModel < MAX_FIXED_MODEL; nCntModel++)
	{
		//---------------------------
		//���b�V���j��
		//---------------------------
		if (g_aFixedmodel[nCntModel].pMeshFixedmodel != NULL)
		{
			g_aFixedmodel[nCntModel].pMeshFixedmodel->Release();
			g_aFixedmodel[nCntModel].pMeshFixedmodel = NULL;
		}

		//---------------------------
		//�}�e���A���j��
		//---------------------------
		if (g_aFixedmodel[nCntModel].pBuffMatFixedmodel != NULL)
		{
			g_aFixedmodel[nCntModel].pBuffMatFixedmodel->Release();
			g_aFixedmodel[nCntModel].pBuffMatFixedmodel = NULL;
		}
	}
}

//---------------------------
//�X�V����
//---------------------------
void UpdateFixedModel(void)
{
	Model *pModel;

	pModel = GetModel();

	for (int nCntModel = 0; nCntModel < MAX_FIXED_MODEL; nCntModel++)
	{
		if (g_aFixedmodel[nCntModel].bUse == true)
		{
			
		}
	}
}

//---------------------------
//�`�揈��
//---------------------------
void DrawFixedModel(void)
{
	LPDIRECT3DDEVICE9	pDevice;			//�f�o�C�X�̃|�C���^

	pDevice = GetDevice();					//�f�o�C�X���擾����

	//---------------------------
	//�}�g���b�N�X�̐ݒ�
	//---------------------------
	D3DXMATRIX			mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	for (int nCntModel = 0; nCntModel < MAX_FIXED_MODEL; nCntModel++)
	{
		if (g_aFixedmodel[nCntModel].bUse == true)
		{
			//���e�X�g
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

			D3DXMatrixIdentity(&g_aFixedmodel[nCntModel].mtxWoldModel);	//�}�g���b�N�X������

			//�����̐ݒ�
			D3DXMatrixRotationYawPitchRoll(	&mtxRot,
											g_aFixedmodel[nCntModel].RotModel.y,
											g_aFixedmodel[nCntModel].RotModel.x,
											g_aFixedmodel[nCntModel].RotModel.z);

			D3DXMatrixMultiply(	&g_aFixedmodel[nCntModel].mtxWoldModel,
								&g_aFixedmodel[nCntModel].mtxWoldModel,
								&mtxRot);
			//�ʒu
			D3DXMatrixTranslation(	&mtxTrans,
									g_aFixedmodel[nCntModel].PosModel.x,
									g_aFixedmodel[nCntModel].PosModel.y,
									g_aFixedmodel[nCntModel].PosModel.z);

			D3DXMatrixMultiply(	&g_aFixedmodel[nCntModel].mtxWoldModel,
								&g_aFixedmodel[nCntModel].mtxWoldModel,
								&mtxTrans);
			//�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(	D3DTS_WORLD,
									&g_aFixedmodel[nCntModel].mtxWoldModel);
			//---------------------------
			//�`�揈��
			//---------------------------
			D3DMATERIAL9		matDef;				//�}�e���A���̈ꎞ�ۑ�
			D3DXMATERIAL		*pMat;				//�}�e���A���f�[�^�̃|�C���^

													//���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			//�}�e���A���f�[�^�̃|�C���^
			pMat = (D3DXMATERIAL*)g_aFixedmodel[nCntModel].pBuffMatFixedmodel->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aFixedmodel[nCntModel].pnNumMatModel; nCntMat++)
			{
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(	0,
										g_apTextureFixemodel[nCntModel][nCntMat]);

				//���f���p�[�c�̕`��
				g_aFixedmodel[nCntModel].pMeshFixedmodel->DrawSubset(nCntMat);
			}
			//�ꎞ�ۑ����Ă�������ǂ�
			pDevice->SetMaterial(&matDef);

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
void SetFixedModel(D3DXVECTOR3 PosModel, D3DXVECTOR3 RotModel, MODEL_TYPE Type)
{
	LPDIRECT3DDEVICE9	pDevice;	//�f�o�C�X�ւ̃|�C���^

	pDevice = GetDevice();			//�f�o�C�X�̎擾

	for (int nCntModel = 0; nCntModel < MAX_FIXED_MODEL; nCntModel++)
	{
		if (g_aFixedmodel[nCntModel].bUse == false)
		{
			g_aFixedmodel[nCntModel].PosModel = PosModel;
			g_aFixedmodel[nCntModel].RotModel = RotModel;
			g_aFixedmodel[nCntModel].aType = Type;

			if (g_aFixedmodel[nCntModel].aType == MODEL_HERTS)
			{
				//---------------------------
				//X�t�@�C���̓ǂݍ���
				//---------------------------
				D3DXLoadMeshFromX(	"data/Model/Herts.x",
									D3DXMESH_SYSTEMMEM,
									pDevice,
									NULL,
									&g_aFixedmodel[nCntModel].pBuffMatFixedmodel,
									NULL,
									&g_aFixedmodel[nCntModel].pnNumMatModel,
									&g_aFixedmodel[nCntModel].pMeshFixedmodel);
			}
			else if (g_aFixedmodel[nCntModel].aType == MODEL_CAT)
			{
				//---------------------------
				//X�t�@�C���̓ǂݍ���
				//---------------------------
				D3DXLoadMeshFromX(	"data/Model/Cat.x",
									D3DXMESH_SYSTEMMEM,
									pDevice,
									NULL,
									&g_aFixedmodel[nCntModel].pBuffMatFixedmodel,
									NULL,
									&g_aFixedmodel[nCntModel].pnNumMatModel,
									&g_aFixedmodel[nCntModel].pMeshFixedmodel);
			}
			//---------------------------
			//�e�N�X�`���̔����o��
			//---------------------------
			D3DXMATERIAL *pMat;	//�}�e���A���̃|�C���^

			//�}�e���A�����̃|�C���^
			pMat = (D3DXMATERIAL*)g_aFixedmodel[nCntModel].pBuffMatFixedmodel->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aFixedmodel[nCntModel].pnNumMatModel; nCntMat++)
			{
				if (pMat[nCntMat].pTextureFilename != NULL)
				{
					//�e�N�X�`���̓ǂݍ���
					D3DXCreateTextureFromFile(	pDevice,
												pMat[nCntMat].pTextureFilename,			//�e�N�X�`��
												&g_apTextureFixemodel[nCntModel][nCntMat]);
				}
			}

			//---------------------------
			//���_���W�̔����o��
			//---------------------------
			int nNumVtx;	//���_��
			DWORD sizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y
			BYTE *pVtxBuff;	//���_�o�b�t�@�̃|�C���^

			//���_�����擾
			nNumVtx = g_aFixedmodel[nCntModel].pMeshFixedmodel->GetNumVertices();

			//���_�t�H�[�}�b�g�̃T�C�Y���擾
			sizeFVF = D3DXGetFVFVertexSize(g_aFixedmodel[nCntModel].pMeshFixedmodel->GetFVF());

			//���_�o�b�t�@�̃��b�N
			g_aFixedmodel[nCntModel].pMeshFixedmodel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
			{
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//���_���W�̑��

				//���_�����r���čŏ��l�A�ő�l�𔲂�
				//X
				if (g_aFixedmodel[nCntModel].vtxMaxModel.x <= vtx.x)
				{
					g_aFixedmodel[nCntModel].vtxMaxModel.x = vtx.x;
				}
				if (g_aFixedmodel[nCntModel].vtxMinModel.x >= vtx.x)
				{
					g_aFixedmodel[nCntModel].vtxMinModel.x = vtx.x;
				}
				//Y
				if (g_aFixedmodel[nCntModel].vtxMaxModel.y <= vtx.y)
				{
					g_aFixedmodel[nCntModel].vtxMaxModel.y = vtx.y;
				}
				if (g_aFixedmodel[nCntModel].vtxMinModel.y >= vtx.y)
				{
					g_aFixedmodel[nCntModel].vtxMinModel.y = vtx.y;
				}
				//Z
				if (g_aFixedmodel[nCntModel].vtxMaxModel.z <= vtx.z)
				{
					g_aFixedmodel[nCntModel].vtxMaxModel.z = vtx.z;
				}
				if (g_aFixedmodel[nCntModel].vtxMinModel.z >= vtx.z)
				{
					g_aFixedmodel[nCntModel].vtxMinModel.z = vtx.z;
				}

				pVtxBuff += sizeFVF;	//���_��i�߂�
			}
			//���_�o�b�t�@���A�����b�N
			g_aFixedmodel[nCntModel].pMeshFixedmodel->UnlockVertexBuffer();
			g_aFixedmodel[nCntModel].nIdex = SetShadow(g_aFixedmodel[nCntModel].PosModel, g_aFixedmodel[nCntModel].vtxMaxModel.x * 4, g_aFixedmodel[nCntModel].vtxMaxModel.z * 4);
			g_aFixedmodel[nCntModel].bUse = true;
			break;
		}
	}
}