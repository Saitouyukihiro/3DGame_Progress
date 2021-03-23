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

	InitRank();

	return S_OK;
}
//---------------------------
//�I������
//---------------------------
void UninitResult(void)
{
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
		nCnt = 0;		//�J�E���g���傫��
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