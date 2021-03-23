//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "gunmodel.h"

//---------------------------
//�O���[�o���ϐ�
//---------------------------
LPDIRECT3DTEXTURE9		g_apTextureGunmodel[MAX_GUN_MODEL][MAX_GUN_TEX] = {};	//�e�N�X�`���̃|�C���^
Gunmodel				g_aGunmodel[MAX_GUN_MODEL];	//���f���̍\����
bool g_CollisionGun = true;

//---------------------------
//����������
//---------------------------
HRESULT InitGunModel(void)
{
	LPDIRECT3DDEVICE9	pDevice;	//�f�o�C�X�ւ̃|�C���^

	pDevice = GetDevice();			//�f�o�C�X�̎擾

	for (int nCntGun = 0; nCntGun < MAX_GUN_MODEL; nCntGun++)
	{
		//�ʒu����������
		g_aGunmodel[nCntGun].pos = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		g_aGunmodel[nCntGun].rot = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		g_aGunmodel[nCntGun].vtxMax = (D3DXVECTOR3(-1000000.0f, -1000000.0f, -1000000.0f));
		g_aGunmodel[nCntGun].vtxMin = (D3DXVECTOR3(1000000.0f, 1000000.0f, 1000000.0f));
		g_aGunmodel[nCntGun].pMesh = {};
		g_aGunmodel[nCntGun].pBuffMat = {};
		g_aGunmodel[nCntGun].bUse = false;
	}
	return S_OK;
}

//---------------------------
//�I������
//---------------------------
void UninitGunModel(void)
{
	for (int nCntGun = 0; nCntGun < MAX_GUN_MODEL; nCntGun++)
	{
		//---------------------------
		//���b�V���j��
		//---------------------------
		if (g_aGunmodel[nCntGun].pMesh != NULL)
		{
			g_aGunmodel[nCntGun].pMesh->Release();
			g_aGunmodel[nCntGun].pMesh = NULL;
		}

		//---------------------------
		//�}�e���A���j��
		//---------------------------
		if (g_aGunmodel[nCntGun].pBuffMat != NULL)
		{
			g_aGunmodel[nCntGun].pBuffMat->Release();
			g_aGunmodel[nCntGun].pBuffMat = NULL;
		}
	}
}

//---------------------------
//�X�V����
//---------------------------
void UpdateGunModel(void)
{

}

