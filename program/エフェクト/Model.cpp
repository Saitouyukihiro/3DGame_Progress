//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
//���f��(�v���C���[)�̏���(Model.cpp)
//Author�F�����G��
//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[

//�C���N���[�h�t�@�C��
#include "main.h"
#include "input.h"
#include "Model.h"
#include "Shadow.h"
#include "camera.h"
#include "Billboard.h"
#include "Bullet.h"
#include "Object.h"
#include "Effect.h"
#include "Enemy.h"

//�O���[�o���ϐ�
D3DXVECTOR3 g_Oldpos;	//�����蔻��ŕK�v

//�t���I�[�g���˂ɕK�v
bool g_bCoolDown;
int g_nCntCoolDown;

D3DXVECTOR3 g_SaveModelRot;

Player g_Player;

int g_EffectTime;//�G�t�F�N�g�̏o��Ԋu

//�}�N��
#define MOVE (5.0f)
#define BULLET_COOLDOWN (3) //�e�̔��ˊԊu
#define MUGZINE_BULLET (30)//�}�K�W�����e��
#define RELOAD_TIME (60) //�����[�h����

#define EFFECT_SIZE_X (15)
#define EFFECT_SIZE_Y (15)

#define EFFECT_LIFE (15)
#define EFFECT_COOLDOWN (30)

//����������
void InitModel(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�̃|�C���^
	pDevice = GetDevice();//�f�o�C�X�̎擾
	//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
	//�\���̏�����
	//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
	g_Player.nNumModel = MAX_MODEL;//�p�[�c��������
	g_Player.state = PLAYERSTATE_NOMAL;
	g_Player.MugzineBullet = MUGZINE_BULLET;
	g_Player.ReloadTime = RELOAD_TIME;
	//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[

	g_EffectTime = 0;
	g_Oldpos = g_Player.pos;//�����ʒu���Ƃ肠�����ۑ�

	//x�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("date/Model/LMG/100_sityu.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[0].pBuffMatModel, NULL, &g_Player.aModel[0].nNumMatmodel, &g_Player.aModel[0].pMeshModel);
	//x�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("date/Model/LMG/101_gun.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[1].pBuffMatModel, NULL, &g_Player.aModel[1].nNumMatmodel, &g_Player.aModel[1].pMeshModel);
	//x�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("date/Model/LMG/102_reg.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[2].pBuffMatModel, NULL, &g_Player.aModel[2].nNumMatmodel, &g_Player.aModel[2].pMeshModel);

	//�O�Ԗڂ̃p�[�c�̃I�t�Z�b�g��
	g_Player.aModel[0].nIndxModelParent = -1;
	g_Player.aModel[0].pos = D3DXVECTOR3(0.0, 10.0, 0.0);
	g_Player.aModel[0].rot = D3DXVECTOR3(0.0, D3DX_PI * 1, 0.0);

	//1�Ԗڂ̃p�[�c�̃I�t�Z�b�g��
	g_Player.aModel[1].nIndxModelParent = 0;
	g_Player.aModel[1].pos = D3DXVECTOR3(0.0, 20.0, 0.0);
	g_Player.aModel[1].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

	//2�Ԗڂ̃p�[�c�̃I�t�Z�b�g��
	g_Player.aModel[2].nIndxModelParent = 0;
	g_Player.aModel[2].pos = D3DXVECTOR3(0.0, 0.0, 0.0);
	g_Player.aModel[2].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

	g_Player.pos = D3DXVECTOR3(0.0, 0.0, 0.0);
	g_Player.rot = D3DXVECTOR3(0.0, 0.0, 0.0);

	g_SaveModelRot = g_Player.aModel[1].rot;

	int nNumVtx; //���_��
	DWORD sizeFVF; //���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff; //���_�o�b�t�@�ւ̃|�C���^

	for (int nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
	{
		//���_���̎擾
		nNumVtx = g_Player.aModel[nCntModel].pMeshModel->GetNumVertices();
		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_Player.aModel[nCntModel].pMeshModel->GetFVF());
		//���_�o�b�t�@���b�N
		g_Player.aModel[nCntModel].pMeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 Vtx = *(D3DXVECTOR3*)pVtxBuff;//���_���W���

			//***************************************
			//X��
			//***************************************
			//��r�Ώۂ�Max���傫��������
			if (Vtx.x > g_Player.aModel[nCntModel].VtxMaxModel.x)
			{
				g_Player.aModel[nCntModel].VtxMaxModel.x = Vtx.x;
			}
			//��r�Ώۂ�Min��菬����������
			if (Vtx.x < g_Player.aModel[nCntModel].VtxMinModel.x)
			{
				g_Player.aModel[nCntModel].VtxMinModel.x = Vtx.x;
			}

			//***************************************
			//Y��
			//***************************************
			//��r�Ώۂ�Max���傫��������
			if (Vtx.y > g_Player.aModel[nCntModel].VtxMaxModel.y)
			{
				g_Player.aModel[nCntModel].VtxMaxModel.y = Vtx.y;
			}
			//��r�Ώۂ�Min��菬����������
			if (Vtx.y < g_Player.aModel[nCntModel].VtxMinModel.y)
			{
				g_Player.aModel[nCntModel].VtxMinModel.y = Vtx.y;
			}

			//***************************************
			//Z��
			//***************************************
			//��r�Ώۂ�Max���傫��������
			if (Vtx.z > g_Player.aModel[nCntModel].VtxMaxModel.z)
			{
				g_Player.aModel[nCntModel].VtxMaxModel.z = Vtx.z;
			}
			//��r�Ώۂ�Min��菬����������
			if (Vtx.z < g_Player.aModel[nCntModel].VtxMinModel.z)
			{
				g_Player.aModel[nCntModel].VtxMinModel.z = Vtx.z;
			}

			pVtxBuff += sizeFVF;//��r�Ώۂ̕ύX
		}
		//���_�o�b�t�@�A�����b�N
		g_Player.aModel[nCntModel].pMeshModel->UnlockVertexBuffer();
	}
	

	//�t���I�[�g���˂ɕK�v
	g_bCoolDown = false;
	g_nCntCoolDown = BULLET_COOLDOWN;

	//�e�̃Z�b�g
	InitShadow();
	SetShadow(g_Player.pos, 100.0f, 100.0f, TYPE_PLAYER);

	
}

