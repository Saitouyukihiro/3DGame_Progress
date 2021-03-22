//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "turret.h"
#include "shadow.h"
#include "keyinput.h"
#include "girl.h"

//---------------------------
//�O���[�o���ϐ�
//---------------------------
Turret				g_aTurret[MAX_TURRET];	//�G�̍\����

//---------------------------
//����������
//---------------------------
HRESULT InitTurret(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	pDevice = GetDevice();		//�f�o�C�X�̎擾

	for (int nCntTurret = 0; nCntTurret < MAX_TURRET; nCntTurret++)
	{
		g_aTurret[nCntTurret].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTurret[nCntTurret].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTurret[nCntTurret].bCollision = false;
		g_aTurret[nCntTurret].bUse = false;

		//---------------------------
		//X�t�@�C���̓ǂݍ���
		//---------------------------
		D3DXLoadMeshFromX(	"data/Model/turret/turret.x",
							D3DXMESH_SYSTEMMEM,
							pDevice,
							NULL,
							&g_aTurret[nCntTurret].pBuffMat,
							NULL,
							&g_aTurret[nCntTurret].pnNumMat,
							&g_aTurret[nCntTurret].pMesh);
		//---------------------------
		//���_���W�̔����o��
		//---------------------------
		int nNumVtx;	//���_��
		DWORD sizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y
		BYTE *pVtxBuff;	//���_�o�b�t�@�̃|�C���^

		//���_�����擾
		nNumVtx = g_aTurret[nCntTurret].pMesh->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_aTurret[nCntTurret].pMesh->GetFVF());

		//���_�o�b�t�@�̃��b�N
		g_aTurret[nCntTurret].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//���_���W�̑��

			//���_�����r���čŏ��l�A�ő�l�𔲂�
			//X
			if (g_aTurret[nCntTurret].vtxMax.x <= vtx.x)
			{
				g_aTurret[nCntTurret].vtxMax.x = vtx.x;
			}
			if (g_aTurret[nCntTurret].vtxMin.x >= vtx.x)
			{
				g_aTurret[nCntTurret].vtxMin.x = vtx.x;
			}
			//Y
			if (g_aTurret[nCntTurret].vtxMax.y <= vtx.y)
			{
				g_aTurret[nCntTurret].vtxMax.y = vtx.y;
			}
			if (g_aTurret[nCntTurret].vtxMin.y >= vtx.y)
			{
				g_aTurret[nCntTurret].vtxMin.y = vtx.y;
			}
			//Z
			if (g_aTurret[nCntTurret].vtxMax.z <= vtx.z)
			{
				g_aTurret[nCntTurret].vtxMax.z = vtx.z;
			}
			if (g_aTurret[nCntTurret].vtxMin.z >= vtx.z)
			{
				g_aTurret[nCntTurret].vtxMin.z = vtx.z;
			}

			pVtxBuff += sizeFVF;	//���_��i�߂�
		}
		//���_�o�b�t�@���A�����b�N
		g_aTurret[nCntTurret].pMesh->UnlockVertexBuffer();
	}
	return S_OK;
}

//---------------------------
//�I������
//---------------------------
void UninitTurret(void)
{
	for (int nCntTurret = 0; nCntTurret < MAX_TURRET; nCntTurret++)
	{
		//---------------------------
		//���b�V���j��
		//---------------------------
		if (g_aTurret[nCntTurret].pMesh != NULL)
		{
			g_aTurret[nCntTurret].pMesh->Release();
			g_aTurret[nCntTurret].pMesh = NULL;
		}

		//---------------------------
		//�}�e���A���j��
		//---------------------------
		if (g_aTurret[nCntTurret].pBuffMat != NULL)
		{
			g_aTurret[nCntTurret].pBuffMat->Release();
			g_aTurret[nCntTurret].pBuffMat = NULL;
		}
	}
}

//---------------------------
//�X�V����
//---------------------------
void UpdateTurret(void)
{

}

