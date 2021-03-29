//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "result.h"
#include "fade.h"
#include "rank.h"
#include "Picture.h"
#include "keyinput.h"
#include "mouseinput.h"
#include "sound.h"

//---------------------------
//�O���[�o���ϐ�
//---------------------------
bool g_bUse2 = false;

//---------------------------
//����������
//---------------------------
HRESULT InitResult(void)
{
	InitPicture();
	SetPicture(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT, PICTURE_RESULT);

	InitRank();
	PlaySound(SOUND_LABEL_BGM02);
	return S_OK;
}
//---------------------------
//�I������
//---------------------------
void UninitResult(void)
{
	StopSound();
	UninitPicture();

	UninitRank();
}
//---------------------------
//�X�V����
//---------------------------
void UpdateResult(void)
{
	static int nCnt;	//�����@�ۃ^�C�}�[
	int nNum = 0;		//rando�p�̕ϐ�

	nCnt++;				//�^�C�}�[���Z

	UpdatePicture();

	UpdateRank();

	//�^�C�}�[��1584�ɂȂ邩 || �G���^�[�L�[�����Ă���
	if (nCnt >= 1584 && GetFade() == FADE_NONE || GetKeyboardTrigger(DIK_RETURN) == true && GetFade() == FADE_NONE || MouseDowan(MOUSE_WHEEL_BOTTON) == true && GetFade() == FADE_NONE)
	{
		SetFade(MODE_TITLE);
		PlaySound(SOUND_LABEL_Enter000);
		nCnt = 0;		//�J�E���g������
	}
}
//---------------------------
//�`�揈��
//---------------------------
void DrawResult(void)
{
	DrawPicture();

	DrawRank();
}