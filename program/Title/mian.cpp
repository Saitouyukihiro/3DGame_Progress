//=============================================================================
//���C���̏���
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS

#include "main.h"
#include <stdio.h>
#include "Picture.h"
#include "Sound.h"
#include"Title.h"
#include "Fade.h"

//-----------------------------------------------------------------------------
//�}�N����`
//-----------------------------------------------------------------------------
#define CLASS_NAME "WindowClass"
#define WINDOW_NAME "�`�����X�`"

//-----------------------------------------------------------------------------
//�v���g�^�C�v�錾
//-----------------------------------------------------------------------------
LRESULT CALLBACK WindowProc(HWND hwnd, UINT  uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
void DrawTxT(void);
//-----------------------------------------------------------------------------
//�O���[�o���ϐ�
//-----------------------------------------------------------------------------
LPDIRECT3D9 g_pD3D = NULL;
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;
MODE g_mode = MODE_TITLE;                //���݂̃��[�h
int g_nCountFPS;
LPD3DXFONT g_pFont = NULL;
//-----------------------------------------------------------------------------
//���C���֐�
//-----------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lPCmdLine, int nCmdShow)
{
	//�\����
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),					//WNDCLASSEN�̃������T�C�Y�̎w��
		CS_CLASSDC,							//�\������E�B���h�E�̃X�^�C����ݒ�
		WindowProc,							//�E�B���h�E�v���V�[�W���̃A�h���X(�֐���)���w��
		0,									//0���w��
		0,									//0���w��
		hInstance,							//Windows�̈����̃C���X�^���X�n���h�����w��
		LoadIcon(NULL,IDI_APPLICATION),		//�^�X�N�o�[�Ɏg���A�C�R�����w��
		LoadCursor(NULL,IDC_ARROW),			//�g���}�E�X�J�[�\�����w��
		(HBRUSH)(COLOR_WINDOW + 1),			//�E�B���h�E�̃N���C�A���g�̈�̔w�i�F���w��
		NULL,								//Window�ɂ��郁�j���[��ݒ�
		CLASS_NAME,							//�E�B���h�E�N���X�̖��O
		LoadIcon(NULL,IDI_APPLICATION)		//�t�@�C���A�C�R���Ɏg���A�C�R����ݒ�
	};

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	HWND hWnd;	//�E�B���h�E�n���h��
	MSG msg;	//���b�Z�[�W���i�[����ϐ�

				//�E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	//�E�B���h�E�𐶐�(������E�B���h�E�n���h���ɔ[�߂ĊǗ�����)
	hWnd = CreateWindowEx(0,				//�g���E�B���h�E�X�^�C��
		CLASS_NAME,							//�E�B���h�E�N���X�̖��O
		WINDOW_NAME,						//�E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW,				//�E�B���h�E�X�^�C��
		CW_USEDEFAULT,						//�E�B���h�E�̍���X���W
		CW_USEDEFAULT,						//�E�B���h�E�̍���Y���W
		(rect.right - rect.left),			//�E�B���h�E�̕�
		(rect.bottom - rect.top),			//�E�B���h�E�̍���
		NULL,								//�e�E�B���h�E�̃n���h��
		NULL,								//���j���[�E�B���h�E�܂��͎q�E�B���h�E
		hInstance,							//�C���X�^���X�n���h��
		NULL								//�E�B���h�E�쐬�f�[�^
	);



	//����������(�E�B���h�E�������Ă�����(DirectX�̐���)
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}

	//�E�B���h�E�̕\��(�����������̌�ɍs��)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	DWORD dwExecLastTime;		//�������s�ŏI����
	DWORD dwFPSLastTime;		//FPS�v���ŏI����
	DWORD dwCurrentTime;		//���ݎ���
	DWORD dwFrameCount;			//�t���[���J�E���g

								// �t���[���J�E���g������
	dwExecLastTime =
		dwFPSLastTime =
		dwCurrentTime = timeGetTime();
	dwFrameCount = 0;

	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)		//���b�Z�[�W���擾�����Ȃ�i��
		{
			if (msg.message == WM_QUIT)		//"WM_QUIT"���b�Z�[�W������ꂽ�烋�[�v�𔲂���
			{
				break;
			}
			else
			{
				//���b�Z�[�W�|��Ƒ��o
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			//DirectX�̏���
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{
				// 0.5�b���ƂɎ��s
				g_nCountFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}

			if ((dwCurrentTime - dwExecLastTime) > (1000 / 60))
			{
				// 1/60�b�o��
				dwExecLastTime = dwCurrentTime;

				// �X�V����
				Update();

				// �`�揈��
				Draw();

				dwFrameCount++;
			}
		}
	}
	//�I������
	Uninit();

	//�E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return(int)msg.wParam;
}

