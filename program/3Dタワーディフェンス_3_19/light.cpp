//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "light.h"
#include "keyinput.h"
#include "camara.h"

//---------------------------
//�O���[�o���ϐ�
//---------------------------
D3DLIGHT9		g_Ligt[MAX_LIGHT];	//���C�g

//---------------------------
//����������
//---------------------------
HRESULT InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�̃|�C���^
	D3DXVECTOR3 VecDir[MAX_LIGHT];	//�x�N�g��

	pDevice = GetDevice(); //�f�o�C�X���擾����

	//---------------------------
	//���C�g�̐ݒ�
	//---------------------------

	for (int nCntLihgt = 0; nCntLihgt < MAX_LIGHT; nCntLihgt++)
	{
		//���C�g�̃N���A
		ZeroMemory(	&g_Ligt[nCntLihgt],
					sizeof(D3DLIGHT9));

		if (nCntLihgt == 0)
		{
			//���C�g�̎��
			g_Ligt[nCntLihgt].Type = D3DLIGHT_DIRECTIONAL;	//���

			//���C�g�̊g�U��
			g_Ligt[nCntLihgt].Diffuse = (D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	//�F

			//���C�g�̏ꏊ
			g_Ligt[nCntLihgt].Position = (D3DXVECTOR3(-1000.0f, 1000.0f, 1000.0f));

			//���C�g�̕���
			VecDir[nCntLihgt] = (D3DXVECTOR3(0.2f, -0.8f, 0.6f));

			//���K������
			D3DXVec3Normalize(	&VecDir[nCntLihgt],
								&VecDir[nCntLihgt]);

			//���C�g�̕���������
			g_Ligt[nCntLihgt].Direction = VecDir[nCntLihgt];

			//���C�g�̐ݒ�
			pDevice->SetLight(nCntLihgt, &g_Ligt[nCntLihgt]);	//0�Ԗڂ̃��C�g�ɐݒ肵���ݒ������

			//���C�g��L���ɂ���
			pDevice->LightEnable(nCntLihgt, TRUE);	//0�Ԗڂ̃��C�g��t����
		}
		else if (nCntLihgt == 1)
		{
			//���C�g�̎��
			g_Ligt[nCntLihgt].Type = D3DLIGHT_DIRECTIONAL;	//���

			//���C�g�̊g�U��
			g_Ligt[nCntLihgt].Diffuse = (D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	//�F

			//���C�g�̏ꏊ
			g_Ligt[nCntLihgt].Position = (D3DXVECTOR3(0.0f, 1000.0f, 0.0f));

			//���C�g�̕���
			VecDir[nCntLihgt] = (D3DXVECTOR3(0.0f, -1.0f, 0.0f));

			//���K������
			D3DXVec3Normalize(	&VecDir[nCntLihgt],
								&VecDir[nCntLihgt]);

			//���C�g�̕���������
			g_Ligt[nCntLihgt].Direction = VecDir[nCntLihgt];

			//���C�g�̐ݒ�
			pDevice->SetLight(nCntLihgt, &g_Ligt[nCntLihgt]);	//1�Ԗڂ̃��C�g�ɐݒ肵���ݒ������

			//���C�g��L���ɂ���
			pDevice->LightEnable(nCntLihgt, TRUE);	//1�Ԗڂ̃��C�g��t����
		}
		else if (nCntLihgt == 2)
		{
			//���C�g�̎��
			g_Ligt[nCntLihgt].Type = D3DLIGHT_DIRECTIONAL;	//���

			//���C�g�̊g�U��
			g_Ligt[nCntLihgt].Diffuse = (D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	//�F

			//���C�g�̏ꏊ
			g_Ligt[nCntLihgt].Position = (D3DXVECTOR3(3000.0f, -1000.0f, -3000.0f));

			//���C�g�̕���
			VecDir[nCntLihgt] = (D3DXVECTOR3(-0.2f, 0.8f, -0.6f));

			//���K������
			D3DXVec3Normalize(	&VecDir[nCntLihgt],
								&VecDir[nCntLihgt]);

			//���C�g�̕���������
			g_Ligt[nCntLihgt].Direction = VecDir[nCntLihgt];

			//���C�g�̐ݒ�
			pDevice->SetLight(nCntLihgt, &g_Ligt[nCntLihgt]);	//2�Ԗڂ̃��C�g�ɐݒ肵���ݒ������

			//���C�g��L���ɂ���
			pDevice->LightEnable(nCntLihgt, TRUE);	//2�Ԗڂ̃��C�g��t����
		}
	}
	return S_OK;
}

//---------------------------
//�I������
//---------------------------
void UninitLight(void)
{

}

//---------------------------
//�X�V����
//---------------------------
void UpdateLight(void)
{

}
