#include "input.h"

#define NUM_KEY_MAX (256)//�L�[�̍ő吔


LPDIRECTINPUT8 g_pInput = NULL;//DirectInput�I�u�W�F�N�g�̃|�C���^
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;//���̓f�o�C�X�ւ̃|�C���^

//�O���[�o���ϐ�
BYTE g_aKeyState[NUM_KEY_MAX];//�L�[�{�[�h�̓��͏��i�v���X���j
BYTE g_aKeyStateTrigger[NUM_KEY_MAX];
BYTE g_GetKeyboardRelese[NUM_KEY_MAX];

//����������
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}

	//���̓f�o�C�X�̐���
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	g_pDevKeyboard->Acquire();
	return S_OK;
}

//�I������
void UninitKeyboard(void)
{
	//���̓f�o�C�X�̊J��
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire();
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}
	//DirectInput�I�u�W�F�N�g�̊J��
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}

void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];
	int nCntkey;
	//���̓f�o�C�X����f�[�^�擾

	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntkey = 0; nCntkey < NUM_KEY_MAX; nCntkey++)
		{
			
			g_aKeyStateTrigger[nCntkey] = (g_aKeyState[nCntkey] ^ aKeyState[nCntkey])& aKeyState[nCntkey];
			g_GetKeyboardRelese[nCntkey] = (g_aKeyState[nCntkey] ^ aKeyState[nCntkey])& g_aKeyState[nCntkey];

			g_aKeyState[nCntkey] = aKeyState[nCntkey];
			
		}
	}
	else
	{
		g_pDevKeyboard->Acquire();
	}
}

bool GetKeyboardTrigger(int nKey)
{
	return(g_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

bool GetKeyboardRelese(int nKey)
{
	return(g_GetKeyboardRelese[nKey] & 0x80) ? true : false;
}

bool GetKeyboardPress(int nKey)
{
	return(g_aKeyState[nKey] & 0x80) ? true : false;
}


