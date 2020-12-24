//**************************************************************
//�J�����̏���(camera.cpp)
//Author�F�����G��
//**************************************************************

#include "camera.h"
#include "input.h"
#include "Model.h"

#define CAMERA_Z (500.0f)
#define MOVE (5.0)
#define DISTANCE_CAMERA (0.6)//�J�����Ƃ̋���
#define AIM_DISTANCE_CAMERA (0.2)//�`�c�r���̃J��������
#define AIM_CAMERA_ROT (0.008f)//ADS���̃J�����̉�]��
#define CAMERA_ROT (0.02f) //�ʏ펞�̃J������]��

D3DXVECTOR3 g_cameraOldposR;
D3DXVECTOR3 g_cameraOldposV;

D3DXVECTOR3 g_OldModelRot;

Camera g_camera;//�J�����̏��

void InitCamera(void)
{
	Player *pPlayer;
	pPlayer = GetModel();

	g_camera.posV = D3DXVECTOR3(0.0f, 500.0f, -CAMERA_Z);

	g_camera.move = D3DXVECTOR3(3.0f, 3.0f, 3.0f);
	g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	g_cameraOldposR = g_camera.posR;
	g_cameraOldposV = g_camera.posV;

	g_camera.posR.y = pPlayer->pos.y + 50;
	g_camera.posV.y = pPlayer->pos.y + 100;


	g_camera.SaveCamera = false;
	g_camera.ShotBullet = false;
}

