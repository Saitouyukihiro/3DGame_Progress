//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
//�G�̏���(Enemy.cpp)
//Author�F�����G��
//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[

//�C���N���[�h�t�@�C��
#include "main.h"
#include "input.h"
#include "Enemy.h"
#include "Shadow.h"
#include "camera.h"
#include "Effect.h"



//�O���[�o���ϐ�

D3DXVECTOR3 g_SaveEnemyRot;

Enemy g_Enemy[MAX_ENEMY];

int g_EnemyMaxParts = 0;

//����������
void InitEnemy(void)
{
	for (int nCntMaxEnemy = 0; nCntMaxEnemy < MAX_ENEMY; nCntMaxEnemy++)
	{
		g_Enemy[nCntMaxEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ʒu
		g_Enemy[nCntMaxEnemy].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//��]

		g_Enemy[nCntMaxEnemy].aEnemy[g_EnemyMaxParts];
		g_Enemy[nCntMaxEnemy].nNumEnemy;

		g_Enemy[nCntMaxEnemy].ntype = 0;
		g_Enemy[nCntMaxEnemy].bUse = false;
		g_Enemy[nCntMaxEnemy].nLife = 0;
	}
}

//�I������
void UninitEnemy(void)//�ǉ��̉\�������邽�ߍ��ڂ͍���Ƃ�
{
	for (int nCntMaxEnemy = 0; nCntMaxEnemy < MAX_ENEMY; nCntMaxEnemy++)
	{
		for (int nCntEnemy = 0; nCntEnemy < g_Enemy[nCntEnemy].nNumEnemy; nCntEnemy++)
		{
			//�e�N�X�`���̔j��
			if (g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].pMeshEnemy != NULL)
			{
				g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].pMeshEnemy->Release();
				g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].pMeshEnemy = NULL;
			}

			//���_�o�b�t�@���j��
			if (g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].pBuffMatEnemy != NULL)
			{
				g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].pBuffMatEnemy->Release();
				g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].pBuffMatEnemy = NULL;
			}
		}
	}
}

//�X�V����
void UpdateEnemy(void)//�ǉ��̉\�������邽�ߍ��ڂ͍���Ƃ�
{
	
}

//�`�揈��
void DrawEnemy(void)
{

	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�̃|�C���^
	pDevice = GetDevice();//�f�o�C�X���擾����
	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X

	D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ�
	D3DXMATERIAL *pMat;//�}�e���A���f�[�^�|�C���^
	for (int nCntMaxEnemy = 0; nCntMaxEnemy < MAX_ENEMY; nCntMaxEnemy++)
	{
		D3DXMatrixIdentity(&g_Enemy[nCntMaxEnemy].mtxWorldEnemy);//���[���h�}�g���b�N�X�̏�����

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Enemy[nCntMaxEnemy].rot.y, g_Enemy[nCntMaxEnemy].rot.x, g_Enemy[nCntMaxEnemy].rot.z);
		D3DXMatrixMultiply(&g_Enemy[nCntMaxEnemy].mtxWorldEnemy, &g_Enemy[nCntMaxEnemy].mtxWorldEnemy, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_Enemy[nCntMaxEnemy].pos.x, g_Enemy[nCntMaxEnemy].pos.y, g_Enemy[nCntMaxEnemy].pos.z);
		D3DXMatrixMultiply(&g_Enemy[nCntMaxEnemy].mtxWorldEnemy, &g_Enemy[nCntMaxEnemy].mtxWorldEnemy, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Enemy[nCntMaxEnemy].mtxWorldEnemy);

		//�p�[�c�P�P�ɐݒ������
		for (int nCntEnemy = 0; nCntEnemy < g_Enemy[nCntEnemy].nNumEnemy; nCntEnemy++)
		{
			D3DXMATRIX mtxRotEnemy, mtxTransEnemy;//�v�Z�p�}�g���b�N�X
			D3DXMATRIX mtxParent;//�e�̃}�g���b�N�X

			D3DXMatrixIdentity(&g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].mtxWorldEnemy);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRotEnemy, g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].rot.y, g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].rot.x, g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].rot.z);
			D3DXMatrixMultiply(&g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].mtxWorldEnemy, &g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].mtxWorldEnemy, &mtxRotEnemy);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTransEnemy, g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].pos.x, g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].pos.y, g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].pos.z);
			D3DXMatrixMultiply(&g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].mtxWorldEnemy, &g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].mtxWorldEnemy, &mtxTransEnemy);

			//�e�̃}�g���b�N�X�𔽉f
			if (g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].nIndxModelParent != -1)
			{
				mtxParent = g_Enemy[nCntMaxEnemy].aEnemy[g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].nIndxModelParent].mtxWorldEnemy;
			}
			else
			{
				mtxParent = g_Enemy[nCntMaxEnemy].mtxWorldEnemy;
			}
			//�Z�o�����e�p�[�c�̃}�g���b�N�X�Ɛe�̃}�g���b�N���|�����킹��
			D3DXMatrixMultiply(&g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].mtxWorldEnemy, &g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].mtxWorldEnemy, &mtxParent);

			//�}�g���b�N�X���Z�b�g
			pDevice->SetTransform(D3DTS_WORLD, &g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].mtxWorldEnemy);

			//���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			//�}�e���A���f�[�^�̎擾
			pMat = (D3DXMATERIAL*)g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].pBuffMatEnemy->GetBufferPointer();

			//�p�[�c����
			for (int nCntMat = 0; nCntMat < (int)g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].nNumMatEnemy; nCntMat++)
			{
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, NULL);
				//���f���p�[�c�̕`��
				g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].pMeshEnemy->DrawSubset(nCntMat);
			}

		}
	}
	//�ۑ������}�e���A���߂�
	pDevice->SetMaterial(&matDef);
}

