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

//---------------------------
//�O���[�o���ϐ�
//---------------------------
LPD3DXMESH				g_pMeshModel = NULL;		//���b�V���̃|�C���^
LPD3DXBUFFER			g_pBuffMatModel = NULL;		//�}�e���A���̃|�C���^
Model					g_aModel;					//���f���̍\����

//---------------------------
//����������
//---------------------------
HRESULT InitModel(void)
{
	LPDIRECT3DDEVICE9	pDevice;	//�f�o�C�X�ւ̃|�C���^

	pDevice = GetDevice();			//�f�o�C�X�̎擾

	//�ʒu����������
	g_aModel.PosModel = (D3DXVECTOR3(0.0f, 0.0f, -100.0f));
	g_aModel.RotModel = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	g_aModel.vtxMaxModel = (D3DXVECTOR3(-1000000.0f, -1000000.0f, -1000000.0f));
	g_aModel.vtxMinModel = (D3DXVECTOR3(1000000.0f, 1000000.0f, 1000000.0f));
	g_aModel.nIdex = 0;

	//---------------------------
	//X�t�@�C���̓ǂݍ���
	//---------------------------
	D3DXLoadMeshFromX(	"data/Model/guys.x",
						D3DXMESH_SYSTEMMEM,
						pDevice,
						NULL,
						&g_pBuffMatModel,
						NULL,
						&g_aModel.pnNumMatModel,
						&g_pMeshModel);
	//---------------------------
	//���_���W�̔����o��
	//---------------------------
	int nNumVtx;	//���_��
	DWORD sizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;	//���_�o�b�t�@�̃|�C���^

	//���_�����擾
	nNumVtx = g_pMeshModel->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(g_pMeshModel->GetFVF());

	//���_�o�b�t�@�̃��b�N
	g_pMeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//���_���W�̑��

		//���_�����r���čŏ��l�A�ő�l�𔲂�
		//X
		if (g_aModel.vtxMaxModel.x <= vtx.x)
		{
			g_aModel.vtxMaxModel.x = vtx.x;
		}
		if (g_aModel.vtxMinModel.x >= vtx.x)
		{
			g_aModel.vtxMinModel.x = vtx.x;
		}
		//Y
		if (g_aModel.vtxMaxModel.y <= vtx.y)
		{
			g_aModel.vtxMaxModel.y = vtx.y;
		}
		if (g_aModel.vtxMinModel.y >= vtx.y)
		{
			g_aModel.vtxMinModel.y = vtx.y;
		}
		//Z
		if (g_aModel.vtxMaxModel.z <= vtx.z)
		{
			g_aModel.vtxMaxModel.z = vtx.z;
		}
		if (g_aModel.vtxMinModel.z >= vtx.z)
		{
			g_aModel.vtxMinModel.z = vtx.z;
		}

		pVtxBuff += sizeFVF;	//���_��i�߂�
	}
	//���_�o�b�t�@���A�����b�N
	g_pMeshModel->UnlockVertexBuffer();

	g_aModel.nIdex = SetShadow(g_aModel.PosModel, 50.0f, 50.0f);

	return S_OK;
}

//---------------------------
//�I������
//---------------------------
void UninitModel(void)
{
	//---------------------------
	//���b�V���j��
	//---------------------------
	if (g_pMeshModel != NULL)
	{
		g_pMeshModel->Release();
		g_pMeshModel = NULL;
	}

	//---------------------------
	//�}�e���A���j��
	//---------------------------
	if (g_pBuffMatModel != NULL)
	{
		g_pBuffMatModel->Release();
		g_pBuffMatModel = NULL;
	}
}

