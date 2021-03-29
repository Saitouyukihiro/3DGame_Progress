//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cube.h"
#include "shadow.h"
#include "keyinput.h"
#include "camara.h"

//---------------------------
//�O���[�o���ϐ�
//---------------------------
LPDIRECT3DTEXTURE9		g_pTextureCube[MAX_CUBE][MAX_CUBE_TEX];	//�e�N�X�`���ւ̃|�C���^
Cube				g_aCube[MAX_CUBE];	//�G�̍\����

//---------------------------
//����������
//---------------------------
HRESULT InitCube(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	pDevice = GetDevice();		//�f�o�C�X�̎擾

	for (int nCntCube = 0; nCntCube < MAX_CUBE; nCntCube++)
	{
		g_aCube[nCntCube].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCube[nCntCube].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCube[nCntCube].bCollision = false;
		g_aCube[nCntCube].bUse = false;
		g_aCube[nCntCube].g_bLoop = true;

		//---------------------------
		//X�t�@�C���̓ǂݍ���
		//---------------------------
		D3DXLoadMeshFromX(	"data/Model/cube/cube.x",
							D3DXMESH_SYSTEMMEM,
							pDevice,
							NULL,
							&g_aCube[nCntCube].pBuffMat,
							NULL,
							&g_aCube[nCntCube].pnNumMat,
							&g_aCube[nCntCube].pMesh);
		//---------------------------
		//�e�N�X�`���̔����o��
		//---------------------------
		D3DXMATERIAL *pMat;	//�}�e���A���̃|�C���^

							//�}�e���A�����̃|�C���^
		pMat = (D3DXMATERIAL*)g_aCube[nCntCube].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_aCube[nCntCube].pnNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				//�e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(	pDevice,
											pMat[nCntMat].pTextureFilename,			//�e�N�X�`��
											&g_pTextureCube[nCntCube][nCntMat]);
			}
		}
		//---------------------------
		//���_���W�̔����o��
		//---------------------------
		int nNumVtx;	//���_��
		DWORD sizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y
		BYTE *pVtxBuff;	//���_�o�b�t�@�̃|�C���^

						//���_�����擾
		nNumVtx = g_aCube[nCntCube].pMesh->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_aCube[nCntCube].pMesh->GetFVF());

		//���_�o�b�t�@�̃��b�N
		g_aCube[nCntCube].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//���_���W�̑��

			//���_�����r���čŏ��l�A�ő�l�𔲂�
			//X
			if (g_aCube[nCntCube].vtxMax.x <= vtx.x)
			{
				g_aCube[nCntCube].vtxMax.x = vtx.x;
			}
			if (g_aCube[nCntCube].vtxMin.x >= vtx.x)
			{
				g_aCube[nCntCube].vtxMin.x = vtx.x;
			}
			//Y
			if (g_aCube[nCntCube].vtxMax.y <= vtx.y)
			{
				g_aCube[nCntCube].vtxMax.y = vtx.y;
			}
			if (g_aCube[nCntCube].vtxMin.y >= vtx.y)
			{
				g_aCube[nCntCube].vtxMin.y = vtx.y;
			}
			//Z
			if (g_aCube[nCntCube].vtxMax.z <= vtx.z)
			{
				g_aCube[nCntCube].vtxMax.z = vtx.z;
			}
			if (g_aCube[nCntCube].vtxMin.z >= vtx.z)
			{
				g_aCube[nCntCube].vtxMin.z = vtx.z;
			}

			pVtxBuff += sizeFVF;	//���_��i�߂�
		}
		//���_�o�b�t�@���A�����b�N
		g_aCube[nCntCube].pMesh->UnlockVertexBuffer();

		g_aCube[nCntCube].vertexpos[0] = D3DXVECTOR3(-g_aCube[nCntCube].vtxMax.x, g_aCube[nCntCube].vtxMax.y, g_aCube[nCntCube].vtxMax.z);
		g_aCube[nCntCube].vertexpos[1] = D3DXVECTOR3(g_aCube[nCntCube].vtxMax.x, g_aCube[nCntCube].vtxMax.y, g_aCube[nCntCube].vtxMax.z);
		g_aCube[nCntCube].vertexpos[2] = D3DXVECTOR3(-g_aCube[nCntCube].vtxMax.x, g_aCube[nCntCube].vtxMax.y, -g_aCube[nCntCube].vtxMax.z);
		g_aCube[nCntCube].vertexpos[3] = D3DXVECTOR3(g_aCube[nCntCube].vtxMax.x, g_aCube[nCntCube].vtxMax.y, -g_aCube[nCntCube].vtxMax.z);
		g_aCube[nCntCube].vertexpos[4] = D3DXVECTOR3(-g_aCube[nCntCube].vtxMax.x, -g_aCube[nCntCube].vtxMax.y, g_aCube[nCntCube].vtxMax.z);
		g_aCube[nCntCube].vertexpos[5] = D3DXVECTOR3(g_aCube[nCntCube].vtxMax.x, -g_aCube[nCntCube].vtxMax.y, g_aCube[nCntCube].vtxMax.z);
		g_aCube[nCntCube].vertexpos[6] = D3DXVECTOR3(-g_aCube[nCntCube].vtxMax.x, -g_aCube[nCntCube].vtxMax.y, -g_aCube[nCntCube].vtxMax.z);
		g_aCube[nCntCube].vertexpos[7] = D3DXVECTOR3(g_aCube[nCntCube].vtxMax.x, -g_aCube[nCntCube].vtxMax.y, -g_aCube[nCntCube].vtxMax.z);
	}
	return S_OK;
}