void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife, int ntype)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�̃|�C���^
	pDevice = GetDevice();//�f�o�C�X���擾����

	int nNumVtx[MAX_ENEMY]; //���_��
	DWORD sizeFVF; //���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff; //���_�o�b�t�@�ւ̃|�C���^

	for (int nCntMaxEnemy = 0; nCntMaxEnemy < MAX_ENEMY; nCntMaxEnemy++)
	{
		if (g_Enemy[nCntMaxEnemy].bUse == false)
		{
			g_Enemy[nCntMaxEnemy].pos = pos;
			g_Enemy[nCntMaxEnemy].rot = rot;
			g_Enemy[nCntMaxEnemy].ntype = ntype;

			switch (g_Enemy[nCntMaxEnemy].ntype)//�G�̃^�C�v�ł��ꂼ���ǂݍ��܂���
		case(ENEMYTYPE_LMG):
			{

				g_Enemy[nCntMaxEnemy].aEnemy[MAX_PARTS];

				g_Enemy[nCntMaxEnemy].nNumEnemy = MAX_PARTS;//�p�[�c��������

				//x�t�@�C���̓ǂݍ���
				D3DXLoadMeshFromX("date/Enemy/LMG/100_sityu.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Enemy[nCntMaxEnemy].aEnemy[0].pBuffMatEnemy, NULL, &g_Enemy[nCntMaxEnemy].aEnemy[0].nNumMatEnemy, &g_Enemy[nCntMaxEnemy].aEnemy[0].pMeshEnemy);
				//x�t�@�C���̓ǂݍ���
				D3DXLoadMeshFromX("date/Enemy/LMG/101_gun.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Enemy[nCntMaxEnemy].aEnemy[1].pBuffMatEnemy, NULL, &g_Enemy[nCntMaxEnemy].aEnemy[1].nNumMatEnemy, &g_Enemy[nCntMaxEnemy].aEnemy[1].pMeshEnemy);
				//x�t�@�C���̓ǂݍ���
				D3DXLoadMeshFromX("date/Enemy/LMG/102_reg.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Enemy[nCntMaxEnemy].aEnemy[2].pBuffMatEnemy, NULL, &g_Enemy[nCntMaxEnemy].aEnemy[2].nNumMatEnemy, &g_Enemy[nCntMaxEnemy].aEnemy[2].pMeshEnemy);

				//�O�Ԗڂ̃p�[�c�̃I�t�Z�b�g��
				g_Enemy[nCntMaxEnemy].aEnemy[0].nIndxModelParent = -1;
				g_Enemy[nCntMaxEnemy].aEnemy[0].pos = D3DXVECTOR3(0.0, 10.0, 0.0);
				g_Enemy[nCntMaxEnemy].aEnemy[0].rot = D3DXVECTOR3(0.0, D3DX_PI * 1, 0.0);

				//1�Ԗڂ̃p�[�c�̃I�t�Z�b�g��
				g_Enemy[nCntMaxEnemy].aEnemy[1].nIndxModelParent = 0;
				g_Enemy[nCntMaxEnemy].aEnemy[1].pos = D3DXVECTOR3(0.0, 20.0, 0.0);
				g_Enemy[nCntMaxEnemy].aEnemy[1].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

				//2�Ԗڂ̃p�[�c�̃I�t�Z�b�g��
				g_Enemy[nCntMaxEnemy].aEnemy[2].nIndxModelParent = 0;
				g_Enemy[nCntMaxEnemy].aEnemy[2].pos = D3DXVECTOR3(0.0, 0.0, 0.0);
				g_Enemy[nCntMaxEnemy].aEnemy[2].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

				g_Enemy[nCntMaxEnemy].pos = D3DXVECTOR3(0.0, 0.0, 0.0);
				g_Enemy[nCntMaxEnemy].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

				

				for (int nCntEnemy = 0; nCntEnemy < g_Enemy[nCntMaxEnemy].nNumEnemy; nCntEnemy++)
				{

					//���_���̎擾
					nNumVtx[nCntEnemy] = g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].pMeshEnemy->GetNumVertices();
					//���_�t�H�[�}�b�g�̃T�C�Y���擾
					sizeFVF = D3DXGetFVFVertexSize(g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].pMeshEnemy->GetFVF());
					//���_�o�b�t�@���b�N
					g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].pMeshEnemy->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

					for (int nCntVtx = 0; nCntVtx < nNumVtx[nCntEnemy]; nCntVtx++)
					{
						D3DXVECTOR3 Vtx = *(D3DXVECTOR3*)pVtxBuff;//���_���W���

						//***************************************
						//X��
						//***************************************
						//��r�Ώۂ�Max���傫��������
						if (Vtx.x > g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].VtxMaxEnemy.x)
						{
							g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].VtxMaxEnemy.x = Vtx.x;
						}
						//��r�Ώۂ�Min��菬����������
						if (Vtx.x < g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].VtxMinEnemy.x)
						{
							g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].VtxMinEnemy.x = Vtx.x;
						}

						//***************************************
						//Y��
						//***************************************
						//��r�Ώۂ�Max���傫��������
						if (Vtx.y > g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].VtxMaxEnemy.y)
						{
							g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].VtxMaxEnemy.y = Vtx.y;
						}
						//��r�Ώۂ�Min��菬����������
						if (Vtx.y < g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].VtxMinEnemy.y)
						{
							g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].VtxMinEnemy.y = Vtx.y;
						}

						//***************************************
						//Z��
						//***************************************
						//��r�Ώۂ�Max���傫��������
						if (Vtx.z > g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].VtxMaxEnemy.z)
						{
							g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].VtxMaxEnemy.z = Vtx.z;
						}
						//��r�Ώۂ�Min��菬����������
						if (Vtx.z < g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].VtxMinEnemy.z)
						{
							g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].VtxMinEnemy.z = Vtx.z;
						}

						pVtxBuff += sizeFVF;//��r�Ώۂ̕ύX
					}
					//���_�o�b�t�@�A�����b�N
					g_Enemy[nCntMaxEnemy].aEnemy[nCntEnemy].pMeshEnemy->UnlockVertexBuffer();
				}
			}
			//�e�̃Z�b�g
			SetShadow(g_Enemy[nCntMaxEnemy].pos, 100.0f, 100.0f, TYPE_PLAYER);

			g_Enemy[nCntMaxEnemy].bUse = true;

			break;
		}
	}
}


Enemy *GetEnemy(void)
{
	return &g_Enemy[0];
}