//�I������
void UninitModel(void)//�ǉ��̉\�������邽�ߍ��ڂ͍���Ƃ�
{
	UninitShadow();
	for (int nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
	{
		//�e�N�X�`���̔j��
		if (g_Player.aModel[nCntModel].pMeshModel != NULL)
		{
			g_Player.aModel[nCntModel].pMeshModel->Release();
			g_Player.aModel[nCntModel].pMeshModel = NULL;
		}

		//���_�o�b�t�@���j��
		if (g_Player.aModel[nCntModel].pBuffMatModel != NULL)
		{
			g_Player.aModel[nCntModel].pBuffMatModel->Release();
			g_Player.aModel[nCntModel].pBuffMatModel = NULL;
		}
	}

}

//�X�V����
void UpdateModel(void)//�ǉ��̉\�������邽�ߍ��ڂ͍���Ƃ�
{
	Camera * pCamera;
	pCamera = GetCamera();
	bool RecoilControl = true;

	switch(g_Player.state)
	{ 
	case(PLAYERSTATE_NOMAL):
	{
		//��񂾂��ʂ�悤�ɂ���X��]�ʂ�ۑ�
		if (GetKeyboardTrigger(DIK_SPACE) == true && RecoilControl == false)
		{
			g_SaveModelRot.x = g_Player.aModel[1].rot.x;
		}

		//�e�̎ˏo
		if (GetKeyboardPress(DIK_SPACE) == true && g_bCoolDown == false)
		{
			SetBullet(D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y + 30, g_Player.pos.z), D3DXVECTOR3(g_Player.aModel[1].rot.x, g_Player.aModel[1].rot.y, g_Player.rot.z), BULLETTYPE_PLAYER);
			g_bCoolDown = true;
			g_nCntCoolDown = BULLET_COOLDOWN;

			g_Player.aModel[1].rot.x += 0.005;

			pCamera->ShotBullet = true;
			RecoilControl = true;

			g_Player.MugzineBullet--;

			if (g_Player.aModel[1].rot.x >= sinf(D3DX_PI * 0.1))
			{
				g_Player.aModel[1].rot.x = sinf(D3DX_PI * 0.1);
			}
		}
		if (GetKeyboardRelese(DIK_SPACE) == true)
		{
			pCamera->ShotBullet = false;
		}
		//�t���I�[�g����
		if (g_bCoolDown = true)
		{
			g_nCntCoolDown--;
			if (g_nCntCoolDown < 0)
			{
				g_bCoolDown = false;
			}
		}
		//�����ŏオ�����e�������鏈��
		if (pCamera->ShotBullet == false && RecoilControl == true)
		{
			g_Player.aModel[1].rot.x -= 0.01;

			if (g_Player.aModel[1].rot.x <= g_SaveModelRot.x)
			{
				g_Player.aModel[1].rot.x = g_SaveModelRot.x;
				RecoilControl = false;
			}
		}

		if (GetKeyboardTrigger(DIK_L) == TRUE || g_Player.MugzineBullet <= 0)
		{
			g_Player.state = PLAYERSTATE_RELOAD;
			g_Player.ReloadTime = RELOAD_TIME;
		}
		break;
	}
	case(PLAYERSTATE_RELOAD):
	{
		g_Player.ReloadTime--;
		if (g_Player.ReloadTime <= 0)
		{
			g_Player.MugzineBullet = MUGZINE_BULLET;
			g_Player.state = PLAYERSTATE_NOMAL;
		}
		break;
	}
		
	}
	

	//****************************************
	//�ړ�����
	//****************************************
	if (GetKeyboardPress(DIK_UP) == true)
	{
		g_Player.pos.z += cosf(pCamera->rot.y) * MOVE;
		g_Player.pos.x += sinf(pCamera->rot.y) * MOVE;
		SetEffect(g_Player.pos, D3DXCOLOR(0, 0, 255, 255), EFFECT_SIZE_X, EFFECT_SIZE_Y, EFFECTTYPE_PLAYER, EFFECT_LIFE);

	}
	else if (GetKeyboardPress(DIK_DOWN) == true)
	{
		g_Player.pos.z -= cosf(pCamera->rot.y) * MOVE;
		g_Player.pos.x -= sinf(pCamera->rot.y) * MOVE;

		SetEffect(g_Player.pos, D3DXCOLOR(0, 0, 255, 255), EFFECT_SIZE_X, EFFECT_SIZE_Y, EFFECTTYPE_PLAYER, EFFECT_LIFE);
	
	}
	if (GetKeyboardPress(DIK_LEFT) == true)
	{
		g_Player.pos.x -= cosf(pCamera->rot.y) * MOVE;
		g_Player.pos.z += sinf(pCamera->rot.y) * MOVE;
		SetEffect(g_Player.pos, D3DXCOLOR(0, 0, 255, 255), EFFECT_SIZE_X, EFFECT_SIZE_Y, EFFECTTYPE_PLAYER, EFFECT_LIFE);

	}
	else if (GetKeyboardPress(DIK_RIGHT) == true)
	{
		g_Player.pos.x += cosf(pCamera->rot.y) * MOVE;
		g_Player.pos.z -= sinf(pCamera->rot.y) * MOVE;

		SetEffect(g_Player.pos, D3DXCOLOR(0, 0, 255, 255), EFFECT_SIZE_X, EFFECT_SIZE_Y, EFFECTTYPE_PLAYER, EFFECT_LIFE);
	}

	//****************************************
	//�G�t�F�N�g�֌W
	//****************************************
	if (g_EffectTime <= 0)
	{
		SetEffect(g_Player.pos, D3DXCOLOR(0, 255, 0, 255), EFFECT_SIZE_X, EFFECT_SIZE_Y, EFFECTTYPE_FOLL_ST, EFFECT_LIFE);
		SetEffect(g_Player.pos, D3DXCOLOR(0, 255, 255, 255), EFFECT_SIZE_X, EFFECT_SIZE_Y, EFFECTTYPE_FOLL_L, EFFECT_LIFE * 2);
		SetEffect(g_Player.pos, D3DXCOLOR(255, 255, 0, 255), EFFECT_SIZE_X, EFFECT_SIZE_Y, EFFECTTYPE_FOLL_R, EFFECT_LIFE * 2);

		SetEffect(g_Player.pos, D3DXCOLOR(0, 255, 0, 255), EFFECT_SIZE_X, EFFECT_SIZE_Y, EFFECTTYPE_UP_ST, EFFECT_LIFE);
		SetEffect(g_Player.pos, D3DXCOLOR(0, 255, 255, 255), EFFECT_SIZE_X, EFFECT_SIZE_Y, EFFECTTYPE_UP_L, EFFECT_LIFE * 2);
		SetEffect(g_Player.pos, D3DXCOLOR(255, 255, 0, 255), EFFECT_SIZE_X, EFFECT_SIZE_Y, EFFECTTYPE_UP_R, EFFECT_LIFE * 2);

		g_EffectTime = EFFECT_COOLDOWN;
	}
	else if (g_EffectTime >= 0)
	{
		g_EffectTime--;
	}

	//****************************************
	//�����蔻��
	//****************************************
	Object *pObject;
	pObject = GetObject();

	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (pObject[nCntObject].bUse == true)
		{
			if (g_Player.pos.x >= pObject[nCntObject].pos.x + (pObject[nCntObject].VtxMinObject.x) && g_Player.pos.x <= pObject[nCntObject].pos.x + (pObject[nCntObject].VtxMaxObject.x) &&
				g_Player.pos.y >= pObject[nCntObject].pos.y + (pObject[nCntObject].VtxMinObject.y) && g_Player.pos.y <= pObject[nCntObject].pos.y + (pObject[nCntObject].VtxMaxObject.y) &&
				g_Player.pos.z >= pObject[nCntObject].pos.z + (pObject[nCntObject].VtxMinObject.z) && g_Player.pos.z <= pObject[nCntObject].pos.z + (pObject[nCntObject].VtxMaxObject.z))
			{
				g_Player.pos = g_Oldpos;
			}
		}
	}
	g_Oldpos = g_Player.pos;

	UpdateShadow();

}

