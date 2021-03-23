//**************************************************************
//���C�g�̏���(ligth.cpp)
//Author�F�����G��
//**************************************************************


#include "ligth.h"

D3DLIGHT9 g_ligth[3];//���C�g�̏��

void InitLigth(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^
	D3DXVECTOR3 vecDir;			//�ݒ�p�����x�N�g��
	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	//**************************************************************
	//���C�g�̐ݒ�
	//**************************************************************
	for (int nCntligth = 0; nCntligth < 3; nCntligth++)
	{
		//���C�g�̃N���A
		ZeroMemory(&g_ligth[nCntligth], sizeof(D3DLIGHT9));

		//���C�g�̎�ނ�ݒ�
		g_ligth[nCntligth].Type = D3DLIGHT_DIRECTIONAL;//��������

		//���C�g�̊g�U����ݒ�
		g_ligth[nCntligth].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//���C�g�O�̕�����ݒ�
		vecDir = D3DXVECTOR3(0.2f, -0.8f, -0.4f);
		D3DXVec3Normalize(&vecDir, &vecDir);//������
		g_ligth[0].Direction = vecDir;

		//���C�g�P�̕�����ݒ�
		vecDir = D3DXVECTOR3(-0.2f, 0.8f, 0.4f);
		D3DXVec3Normalize(&vecDir, &vecDir);//������
		g_ligth[1].Direction = vecDir;

		//���C�g�Q�̕�����ݒ�
		vecDir = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		D3DXVec3Normalize(&vecDir, &vecDir);//������
		g_ligth[2].Direction = vecDir;

		//�e���C�g�̐ݒ肷��
		pDevice->SetLight(nCntligth, &g_ligth[nCntligth]);
		//�e���C�g��L��
		pDevice->LightEnable(nCntligth, TRUE);
	}
}

void UninitLigth(void)
{

}

void UpdateLigth(void)
{

}
