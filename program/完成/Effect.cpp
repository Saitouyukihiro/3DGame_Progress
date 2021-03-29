//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
//�G�t�F�N�g�̏���(Effect.cpp)
//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
#define _CRT_SECURE_NO_WARNINGS
#include "main.h"
#include "Effect.h"

#include <stdio.h>

#define MOVE_Y (3.0f)


//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureEffect[64] = {};//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;//���_�o�b�t�@�ւ̃|�C���^

Effect g_Effect[MAX_EFFECT];

Effectstate g_Effectstate;

D3DXVECTOR3 rot;
D3DXVECTOR3 rot2;

int g_EffectTexture;
int g_EffectMaxTexture;


//����������
void InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�̃|�C���^
	int nCntEffect;
	pDevice = GetDevice();//�f�o�C�X�̎擾

	g_EffectTexture = 0;
	g_EffectMaxTexture = 0;

	//�G�t�F�N�g�̏�����
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		g_Effect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		g_Effect[nCntEffect].colorR = 0;
		g_Effect[nCntEffect].colorG = 0;
		g_Effect[nCntEffect].colorB = 0;
		g_Effect[nCntEffect].colorA = 0;

		g_Effect[nCntEffect].MinColorR = 0;
		g_Effect[nCntEffect].MinColorG = 0;
		g_Effect[nCntEffect].MinColorB = 0;
		g_Effect[nCntEffect].MinColorA = 0;

		g_Effect[nCntEffect].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Effect[nCntEffect].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		g_Effect[nCntEffect].fHight = 0;
		g_Effect[nCntEffect].fWhidth = 0;

		g_Effect[nCntEffect].bUse = false;
		g_Effect[nCntEffect].nlife = 0;
		g_Effect[nCntEffect].ntype = 0;
	}



	g_Effectstate.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Effectstate.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Effectstate.nRadius = 50;
	g_Effectstate.nDensity = 10;


	char aFile[256];

	FILE *pFile = fopen(LOADFILENAME, "r");

	if (pFile != NULL)//��x�t�@�C����ǂݍ���ŕK�v�ȏ��𔲂�
	{
		while (true)
		{
			fscanf(pFile, "%s", &aFile[0]);
			if (strcmp(&aFile[0], "NUM_TEXTURE") == 0)	//NUM_TEXTURE�̕��������������
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d", &g_EffectMaxTexture);
			}
			if (strcmp(&aFile[0], "TEXTURE_FILENAME") == 0) //TEXTURE_FILENAME�̕��������������
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%s", &aFile[0]);
				D3DXCreateTextureFromFile(pDevice, &aFile[0], &g_pTextureEffect[g_EffectTexture]);
				g_EffectTexture++;

			}

			if (strcmp(&aFile[0], "END_SCRIPT") == 0) //END_SCRIPT�̕��������������
			{
				break;
			}
		}
	}
	fclose(pFile);
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EFFECT, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffEffect, NULL);

}

//�I������
void UninitEffect(void)//�ǉ��̉\�������邽�ߍ��ڂ͍���Ƃ�
{
	for (int nCntEffect = 0; nCntEffect < g_EffectMaxTexture; nCntEffect++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureEffect != NULL)
		{
			g_pTextureEffect[nCntEffect]->Release();
			g_pTextureEffect[nCntEffect] = NULL;
		}

		//���_�o�b�t�@���j��
		if (g_pVtxBuffEffect != NULL)
		{
			g_pVtxBuffEffect->Release();
			g_pVtxBuffEffect = NULL;
		}
	}
}