//�`�揈��
void DrawModel(void)
{

	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�̃|�C���^
	pDevice = GetDevice();//�f�o�C�X���擾����
	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X

	D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ�
	D3DXMATERIAL *pMat;//�}�e���A���f�[�^�|�C���^

	D3DXMatrixIdentity(&g_Player.mtxWorldPlayer);//���[���h�}�g���b�N�X�̏�����

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);
	D3DXMatrixMultiply(&g_Player.mtxWorldPlayer, &g_Player.mtxWorldPlayer, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
	D3DXMatrixMultiply(&g_Player.mtxWorldPlayer, &g_Player.mtxWorldPlayer, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_Player.mtxWorldPlayer);

	//�p�[�c�P�P�ɐݒ������
	for (int nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
	{
		D3DXMATRIX mtxRotModel, mtxTransModel;//�v�Z�p�}�g���b�N�X
		D3DXMATRIX mtxParent;//�e�̃}�g���b�N�X

		D3DXMatrixIdentity(&g_Player.aModel[nCntModel].mtxWorldModel);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_Player.aModel[nCntModel].rot.y, g_Player.aModel[nCntModel].rot.x, g_Player.aModel[nCntModel].rot.z);
		D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorldModel, &g_Player.aModel[nCntModel].mtxWorldModel, &mtxRotModel);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTransModel, g_Player.aModel[nCntModel].pos.x, g_Player.aModel[nCntModel].pos.y, g_Player.aModel[nCntModel].pos.z);
		D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorldModel, &g_Player.aModel[nCntModel].mtxWorldModel, &mtxTransModel);

		//�e�̃}�g���b�N�X�𔽉f
		if (g_Player.aModel[nCntModel].nIndxModelParent != -1)
		{
			mtxParent = g_Player.aModel[g_Player.aModel[nCntModel].nIndxModelParent].mtxWorldModel;
		}
		else
		{
			mtxParent = g_Player.mtxWorldPlayer;
		}
		//�Z�o�����e�p�[�c�̃}�g���b�N�X�Ɛe�̃}�g���b�N���|�����킹��
		D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorldModel, &g_Player.aModel[nCntModel].mtxWorldModel, &mtxParent);

		//�}�g���b�N�X���Z�b�g
		pDevice->SetTransform(D3DTS_WORLD, &g_Player.aModel[nCntModel].mtxWorldModel);

		//���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		//�}�e���A���f�[�^�̎擾
		pMat = (D3DXMATERIAL*)g_Player.aModel[nCntModel].pBuffMatModel->GetBufferPointer();

		//�p�[�c����
		for (int nCntMat = 0; nCntMat < (int)g_Player.aModel[nCntModel].nNumMatmodel; nCntMat++)
		{
			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, NULL);
			//���f���p�[�c�̕`��
			g_Player.aModel[nCntModel].pMeshModel->DrawSubset(nCntMat);
		}

	}
	//�ۑ������}�e���A���߂�
	pDevice->SetMaterial(&matDef);
}

Player *GetModel(void)
{
	return &g_Player;
}
