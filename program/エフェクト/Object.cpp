//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
//���f���̏���(Object.cpp)
//Author�F�����G��
//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[

#include "main.h"
#include "Object.h"
#include "Shadow.h"
#include "camera.h"
#include "Effect.h"

//�O���[�o���ϐ�
LPD3DXMESH g_pMeshObject[MAX_OBJECT] = {};//���b�V���ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatObject[MAX_OBJECT] = {};//�}�e���A���ւ̃|�C���^
DWORD g_nNumMatObject[MAX_OBJECT] = {};		//�}�e���A���̐�

LPDIRECT3DTEXTURE9 g_pTextueObject[MAX_OBJECT][64] = {};//�e�N�X�`��

Object g_Object[MAX_OBJECT];

//����������
void InitObject(void)
{

	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		g_Object[nCntObject].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Object[nCntObject].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Object[nCntObject].Color = D3DXCOLOR(255, 255, 255, 255);

		g_Object[nCntObject].VtxMaxObject = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Object[nCntObject].VtxMinObject = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		g_Object[nCntObject].ntype = 0;
		g_Object[nCntObject].bUse = false;
	}
	
}

//�I������
void UninitObject(void)//�ǉ��̉\�������邽�ߍ��ڂ͍���Ƃ�
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		//�I�u�W�F�N�g�̔j��
		if (g_pMeshObject[nCntObject] != NULL)
		{
			g_pMeshObject[nCntObject]->Release();
			g_pMeshObject[nCntObject] = NULL;
		}
		//���_�o�b�t�@���j��
		if (g_pBuffMatObject[nCntObject] != NULL)
		{
			g_pBuffMatObject[nCntObject]->Release();
			g_pBuffMatObject[nCntObject] = NULL;
		}
	}
	
}

//�X�V����
void UpdateObject(void)//�ǉ��̉\�������邽�ߍ��ڂ͍���Ƃ�
{

}

//�`�揈��
void DrawObject(void)
{

	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�̃|�C���^
	pDevice = GetDevice();//�f�o�C�X���擾����
	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X

	D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ�
	D3DXMATERIAL *pMat;//�}�e���A���f�[�^�|�C���^

	D3DCOLORVALUE *pMatColor;

	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (g_Object[nCntObject].bUse == true)
		{
			D3DXMatrixIdentity(&g_Object[nCntObject].mtxObject);//���[���h�}�g���b�N�X�̏�����

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Object[nCntObject].rot.y, g_Object[nCntObject].rot.x, g_Object[nCntObject].rot.z);
			D3DXMatrixMultiply(&g_Object[nCntObject].mtxObject, &g_Object[nCntObject].mtxObject, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Object[nCntObject].pos.x, g_Object[nCntObject].pos.y, g_Object[nCntObject].pos.z);
			D3DXMatrixMultiply(&g_Object[nCntObject].mtxObject, &g_Object[nCntObject].mtxObject, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Object[nCntObject].mtxObject);

			//���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			//�}�e���A���f�[�^�̎擾
			pMat = (D3DXMATERIAL*)g_pBuffMatObject[nCntObject]->GetBufferPointer();
			pMatColor = (D3DCOLORVALUE*)g_pBuffMatObject[nCntObject]->GetBufferPointer();

			//�p�[�c����
			for (int nCntMat = 0; nCntMat < (int)g_nNumMatObject[nCntObject]; nCntMat++)
			{
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextueObject[nCntObject][nCntMat]);
				
				//���f���p�[�c�̕`��
				g_pMeshObject[nCntObject]->DrawSubset(nCntMat);
				
			}
		}
	}
	//�ۑ������}�e���A���߂�
	pDevice->SetMaterial(&matDef);

}