//�X�V����
void UpdateEffect(void)
{
	VERTEX_3D*pVtx;//���_���ւ̃|�C���^


	float fAngle = 0;
	float fSpeed = 3;


	//switch (g_Effectstate.SerectType)
	//{
	//case(EFFECTTYPE_CIRCLE):
	//	if (GetKeyboardTrigger(DIK_SPACE) == TRUE)
	//	{

	//	}

	//	for (int nCnt = 0; nCnt < g_Effectstate.nDensity; nCnt++)
	//	{
	//		fAngle = CIRCLE;
	//		D3DXVECTOR3 move = D3DXVECTOR3(sinf(fAngle)* fSpeed, cosf(fAngle) * fSpeed, tanf(fAngle)* fSpeed);
	//		SetEffect(D3DXVECTOR3(sinf(fAngle) * g_Effectstate.nRadius, 10.0, cosf(fAngle) * g_Effectstate.nRadius), D3DXCOLOR(g_Effectstate.colorR, g_Effectstate.colorG, g_Effectstate.colorB, g_Effectstate.colorA), move, g_Effectstate.fWhidth, g_Effectstate.fHight, g_Effectstate.SerectType, g_Effectstate.nLifeSerect);
	//	}


	//	break;
	//case(EFFECTTYPE_STRIGHIT):
	//	if (GetKeyboardTrigger(DIK_SPACE) == TRUE)
	//	{

	//	}

	//	for (int nCnt = 0; nCnt < g_Effectstate.nDensity; nCnt++)
	//	{
	//		SetEffect(D3DXVECTOR3(0.0, 10.0, 0.0), D3DXCOLOR(g_Effectstate.colorR, g_Effectstate.colorG, g_Effectstate.colorB, g_Effectstate.colorA), D3DXVECTOR3(0.0, pCamera->rot.y, 0.0), g_Effectstate.fWhidth, g_Effectstate.fHight, g_Effectstate.SerectType, g_Effectstate.nLifeSerect);
	//	}

	//	break;
	//case(EFFECTTYPE_FOLL):

	//	for (int nCnt = 0; nCnt < g_Effectstate.nDensity; nCnt++)
	//	{
	//		fAngle = CIRCLE;
	//		D3DXVECTOR3 move = D3DXVECTOR3(sinf(fAngle)* fSpeed, cosf(fAngle) * fSpeed, tanf(fAngle)* fSpeed);
	//		SetEffect(D3DXVECTOR3(0.0, 10.0, 0.0), D3DXCOLOR(g_Effectstate.colorR, g_Effectstate.colorG, g_Effectstate.colorB, g_Effectstate.colorA), move, g_Effectstate.fWhidth, g_Effectstate.fHight, g_Effectstate.SerectType, g_Effectstate.nLifeSerect);
	//	}

	//	break;
	//case(EFFECTTYPE_POP):
	//	if (GetKeyboardTrigger(DIK_SPACE) == TRUE)
	//	{

	//	}

	//	for (int nCnt = 0; nCnt < g_Effectstate.nDensity; nCnt++)
	//	{
	//		fAngle = CIRCLE;
	//		D3DXVECTOR3 move = D3DXVECTOR3(sinf(fAngle)* fSpeed, cosf(fAngle) * fSpeed, CIRCLE * 1.5f);
	//		SetEffect(D3DXVECTOR3(0.0, 10.0, 0.0), D3DXCOLOR(g_Effectstate.colorR, g_Effectstate.colorG, g_Effectstate.colorB, g_Effectstate.colorA), move, g_Effectstate.fWhidth, g_Effectstate.fHight, g_Effectstate.SerectType, g_Effectstate.nLifeSerect);
	//	}
	//	break;

	//}

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{

		if (g_Effect[nCntEffect].bUse == true)
		{
			//�G�t�F�N�g�̎�ނŏ����𕪂��邽�߃X�C�b�`�g��
			switch (g_Effect[nCntEffect].ntype)
			{
			case(EFFECTTYPE_CIRCLE)://�o���ʒu���~�`

				g_Effect[nCntEffect].move.y += 0.2;
				g_Effect[nCntEffect].pos.y += g_Effect[nCntEffect].move.y;
				break;

			case(EFFECTTYPE_STRIGHIT):

				//g_Effect[nCntEffect].pos.x += sinf(g_Effect[nCntEffect].rot.y) * 10;
				//g_Effect[nCntEffect].pos.z += cosf(g_Effect[nCntEffect].rot.y) * 10;
				break;

			case(EFFECTTYPE_FOLL):

				g_Effect[nCntEffect].move.y -= 1;
				g_Effect[nCntEffect].pos.x += sinf(g_Effect[nCntEffect].rot.y) * 5;
				g_Effect[nCntEffect].pos.z += cosf(g_Effect[nCntEffect].rot.y) * 5;
				g_Effect[nCntEffect].pos.y += g_Effect[nCntEffect].move.y;
				break;

			case(EFFECTTYPE_POP):

				g_Effect[nCntEffect].pos += g_Effect[nCntEffect].rot;
				break;

			}

			//��ɕK�v�ȏ���
#if 1
			//�T�C�Y�ύX
			g_Effect[nCntEffect].fHight -= g_Effect[nCntEffect].fMinHight;
			g_Effect[nCntEffect].fWhidth -= g_Effect[nCntEffect].fMinWhidth;

			//�F�ύX
			g_Effect[nCntEffect].colorR -= g_Effect[nCntEffect].MinColorR;
			g_Effect[nCntEffect].colorG -= g_Effect[nCntEffect].MinColorG;
			g_Effect[nCntEffect].colorB -= g_Effect[nCntEffect].MinColorB;
			g_Effect[nCntEffect].colorA -= g_Effect[nCntEffect].MinColorA;

			//�������炵
			g_Effect[nCntEffect].nlife--;
			if (g_Effect[nCntEffect].nlife < 0)
			{
				g_Effect[nCntEffect].bUse = false;
			}
			//0��艺�̐��l�ɍs���Ȃ��悤�ɂ���
			if (g_Effect[nCntEffect].colorR < 0)
			{
				g_Effect[nCntEffect].colorR = 0;
			}

			if (g_Effect[nCntEffect].colorG < 0)
			{
				g_Effect[nCntEffect].colorG = 0;
			}

			if (g_Effect[nCntEffect].colorB < 0)
			{
				g_Effect[nCntEffect].colorB = 0;
			}

			if (g_Effect[nCntEffect].colorA < 0)
			{
				g_Effect[nCntEffect].colorA = 0;
			}

			if (g_Effect[nCntEffect].fHight < 0)
			{
				g_Effect[nCntEffect].fHight = 0;
			}
			if (g_Effect[nCntEffect].fWhidth < 0)
			{
				g_Effect[nCntEffect].fWhidth = 0;
			}
#endif
			//���_�̍��W
			pVtx[0].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fWhidth / 2, +g_Effect[nCntEffect].fHight / 2, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(+g_Effect[nCntEffect].fWhidth / 2, +g_Effect[nCntEffect].fHight / 2, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fWhidth / 2, -g_Effect[nCntEffect].fHight / 2, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(+g_Effect[nCntEffect].fWhidth / 2, -g_Effect[nCntEffect].fHight / 2, 0.0f);

			//���_�̐F
			pVtx[0].col = D3DCOLOR_RGBA(g_Effect[nCntEffect].colorR, g_Effect[nCntEffect].colorG, g_Effect[nCntEffect].colorB, g_Effect[nCntEffect].colorA);
			pVtx[1].col = D3DCOLOR_RGBA(g_Effect[nCntEffect].colorR, g_Effect[nCntEffect].colorG, g_Effect[nCntEffect].colorB, g_Effect[nCntEffect].colorA);
			pVtx[2].col = D3DCOLOR_RGBA(g_Effect[nCntEffect].colorR, g_Effect[nCntEffect].colorG, g_Effect[nCntEffect].colorB, g_Effect[nCntEffect].colorA);
			pVtx[3].col = D3DCOLOR_RGBA(g_Effect[nCntEffect].colorR, g_Effect[nCntEffect].colorG, g_Effect[nCntEffect].colorB, g_Effect[nCntEffect].colorA);
			pVtx += 4;
		}

	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffEffect->Unlock();


	//3.14 �` -3.14�ɕς��鏈��
	if (rot.y > D3DX_PI)
	{
		rot.y -= D3DX_PI * 2;
	}

	else if (rot.y < -D3DX_PI)
	{
		rot.y += D3DX_PI * 2;
	}

	//3.14 �` -3.14�ɕς��鏈��
	if (rot2.y > D3DX_PI)
	{
		rot2.y -= D3DX_PI * 2;
	}

	else if (rot2.y < -D3DX_PI)
	{
		rot2.y += D3DX_PI * 2;
	}

}



//�`�揈��
void DrawEffect(void)
{
	int nCntEffect;
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�̃|�C���^

	D3DXMATRIX mtxTrans;
	pDevice = GetDevice();//�f�o�C�X���擾����

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_Effect[nCntEffect].bUse == true)
		{

			//Z�e�X�g�֌W
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

			//�A���t�@�e�X�g�֌W
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0);


			//���Z�����֌W
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

			//�}�g���b�N�X������
			D3DXMatrixIdentity(&g_Effect[nCntEffect].mtxWorld);

			//�r���[�}�g���b�N�X�̎擾
			pDevice->GetTransform(D3DTS_VIEW, &g_Effect[nCntEffect].mtxView);

			//�|���S�����J�����ɑ΂��Đ��ʂ�
			D3DXMatrixInverse(&g_Effect[nCntEffect].mtxWorld, NULL, &g_Effect[nCntEffect].mtxView);

			g_Effect[nCntEffect].mtxWorld._41 = 0.0f;
			g_Effect[nCntEffect].mtxWorld._42 = 0.0f;
			g_Effect[nCntEffect].mtxWorld._43 = 0.0f;

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Effect[nCntEffect].pos.x, g_Effect[nCntEffect].pos.y, g_Effect[nCntEffect].pos.z);
			D3DXMatrixMultiply(&g_Effect[nCntEffect].mtxWorld, &g_Effect[nCntEffect].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Effect[nCntEffect].mtxWorld);

			//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_3D));

			pDevice->SetFVF(FVF_VERTEX_3D);//���_�t�H�[�}�b�g�̐ݒ�

			pDevice->SetTexture(0, g_pTextureEffect[g_Effect[nCntEffect].ntype]);//�e�N�X�`���̐ݒ�

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEffect * 4, 2);

			//Z�e�X�g�֌W
			
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

			//�ʏ퍇���ɖ߂�(���Z����)
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

			//�A���t�@�e�X�g�֌W
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);
		}

	}

}