//---------------------------
//�X�V����
//---------------------------
void UpdateModel(void)
{
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
				g_aModel.PosModel.x = g_aModel.PosModel.x + sinf(pCamera->Rot.y) * CAMERA_MOVE_SPEED;
				g_aModel.PosModel.z = g_aModel.PosModel.z + cosf(pCamera->Rot.y) * CAMERA_MOVE_SPEED;

				//�J�����̌����ɓ]��
				g_aModel.RotModel.y = pCamera->Rot.y + -D3DX_PI;
			}
			if (GetKeyboardPress(DIK_S) == true)
			{
				g_aModel.PosModel.x = g_aModel.PosModel.x - sinf(pCamera->Rot.y) * CAMERA_MOVE_SPEED;
				g_aModel.PosModel.z = g_aModel.PosModel.z - cosf(pCamera->Rot.y) * CAMERA_MOVE_SPEED;

				//�J�����̌����ɓ]��
				g_aModel.RotModel.y = pCamera->Rot.y;
			}
			if (GetKeyboardPress(DIK_A) == true)
			{
				g_aModel.PosModel.x = g_aModel.PosModel.x - cosf(pCamera->Rot.y) * CAMERA_MOVE_SPEED;
				g_aModel.PosModel.z = g_aModel.PosModel.z + sinf(pCamera->Rot.y) * CAMERA_MOVE_SPEED;

				//�J�����̌����ɓ]��
				g_aModel.RotModel.y = pCamera->Rot.y + D3DX_PI / 2;
			}
			if (GetKeyboardPress(DIK_D) == true)
			{
				g_aModel.PosModel.x = g_aModel.PosModel.x + cosf(pCamera->Rot.y) * CAMERA_MOVE_SPEED;
				g_aModel.PosModel.z = g_aModel.PosModel.z - sinf(pCamera->Rot.y) * CAMERA_MOVE_SPEED;

				//�J�����̌����ɓ]��
				g_aModel.RotModel.y = pCamera->Rot.y + -D3DX_PI / 2;
			}
			if (GetKeyboardPress(DIK_I) == true)
			{
				g_aModel.PosModel.y += 1.0f;
			}
			if (GetKeyboardPress(DIK_K) == true)
			{
				g_aModel.PosModel.y -= 1.0f;
			}
		}
	}
	pCamera-= (MAX_CAMERA - 1);

	//---------------------------
	//���Z�b�g
	//---------------------------
	if (GetKeyboardPress(DIK_RETURN) == true)
	{
		g_aModel.PosModel = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		g_aModel.RotModel = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));
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
				SetBullet(D3DXVECTOR3(g_aModel.PosModel.x, g_aModel.PosModel.y + 25.0f, g_aModel.PosModel.z + 25.0f), D3DXVECTOR3(pCamera->Rot.x, pCamera->Rot.y, 0.0f), 25.0f, 25.0f, 0);
				nSpan = 0;
			}
		}
		pCamera -= MAX_CAMERA;
	}

	//�����̉e
	SetPointShadow(g_aModel.nIdex, g_aModel.PosModel, 50.0f, 50.0f);
}

//---------------------------
//�`�揈��
//---------------------------
void DrawModel(void)
{
	LPDIRECT3DDEVICE9	pDevice;			//�f�o�C�X�̃|�C���^

	pDevice = GetDevice();					//�f�o�C�X���擾����

	//---------------------------
	//�}�g���b�N�X�̐ݒ�
	//---------------------------
	D3DXMATRIX			mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	D3DXMatrixIdentity(&g_aModel.mtxWoldModel);	//�}�g���b�N�X������

	//�����̐ݒ�
	D3DXMatrixRotationYawPitchRoll(	&mtxRot,
									g_aModel.RotModel.y,
									g_aModel.RotModel.x,
									g_aModel.RotModel.z);

	D3DXMatrixMultiply(	&g_aModel.mtxWoldModel,
						&g_aModel.mtxWoldModel,
						&mtxRot);
	//�ʒu
	D3DXMatrixTranslation(	&mtxTrans,
							g_aModel.PosModel.x,
							g_aModel.PosModel.y,
							g_aModel.PosModel.z);

	D3DXMatrixMultiply(	&g_aModel.mtxWoldModel,
						&g_aModel.mtxWoldModel,
						&mtxTrans);
	//�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(	D3DTS_WORLD,
							&g_aModel.mtxWoldModel);
	//---------------------------
	//�`�揈��
	//---------------------------
	D3DMATERIAL9		matDef;				//�}�e���A���̈ꎞ�ۑ�
	D3DXMATERIAL		*pMat;				//�}�e���A���f�[�^�̃|�C���^

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�̃|�C���^
	pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_aModel.pnNumMatModel; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0,
							NULL);

		//���f���p�[�c�̕`��
		g_pMeshModel->DrawSubset(nCntMat);
	}
	//�ꎞ�ۑ����Ă�������ǂ�
	pDevice->SetMaterial(&matDef);
}

//---------------------------
//���f�����擾
//---------------------------
Model *GetModel(void)
{
	return &g_aModel;
}