//---------------------------
//�`�揈��
//---------------------------
void DrawGunModel(void)
{
	LPDIRECT3DDEVICE9	pDevice;			//�f�o�C�X�̃|�C���^

	pDevice = GetDevice();					//�f�o�C�X���擾����

	//---------------------------
	//�}�g���b�N�X�̐ݒ�
	//---------------------------
	D3DXMATRIX			mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	for (int nCntGun = 0; nCntGun < MAX_GUN_MODEL; nCntGun++)
	{
		if (g_aGunmodel[nCntGun].bUse == true)
		{
			//���e�X�g
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

			D3DXMatrixIdentity(&g_aGunmodel[nCntGun].mtxWold);	//�}�g���b�N�X������

			//�����̐ݒ�
			D3DXMatrixRotationYawPitchRoll(	&mtxRot,
											g_aGunmodel[nCntGun].rot.y,
											g_aGunmodel[nCntGun].rot.x,
											g_aGunmodel[nCntGun].rot.z);

			D3DXMatrixMultiply(	&g_aGunmodel[nCntGun].mtxWold,
								&g_aGunmodel[nCntGun].mtxWold,
								&mtxRot);
			//�ʒu
			D3DXMatrixTranslation(	&mtxTrans,
									g_aGunmodel[nCntGun].pos.x,
									g_aGunmodel[nCntGun].pos.y,
									g_aGunmodel[nCntGun].pos.z);

			D3DXMatrixMultiply(	&g_aGunmodel[nCntGun].mtxWold,
								&g_aGunmodel[nCntGun].mtxWold,
								&mtxTrans);
			//�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(	D3DTS_WORLD,
									&g_aGunmodel[nCntGun].mtxWold);
			//---------------------------
			//�`�揈��
			//---------------------------
			D3DMATERIAL9		matDef;				//�}�e���A���̈ꎞ�ۑ�
			D3DXMATERIAL		*pMat;				//�}�e���A���f�[�^�̃|�C���^

			//���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			//�}�e���A���f�[�^�̃|�C���^
			pMat = (D3DXMATERIAL*)g_aGunmodel[nCntGun].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aGunmodel[nCntGun].pnNumMat; nCntMat++)
			{
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(	0,
										g_apTextureGunmodel[nCntGun][nCntMat]);

				//���f���p�[�c�̕`��
				g_aGunmodel[nCntGun].pMesh->DrawSubset(nCntMat);
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
int SetGunModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, Guntype Type)
{
	LPDIRECT3DDEVICE9	pDevice;	//�f�o�C�X�ւ̃|�C���^
	int nIdx = -1;

	pDevice = GetDevice();			//�f�o�C�X�̎擾

	for (int nCntGun = 0; nCntGun < MAX_GUN_MODEL; nCntGun++)
	{
		if (g_aGunmodel[nCntGun].bUse == false)
		{
			g_aGunmodel[nCntGun].pos = pos;
			g_aGunmodel[nCntGun].pos.y = pos.y + 15.0f;
			g_aGunmodel[nCntGun].rot = rot;
			g_aGunmodel[nCntGun].aType = Type;

			if (g_aGunmodel[nCntGun].aType == HANDGUN)
			{
				//---------------------------
				//X�t�@�C���̓ǂݍ���
				//---------------------------
				D3DXLoadMeshFromX(	"data/Model/Gun/handgun_00.x",
									D3DXMESH_SYSTEMMEM,
									pDevice,
									NULL,
									&g_aGunmodel[nCntGun].pBuffMat,
									NULL,
									&g_aGunmodel[nCntGun].pnNumMat,
									&g_aGunmodel[nCntGun].pMesh);
			}
			else if (g_aGunmodel[nCntGun].aType == ASULTRIFLE)
			{
				//---------------------------
				//X�t�@�C���̓ǂݍ���
				//---------------------------
				D3DXLoadMeshFromX(	"data/Model/Gun/asultrifle_00.x",
									D3DXMESH_SYSTEMMEM,
									pDevice,
									NULL,
									&g_aGunmodel[nCntGun].pBuffMat,
									NULL,
									&g_aGunmodel[nCntGun].pnNumMat,
									&g_aGunmodel[nCntGun].pMesh);
			}
			//---------------------------
			//�e�N�X�`���̔����o��
			//---------------------------
			D3DXMATERIAL *pMat;	//�}�e���A���̃|�C���^

			//�}�e���A�����̃|�C���^
			pMat = (D3DXMATERIAL*)g_aGunmodel[nCntGun].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aGunmodel[nCntGun].pnNumMat; nCntMat++)
			{
				if (pMat[nCntMat].pTextureFilename != NULL)
				{
					//�e�N�X�`���̓ǂݍ���
					D3DXCreateTextureFromFile(	pDevice,
												pMat[nCntMat].pTextureFilename,			//�e�N�X�`��
												&g_apTextureGunmodel[nCntGun][nCntMat]);
				}
			}

			//---------------------------
			//���_���W�̔����o��
			//---------------------------
			int nNumVtx;	//���_��
			DWORD sizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y
			BYTE *pVtxBuff;	//���_�o�b�t�@�̃|�C���^

			//���_�����擾
			nNumVtx = g_aGunmodel[nCntGun].pMesh->GetNumVertices();

			//���_�t�H�[�}�b�g�̃T�C�Y���擾
			sizeFVF = D3DXGetFVFVertexSize(g_aGunmodel[nCntGun].pMesh->GetFVF());

			//���_�o�b�t�@�̃��b�N
			g_aGunmodel[nCntGun].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
			{
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//���_���W�̑��

				//���_�����r���čŏ��l�A�ő�l�𔲂�
				//X
				if (g_aGunmodel[nCntGun].vtxMax.x <= vtx.x)
				{
					g_aGunmodel[nCntGun].vtxMax.x = vtx.x;
				}
				if (g_aGunmodel[nCntGun].vtxMin.x >= vtx.x)
				{
					g_aGunmodel[nCntGun].vtxMin.x = vtx.x;
				}
				//Y
				if (g_aGunmodel[nCntGun].vtxMax.y <= vtx.y)
				{
					g_aGunmodel[nCntGun].vtxMax.y = vtx.y;
				}
				if (g_aGunmodel[nCntGun].vtxMin.y >= vtx.y)
				{
					g_aGunmodel[nCntGun].vtxMin.y = vtx.y;
				}
				//Z
				if (g_aGunmodel[nCntGun].vtxMax.z <= vtx.z)
				{
					g_aGunmodel[nCntGun].vtxMax.z = vtx.z;
				}
				if (g_aGunmodel[nCntGun].vtxMin.z >= vtx.z)
				{
					g_aGunmodel[nCntGun].vtxMin.z = vtx.z;
				}

				pVtxBuff += sizeFVF;	//���_��i�߂�
			}
			//���_�o�b�t�@���A�����b�N
			g_aGunmodel[nCntGun].pMesh->UnlockVertexBuffer();

			g_aGunmodel[nCntGun].bUse = true;
			nIdx = nCntGun;
			break;
		}
	}
	return nIdx;
}