//---------------------------
//�I������
//---------------------------
void UninitCube(void)
{
	for (int nCntCube = 0; nCntCube < MAX_CUBE; nCntCube++)
	{
		//---------------------------
		//���b�V���j��
		//---------------------------
		if (g_aCube[nCntCube].pMesh != NULL)
		{
			g_aCube[nCntCube].pMesh->Release();
			g_aCube[nCntCube].pMesh = NULL;
		}

		//---------------------------
		//�}�e���A���j��
		//---------------------------
		if (g_aCube[nCntCube].pBuffMat != NULL)
		{
			g_aCube[nCntCube].pBuffMat->Release();
			g_aCube[nCntCube].pBuffMat = NULL;
		}
	}
}

//---------------------------
//�X�V����
//---------------------------
void UpdateCube(void)
{

}

//---------------------------
//�`�揈��
//---------------------------
void DrawCube(void)
{
	LPDIRECT3DDEVICE9	pDevice;			//�f�o�C�X�̃|�C���^

	pDevice = GetDevice();					//�f�o�C�X���擾����

	for (int nCntCube = 0; nCntCube < MAX_CUBE; nCntCube++)
	{
		if (g_aCube[nCntCube].bUse == true)
		{
			//-------------------------------
			//�v���C���[(���_)�̃}�g���b�N�X�̐ݒ�
			//-------------------------------
			D3DXMATRIX			mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

			if (g_aCube[nCntCube].bCollision == false)
			{
				pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
			}
			else
			{
				pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
			}

			D3DXMatrixIdentity(&g_aCube[nCntCube].mtxWold);	//�}�g���b�N�X������

			//�����̐ݒ�
			D3DXMatrixRotationYawPitchRoll(	&mtxRot,
											g_aCube[nCntCube].rot.y,
											g_aCube[nCntCube].rot.x,
											g_aCube[nCntCube].rot.z);

			D3DXMatrixMultiply(	&g_aCube[nCntCube].mtxWold,
								&g_aCube[nCntCube].mtxWold,
								&mtxRot);
			//�ʒu
			D3DXMatrixTranslation(	&mtxTrans,
									g_aCube[nCntCube].pos.x,
									g_aCube[nCntCube].pos.y,
									g_aCube[nCntCube].pos.z);

			D3DXMatrixMultiply(	&g_aCube[nCntCube].mtxWold,
								&g_aCube[nCntCube].mtxWold,
								&mtxTrans);
			//�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(	D3DTS_WORLD,
									&g_aCube[nCntCube].mtxWold);
			//---------------------------
			//�`�揈��
			//---------------------------
			D3DMATERIAL9		matDef;				//�}�e���A���̈ꎞ�ۑ�
			D3DXMATERIAL		*pMat;				//�}�e���A���f�[�^�̃|�C���^

													//���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			//�}�e���A���f�[�^�̃|�C���^
			pMat = (D3DXMATERIAL*)g_aCube[nCntCube].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aCube[nCntCube].pnNumMat; nCntMat++)
			{
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0,
					g_pTextureCube[nCntCube][nCntMat]);

				//���f���p�[�c�̕`��
				g_aCube[nCntCube].pMesh->DrawSubset(nCntMat);
			}
			//�ꎞ�ۑ����Ă�������ǂ�
			pDevice->SetMaterial(&matDef);

			for (int nCntVtx = 0; nCntVtx < 8; nCntVtx++)
			{
				D3DXMATRIX			mtxvtxRot, mtxvtxTrans;	//�v�Z�p�}�g���b�N�X
				D3DXMATRIX			mtxParent;

				D3DXMatrixIdentity(&g_aCube[nCntCube].vertexmtxWold[nCntVtx]);	//�}�g���b�N�X������

				//�����̐ݒ�
				D3DXMatrixRotationYawPitchRoll(&mtxvtxRot,
					g_aCube[nCntCube].vertexrot[nCntVtx].y,
					g_aCube[nCntCube].vertexrot[nCntVtx].x,
					g_aCube[nCntCube].vertexrot[nCntVtx].z);

				D3DXMatrixMultiply(&g_aCube[nCntCube].vertexmtxWold[nCntVtx],
					&g_aCube[nCntCube].vertexmtxWold[nCntVtx],
					&mtxvtxRot);
				//�ʒu
				D3DXMatrixTranslation(&mtxvtxTrans,
					g_aCube[nCntCube].vertexpos[nCntVtx].x,
					g_aCube[nCntCube].vertexpos[nCntVtx].y,
					g_aCube[nCntCube].vertexpos[nCntVtx].z);

				D3DXMatrixMultiply(&g_aCube[nCntCube].vertexmtxWold[nCntVtx],
					&g_aCube[nCntCube].vertexmtxWold[nCntVtx],
					&mtxvtxTrans);

				//�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃��[���h�}�g���b�N�X���|�����킹��
				D3DXMatrixMultiply(&g_aCube[nCntCube].vertexmtxWold[nCntVtx],
					&g_aCube[nCntCube].vertexmtxWold[nCntVtx],
					&g_aCube[nCntCube].mtxWold);

				mtxParent = g_aCube[nCntCube].mtxWold;

				//�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(D3DTS_WORLD,
					&g_aCube[nCntCube].vertexmtxWold[nCntVtx]);
			}
		}
	}
}

