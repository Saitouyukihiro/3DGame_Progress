//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include <stdio.h>
#include "model.h"
#include "keyinput.h"
#include "camara.h"
#include "mouseinput.h"
#include "shadow.h"
#include "bullet.h"
#include "wall.h"
#include "meshfield.h"

//---------------------------
//�O���[�o���ϐ�
//---------------------------
Model					g_aModel;	//���f���̍\����
Player					g_aPlayer;	//�v���C���[

//---------------------------
//����������
//---------------------------
HRESULT InitModel(void)
{
	LPDIRECT3DDEVICE9	pDevice;	//�f�o�C�X�ւ̃|�C���^

	pDevice = GetDevice();			//�f�o�C�X�̎擾

	//---------------------------
	//X�t�@�C���̓ǂݍ���
	//---------------------------
	D3DXLoadMeshFromX(	"data/Model/guys1.4_body.x",
						D3DXMESH_SYSTEMMEM,
						pDevice,
						NULL,
						&g_aPlayer.aModel[0].pBuffMatModel,
						NULL,
						&g_aPlayer.aModel[0].pnNumMatModel,
						&g_aPlayer.aModel[0].pMeshModel);
	D3DXLoadMeshFromX(	"data/Model/guys1.4_rigthhand.x",
						D3DXMESH_SYSTEMMEM,
						pDevice,
						NULL,
						&g_aPlayer.aModel[1].pBuffMatModel,
						NULL,
						&g_aPlayer.aModel[1].pnNumMatModel,
						&g_aPlayer.aModel[1].pMeshModel);
	D3DXLoadMeshFromX(	"data/Model/guys1.4_rigthhand_up.x",
						D3DXMESH_SYSTEMMEM,
						pDevice,
						NULL,
						&g_aPlayer.aModel[2].pBuffMatModel,
						NULL,
						&g_aPlayer.aModel[2].pnNumMatModel,
						&g_aPlayer.aModel[2].pMeshModel);
	D3DXLoadMeshFromX(	"data/Model/guys1.4_lefthand.x",
						D3DXMESH_SYSTEMMEM,
						pDevice,
						NULL,
						&g_aPlayer.aModel[3].pBuffMatModel,
						NULL,
						&g_aPlayer.aModel[3].pnNumMatModel,
						&g_aPlayer.aModel[3].pMeshModel);
	D3DXLoadMeshFromX(	"data/Model/guys1.4_lefthand_up.x",
						D3DXMESH_SYSTEMMEM,
						pDevice,
						NULL,
						&g_aPlayer.aModel[4].pBuffMatModel,
						NULL,
						&g_aPlayer.aModel[4].pnNumMatModel,
						&g_aPlayer.aModel[4].pMeshModel);
	D3DXLoadMeshFromX(	"data/Model/guys1.4_rigthleg.x",
						D3DXMESH_SYSTEMMEM,
						pDevice,
						NULL,
						&g_aPlayer.aModel[5].pBuffMatModel,
						NULL,
						&g_aPlayer.aModel[5].pnNumMatModel,
						&g_aPlayer.aModel[5].pMeshModel);
	D3DXLoadMeshFromX(	"data/Model/guys1.4_rigthleg_down.x",
						D3DXMESH_SYSTEMMEM,
						pDevice,
						NULL,
						&g_aPlayer.aModel[6].pBuffMatModel,
						NULL,
						&g_aPlayer.aModel[6].pnNumMatModel,
						&g_aPlayer.aModel[6].pMeshModel);
	D3DXLoadMeshFromX(	"data/Model/guys1.4_leftleg.x",
						D3DXMESH_SYSTEMMEM,
						pDevice,
						NULL,
						&g_aPlayer.aModel[7].pBuffMatModel,
						NULL,
						&g_aPlayer.aModel[7].pnNumMatModel,
						&g_aPlayer.aModel[7].pMeshModel);
	D3DXLoadMeshFromX(	"data/Model/guys1.4_leftleg_down.x",
						D3DXMESH_SYSTEMMEM,
						pDevice,
						NULL,
						&g_aPlayer.aModel[8].pBuffMatModel,
						NULL,
						&g_aPlayer.aModel[8].pnNumMatModel,
						&g_aPlayer.aModel[8].pMeshModel);

	//---------------------------
	//�p�[�c�̊K�w�\��
	//---------------------------
	g_aPlayer.aModel[0].nIdxModel = -1;								//�e���f���̃C���f�b�N�X(�e������(���_)��-1)
	g_aPlayer.aModel[0].PosModel = D3DXVECTOR3(0.0f, 2.5f, 0.0f);	//�ʒu(�I�t�Z�b�g)
	g_aPlayer.aModel[0].RotModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//����
	g_aPlayer.aModel[0].vtxMaxModel = D3DXVECTOR3(-1000000.0f, -1000000.0f, -1000000.0f);
	g_aPlayer.aModel[0].vtxMinModel = D3DXVECTOR3(1000000.0f, 1000000.0f, 1000000.0f);

	g_aPlayer.aModel[1].nIdxModel = 0;								//�e���f���̃C���f�b�N�X(�e������(���_)��-1)
	g_aPlayer.aModel[1].PosModel = D3DXVECTOR3(6.0f, 12.0f, 0.0f);	//�ʒu(�I�t�Z�b�g)
	g_aPlayer.aModel[1].RotModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//����
	g_aPlayer.aModel[1].vtxMaxModel = D3DXVECTOR3(-1000000.0f, -1000000.0f, -1000000.0f);
	g_aPlayer.aModel[1].vtxMinModel = D3DXVECTOR3(1000000.0f, 1000000.0f, 1000000.0f);

	g_aPlayer.aModel[2].nIdxModel = 1;								//�e���f���̃C���f�b�N�X(�e������(���_)��-1)
	g_aPlayer.aModel[2].PosModel = D3DXVECTOR3(10.0f, 0.0f, 0.0f);	//�ʒu(�I�t�Z�b�g)
	g_aPlayer.aModel[2].RotModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//����
	g_aPlayer.aModel[2].vtxMaxModel = D3DXVECTOR3(-1000000.0f, -1000000.0f, -1000000.0f);
	g_aPlayer.aModel[2].vtxMinModel = D3DXVECTOR3(1000000.0f, 1000000.0f, 1000000.0f);

	g_aPlayer.aModel[3].nIdxModel = 0;								//�e���f���̃C���f�b�N�X(�e������(���_)��-1)
	g_aPlayer.aModel[3].PosModel = D3DXVECTOR3(-6.0f, 12.0f, 0.0f);	//�ʒu(�I�t�Z�b�g)
	g_aPlayer.aModel[3].RotModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//����
	g_aPlayer.aModel[3].vtxMaxModel = D3DXVECTOR3(-1000000.0f, -1000000.0f, -1000000.0f);
	g_aPlayer.aModel[3].vtxMinModel = D3DXVECTOR3(1000000.0f, 1000000.0f, 1000000.0f);

	g_aPlayer.aModel[4].nIdxModel = 3;								//�e���f���̃C���f�b�N�X(�e������(���_)��-1)
	g_aPlayer.aModel[4].PosModel = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);	//�ʒu(�I�t�Z�b�g)
	g_aPlayer.aModel[4].RotModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//����
	g_aPlayer.aModel[4].vtxMaxModel = D3DXVECTOR3(-1000000.0f, -1000000.0f, -1000000.0f);
	g_aPlayer.aModel[4].vtxMinModel = D3DXVECTOR3(1000000.0f, 1000000.0f, 1000000.0f);

	g_aPlayer.aModel[5].nIdxModel = 0;								//�e���f���̃C���f�b�N�X(�e������(���_)��-1)
	g_aPlayer.aModel[5].PosModel = D3DXVECTOR3(-2.0f, 3.0f, 0.0f);	//�ʒu(�I�t�Z�b�g)
	g_aPlayer.aModel[5].RotModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//����
	g_aPlayer.aModel[5].vtxMaxModel = D3DXVECTOR3(-1000000.0f, -1000000.0f, -1000000.0f);
	g_aPlayer.aModel[5].vtxMinModel = D3DXVECTOR3(1000000.0f, 1000000.0f, 1000000.0f);

	g_aPlayer.aModel[6].nIdxModel = 5;								//�e���f���̃C���f�b�N�X(�e������(���_)��-1)
	g_aPlayer.aModel[6].PosModel = D3DXVECTOR3(0.0f, -4.5f, 0.0f);	//�ʒu(�I�t�Z�b�g)
	g_aPlayer.aModel[6].RotModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//����
	g_aPlayer.aModel[6].vtxMaxModel = D3DXVECTOR3(-1000000.0f, -1000000.0f, -1000000.0f);
	g_aPlayer.aModel[6].vtxMinModel = D3DXVECTOR3(1000000.0f, 1000000.0f, 1000000.0f);

	g_aPlayer.aModel[7].nIdxModel = 0;								//�e���f���̃C���f�b�N�X(�e������(���_)��-1)
	g_aPlayer.aModel[7].PosModel = D3DXVECTOR3(2.0f, 3.0f, 0.0f);	//�ʒu(�I�t�Z�b�g)
	g_aPlayer.aModel[7].RotModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//����
	g_aPlayer.aModel[7].vtxMaxModel = D3DXVECTOR3(-1000000.0f, -1000000.0f, -1000000.0f);
	g_aPlayer.aModel[7].vtxMinModel = D3DXVECTOR3(1000000.0f, 1000000.0f, 1000000.0f);

	g_aPlayer.aModel[8].nIdxModel = 7;								//�e���f���̃C���f�b�N�X(�e������(���_)��-1)
	g_aPlayer.aModel[8].PosModel = D3DXVECTOR3(0.0f, -4.5f, 0.0f);	//�ʒu(�I�t�Z�b�g)
	g_aPlayer.aModel[8].RotModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//����
	g_aPlayer.aModel[8].vtxMaxModel = D3DXVECTOR3(-1000000.0f, -1000000.0f, -1000000.0f);
	g_aPlayer.aModel[8].vtxMinModel = D3DXVECTOR3(1000000.0f, 1000000.0f, 1000000.0f);

	//---------------------------
	//�v���C���[(���_)�̐ݒ�
	//---------------------------
	g_aPlayer.PosModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aPlayer.RotModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aPlayer.Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aPlayer.nIdex = 0;

	//---------------------------
	//���_���W�̔����o��
	//---------------------------
	int nNumVtx;	//���_��
	DWORD sizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;	//���_�o�b�t�@�̃|�C���^

	for (int nCntModel = 0; nCntModel < g_aPlayer.nNumModel; nCntModel++)
	{
		//���_�����擾
		nNumVtx = g_aPlayer.aModel[nCntModel].pMeshModel->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_aPlayer.aModel[nCntModel].pMeshModel->GetFVF());

		//���_�o�b�t�@�̃��b�N
		g_aPlayer.aModel[nCntModel].pMeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//���_���W�̑��

			//���_�����r���čŏ��l�A�ő�l�𔲂�
			//X
			if (g_aPlayer.aModel[nCntModel].vtxMaxModel.x <= vtx.x)
			{
				g_aPlayer.aModel[nCntModel].vtxMaxModel.x = vtx.x;
			}
			if (g_aPlayer.aModel[nCntModel].vtxMinModel.x >= vtx.x)
			{
				g_aPlayer.aModel[nCntModel].vtxMinModel.x = vtx.x;
			}
			//Y
			if (g_aPlayer.aModel[nCntModel].vtxMaxModel.y <= vtx.y)
			{
				g_aPlayer.aModel[nCntModel].vtxMaxModel.y = vtx.y;
			}
			if (g_aPlayer.aModel[nCntModel].vtxMinModel.y >= vtx.y)
			{
				g_aPlayer.aModel[nCntModel].vtxMinModel.y = vtx.y;
			}
			//Z
			if (g_aPlayer.aModel[nCntModel].vtxMaxModel.z <= vtx.z)
			{
				g_aPlayer.aModel[nCntModel].vtxMaxModel.z = vtx.z;
			}
			if (g_aPlayer.aModel[nCntModel].vtxMinModel.z >= vtx.z)
			{
				g_aPlayer.aModel[nCntModel].vtxMinModel.z = vtx.z;
			}

			pVtxBuff += sizeFVF;	//���_��i�߂�
		}
		//���_�o�b�t�@���A�����b�N
		g_aPlayer.aModel[nCntModel].pMeshModel->UnlockVertexBuffer();
	}

	g_aPlayer.nIdex = SetShadow(g_aPlayer.PosModel, 50.0f, 50.0f);

	return S_OK;
}