//�E�B���h�E�v���V�[�W��
LRESULT CALLBACK WindowProc(HWND hWnd, UINT  uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:					//�E�B���h�E�j���̃��b�Z�[�W
		PostQuitMessage(0);				//WM_QUIT���b�Z�[�W��Ԃ�
		break;

	case WM_KEYDOWN:					//�����L�[���������ꂽ
		switch (wParam)
		{
		case VK_ESCAPE:					//[ESC]�L�[���������ꂽ
			DestroyWindow(hWnd);		//�E�B���h�E�j��(WM_DESTROY���b�Z�[�W�𑗂�)
		}
		break;

	case WM_CLOSE:						//�E��̃o�c
		DestroyWindow(hWnd);			//�E�B���h�E�j��(WM_DESTROY���b�Z�[�W�𑗂�)
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//-----------------------------------------------------------------------------
//����������
//-----------------------------------------------------------------------------
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;


	//DirectX�I�u�W�F�N�g�̐���
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//�f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));								//���[�N���[���N���A
	d3dpp.BackBufferCount = 1;										//�o�b�N�o�b�t�@�̐�
	d3dpp.BackBufferWidth = SCREEN_WIDTH;							//�Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;							//�Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;							//�J���[���[�h�̎w��
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;						//�f���M���ɓ������ăt���b�v����
	d3dpp.Windowed = bWindow;											//�E�B���h�E���[�h	false	bWindow
	d3dpp.EnableAutoDepthStencil = TRUE;							//�f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;						//�f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		//���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		//�C���^�[�o��

																	//�f�o�C�X�̐���
																	//�f�B�X�v���C�A�_�v�^��\�����߂̃f�o�C�X���쐬
																	//�`��ƒ��_�������n�[�h�E�F�A�ōs�Ȃ�
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &g_pD3DDevice)))
	{
		//��L�̐ݒ肪���s������
		//�`����n�[�h�E�F�A�ōs���A���_������CPU�ōs�Ȃ�
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &g_pD3DDevice)))
		{
			//��L�̐ݒ肪���s������
			//�`��ƒ��_������CPU�ōs�Ȃ�
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp, &g_pD3DDevice)))
			{
				//���������s
				return E_FAIL;
			}
		}
	}

	//�����_�[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				//�J�����O���s��Ȃ�
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						//Z�o�b�t�@���g�p
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				//���u�����h���s��
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		//���\�[�X�J���[�̎w��
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	//���f�X�e�B�l�[�V�����J���[�̎w��

																			//�T���v���[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	//�e�N�X�`���A�h���b�V���O���@(U�l)��ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	//�e�N�X�`���A�h���b�V���O���@(V�l)��ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	//�e�N�X�`���k���t�B���^���[�h��ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	//�e�N�X�`���g��t�B���^���[�h��ݒ�

																			//�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	D3DXCreateFont(g_pD3DDevice, 30, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Teminal", &g_pFont);

	SetMode(g_mode);
	InitFade(g_mode);
	InitSound(hWnd);
	return S_OK;
}

//-----------------------------------------------------------------------------
//�I������
//-----------------------------------------------------------------------------
void Uninit(void)
{
	UninitTitle();
	UninitFade();
	UninitSound();

	//Direct3D�f�o�C�X�̊J��
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	//Direct3D�I�u�W�F�N�g�̊J��
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//-----------------------------------------------------------------------------
//�X�V����
//-----------------------------------------------------------------------------
void Update(void)
{
#if(1)
	//�e��I�u�W�F�N�g�X�V����
	switch (g_mode)
	{
	case MODE_TITLE:
		UpdateTitle();
		break;
	}
	UpdateFade();

#endif
}

//-----------------------------------------------------------------------------
//�`�揈��
//-----------------------------------------------------------------------------
void Draw(void)
{

	//back�o�b�t�@�AZ�o�b�t�@�̃N���A
	g_pD3DDevice->Clear(0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);


#if(1)//�J�����̐����A�J��Ԃ�
	//�`��J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		DrawTxT();
		switch (g_mode)
		{
		case MODE_TITLE:
			DrawTitle();
			break;
		}

		D3DVIEWPORT9 viewportDef;
		//���݂̃r���[�|�[�g���擾
		g_pD3DDevice->GetViewport(&viewportDef);
		DrawFade();
		//�J�����̐ݒ�
		//SetCamera();


		//�r���[�|�[�g�����ɖ߂�
		g_pD3DDevice->SetViewport(&viewportDef);


		//�`��I��
		g_pD3DDevice->EndScene();
	}
#endif
	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//-----------------------------------------------------------------------------
//���[�h�̐ݒ�
//-----------------------------------------------------------------------------
void SetMode(MODE mode)
{
#if(1)
	switch (g_mode)
	{
	case MODE_TITLE:
		UninitTitle();
		break;
	}

	switch (mode)
	{
	case MODE_TITLE:
		InitTitle();
		break;
	}
	g_mode = mode;
#endif
}

//-----------------------------------------------------------------------------
//�`�ʏ���
//-----------------------------------------------------------------------------
MODE *GetMode(void)
{
	return &g_mode;
}

//-----------------------------------------------------------------------------
//���W�ݒ�
//-----------------------------------------------------------------------------
void DrawTxT(void)
{
#if(0)
	Camera *pcamera;
	pcamera = GetCamera();

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

	char aStr[512];
	int nNUm = sprintf(&aStr[0], "FPS:%d\n", g_nCountFPS);
	nNUm += sprintf(&aStr[nNUm], "�J�����̈ʒu:  %0.1f,  %0.1f,  %0.1f\n", pcamera->posV.x, pcamera->posV.y, pcamera->posV.z);
	nNUm += sprintf(&aStr[nNUm], "�����_�̈ʒu:  %0.1f,  %0.1f,  %0.1f", pcamera->posR.x, pcamera->posR.y, pcamera->posR.z);

	//�e�L�X�g
	g_pFont->DrawTextA(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
#endif
}

//-----------------------------------------------------------------------------
//�`�ʏ���
//-----------------------------------------------------------------------------
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}