//---------------------------
//�`�揈��
//---------------------------
void DrawTurret(void)
{
	LPDIRECT3DDEVICE9	pDevice;			//�f�o�C�X�̃|�C���^

	pDevice = GetDevice();					//�f�o�C�X���擾����

	for (int nCntTurret = 0; nCntTurret < MAX_TURRET; nCntTurret++)
	{
		if (g_aTurret[nCntTurret].bUse == true)
		{
			//-------------------------------
			//�v���C���[(���_)�̃}�g���b�N�X�̐ݒ�
			//-------------------------------
			D3DXMATRIX			mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

			if (g_aTurret[nCntTurret].bCollision == false)
			{
				pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
			}
			else
			{
				pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
			}

			D3DXMatrixIdentity(&g_aTurret[nCntTurret].mtxWold);	//�}�g���b�N�X������

			//�����̐ݒ�
			D3DXMatrixRotationYawPitchRoll(	&mtxRot,
											g_aTurret[nCntTurret].rot.y,
											g_aTurret[nCntTurret].rot.x,
											g_aTurret[nCntTurret].rot.z);

			D3DXMatrixMultiply(	&g_aTurret[nCntTurret].mtxWold,
								&g_aTurret[nCntTurret].mtxWold,
								&mtxRot);
			//�ʒu
			D3DXMatrixTranslation(	&mtxTrans,
									g_aTurret[nCntTurret].pos.x,
									g_aTurret[nCntTurret].pos.y,
									g_aTurret[nCntTurret].pos.z);

			D3DXMatrixMultiply(	&g_aTurret[nCntTurret].mtxWold,
								&g_aTurret[nCntTurret].mtxWold,
								&mtxTrans);
			//�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(	D3DTS_WORLD,
									&g_aTurret[nCntTurret].mtxWold);

			//---------------------------
			//�`�揈��
			//---------------------------
			D3DMATERIAL9		matDef;				//�}�e���A���̈ꎞ�ۑ�
			D3DXMATERIAL		*pMat;				//�}�e���A���f�[�^�̃|�C���^

			//���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			//�}�e���A���f�[�^�̃|�C���^
			pMat = (D3DXMATERIAL*)g_aTurret[nCntTurret].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aTurret[nCntTurret].pnNumMat; nCntMat++)
			{
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(	0,
										NULL);

				//���f���p�[�c�̕`��
				g_aTurret[nCntTurret].pMesh->DrawSubset(nCntMat);
			}
			//�ꎞ�ۑ����Ă�������ǂ�
			pDevice->SetMaterial(&matDef);
		}
	}
}

//---------------------------
//�Z�b�g
//---------------------------
void SetTurret(int nIdx, D3DXVECTOR3 rot, D3DXVECTOR3 pos, bool bCollision)
{
	g_aTurret[nIdx].pos = pos;
	g_aTurret[nIdx].rot = rot;
	g_aTurret[nIdx].bCollision = bCollision;
}

int SetTurretUse(D3DXVECTOR3 rot, D3DXVECTOR3 pos, bool bCollision)
{
	int nIndex = -1;

	for (int nCntTurret = 0; nCntTurret < MAX_TURRET; nCntTurret++)
	{
		if (g_aTurret[nCntTurret].bUse == false)
		{
			g_aTurret[nCntTurret].pos = pos;
			g_aTurret[nCntTurret].rot = rot;
			g_aTurret[nCntTurret].bCollision = bCollision;

			g_aTurret[nCntTurret].bUse = true;
			nIndex = nCntTurret;
			break;
		}
	}
	return nIndex;
}

Turret *GetTurret(void)
{
	return &g_aTurret[0];
}

bool ColisionTurret(D3DXVECTOR3 *pos, D3DXVECTOR3 *posold, D3DXVECTOR3 *move, float fWidth, float fHeight, float fDepht, int nType)
{
	return true;
}