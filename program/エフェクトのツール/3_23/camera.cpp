//**************************************************************
//�J�����̏���(camera.cpp)
//Author�F�����G��
//**************************************************************

#include "camera.h"
#include "input.h"

#define CAMERA_Z (400.0f)
#define MOVE (5.0)
#define DISTANCE_CAMERA (0.6)//�J�����Ƃ̋���
#define CAMERA_ROT (0.04f) //�ʏ펞�̃J������]��

D3DXVECTOR3 g_cameraOldposR;
D3DXVECTOR3 g_cameraOldposV;

D3DXVECTOR3 g_OldModelRot;

Camera g_camera;//�J�����̏��

void InitCamera(void)
{

	g_camera.posV = D3DXVECTOR3(0.0f, 500.0f, -CAMERA_Z);

	g_camera.move = D3DXVECTOR3(3.0f, 3.0f, 3.0f);
	g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	g_cameraOldposR = g_camera.posR;
	g_cameraOldposV = g_camera.posV;

}

void UninitCamera(void)
{

}
void UpdateCamera(void)
{

	XINPUT_STATE state;
	ZeroMemory(&state, sizeof(XINPUT_STATE));
	DWORD dwResult = XInputGetState(0, &state);

		////**************************************************************
		////�J�����̈ړ�
		////**************************************************************

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

#if 1

		//**************************************************************
		//�J�����̎��_�ړ�
		//**************************************************************

		if (GetKeyboardPress(DIK_F) == true || state.Gamepad.sThumbRY >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
		{
			g_camera.posR.y += 4.0f;
			g_camera.posV.y -= 4.0f;
		}

		else if (GetKeyboardPress(DIK_R) == true || state.Gamepad.sThumbRY <= -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
		{
			g_camera.posR.y -= 4.0f;
			g_camera.posV.y += 4.0f;
		}
#endif

		//**************************************************************
		//�J�����̒����_�ړ�
		//**************************************************************

#if 1
		if (GetKeyboardPress(DIK_Q) == true)
		{
			g_camera.rot.y -= 0.02;

			g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y)*CAMERA_Z;
			g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y)*CAMERA_Z;
		}

		else if (GetKeyboardPress(DIK_E) == true)
		{
			g_camera.rot.y += 0.02;

			g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * CAMERA_Z;
			g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * CAMERA_Z;

		}

		if (GetKeyboardPress(DIK_T) == true)
		{
			g_camera.posR.y += 4.0f;
		}

		else if (GetKeyboardPress(DIK_G) == true)
		{
			g_camera.posR.y -= 4.0f;
		}
#endif
			g_cameraOldposR = g_camera.posR;
			g_cameraOldposV = g_camera.posV;

			
	

	//3.14 �` -3.14�ɕς��鏈��
	if (g_camera.rot.y > D3DX_PI)
	{
		g_camera.rot.y -= D3DX_PI * 2;
	}

	else if (g_camera.rot.y < -D3DX_PI)
	{
		g_camera.rot.y += D3DX_PI * 2;
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