void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR color, D3DXCOLOR Mincolor, D3DXVECTOR3 rot, float fWhidth, float fHight, float fMinWhidth, float fMinHight, int ntype, int nLife)
{
	int nCntEffect;
	int frand = 0;
	frand = POSRAND;
	VERTEX_3D*pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_Effect[nCntEffect].bUse == false)
		{
			g_Effect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			g_Effect[nCntEffect].fWhidth = fWhidth;
			g_Effect[nCntEffect].fHight = fHight;

			g_Effect[nCntEffect].fMinWhidth = fMinWhidth;
			g_Effect[nCntEffect].fMinHight = fMinHight;

			g_Effect[nCntEffect].ntype = ntype;
			g_Effect[nCntEffect].pos = pos;

			g_Effect[nCntEffect].colorR = color.r;
			g_Effect[nCntEffect].colorG = color.g; 
			g_Effect[nCntEffect].colorB = color.b; 
			g_Effect[nCntEffect].colorA = color.a;

			g_Effect[nCntEffect].MinColorR = Mincolor.r;
			g_Effect[nCntEffect].MinColorG = Mincolor.g;
			g_Effect[nCntEffect].MinColorB = Mincolor.b;
			g_Effect[nCntEffect].MinColorA = Mincolor.a;

			g_Effect[nCntEffect].rot = rot;


			//���_�̍��W
			pVtx[0].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fWhidth / 2, +g_Effect[nCntEffect].fHight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(+g_Effect[nCntEffect].fWhidth / 2, +g_Effect[nCntEffect].fHight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fWhidth / 2, 0.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(+g_Effect[nCntEffect].fWhidth / 2, 0.0f, 0.0f);

			//�x�N�g���̐ݒ�
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//�e�N�X�`����UV���W
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


			g_Effect[nCntEffect].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			if (g_Effect[nCntEffect].ntype == EFFECTTYPE_FOLL)
			{
				g_Effect[nCntEffect].move.y = frand;
			}
			else if (g_Effect[nCntEffect].ntype == EFFECTTYPE_POP)
			{
				g_Effect[nCntEffect].move.y = rand() % 5 - 1 - rand() % -5 + 1;
			}

			g_Effect[nCntEffect].nlife = nLife;
			g_Effect[nCntEffect].bUse = true;


			break;
		}
		pVtx += 4;

	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffEffect->Unlock();
}