void UninitCamera(void)
{

}
void UpdateCamera(void)
{
	Player *pPlayer;
	pPlayer = GetModel();

	if (g_camera.SaveCamera == false)
	{
		////**************************************************************
		////�J�����̈ړ�
		////**************************************************************
#if 0
		if (GetKeyboardPress(DIK_A) == true)
		{
			g_camera.posR.x = g_camera.posR.x - cosf(g_camera.rot.y) * MOVE;
			g_camera.posR.z = g_camera.posR.z + sinf(g_camera.rot.y) * MOVE;

			g_camera.posV.x = g_camera.posV.x - cosf(g_camera.rot.y) * MOVE;
			g_camera.posV.z = g_camera.posV.z + sinf(g_camera.rot.y) * MOVE;
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{
			g_camera.posR.x = g_camera.posR.x + cosf(g_camera.rot.y) * MOVE;
			g_camera.posR.z = g_camera.posR.z - sinf(g_camera.rot.y) * MOVE;

			g_camera.posV.x = g_camera.posV.x + cosf(g_camera.rot.y) * MOVE;
			g_camera.posV.z = g_camera.posV.z - sinf(g_camera.rot.y) * MOVE;
		}

		if (GetKeyboardPress(DIK_W) == true)
		{
			g_camera.posR.x = g_camera.posR.x + sinf(g_camera.rot.y) * MOVE;
			g_camera.posR.z = g_camera.posR.z + cosf(g_camera.rot.y) * MOVE;

			g_camera.posV.x = g_camera.posV.x + sinf(g_camera.rot.y) * MOVE;
			g_camera.posV.z = g_camera.posV.z + cosf(g_camera.rot.y) * MOVE;
		}

		else if (GetKeyboardPress(DIK_S) == true)
		{
			g_camera.posR.x = g_camera.posR.x - sinf(g_camera.rot.y) * MOVE;
			g_camera.posR.z = g_camera.posR.z - cosf(g_camera.rot.y) * MOVE;

			g_camera.posV.x = g_camera.posV.x - sinf(g_camera.rot.y) * MOVE;
			g_camera.posV.z = g_camera.posV.z - cosf(g_camera.rot.y) * MOVE;
		}

#endif
		g_camera.posR.x = pPlayer->pos.x;
		g_camera.posR.z = pPlayer->pos.z;

		g_camera.posV.x = pPlayer->pos.x - sinf(g_camera.rot.y) * CAMERA_Z * DISTANCE_CAMERA;
		g_camera.posV.z = pPlayer->pos.z - cosf(g_camera.rot.y) * CAMERA_Z * DISTANCE_CAMERA;

		//**************************************************************
		//�J�����̎��_�ړ�
		//**************************************************************
		if (GetKeyboardPress(DIK_D) == true)
		{
			g_camera.rot.y += CAMERA_ROT;
			pPlayer->aModel[1].rot.y += CAMERA_ROT;

			g_camera.posV.x = pPlayer->pos.x - sinf(g_camera.rot.y) * CAMERA_Z * DISTANCE_CAMERA;
			g_camera.posV.z = pPlayer->pos.z - cosf(g_camera.rot.y) * CAMERA_Z * DISTANCE_CAMERA;
		}

		else if (GetKeyboardPress(DIK_A) == true)
		{
			g_camera.rot.y -= CAMERA_ROT;
			pPlayer->aModel[1].rot.y -= CAMERA_ROT;

			g_camera.posV.x = pPlayer->pos.x - sinf(g_camera.rot.y) * CAMERA_Z * DISTANCE_CAMERA;
			g_camera.posV.z = pPlayer->pos.z - cosf(g_camera.rot.y) * CAMERA_Z * DISTANCE_CAMERA;
		}

		if (GetKeyboardPress(DIK_W) == true)
		{
			g_camera.posR.y += 4.0f;
		}

		else if (GetKeyboardPress(DIK_S) == true)
		{
			g_camera.posR.y -= 4.0f;

		}

		//**************************************************************
		//�J�����̒����_�ړ�
		//**************************************************************

#if 0
		if (GetKeyboardPress(DIK_Q) == true)
		{
			g_camera.rot.y -= 0.02;

			g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y)*CAMERA_Z * 0.8;
			g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y)*CAMERA_Z * 0.8;
		}

		else if (GetKeyboardPress(DIK_E) == true)
		{
			g_camera.rot.y += 0.02;

			g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * CAMERA_Z * 0.8;
			g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * CAMERA_Z * 0.8;

		}

		if (GetKeyboardPress(DIK_T) == true)
		{
			g_camera.posR.y += 4.0f;
		}

		else if (GetKeyboardPress(DIK_B) == true)
		{
			g_camera.posR.y -= 4.0f;
		}
#endif
			g_cameraOldposR = g_camera.posR;
			g_cameraOldposV = g_camera.posV;

			//g_OldModelRot.x = pPlayer->aModel[1].rot.x;
	}

	//3.14 �` -3.14�ɕς��鏈��
	if (g_camera.rot.y > D3DX_PI)
	{
		g_camera.rot.y -= D3DX_PI * 2;
	}

	else if (g_camera.rot.y < -D3DX_PI)
	{
		g_camera.rot.y += D3DX_PI * 2;
	}

	//�G���^�[�������Ƃ��̏���
	if (GetKeyboardPress(DIK_RETURN) == true)
	{
		g_camera.posV.x = pPlayer->pos.x - sinf(pPlayer->aModel[1].rot.y);
		g_camera.posV.z = pPlayer->pos.z - cosf(pPlayer->aModel[1].rot.y);
		g_camera.posV.y = pPlayer->pos.y - tanf(pPlayer->aModel[1].rot.x) + 50;

		g_camera.posR.x = g_camera.posV.x + sinf(pPlayer->aModel[1].rot.y) * CAMERA_Z * AIM_DISTANCE_CAMERA;
		g_camera.posR.z = g_camera.posV.z + cosf(pPlayer->aModel[1].rot.y) * CAMERA_Z * AIM_DISTANCE_CAMERA;
		g_camera.posR.y = g_camera.posV.y + tanf(pPlayer->aModel[1].rot.x) * CAMERA_Z * AIM_DISTANCE_CAMERA;


		if (GetKeyboardPress(DIK_A) == true)
		{
			g_camera.rot.y -= AIM_CAMERA_ROT;
			pPlayer->aModel[1].rot.y -= AIM_CAMERA_ROT;

			g_camera.posR.x = g_camera.posV.x + sinf(pPlayer->aModel[1].rot.y)*CAMERA_Z * AIM_DISTANCE_CAMERA;
			g_camera.posR.z = g_camera.posV.z + cosf(pPlayer->aModel[1].rot.y)*CAMERA_Z * AIM_DISTANCE_CAMERA;
		}

		else if (GetKeyboardPress(DIK_D) == true)
		{
			g_camera.rot.y += AIM_CAMERA_ROT;
			pPlayer->aModel[1].rot.y += AIM_CAMERA_ROT;

			g_camera.posR.x = g_camera.posV.x + sinf(pPlayer->aModel[1].rot.y) * CAMERA_Z * AIM_DISTANCE_CAMERA;
			g_camera.posR.z = g_camera.posV.z + cosf(pPlayer->aModel[1].rot.y) * CAMERA_Z * AIM_DISTANCE_CAMERA;
		}
		if (GetKeyboardPress(DIK_W) == true)
		{
			g_camera.posR.y += AIM_CAMERA_ROT * 20;
			pPlayer->aModel[1].rot.x += AIM_CAMERA_ROT;
		}

		else if (GetKeyboardPress(DIK_S) == true)
		{
			g_camera.posR.y -= AIM_CAMERA_ROT * 20;
			pPlayer->aModel[1].rot.x -= AIM_CAMERA_ROT;
		}
		g_camera.SaveCamera = true;

	}

	//�G���^�[�����[�X���̏���
	if (GetKeyboardRelese(DIK_RETURN) == true)
	{
		g_camera.posR.x = g_cameraOldposR.x - cosf(g_camera.rot.y);
		g_camera.posR.z = g_cameraOldposR.z + sinf(g_camera.rot.y);
		g_camera.posR.y = g_cameraOldposR.y;


		g_camera.posV.x = g_cameraOldposV.x - cosf(g_camera.rot.y);
		g_camera.posV.z = g_cameraOldposV.z + sinf(g_camera.rot.y);
		g_camera.posV.y = g_cameraOldposV.y;
		g_camera.SaveCamera = false;

		//pPlayer->aModel[1].rot.x = g_OldModelRot.x;
	}
}
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�̃|�C���^
	pDevice = GetDevice();//�f�o�C�X���擾����

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection,
								D3DXToRadian(45.0f),//��p
								(float) SCREEN_WIDTH / (float) SCREEN_HEIGTH,
								10.0f,//�ŏ��`�拗��
								3000.0f);//�ő�`�拗��

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&g_camera.mtxView, &g_camera.posV, &g_camera.posR, &g_camera.vecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);
}

Camera * GetCamera(void)
{
	return &g_camera;
}