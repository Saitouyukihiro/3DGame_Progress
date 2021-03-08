//-----------------------------------------------------------------------------
//���C���̏���
//-----------------------------------------------------------------------------
#ifndef _MAIN_H_
#define _MAIN_H_
#define DIRECTINPUT_VERSION (0x0800)  //�r���h���̌x���Ώ��p�}�N��

//-----------------------------------------------------------------------------
//�C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include <windows.h>
#include "d3dx9.h"
#include "dinput.h"  //���͏����ɕK�v
#include "xaudio2.h"
#include "xinput.h"
//-----------------------------------------------------------------------------
//���C�u�����̃����N
//-----------------------------------------------------------------------------
#pragma comment (lib,"d3d9.lib")		//�`��ɕK�v
#pragma comment (lib,"d3dx9.lib")		//[d3d9.lib]�̊g�����C�u����
#pragma comment (lib,"dxguid.lib")		//DirectX�R���|�[�l���g(���i)�g�p�ɕK�v
#pragma comment (lib,"dinput8.lib")		//���͏����ɕK�v
#pragma comment (lib,"winmm.lib")  
#pragma comment (lib,"xinput.lib")		//XINPUT�̂��
//-----------------------------------------------------------------------------
//�}�N����`
//-----------------------------------------------------------------------------
#define SCREEN_WIDTH  (1280)           //�E�C���h�E�̕�
#define SCREEN_HEIGHT (720)            //�E�C���h�E�̍���
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)
//-----------------------------------------------------------------------------
//�\���̒�`
//-----------------------------------------------------------------------------
typedef struct
{
	//2D
	D3DVECTOR pos;   //�ʒu
	float  rhw;      //rhw
	D3DCOLOR col;    //�F
	D3DXVECTOR2 tex; //�e�N�X�`��

} VERTEX_2D;

typedef struct
{
	//3D
	D3DXVECTOR3 pos;	//���_���W
	D3DXVECTOR3 nor;	//�@���x�N�g��
	D3DCOLOR	col;	//���_�J���[
	D3DXVECTOR2 tex;	//�e�N�X�`�����W
} VERTEX_3D;

//���(���[�h)�̎��
typedef enum
{
	MODE_TITLE = 0,
	MODE_MAX,
}MODE;

//-----------------------------------------------------------------------------
//�v���g�^�C�v�錾
//-----------------------------------------------------------------------------
LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode);
MODE *GetMode(void);
#endif _MAIN_H_