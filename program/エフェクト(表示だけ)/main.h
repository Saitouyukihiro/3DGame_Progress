//===============================================================================================================
//
// ���C���w�b�_�[ [main.h]
// Author:sato syusuke
//
//===============================================================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include "d3dx9.h"						// �`�揈���ɕK�v
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <XInput.h>

#define DIRECTINPUT_VERSION (0x0800)
#include "dinput.h"						// ���͏����ɕK�v
#include "xaudio2.h"
#include "stdio.h"

//===============================================================================================================
// ���C�u�����̃����N
//===============================================================================================================
#pragma comment(lib, "d3d9.lib")	// �`�揈���ɕK�v
#pragma comment(lib, "d3dx9.lib")	// �g�����C�u����
#pragma comment(lib, "dxguid.lib")	// �R���|�[�l���g�g�p�ɕK�v
#pragma comment(lib, "dinput8.lib")	// ���͏����ɕK�v
#pragma comment(lib, "winmm.lib")

#pragma comment(lib, "xinput.lib") //�R���g���[���[�̂�ŕK�v���ď����Ă�

//===============================================================================================================
// �}�N����`
//===============================================================================================================
#define SCREEN_WIDTH	(1280)		// �X�N���[���̕�
#define SCREEN_HEIGTH	(720)		// �X�N���[���̍���
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//===============================================================================================================
// �\���̂̒�`
//===============================================================================================================
// ���_�t�H�[�}�b�g�ɍ��킹���\����
typedef struct
{
	D3DXVECTOR3 pos;	// ���_����
	float rhw;			// 1.0�ŌŒ�
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`���̍��W
} VERTEX_2D;

typedef struct
{
	D3DXVECTOR3 pos;	// ���_����
	D3DXVECTOR3 nor;
	D3DCOLOR col;
	D3DXVECTOR2 tex;	// �e�N�X�`���̍��W
}VERTEX_3D;


//===============================================================================================================
// �v���g�^�C�v�錾
//===============================================================================================================
LPDIRECT3DDEVICE9 GetDevice(void);

#endif