//---------------------------
//�Z�b�g
//---------------------------
void SetCube(int nIdx, D3DXVECTOR3 rot, D3DXVECTOR3 pos, bool bCollision)
{
	g_aCube[nIdx].pos = pos;
	g_aCube[nIdx].rot = rot;
	g_aCube[nIdx].bCollision = bCollision;
}

int SetCubeUse(D3DXVECTOR3 rot, D3DXVECTOR3 pos, bool bCollision)
{
	int nIndex = -1;

	for (int nCntCube = 0; nCntCube < MAX_CUBE; nCntCube++)
	{
		if (g_aCube[nCntCube].bUse == false)
		{
			g_aCube[nCntCube].pos = pos;
			g_aCube[nCntCube].rot = rot;
			g_aCube[nCntCube].bCollision = bCollision;

			g_aCube[nCntCube].bUse = true;
			nIndex = nCntCube;
			break;
		}
	}
	return nIndex;
}

void SetCube(D3DXVECTOR3 rot, D3DXVECTOR3 pos)
{
	for (int nCntCube = 0; nCntCube < MAX_CUBE; nCntCube++)
	{
		if (g_aCube[nCntCube].bUse == false)
		{
			g_aCube[nCntCube].pos = pos;
			g_aCube[nCntCube].rot = rot;

			g_aCube[nCntCube].bUse = true;
			g_aCube[nCntCube].bCollision = true;
			break;
		}
	}
}

