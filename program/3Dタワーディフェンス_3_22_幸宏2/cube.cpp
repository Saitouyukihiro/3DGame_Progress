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
				pDevice->SetTexture(	0,
										g_pTextureCube[nCntCube][nCntMat]);

				//���f���p�[�c�̕`��
				g_aCube[nCntCube].pMesh->DrawSubset(nCntMat);
			}
			//�ꎞ�ۑ����Ă�������ǂ�
			pDevice->SetMaterial(&matDef);
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

Cube *GetCube(void)
{
	return &g_aCube[0];
}

bool CollisionCude(D3DXVECTOR3 *pos, D3DXVECTOR3 *posold, D3DXVECTOR3 *move, float fWidth, float fHeight)
{
	bool bCollision = false;
	D3DXVECTOR3 posdfrc;
	D3DXVECTOR3 efectmove;
	float nGuysR = 50.0f;
	float fposdfrcX;

	posdfrc = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	for (int nCntCube = 0; nCntCube < MAX_CUBE; nCntCube++)
	{
		if (g_aCube[nCntCube].bUse == true)
		{
			posdfrc.x = g_aCube[nCntCube].pos.x - pos->x;
			posdfrc.z = g_aCube[nCntCube].pos.z - pos->z;

			posdfrc.x = posdfrc.x * posdfrc.x;
			posdfrc.z = posdfrc.z * posdfrc.z;

			fposdfrcX = posdfrc.x + posdfrc.z;

			fposdfrcX = sqrtf(fposdfrcX);

			if (g_aCube[nCntCube].pos.y <= pos->y + fHeight / 2 &&
				g_aCube[nCntCube].pos.y + g_aCube[nCntCube].fHight >= pos->y - fHeight / 2 &&
				fposdfrcX < nGuysR)
			{
				bCollision = true;
			}
		}
	}
	return bCollision;
}