//�I�u�W�F�N�g�̐ݒ菈��
void SetObject(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int ntype)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//�f�o�C�X�̃|�C���^
	
	int nNumVtx; //���_��
	DWORD sizeFVF; //���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff; //���_�o�b�t�@�ւ̃|�C���^
	D3DXMATERIAL * pMat;//�}�e���A���|�C���^

	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (g_Object[nCntObject].bUse == false)
		{
			
				g_Object[nCntObject].pos = pos;
				g_Object[nCntObject].ntype = ntype;
				g_Object[nCntObject].rot = rot;

				if (g_Object[nCntObject].ntype == OBJECTTYPE_TANK)
				{
					//x�t�@�C���̓ǂݍ���
					D3DXLoadMeshFromX("date/Model/Tank.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatObject[nCntObject], NULL, &g_nNumMatObject[nCntObject], &g_pMeshObject[nCntObject]);
				}

				else if (g_Object[nCntObject].ntype == OBJECTTYPE_SANDBAG)
				{
					//x�t�@�C���̓ǂݍ���
					D3DXLoadMeshFromX("date/Model/Sandbag.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatObject[nCntObject], NULL, &g_nNumMatObject[nCntObject], &g_pMeshObject[nCntObject]);
				}

				else if (g_Object[nCntObject].ntype == OBJECTTYPE_BLOCK00)
				{
					//x�t�@�C���̓ǂݍ���
					D3DXLoadMeshFromX("date/Model/Block.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatObject[nCntObject], NULL, &g_nNumMatObject[nCntObject], &g_pMeshObject[nCntObject]);
				}

				else if (g_Object[nCntObject].ntype == OBJECTTYPE_BLOCK01)
				{
					//x�t�@�C���̓ǂݍ���
					D3DXLoadMeshFromX("date/Model/Block01.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatObject[nCntObject], NULL, &g_nNumMatObject[nCntObject], &g_pMeshObject[nCntObject]);
				}

				//�}�e���A���f�[�^�̎擾
				pMat = (D3DXMATERIAL*)g_pBuffMatObject[nCntObject]->GetBufferPointer();
				for (int nCantMat = 0; nCantMat < g_nNumMatObject[nCntObject]; nCantMat++)
				{
					if (pMat[nCantMat].pTextureFilename != NULL)
					{
						D3DXCreateTextureFromFile(pDevice, pMat[nCantMat].pTextureFilename, &g_pTextueObject[nCntObject][nCantMat]);
					}
				}

					//���_���̎擾
					nNumVtx = g_pMeshObject[nCntObject]->GetNumVertices();

					//���_�t�H�[�}�b�g�̃T�C�Y���擾
					sizeFVF = D3DXGetFVFVertexSize(g_pMeshObject[nCntObject]->GetFVF());

					//���_�o�b�t�@���b�N
					g_pMeshObject[nCntObject]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

					//�傫���̊m�F
					for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
					{
						D3DXVECTOR3 Vtx = *(D3DXVECTOR3*)pVtxBuff;//���_���W���
	
						//***************************************
						//X��
						//***************************************
						//��r�Ώۂ�Max���傫��������
						if (Vtx.x > g_Object[nCntObject].VtxMaxObject.x)
						{
							g_Object[nCntObject].VtxMaxObject.x = Vtx.x + MAX_COLLISION;
						}
						//��r�Ώۂ�Min��菬����������
						if (Vtx.x < g_Object[nCntObject].VtxMinObject.x)
						{
							g_Object[nCntObject].VtxMinObject.x = Vtx.x - MIN_COLLISION;
						}

						//***************************************
						//Y��
						//***************************************
						//��r�Ώۂ�Max���傫��������
						if (Vtx.y > g_Object[nCntObject].VtxMaxObject.y)
						{
							g_Object[nCntObject].VtxMaxObject.y = Vtx.y + MAX_COLLISION;
						}
						//��r�Ώۂ�Min��菬����������
						if (Vtx.y < g_Object[nCntObject].VtxMinObject.y)
						{
							g_Object[nCntObject].VtxMinObject.y = Vtx.y - MIN_COLLISION;
						}

						//***************************************
						//Z��
						//***************************************
						//��r�Ώۂ�Max���傫��������
						if (Vtx.z > g_Object[nCntObject].VtxMaxObject.z)
						{
							g_Object[nCntObject].VtxMaxObject.z = Vtx.z + MAX_COLLISION;
						}
						//��r�Ώۂ�Min��菬����������
						if (Vtx.z < g_Object[nCntObject].VtxMinObject.z)
						{
							g_Object[nCntObject].VtxMinObject.z = Vtx.z - MIN_COLLISION;
						}

						pVtxBuff += sizeFVF;//��r�Ώۂ̕ύX
					}

					//���_�o�b�t�@�A�����b�N
					g_pMeshObject[nCntObject]->UnlockVertexBuffer();
					g_Object[nCntObject].bUse = true;
			break;
		}

	}
}

Object *GetObject(void)
{
	return &g_Object[0];
}

//#endif