bool CollisionCude(D3DXVECTOR3 *pos, D3DXVECTOR3 *posold, D3DXVECTOR3 *move, float fRadiou)
{
	Camera *pCamera = GetCamera();
	Cube *pCube = GetCube();
	D3DXVECTOR3 vec[4];
	D3DXVECTOR3 pvec[4];
	D3DXVECTOR3 poldvec[4];
	LPDIRECT3DDEVICE9	pDevice; //�f�o�C�X�̃|�C���^
	float fask[4];
	float faskold[4];

	pDevice = GetDevice();	//�f�o�C�X���擾����

	for (int nCnt4 = 0; nCnt4 < 4; nCnt4++)
	{
		vec[nCnt4] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pvec[nCnt4] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		poldvec[nCnt4] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		fask[nCnt4] = 0.0f;
	}

	for (int nCntCube = 0; nCntCube < MAX_CUBE; nCntCube++, pCube++)
	{
		if (g_aCube[nCntCube].bUse == true)
		{	
			if (g_aCube[nCntCube].g_bLoop == true)
			{
				g_aCube[nCntCube].vertexpos[0].x -= fRadiou;
				g_aCube[nCntCube].vertexpos[0].z += fRadiou;

				g_aCube[nCntCube].vertexpos[1].x += fRadiou;
				g_aCube[nCntCube].vertexpos[1].z += fRadiou;

				g_aCube[nCntCube].vertexpos[2].x -= fRadiou;
				g_aCube[nCntCube].vertexpos[2].z -= fRadiou;

				g_aCube[nCntCube].vertexpos[3].x += fRadiou;
				g_aCube[nCntCube].vertexpos[3].z -= fRadiou;

				g_aCube[nCntCube].vertexpos[4].x -= fRadiou;
				g_aCube[nCntCube].vertexpos[4].z += fRadiou;

				g_aCube[nCntCube].vertexpos[5].x += fRadiou;
				g_aCube[nCntCube].vertexpos[5].z += fRadiou;

				g_aCube[nCntCube].vertexpos[6].x -= fRadiou;
				g_aCube[nCntCube].vertexpos[6].z -= fRadiou;

				g_aCube[nCntCube].vertexpos[7].x += fRadiou;
				g_aCube[nCntCube].vertexpos[7].z -= fRadiou;

				g_aCube[nCntCube].g_bLoop = false;
			}

			for (int nCntVtx = 0; nCntVtx < 8; nCntVtx++)
			{
				D3DXMATRIX			mtxvtxRot, mtxvtxTrans;	//�v�Z�p�}�g���b�N�X
				D3DXMATRIX			mtxParent;

				D3DXMatrixIdentity(&g_aCube[nCntCube].vertexmtxWold[nCntVtx]);	//�}�g���b�N�X������

				//�����̐ݒ�
				D3DXMatrixRotationYawPitchRoll(	&mtxvtxRot,
												g_aCube[nCntCube].vertexrot[nCntVtx].y,
												g_aCube[nCntCube].vertexrot[nCntVtx].x,
												g_aCube[nCntCube].vertexrot[nCntVtx].z);

				D3DXMatrixMultiply(	&g_aCube[nCntCube].vertexmtxWold[nCntVtx],
									&g_aCube[nCntCube].vertexmtxWold[nCntVtx],
									&mtxvtxRot);
				//�ʒu
				D3DXMatrixTranslation(	&mtxvtxTrans,
										g_aCube[nCntCube].vertexpos[nCntVtx].x,
										g_aCube[nCntCube].vertexpos[nCntVtx].y,
										g_aCube[nCntCube].vertexpos[nCntVtx].z);

				D3DXMatrixMultiply(	&g_aCube[nCntCube].vertexmtxWold[nCntVtx],
									&g_aCube[nCntCube].vertexmtxWold[nCntVtx],
									&mtxvtxTrans);

				mtxParent = g_aCube[nCntCube].mtxWold;

				//�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃��[���h�}�g���b�N�X���|�����킹��
				D3DXMatrixMultiply(	&g_aCube[nCntCube].vertexmtxWold[nCntVtx],
									&g_aCube[nCntCube].vertexmtxWold[nCntVtx],
									&mtxParent);

				//�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(	D3DTS_WORLD,
										&g_aCube[nCntCube].vertexmtxWold[nCntVtx]);
			}

			//---------------------------
			//�O��
			//---------------------------
			//���_���璸�_�̃x�N�g��(�� - �O)		�����[���h�}�g���b�N�X�ł��
			vec[0].x = pCube->vertexmtxWold[5]._41 - pCube->vertexmtxWold[4]._41;
			vec[0].z = pCube->vertexmtxWold[5]._43 - pCube->vertexmtxWold[4]._43;

			vec[1].x = pCube->vertexmtxWold[7]._41 - pCube->vertexmtxWold[5]._41;
			vec[1].z = pCube->vertexmtxWold[7]._43 - pCube->vertexmtxWold[5]._43;

			vec[2].x = pCube->vertexmtxWold[6]._41 - pCube->vertexmtxWold[7]._41;
			vec[2].z = pCube->vertexmtxWold[6]._43 - pCube->vertexmtxWold[7]._43;

			vec[3].x = pCube->vertexmtxWold[4]._41 - pCube->vertexmtxWold[6]._41;
			vec[3].z = pCube->vertexmtxWold[4]._43 - pCube->vertexmtxWold[6]._43;

			//���_�Ɠ������̃x�N�g��(�������� - ���_)		�����[���h�}�g���b�N�X�ł��
			pvec[0].x = pos->x - pCube->vertexmtxWold[4]._41;
			pvec[0].z = pos->z - pCube->vertexmtxWold[4]._43;

			pvec[1].x = pos->x - pCube->vertexmtxWold[5]._41;
			pvec[1].z = pos->z - pCube->vertexmtxWold[5]._43;

			pvec[2].x = pos->x - pCube->vertexmtxWold[7]._41;
			pvec[2].z = pos->z - pCube->vertexmtxWold[7]._43;

			pvec[3].x = pos->x - pCube->vertexmtxWold[6]._41;
			pvec[3].z = pos->z - pCube->vertexmtxWold[6]._43;

			//���_�ƑO��̓������̃x�N�g��(�������� - ���_)		�����[���h�}�g���b�N�X�ł��
			poldvec[0].x = posold->x - pCube->vertexmtxWold[4]._41;
			poldvec[0].z = posold->z - pCube->vertexmtxWold[4]._43;

			poldvec[1].x = posold->x - pCube->vertexmtxWold[5]._41;
			poldvec[1].z = posold->z - pCube->vertexmtxWold[5]._43;

			poldvec[2].x = posold->x - pCube->vertexmtxWold[7]._41;
			poldvec[2].z = posold->z - pCube->vertexmtxWold[7]._43;

			poldvec[3].x = posold->x - pCube->vertexmtxWold[6]._41;
			poldvec[3].z = posold->z - pCube->vertexmtxWold[6]._43;

			//���̊O��
			fask[0] = (vec[0].x * pvec[0].z) - (pvec[0].x * vec[0].z);
			fask[1] = (vec[1].x * pvec[1].z) - (pvec[1].x * vec[1].z);
			fask[2] = (vec[2].x * pvec[2].z) - (pvec[2].x * vec[2].z);
			fask[3] = (vec[3].x * pvec[3].z) - (pvec[3].x * vec[3].z);

			//�O��̊O��
			faskold[0] = (vec[0].x * poldvec[0].z) - (poldvec[0].x * vec[0].z);
			faskold[1] = (vec[1].x * poldvec[1].z) - (poldvec[1].x * vec[1].z);
			faskold[2] = (vec[2].x * poldvec[2].z) - (poldvec[2].x * vec[2].z);
			faskold[3] = (vec[3].x * poldvec[3].z) - (poldvec[3].x * vec[3].z);

			//
			if ((fask[0] < 0.0f && fask[1] < 0.0f && fask[2] < 0.0f && fask[3] < 0.0f) &&
				(faskold[0] >= 0.0f || faskold[1] >= 0.0f || faskold[2] >= 0.0f || faskold[3] >= 0.0f))
			{
				pos->x = posold->x;
				pos->z = posold->z;
			}
		}
	}
	pCube -= MAX_CUBE;
	return true;
}

Cube *GetCube(void)
{
	return &g_aCube[0];
}