//---------------------------
//�I������
//---------------------------
void UninitModel(void)
{
	for (int nCntModelNum = 0; nCntModelNum < g_aPlayer.nNumModel; nCntModelNum++)
	{
		//---------------------------
		//���b�V���j��
		//---------------------------
		if (g_aPlayer.aModel[nCntModelNum].pMeshModel != NULL)
		{
			g_aPlayer.aModel[nCntModelNum].pMeshModel->Release();
			g_aPlayer.aModel[nCntModelNum].pMeshModel = NULL;
		}

		//---------------------------
		//�}�e���A���j��
		//---------------------------
		if (g_aPlayer.aModel[nCntModelNum].pBuffMatModel != NULL)
		{
			g_aPlayer.aModel[nCntModelNum].pBuffMatModel->Release();
			g_aPlayer.aModel[nCntModelNum].pBuffMatModel = NULL;
		}
	}
}

//---------------------------
//�X�V����
//---------------------------
void UpdateModel(void)
{
	g_aPlayer.PosoldModel = g_aPlayer.PosModel;
	Camera *pCamera;		//�J�����̍\���̂̃|�C���^
	Camera *p1Camera;		//0��(FPS)�J����
	static int nSpan;		//�N�[���^�C��

	pCamera = GetCamera();		//�J�����̏����擾
	p1Camera = Get1Camera();	//0��(FPS)�J����

	//---------------------------
	//�l�����ړ���
	//---------------------------
	for (int nCntCamera = 0; nCntCamera < MAX_CAMERA - 1; nCntCamera++, pCamera++)
	{
		if (pCamera->bUse == true)
		{
			if (GetKeyboardPress(DIK_W) == true)
			{
				g_aPlayer.PosModel.x = g_aPlayer.PosModel.x + sinf(pCamera->Rot.y) * CAMERA_MOVE_SPEED;
				g_aPlayer.PosModel.z = g_aPlayer.PosModel.z + cosf(pCamera->Rot.y) * CAMERA_MOVE_SPEED;

				//�J�����̌����ɓ]��
				g_aPlayer.RotModel.y = pCamera->Rot.y + -D3DX_PI;
			}
			if (GetKeyboardPress(DIK_S) == true)
			{
				g_aPlayer.PosModel.x = g_aPlayer.PosModel.x - sinf(pCamera->Rot.y) * CAMERA_MOVE_SPEED;
				g_aPlayer.PosModel.z = g_aPlayer.PosModel.z - cosf(pCamera->Rot.y) * CAMERA_MOVE_SPEED;

				//�J�����̌����ɓ]��
				g_aPlayer.RotModel.y = pCamera->Rot.y;
			}
			if (GetKeyboardPress(DIK_A) == true)
			{
				g_aPlayer.PosModel.x = g_aPlayer.PosModel.x - cosf(pCamera->Rot.y) * CAMERA_MOVE_SPEED;
				g_aPlayer.PosModel.z = g_aPlayer.PosModel.z + sinf(pCamera->Rot.y) * CAMERA_MOVE_SPEED;

				//�J�����̌����ɓ]��
				g_aPlayer.RotModel.y = pCamera->Rot.y + D3DX_PI / 2;
			}
			if (GetKeyboardPress(DIK_D) == true)
			{
				g_aPlayer.PosModel.x = g_aPlayer.PosModel.x + cosf(pCamera->Rot.y) * CAMERA_MOVE_SPEED;
				g_aPlayer.PosModel.z = g_aPlayer.PosModel.z - sinf(pCamera->Rot.y) * CAMERA_MOVE_SPEED;

				//�J�����̌����ɓ]��
				g_aPlayer.RotModel.y = pCamera->Rot.y + -D3DX_PI / 2;
			}
			if (GetKeyboardPress(DIK_I) == true)
			{
				g_aPlayer.PosModel.y += 1.0f;
			}
			if (GetKeyboardPress(DIK_K) == true)
			{
				g_aPlayer.PosModel.y -= 1.0f;
			}
		}
	}
	pCamera-= (MAX_CAMERA - 1);

	//---------------------------
	//���Z�b�g
	//---------------------------
	if (GetKeyboardPress(DIK_RETURN) == true)
	{
		g_aPlayer.PosModel = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		g_aPlayer.RotModel = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
	//---------------------------
	//�e�̔���
	//---------------------------
	nSpan++;
	if (GetKeyboardPress(DIK_Q) == true && nSpan > BULLET_SPAN)
	{
		for (int nCntCm = 0; nCntCm < MAX_CAMERA; nCntCm++, pCamera++)
		{
			if (pCamera->bUse == true)
			{
				SetBullet(D3DXVECTOR3(g_aPlayer.PosModel.x, g_aPlayer.PosModel.y + 25.0f, g_aPlayer.PosModel.z + 25.0f), D3DXVECTOR3(pCamera->Rot.x, pCamera->Rot.y, 0.0f), 25.0f, 25.0f, 0);
				nSpan = 0;
			}
		}
		pCamera -= MAX_CAMERA;
	}

	//g_aPlayer.Move.y += G_POW;

	//g_aPlayer.PosModel.y += g_aPlayer.Move.y;

	//�����̉e
	SetPointShadow(g_aPlayer.nIdex, g_aPlayer.PosModel, 50.0f, 50.0f);
}

//---------------------------
//�`�揈��
//---------------------------
void DrawModel(void)
{
	LPDIRECT3DDEVICE9	pDevice;			//�f�o�C�X�̃|�C���^

	pDevice = GetDevice();					//�f�o�C�X���擾����

	//-------------------------------
	//�v���C���[(���_)�̃}�g���b�N�X�̐ݒ�
	//-------------------------------
	D3DXMATRIX			mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	D3DXMatrixIdentity(&g_aPlayer.mtxWoldModel);	//�}�g���b�N�X������

	//�����̐ݒ�
	D3DXMatrixRotationYawPitchRoll(	&mtxRot,
									g_aPlayer.RotModel.y,
									g_aPlayer.RotModel.x,
									g_aPlayer.RotModel.z);

	D3DXMatrixMultiply(	&g_aPlayer.mtxWoldModel,
						&g_aPlayer.mtxWoldModel,
						&mtxRot);
	//�ʒu
	D3DXMatrixTranslation(	&mtxTrans,
							g_aPlayer.PosModel.x,
							g_aPlayer.PosModel.y,
							g_aPlayer.PosModel.z);

	D3DXMatrixMultiply(	&g_aPlayer.mtxWoldModel,
						&g_aPlayer.mtxWoldModel,
						&mtxTrans);
	//�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(	D3DTS_WORLD,
							&g_aPlayer.mtxWoldModel);

	//---------------------------------
	//���f���p�[�c�̃}�g���b�N�X�̐ݒ�
	//---------------------------------
	for (int nCntModel = 0; nCntModel < g_aPlayer.nNumModel; nCntModel++)
	{
		D3DXMATRIX mtxRotModel, mtxTransModel;	//�v�Z�p�}�g���b�N�X
		D3DXMATRIX mtxParent;					//�e�̃}�g���b�N�X

		D3DXMatrixIdentity(&g_aPlayer.aModel[nCntModel].mtxWoldModel);	//�}�g���b�N�X������

		//�����̐ݒ�
		D3DXMatrixRotationYawPitchRoll(	&mtxRotModel,
										g_aPlayer.aModel[nCntModel].RotModel.y,
										g_aPlayer.aModel[nCntModel].RotModel.x,
										g_aPlayer.aModel[nCntModel].RotModel.z);

		D3DXMatrixMultiply(	&g_aPlayer.aModel[nCntModel].mtxWoldModel,
							&g_aPlayer.aModel[nCntModel].mtxWoldModel,
							&mtxRotModel);
		//�ʒu
		D3DXMatrixTranslation(	&mtxTransModel,
								g_aPlayer.aModel[nCntModel].PosModel.x,
								g_aPlayer.aModel[nCntModel].PosModel.y,
								g_aPlayer.aModel[nCntModel].PosModel.z);

		D3DXMatrixMultiply(	&g_aPlayer.aModel[nCntModel].mtxWoldModel,
							&g_aPlayer.aModel[nCntModel].mtxWoldModel,
							&mtxTransModel);

		//�p�[�c�̐e�̃}�g���b�N�X��ݒ�
		//�����e��������
		if (g_aPlayer.aModel[nCntModel].nIdxModel != -1)
		{
			mtxParent = g_aPlayer.aModel[g_aPlayer.aModel[nCntModel].nIdxModel].mtxWoldModel;
		}
		else
		{
			mtxParent = g_aPlayer.mtxWoldModel;
		}

		//�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃��[���h�}�g���b�N�X���|�����킹��
		D3DXMatrixMultiply(	&g_aPlayer.aModel[nCntModel].mtxWoldModel,
							&g_aPlayer.aModel[nCntModel].mtxWoldModel,
							&mtxParent);

		//�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(	D3DTS_WORLD,
								&g_aPlayer.aModel[nCntModel].mtxWoldModel);

		//---------------------------
		//�`�揈��
		//---------------------------
		D3DMATERIAL9		matDef;				//�}�e���A���̈ꎞ�ۑ�
		D3DXMATERIAL		*pMat;				//�}�e���A���f�[�^�̃|�C���^

		//���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		//�}�e���A���f�[�^�̃|�C���^
		pMat = (D3DXMATERIAL*)g_aPlayer.aModel[nCntModel].pBuffMatModel->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_aPlayer.aModel[nCntModel].pnNumMatModel; nCntMat++)
		{
			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(	0,
									NULL);

			//���f���p�[�c�̕`��
			g_aPlayer.aModel[nCntModel].pMeshModel->DrawSubset(nCntMat);
		}
		//�ꎞ�ۑ����Ă�������ǂ�
		pDevice->SetMaterial(&matDef);
	}
}

//---------------------------
//���f�����擾
//---------------------------
Player *GetPlayer(void)
{
	return &g_aPlayer;
}