//---------------------------
//�Z�b�g
//---------------------------
Guntype SetPointGunModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nIdx)
{
	g_aGunmodel[nIdx].rot = rot;
	g_aGunmodel[nIdx].rot.x *= -1;

	if (g_aGunmodel[nIdx].aType == HANDGUN)
	{
		g_aGunmodel[nIdx].pos.x = pos.x + cosf(g_aGunmodel[nIdx].rot.y) * 20.0f;
		g_aGunmodel[nIdx].pos.y = pos.y + 15.0f;								
		g_aGunmodel[nIdx].pos.z = pos.z - sinf(g_aGunmodel[nIdx].rot.y) * 20.0f;

		g_aGunmodel[nIdx].pos.x = g_aGunmodel[nIdx].pos.x + cosf(g_aGunmodel[nIdx].rot.y - D3DX_PI / 2) * 20.0f;
		g_aGunmodel[nIdx].pos.z = g_aGunmodel[nIdx].pos.z - sinf(g_aGunmodel[nIdx].rot.y - D3DX_PI / 2) * 20.0f;

		if (g_CollisionGun == true)
		{
			g_CollisionGun = false;
		}
	}
	else if (g_aGunmodel[nIdx].aType == ASULTRIFLE)
	{
		g_aGunmodel[nIdx].pos.x = pos.x + cosf(g_aGunmodel[nIdx].rot.y) * 20.0f;
		g_aGunmodel[nIdx].pos.y = pos.y + 15.0f;
		g_aGunmodel[nIdx].pos.z = pos.z - sinf(g_aGunmodel[nIdx].rot.y) * 20.0f;

		g_aGunmodel[nIdx].pos.x = g_aGunmodel[nIdx].pos.x + cosf(g_aGunmodel[nIdx].rot.y - D3DX_PI / 2) * 15.0f;
		g_aGunmodel[nIdx].pos.z = g_aGunmodel[nIdx].pos.z - sinf(g_aGunmodel[nIdx].rot.y - D3DX_PI / 2) * 15.0f;

		if (g_CollisionGun == true)
		{
			g_CollisionGun = false;
		}
	}
	return g_aGunmodel[nIdx].aType;
}

bool CollisionGunModel(D3DXVECTOR3 *pos, D3DXVECTOR3 *posold, D3DXVECTOR3 *move, float fWidth, float fHeight, int *nIdx)
{
	int nIndx = *nIdx;
	bool bCollision = false;
	D3DXVECTOR3 posdfrc;
	D3DXVECTOR3 efectmove;
	float fAngle;
	float fSpeed = 2.5f;
	float nGuysR = 25.0f;
	float fposdfrcX;

	posdfrc = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	for (int nCntGun = 0; nCntGun < MAX_GUN_MODEL; nCntGun++)
	{
		if (g_aGunmodel[nCntGun].bUse == true)
		{
			if (nCntGun != nIndx)
			{
				g_aGunmodel[nCntGun].nCnt++;

				posdfrc.x = g_aGunmodel[nCntGun].pos.x - pos->x;
				posdfrc.z = g_aGunmodel[nCntGun].pos.z - pos->z;

				posdfrc.x = posdfrc.x * posdfrc.x;
				posdfrc.z = posdfrc.z * posdfrc.z;

				fposdfrcX = posdfrc.x + posdfrc.z;

				fposdfrcX = sqrtf(fposdfrcX);

				if (g_aGunmodel[nCntGun].pos.y <= pos->y + fHeight / 2 &&
					g_aGunmodel[nCntGun].pos.y + 5.0f >= pos->y - fHeight / 2 &&
					fposdfrcX < nGuysR)
				{
					*nIdx = nCntGun;
					g_aGunmodel[nIndx].bUse = false;
					g_CollisionGun = true;
					bCollision = true;
				}
				if (g_aGunmodel[nCntGun].nCnt > 1440)
				{
					g_aGunmodel[nCntGun].bUse = false;
					g_aGunmodel[nCntGun].nCnt = 0;
				}
			}
		}
	}
	return bCollision;
}