void SetEffectState(void)
{
	char aFile[256];
	FILE *pFile = fopen(LOADFILENAME, "r");

	if (pFile != NULL)//��x�t�@�C����ǂݍ���ŕK�v�ȏ��𔲂�
	{
		while (true)
		{
			fscanf(pFile, "%s", &aFile[0]);
			if (strcmp(&aFile[0], "TYPE") == 0)	//TYPE�̕��������������
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d", &g_Effectstate.ntype);
			}

			if (strcmp(&aFile[0], "COLOR") == 0) //COLOR�̕��������������
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d %d %d %d", &g_Effectstate.colorR, g_Effectstate.colorG, g_Effectstate.colorB, g_Effectstate.colorA);
			}

			if (strcmp(&aFile[0], "COLORMIN") == 0) //COLORMIN�̕��������������
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d %d %d %d", &g_Effectstate.colorR, g_Effectstate.colorG, g_Effectstate.colorB, g_Effectstate.colorA);
			}

			if (strcmp(&aFile[0], "LIFE") == 0) //LIFE�̕��������������
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d", &g_Effectstate.nlife);
			}

			if (strcmp(&aFile[0], "SIZE") == 0) //SIZE�̕��������������
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%f %f", &g_Effectstate.fHight, g_Effectstate.fWhidth);
			}
			if (strcmp(&aFile[0], "SIZEMIN") == 0) //SIZEMIN�̕��������������
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%f %f", &g_Effectstate.fMinHight, g_Effectstate.fMinWhidth);
			}

			if (strcmp(&aFile[0], "EFFECTSTATE_END") == 0) //END_SCRIPT�̕��������������
			{
				break;
			}
		}
	}
	fclose(pFile);

}


Effect *GetEffect(void)
{
	return &g_Effect[0];
}


Effectstate * GetEffectstate(void)
{
	return &g_Effectstate;
}
