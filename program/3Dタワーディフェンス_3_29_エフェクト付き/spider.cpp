//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "spider.h"
#include "shadow.h"
#include "keyinput.h"
#include "girl.h"
#include "score.h"
#include "keyinput.h"
#include "Effect.h"

//---------------------------
//�O���[�o���ϐ�
//---------------------------
LPDIRECT3DTEXTURE9	g_apTextureEnemy[MAX_SPIDER_PARTS_NUM][MAX_SPIDER_TEX] = {};	//�e�N�X�`���̃|�C���^
Spider				g_aSpider[MAX_SPIDER_MODEL];	//�G�̍\����
int					g_nCntDeth;
int g_nCounttrue;

//---------------------------
//����������
//---------------------------
HRESULT InitSpider(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	pDevice = GetDevice();		//�f�o�C�X�̎擾

	for (int nCntSpider = 0; nCntSpider < MAX_SPIDER_MODEL; nCntSpider++)
	{
		g_aSpider[nCntSpider].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSpider[nCntSpider].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSpider[nCntSpider].nKeyold = -1;
		g_aSpider[nCntSpider].aState = SPIDER_STATE_WALK;
		g_aSpider[nCntSpider].aLook = SPIDER_STATE_NOLOOK;
		g_aSpider[nCntSpider].bCllision = false;
		g_aSpider[nCntSpider].bUse = false;
		for (int nCntParts = 0; nCntParts < MAX_SPIDER_PARTS_NUM; nCntParts++)
		{
			g_aSpider[nCntSpider].aModel[nCntParts].pMesh = {};
			g_aSpider[nCntSpider].aModel[nCntParts].pBuffMat = {};
		}
	}
	for (int nCntSpider = 0; nCntSpider < MAX_SPIDER_MODEL; nCntSpider++)
	{
		//---------------------------
		//X�t�@�C���̓ǂݍ���
		//---------------------------
		D3DXLoadMeshFromX(	"data/Model/spider/spiderB.x",
							D3DXMESH_SYSTEMMEM,
							pDevice,
							NULL,
							&g_aSpider[nCntSpider].aModel[0].pBuffMat,
							NULL,
							&g_aSpider[nCntSpider].aModel[0].pnNumMat,
							&g_aSpider[nCntSpider].aModel[0].pMesh);
		D3DXLoadMeshFromX(	"data/Model/spider/spiderH.x",
							D3DXMESH_SYSTEMMEM,
							pDevice,
							NULL,
							&g_aSpider[nCntSpider].aModel[1].pBuffMat,
							NULL,
							&g_aSpider[nCntSpider].aModel[1].pnNumMat,
							&g_aSpider[nCntSpider].aModel[1].pMesh);
		D3DXLoadMeshFromX(	"data/Model/spider/spiderR.x",
							D3DXMESH_SYSTEMMEM,
							pDevice,
							NULL,
							&g_aSpider[nCntSpider].aModel[2].pBuffMat,
							NULL,
							&g_aSpider[nCntSpider].aModel[2].pnNumMat,
							&g_aSpider[nCntSpider].aModel[2].pMesh);
		D3DXLoadMeshFromX(	"data/Model/spider/spiderL.x",
							D3DXMESH_SYSTEMMEM,
							pDevice,
							NULL,
							&g_aSpider[nCntSpider].aModel[3].pBuffMat,
							NULL,
							&g_aSpider[nCntSpider].aModel[3].pnNumMat,
							&g_aSpider[nCntSpider].aModel[3].pMesh);
		D3DXLoadMeshFromX(	"data/Model/spider/spiderR2.x",
							D3DXMESH_SYSTEMMEM,
							pDevice,
							NULL,
							&g_aSpider[nCntSpider].aModel[4].pBuffMat,
							NULL,
							&g_aSpider[nCntSpider].aModel[4].pnNumMat,
							&g_aSpider[nCntSpider].aModel[4].pMesh);
		D3DXLoadMeshFromX(	"data/Model/spider/spiderL2.x",
							D3DXMESH_SYSTEMMEM,
							pDevice,
							NULL,
							&g_aSpider[nCntSpider].aModel[5].pBuffMat,
							NULL,
							&g_aSpider[nCntSpider].aModel[5].pnNumMat,
							&g_aSpider[nCntSpider].aModel[5].pMesh);
		//---------------------------
		//�p�[�c�̊K�w�\��
		//---------------------------
		FILE *pFile = fopen("data/Model/spider/spider_motion.txt", "r");
		char string[256][256];
		char INDEX[] = "INDEX";
		char MOTIONSET[] = "MOTIONSET";
		char END_MOTIONSET[] = "END_MOTIONSET";
		char KEYSET[] = "KEYSET";
		char END_KEYSET[] = "END_KEYSET";
		char KEY[] = "KEY";

		//�K�w�\���̃e�L�X�g�ǂݎ��
		for (int nCntParts = 0; nCntParts < g_aSpider[nCntSpider].nNumModel; nCntParts++)
		{
			while (fgets(string[0], 256, pFile) != NULL)
			{
				if (strstr(string[0], INDEX))
				{
					fscanf(pFile, "%s%s%d%*s%*s", string[1], string[2], &g_aSpider[nCntSpider].aModel[nCntParts].nIdx);
					fscanf(pFile, "%s%s%f%f%f", string[3], string[4], &g_aSpider[nCntSpider].aModel[nCntParts].pos.x, &g_aSpider[nCntSpider].aModel[nCntParts].pos.y, &g_aSpider[nCntSpider].aModel[nCntParts].pos.z);
					fscanf(pFile, "%s%s%f%f%f", string[5], string[6], &g_aSpider[nCntSpider].aModel[nCntParts].rot.x, &g_aSpider[nCntSpider].aModel[nCntParts].rot.y, &g_aSpider[nCntSpider].aModel[nCntParts].rot.z);
					break;
				}
			}
			g_aSpider[nCntSpider].aModel[nCntParts].vtxMax = D3DXVECTOR3(-1000000.0f, -1000000.0f, -1000000.0f);
			g_aSpider[nCntSpider].aModel[nCntParts].vtxMin = D3DXVECTOR3(1000000.0f, 1000000.0f, 1000000.0f);
		}

		//---------------------------
		//���[�V����
		//---------------------------
		for (int nCntMosion = 0; nCntMosion < SPIDER_STATE_MAX; nCntMosion++)
		{
			while (fgets(string[0], 256, pFile) != NULL)
			{
				if (strstr(string[0], MOTIONSET))
				{
					fscanf(pFile, "%s%s%d%*s%*s%*s%*s", string[1], string[2], &g_aSpider[nCntSpider].aMotioninfo[nCntMosion].bLoop);
					fscanf(pFile, "%s%s%d", string[3], string[4], &g_aSpider[nCntSpider].aMotioninfo[nCntMosion].nNumKey);
					break;
				}
			}

			for (int nCntKey = 0; nCntKey < g_aSpider[nCntSpider].aMotioninfo[nCntMosion].nNumKey; nCntKey++)
			{
				while (fgets(string[0], 256, pFile) != NULL)
				{
					if (strstr(string[0], KEYSET))
					{
						fscanf(pFile, "%s%s%f", string[1], string[2], &g_aSpider[nCntSpider].aMotioninfo[nCntMosion].aKeyinfo[nCntKey].nFrame);
						g_aSpider[nCntSpider].aMotioninfo[nCntMosion].aKeyinfo[nCntKey].nFrame *= 5.0f;
						break;
					}
				}

				for (int nCntParts = 0; nCntParts < g_aSpider[nCntSpider].nNumModel; nCntParts++)
				{
					while (fgets(string[0], 256, pFile) != NULL)
					{
						if (strstr(string[0], KEY))
						{
							fscanf(pFile, "%s%s%f%f%f", string[1], string[2], &g_aSpider[nCntSpider].aMotioninfo[nCntMosion].aKeyinfo[nCntKey].aKey[nCntParts].fPosX, &g_aSpider[nCntSpider].aMotioninfo[nCntMosion].aKeyinfo[nCntKey].aKey[nCntParts].fPosY, &g_aSpider[nCntSpider].aMotioninfo[nCntMosion].aKeyinfo[nCntKey].aKey[nCntParts].fPosZ);
							fscanf(pFile, "%s%s%f%f%f%*s", string[3], string[4], &g_aSpider[nCntSpider].aMotioninfo[nCntMosion].aKeyinfo[nCntKey].aKey[nCntParts].fRotX, &g_aSpider[nCntSpider].aMotioninfo[nCntMosion].aKeyinfo[nCntKey].aKey[nCntParts].fRotY, &g_aSpider[nCntSpider].aMotioninfo[nCntMosion].aKeyinfo[nCntKey].aKey[nCntParts].fRotZ);
							break;
						}
					}
				}
				while (fgets(string[0], 256, pFile) != NULL)
				{
					if (strstr(string[0], END_KEYSET))
					{
						break;
					}
				}
			}

			while (fgets(string[0], 256, pFile) != NULL)
			{
				if (strstr(string[0], END_MOTIONSET))
				{
					break;
				}
			}
		}
		fclose(pFile);

		for (int nCntMosion = 0; nCntMosion < SPIDER_STATE_MAX; nCntMosion++)
		{
			for (int nCntKey = 0; nCntKey < g_aSpider[nCntSpider].aMotioninfo[nCntMosion].nNumKey; nCntKey++)
			{
				for (int nCntParts = 0; nCntParts < g_aSpider[nCntSpider].nNumModel; nCntParts++)
				{
					g_aSpider[nCntSpider].aMotioninfo[nCntMosion].aKeyinfo[nCntKey].aKey[nCntParts].fPosX = g_aSpider[nCntSpider].aModel[nCntParts].pos.x + g_aSpider[nCntSpider].aMotioninfo[nCntMosion].aKeyinfo[nCntKey].aKey[nCntParts].fPosX;
					g_aSpider[nCntSpider].aMotioninfo[nCntMosion].aKeyinfo[nCntKey].aKey[nCntParts].fPosY = g_aSpider[nCntSpider].aModel[nCntParts].pos.y + g_aSpider[nCntSpider].aMotioninfo[nCntMosion].aKeyinfo[nCntKey].aKey[nCntParts].fPosY;
					g_aSpider[nCntSpider].aMotioninfo[nCntMosion].aKeyinfo[nCntKey].aKey[nCntParts].fPosZ = g_aSpider[nCntSpider].aModel[nCntParts].pos.z + g_aSpider[nCntSpider].aMotioninfo[nCntMosion].aKeyinfo[nCntKey].aKey[nCntParts].fPosZ;

					g_aSpider[nCntSpider].aMotioninfo[nCntMosion].aKeyinfo[nCntKey].aKey[nCntParts].fRotX = g_aSpider[nCntSpider].aModel[nCntParts].rot.x + g_aSpider[nCntSpider].aMotioninfo[nCntMosion].aKeyinfo[nCntKey].aKey[nCntParts].fRotX;
					g_aSpider[nCntSpider].aMotioninfo[nCntMosion].aKeyinfo[nCntKey].aKey[nCntParts].fRotY = g_aSpider[nCntSpider].aModel[nCntParts].rot.y + g_aSpider[nCntSpider].aMotioninfo[nCntMosion].aKeyinfo[nCntKey].aKey[nCntParts].fRotY;
					g_aSpider[nCntSpider].aMotioninfo[nCntMosion].aKeyinfo[nCntKey].aKey[nCntParts].fRotZ = g_aSpider[nCntSpider].aModel[nCntParts].rot.z + g_aSpider[nCntSpider].aMotioninfo[nCntMosion].aKeyinfo[nCntKey].aKey[nCntParts].fRotZ;
				}
			}
		}

		//---------------------------
		//�e�N�X�`���̔����o��
		//---------------------------
		D3DXMATERIAL *pMat;	//�}�e���A���̃|�C���^

		for (int nCntParts = 0; nCntParts < MAX_SPIDER_PARTS_NUM; nCntParts++)
		{
			//�}�e���A�����̃|�C���^
			pMat = (D3DXMATERIAL*)g_aSpider[nCntSpider].aModel[nCntParts].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aSpider[nCntSpider].aModel[nCntParts].pnNumMat; nCntMat++)
			{
				if (pMat[nCntMat].pTextureFilename != NULL)
				{
					//�e�N�X�`���̓ǂݍ���
					D3DXCreateTextureFromFile(	pDevice,
												pMat[nCntMat].pTextureFilename,			//�e�N�X�`��
												&g_apTextureEnemy[nCntParts][nCntMat]);
				}		
			}
		}
		//---------------------------
		//���_���W�̔����o��
		//---------------------------
		int nNumVtx;	//���_��
		DWORD sizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y
		BYTE *pVtxBuff;	//���_�o�b�t�@�̃|�C���^

		for (int nCntParts = 0; nCntParts < MAX_SPIDER_PARTS_NUM; nCntParts++)
		{
			//���_�����擾
			nNumVtx = g_aSpider[nCntSpider].aModel[nCntParts].pMesh->GetNumVertices();

			//���_�t�H�[�}�b�g�̃T�C�Y���擾
			sizeFVF = D3DXGetFVFVertexSize(g_aSpider[nCntSpider].aModel[nCntParts].pMesh->GetFVF());

			//���_�o�b�t�@�̃��b�N
			g_aSpider[nCntSpider].aModel[nCntParts].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
			{
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//���_���W�̑��

				//���_�����r���čŏ��l�A�ő�l�𔲂�
				//X
				if (g_aSpider[nCntSpider].aModel[nCntParts].vtxMax.x <= vtx.x)
				{
					g_aSpider[nCntSpider].aModel[nCntParts].vtxMax.x = vtx.x;
				}
				if (g_aSpider[nCntSpider].aModel[nCntParts].vtxMin.x >= vtx.x)
				{
					g_aSpider[nCntSpider].aModel[nCntParts].vtxMin.x = vtx.x;
				}
				//Y
				if (g_aSpider[nCntSpider].aModel[nCntParts].vtxMax.y <= vtx.y)
				{
					g_aSpider[nCntSpider].aModel[nCntParts].vtxMax.y = vtx.y;
				}
				if (g_aSpider[nCntSpider].aModel[nCntParts].vtxMin.y >= vtx.y)
				{
					g_aSpider[nCntSpider].aModel[nCntParts].vtxMin.y = vtx.y;
				}
				//Z
				if (g_aSpider[nCntSpider].aModel[nCntParts].vtxMax.z <= vtx.z)
				{
					g_aSpider[nCntSpider].aModel[nCntParts].vtxMax.z = vtx.z;
				}
				if (g_aSpider[nCntSpider].aModel[nCntParts].vtxMin.z >= vtx.z)
				{
					g_aSpider[nCntSpider].aModel[nCntParts].vtxMin.z = vtx.z;
				}

				pVtxBuff += sizeFVF;	//���_��i�߂�
			}
			//���_�o�b�t�@���A�����b�N
			g_aSpider[nCntSpider].aModel[nCntParts].pMesh->UnlockVertexBuffer();
		}
	}
	return S_OK;
}

//---------------------------
//�I������
//---------------------------
void UninitSpider(void)
{
	for (int nCntSpider = 0; nCntSpider < MAX_SPIDER_MODEL; nCntSpider++)
	{
		for (int nCntParts = 0; nCntParts < MAX_SPIDER_PARTS_NUM; nCntParts++)
		{
			//---------------------------
			//���b�V���j��
			//---------------------------
			if (g_aSpider[nCntSpider].aModel[nCntParts].pMesh!= NULL)
			{
				g_aSpider[nCntSpider].aModel[nCntParts].pMesh->Release();
				g_aSpider[nCntSpider].aModel[nCntParts].pMesh = NULL;
			}

			//---------------------------
			//�}�e���A���j��
			//---------------------------
			if (g_aSpider[nCntSpider].aModel[nCntParts].pBuffMat != NULL)
			{
				g_aSpider[nCntSpider].aModel[nCntParts].pBuffMat->Release();
				g_aSpider[nCntSpider].aModel[nCntParts].pBuffMat = NULL;
			}
		}
	}
}

//---------------------------
//�X�V����
//---------------------------
void UpdateSpider(void)
{
	float fPosXAsk[MAX_SPIDER_PARTS_NUM];		//���߂�l�ʒuX
	float fPosYAsk[MAX_SPIDER_PARTS_NUM];		//���߂�l�ʒuY
	float fPosZAsk[MAX_SPIDER_PARTS_NUM];		//���߂�l�ʒuZ
	float fRotXAsk[MAX_SPIDER_PARTS_NUM];		//���߂�l����X
	float fRotYAsk[MAX_SPIDER_PARTS_NUM];		//���߂�l����Y
	float fRotZAsk[MAX_SPIDER_PARTS_NUM];		//���߂�l����Z
	float PosXDifference[MAX_SPIDER_PARTS_NUM];	//�ʒu�̍���X
	float PosYDifference[MAX_SPIDER_PARTS_NUM];	//�ʒu�̍���Y
	float PosZDifference[MAX_SPIDER_PARTS_NUM];	//�ʒu�̍���Z
	float RotXDifference[MAX_SPIDER_PARTS_NUM];	//�����̍���X
	float RotYDifference[MAX_SPIDER_PARTS_NUM];	//�����̍���Y
	float RotZDifference[MAX_SPIDER_PARTS_NUM];	//�����̍���Z

	for (int nCntSpider = 0; nCntSpider < MAX_SPIDER_MODEL; nCntSpider++)
	{
		if (g_aSpider[nCntSpider].bUse == true)
		{
			g_aSpider[nCntSpider].pos += g_aSpider[nCntSpider].move;

			SpiderLooknig(nCntSpider);

			if (g_aSpider[nCntSpider].aState == SPIDER_STATE_WALK)
			{
				if (g_aSpider[nCntSpider].nKey == 0)
				{
					for (int nCntModel = 0; nCntModel < MAX_SPIDER_PARTS_NUM; nCntModel++)
					{
						PosXDifference[nCntModel] = g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_WALK].aKeyinfo[g_aSpider[nCntSpider].nKey + 1].aKey[nCntModel].fPosX - g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_WALK].aKeyinfo[g_aSpider[nCntSpider].nKey].aKey[nCntModel].fPosX;
						PosYDifference[nCntModel] = g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_WALK].aKeyinfo[g_aSpider[nCntSpider].nKey + 1].aKey[nCntModel].fPosY - g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_WALK].aKeyinfo[g_aSpider[nCntSpider].nKey].aKey[nCntModel].fPosY;
						PosZDifference[nCntModel] = g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_WALK].aKeyinfo[g_aSpider[nCntSpider].nKey + 1].aKey[nCntModel].fPosZ - g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_WALK].aKeyinfo[g_aSpider[nCntSpider].nKey].aKey[nCntModel].fPosZ;
																																																			
						RotXDifference[nCntModel] = g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_WALK].aKeyinfo[g_aSpider[nCntSpider].nKey + 1].aKey[nCntModel].fRotX - g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_WALK].aKeyinfo[g_aSpider[nCntSpider].nKey].aKey[nCntModel].fRotX;
						RotYDifference[nCntModel] = g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_WALK].aKeyinfo[g_aSpider[nCntSpider].nKey + 1].aKey[nCntModel].fRotY - g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_WALK].aKeyinfo[g_aSpider[nCntSpider].nKey].aKey[nCntModel].fRotY;
						RotZDifference[nCntModel] = g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_WALK].aKeyinfo[g_aSpider[nCntSpider].nKey + 1].aKey[nCntModel].fRotZ - g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_WALK].aKeyinfo[g_aSpider[nCntSpider].nKey].aKey[nCntModel].fRotZ;

						fPosXAsk[nCntModel] = g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_WALK].aKeyinfo[g_aSpider[nCntSpider].nKey].aKey[nCntModel].fPosX + PosXDifference[nCntModel] * (g_aSpider[nCntSpider].fMotion / g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_WALK].aKeyinfo[g_aSpider[nCntSpider].nKey].nFrame);
						fPosYAsk[nCntModel] = g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_WALK].aKeyinfo[g_aSpider[nCntSpider].nKey].aKey[nCntModel].fPosY + PosYDifference[nCntModel] * (g_aSpider[nCntSpider].fMotion / g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_WALK].aKeyinfo[g_aSpider[nCntSpider].nKey].nFrame);
						fPosZAsk[nCntModel] = g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_WALK].aKeyinfo[g_aSpider[nCntSpider].nKey].aKey[nCntModel].fPosZ + PosZDifference[nCntModel] * (g_aSpider[nCntSpider].fMotion / g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_WALK].aKeyinfo[g_aSpider[nCntSpider].nKey].nFrame);
																																																														
						fRotXAsk[nCntModel] = g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_WALK].aKeyinfo[g_aSpider[nCntSpider].nKey].aKey[nCntModel].fRotX + RotXDifference[nCntModel] * (g_aSpider[nCntSpider].fMotion / g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_WALK].aKeyinfo[g_aSpider[nCntSpider].nKey].nFrame);
						fRotYAsk[nCntModel] = g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_WALK].aKeyinfo[g_aSpider[nCntSpider].nKey].aKey[nCntModel].fRotY + RotYDifference[nCntModel] * (g_aSpider[nCntSpider].fMotion / g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_WALK].aKeyinfo[g_aSpider[nCntSpider].nKey].nFrame);
						fRotZAsk[nCntModel] = g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_WALK].aKeyinfo[g_aSpider[nCntSpider].nKey].aKey[nCntModel].fRotZ + RotZDifference[nCntModel] * (g_aSpider[nCntSpider].fMotion / g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_WALK].aKeyinfo[g_aSpider[nCntSpider].nKey].nFrame);

						g_aSpider[nCntSpider].aModel[nCntModel].pos.x = fPosXAsk[nCntModel];
						g_aSpider[nCntSpider].aModel[nCntModel].pos.y = fPosYAsk[nCntModel];
						g_aSpider[nCntSpider].aModel[nCntModel].pos.z = fPosZAsk[nCntModel];

						g_aSpider[nCntSpider].aModel[nCntModel].rot.x = fRotXAsk[nCntModel];
						g_aSpider[nCntSpider].aModel[nCntModel].rot.y = fRotYAsk[nCntModel];
						g_aSpider[nCntSpider].aModel[nCntModel].rot.z = fRotZAsk[nCntModel];
					}
					//���t���[��1.0���₵�Ă���
					g_aSpider[nCntSpider].fMotion += 1.0f;
					//���[�V�����J�E���^���t���[�����𒴂�����
					if (g_aSpider[nCntSpider].fMotion >= g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_WALK].aKeyinfo[g_aSpider[nCntSpider].nKey].nFrame)
					{
						g_aSpider[nCntSpider].nKeyold = g_aSpider[nCntSpider].nKey;
						g_aSpider[nCntSpider].nKey++;
						//���[�V�����J�E���^������
						g_aSpider[nCntSpider].fMotion = 0.0f;
					}
				}

				else if (g_aSpider[nCntSpider].nKey == 1)
				{
					for (int nCntModel = 0; nCntModel < MAX_SPIDER_PARTS_NUM; nCntModel++)
					{
						PosXDifference[nCntModel] = g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_WALK].aKeyinfo[g_aSpider[nCntSpider].nKey - 1].aKey[nCntModel].fPosX - g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_WALK].aKeyinfo[g_aSpider[nCntSpider].nKey].aKey[nCntModel].fPosX;
						PosYDifference[nCntModel] = g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_WALK].aKeyinfo[g_aSpider[nCntSpider].nKey - 1].aKey[nCntModel].fPosY - g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_WALK].aKeyinfo[g_aSpider[nCntSpider].nKey].aKey[nCntModel].fPosY;
						PosZDifference[nCntModel] = g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_WALK].aKeyinfo[g_aSpider[nCntSpider].nKey - 1].aKey[nCntModel].fPosZ - g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_WALK].aKeyinfo[g_aSpider[nCntSpider].nKey].aKey[nCntModel].fPosZ;
																																			 
						RotXDifference[nCntModel] = g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_WALK].aKeyinfo[g_aSpider[nCntSpider].nKey - 1].aKey[nCntModel].fRotX - g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_WALK].aKeyinfo[g_aSpider[nCntSpider].nKey].aKey[nCntModel].fRotX;
						RotYDifference[nCntModel] = g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_WALK].aKeyinfo[g_aSpider[nCntSpider].nKey - 1].aKey[nCntModel].fRotY - g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_WALK].aKeyinfo[g_aSpider[nCntSpider].nKey].aKey[nCntModel].fRotY;
						RotZDifference[nCntModel] = g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_WALK].aKeyinfo[g_aSpider[nCntSpider].nKey - 1].aKey[nCntModel].fRotZ - g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_WALK].aKeyinfo[g_aSpider[nCntSpider].nKey].aKey[nCntModel].fRotZ;

						fPosXAsk[nCntModel] = g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_WALK].aKeyinfo[g_aSpider[nCntSpider].nKey].aKey[nCntModel].fPosX + PosXDifference[nCntModel] * (g_aSpider[nCntSpider].fMotion / g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_WALK].aKeyinfo[g_aSpider[nCntSpider].nKey].nFrame);
						fPosYAsk[nCntModel] = g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_WALK].aKeyinfo[g_aSpider[nCntSpider].nKey].aKey[nCntModel].fPosY + PosYDifference[nCntModel] * (g_aSpider[nCntSpider].fMotion / g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_WALK].aKeyinfo[g_aSpider[nCntSpider].nKey].nFrame);
						fPosZAsk[nCntModel] = g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_WALK].aKeyinfo[g_aSpider[nCntSpider].nKey].aKey[nCntModel].fPosZ + PosZDifference[nCntModel] * (g_aSpider[nCntSpider].fMotion / g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_WALK].aKeyinfo[g_aSpider[nCntSpider].nKey].nFrame);

						fRotXAsk[nCntModel] = g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_WALK].aKeyinfo[g_aSpider[nCntSpider].nKey].aKey[nCntModel].fRotX + RotXDifference[nCntModel] * (g_aSpider[nCntSpider].fMotion / g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_WALK].aKeyinfo[g_aSpider[nCntSpider].nKey].nFrame);
						fRotYAsk[nCntModel] = g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_WALK].aKeyinfo[g_aSpider[nCntSpider].nKey].aKey[nCntModel].fRotY + RotYDifference[nCntModel] * (g_aSpider[nCntSpider].fMotion / g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_WALK].aKeyinfo[g_aSpider[nCntSpider].nKey].nFrame);
						fRotZAsk[nCntModel] = g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_WALK].aKeyinfo[g_aSpider[nCntSpider].nKey].aKey[nCntModel].fRotZ + RotZDifference[nCntModel] * (g_aSpider[nCntSpider].fMotion / g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_WALK].aKeyinfo[g_aSpider[nCntSpider].nKey].nFrame);

						g_aSpider[nCntSpider].aModel[nCntModel].pos.x = fPosXAsk[nCntModel];
						g_aSpider[nCntSpider].aModel[nCntModel].pos.y = fPosYAsk[nCntModel];
						g_aSpider[nCntSpider].aModel[nCntModel].pos.z = fPosZAsk[nCntModel];

						g_aSpider[nCntSpider].aModel[nCntModel].rot.x = fRotXAsk[nCntModel];
						g_aSpider[nCntSpider].aModel[nCntModel].rot.y = fRotYAsk[nCntModel];
						g_aSpider[nCntSpider].aModel[nCntModel].rot.z = fRotZAsk[nCntModel];
					}
					//���t���[��1.0���₵�Ă���
					g_aSpider[nCntSpider].fMotion += 1.0f;
					//���[�V�����J�E���^���t���[�����𒴂�����
					if (g_aSpider[nCntSpider].fMotion >= g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_WALK].aKeyinfo[g_aSpider[nCntSpider].nKey].nFrame)
					{
						if (g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_WALK].bLoop == true)
						{
							g_aSpider[nCntSpider].nKeyold = g_aSpider[nCntSpider].nKey;
							g_aSpider[nCntSpider].nKey--;
							//���[�V�����J�E���^������
							g_aSpider[nCntSpider].fMotion = 0.0f;
						}
						else
						{
							g_aSpider[nCntSpider].nKey = 2;
						}
					}
				}
			}
			else if (g_aSpider[nCntSpider].aState == SPIDER_STATE_ATTACK)
			{
				if (g_aSpider[nCntSpider].nKey == 0)
				{
					for (int nCntModel = 0; nCntModel < MAX_SPIDER_PARTS_NUM; nCntModel++)
					{
						PosXDifference[nCntModel] = g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey + 1].aKey[nCntModel].fPosX - g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey].aKey[nCntModel].fPosX;
						PosYDifference[nCntModel] = g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey + 1].aKey[nCntModel].fPosY - g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey].aKey[nCntModel].fPosY;
						PosZDifference[nCntModel] = g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey + 1].aKey[nCntModel].fPosZ - g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey].aKey[nCntModel].fPosZ;

						RotXDifference[nCntModel] = g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey + 1].aKey[nCntModel].fRotX - g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey].aKey[nCntModel].fRotX;
						RotYDifference[nCntModel] = g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey + 1].aKey[nCntModel].fRotY - g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey].aKey[nCntModel].fRotY;
						RotZDifference[nCntModel] = g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey + 1].aKey[nCntModel].fRotZ - g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey].aKey[nCntModel].fRotZ;

						fPosXAsk[nCntModel] = g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey].aKey[nCntModel].fPosX + PosXDifference[nCntModel] * (g_aSpider[nCntSpider].fMotion / g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey].nFrame);
						fPosYAsk[nCntModel] = g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey].aKey[nCntModel].fPosY + PosYDifference[nCntModel] * (g_aSpider[nCntSpider].fMotion / g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey].nFrame);
						fPosZAsk[nCntModel] = g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey].aKey[nCntModel].fPosZ + PosZDifference[nCntModel] * (g_aSpider[nCntSpider].fMotion / g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey].nFrame);

						fRotXAsk[nCntModel] = g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey].aKey[nCntModel].fRotX + RotXDifference[nCntModel] * (g_aSpider[nCntSpider].fMotion / g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey].nFrame);
						fRotYAsk[nCntModel] = g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey].aKey[nCntModel].fRotY + RotYDifference[nCntModel] * (g_aSpider[nCntSpider].fMotion / g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey].nFrame);
						fRotZAsk[nCntModel] = g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey].aKey[nCntModel].fRotZ + RotZDifference[nCntModel] * (g_aSpider[nCntSpider].fMotion / g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey].nFrame);

						g_aSpider[nCntSpider].aModel[nCntModel].pos.x = fPosXAsk[nCntModel];
						g_aSpider[nCntSpider].aModel[nCntModel].pos.y = fPosYAsk[nCntModel];
						g_aSpider[nCntSpider].aModel[nCntModel].pos.z = fPosZAsk[nCntModel];

						g_aSpider[nCntSpider].aModel[nCntModel].rot.x = fRotXAsk[nCntModel];
						g_aSpider[nCntSpider].aModel[nCntModel].rot.y = fRotYAsk[nCntModel];
						g_aSpider[nCntSpider].aModel[nCntModel].rot.z = fRotZAsk[nCntModel];
					}
					//���t���[��1.0���₵�Ă���
					g_aSpider[nCntSpider].fMotion += 1.0f;
					//���[�V�����J�E���^���t���[�����𒴂�����
					if (g_aSpider[nCntSpider].fMotion >= g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey].nFrame)
					{
						g_aSpider[nCntSpider].nKeyold = g_aSpider[nCntSpider].nKey;
						g_aSpider[nCntSpider].nKey++;
						//���[�V�����J�E���^������
						g_aSpider[nCntSpider].fMotion = 0.0f;
					}
				}
				else if (g_aSpider[nCntSpider].nKey == 1)
				{
					for (int nCntModel = 0; nCntModel < MAX_SPIDER_PARTS_NUM; nCntModel++)
					{
						PosXDifference[nCntModel] = g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey + 1].aKey[nCntModel].fPosX - g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey].aKey[nCntModel].fPosX;
						PosYDifference[nCntModel] = g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey + 1].aKey[nCntModel].fPosY - g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey].aKey[nCntModel].fPosY;
						PosZDifference[nCntModel] = g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey + 1].aKey[nCntModel].fPosZ - g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey].aKey[nCntModel].fPosZ;

						RotXDifference[nCntModel] = g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey + 1].aKey[nCntModel].fRotX - g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey].aKey[nCntModel].fRotX;
						RotYDifference[nCntModel] = g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey + 1].aKey[nCntModel].fRotY - g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey].aKey[nCntModel].fRotY;
						RotZDifference[nCntModel] = g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey + 1].aKey[nCntModel].fRotZ - g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey].aKey[nCntModel].fRotZ;

						fPosXAsk[nCntModel] = g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey].aKey[nCntModel].fPosX + PosXDifference[nCntModel] * (g_aSpider[nCntSpider].fMotion / g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey].nFrame);
						fPosYAsk[nCntModel] = g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey].aKey[nCntModel].fPosY + PosYDifference[nCntModel] * (g_aSpider[nCntSpider].fMotion / g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey].nFrame);
						fPosZAsk[nCntModel] = g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey].aKey[nCntModel].fPosZ + PosZDifference[nCntModel] * (g_aSpider[nCntSpider].fMotion / g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey].nFrame);

						fRotXAsk[nCntModel] = g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey].aKey[nCntModel].fRotX + RotXDifference[nCntModel] * (g_aSpider[nCntSpider].fMotion / g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey].nFrame);
						fRotYAsk[nCntModel] = g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey].aKey[nCntModel].fRotY + RotYDifference[nCntModel] * (g_aSpider[nCntSpider].fMotion / g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey].nFrame);
						fRotZAsk[nCntModel] = g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey].aKey[nCntModel].fRotZ + RotZDifference[nCntModel] * (g_aSpider[nCntSpider].fMotion / g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey].nFrame);

						g_aSpider[nCntSpider].aModel[nCntModel].pos.x = fPosXAsk[nCntModel];
						g_aSpider[nCntSpider].aModel[nCntModel].pos.y = fPosYAsk[nCntModel];
						g_aSpider[nCntSpider].aModel[nCntModel].pos.z = fPosZAsk[nCntModel];

						g_aSpider[nCntSpider].aModel[nCntModel].rot.x = fRotXAsk[nCntModel];
						g_aSpider[nCntSpider].aModel[nCntModel].rot.y = fRotYAsk[nCntModel];
						g_aSpider[nCntSpider].aModel[nCntModel].rot.z = fRotZAsk[nCntModel];
					}
					//���t���[��1.0���₵�Ă���
					g_aSpider[nCntSpider].fMotion += 1.0f;
					//���[�V�����J�E���^���t���[�����𒴂�����
					if (g_aSpider[nCntSpider].fMotion >= g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey].nFrame)
					{
						g_aSpider[nCntSpider].nKeyold = g_aSpider[nCntSpider].nKey;
						g_aSpider[nCntSpider].nKey++;
						//���[�V�����J�E���^������
						g_aSpider[nCntSpider].fMotion = 0.0f;
					}
				}
				else if (g_aSpider[nCntSpider].nKey == 2)
				{
					for (int nCntModel = 0; nCntModel < MAX_SPIDER_PARTS_NUM; nCntModel++)
					{
						PosXDifference[nCntModel] = g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey + 1].aKey[nCntModel].fPosX - g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey].aKey[nCntModel].fPosX;
						PosYDifference[nCntModel] = g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey + 1].aKey[nCntModel].fPosY - g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey].aKey[nCntModel].fPosY;
						PosZDifference[nCntModel] = g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey + 1].aKey[nCntModel].fPosZ - g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey].aKey[nCntModel].fPosZ;

						RotXDifference[nCntModel] = g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey + 1].aKey[nCntModel].fRotX - g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey].aKey[nCntModel].fRotX;
						RotYDifference[nCntModel] = g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey + 1].aKey[nCntModel].fRotY - g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey].aKey[nCntModel].fRotY;
						RotZDifference[nCntModel] = g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey + 1].aKey[nCntModel].fRotZ - g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey].aKey[nCntModel].fRotZ;

						fPosXAsk[nCntModel] = g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey].aKey[nCntModel].fPosX + PosXDifference[nCntModel] * (g_aSpider[nCntSpider].fMotion / g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey].nFrame);
						fPosYAsk[nCntModel] = g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey].aKey[nCntModel].fPosY + PosYDifference[nCntModel] * (g_aSpider[nCntSpider].fMotion / g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey].nFrame);
						fPosZAsk[nCntModel] = g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey].aKey[nCntModel].fPosZ + PosZDifference[nCntModel] * (g_aSpider[nCntSpider].fMotion / g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey].nFrame);

						fRotXAsk[nCntModel] = g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey].aKey[nCntModel].fRotX + RotXDifference[nCntModel] * (g_aSpider[nCntSpider].fMotion / g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey].nFrame);
						fRotYAsk[nCntModel] = g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey].aKey[nCntModel].fRotY + RotYDifference[nCntModel] * (g_aSpider[nCntSpider].fMotion / g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey].nFrame);
						fRotZAsk[nCntModel] = g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey].aKey[nCntModel].fRotZ + RotZDifference[nCntModel] * (g_aSpider[nCntSpider].fMotion / g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey].nFrame);

						g_aSpider[nCntSpider].aModel[nCntModel].pos.x = fPosXAsk[nCntModel];
						g_aSpider[nCntSpider].aModel[nCntModel].pos.y = fPosYAsk[nCntModel];
						g_aSpider[nCntSpider].aModel[nCntModel].pos.z = fPosZAsk[nCntModel];

						g_aSpider[nCntSpider].aModel[nCntModel].rot.x = fRotXAsk[nCntModel];
						g_aSpider[nCntSpider].aModel[nCntModel].rot.y = fRotYAsk[nCntModel];
						g_aSpider[nCntSpider].aModel[nCntModel].rot.z = fRotZAsk[nCntModel];
					}
					//���t���[��1.0���₵�Ă���
					g_aSpider[nCntSpider].fMotion += 1.0f;
					//���[�V�����J�E���^���t���[�����𒴂�����
					if (g_aSpider[nCntSpider].fMotion >= g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].aKeyinfo[g_aSpider[nCntSpider].nKey].nFrame)
					{
						g_aSpider[nCntSpider].nKeyold = g_aSpider[nCntSpider].nKey;
						g_aSpider[nCntSpider].nKey++;
						//���[�V�����J�E���^������
						g_aSpider[nCntSpider].fMotion = 0.0f;
#if (0)
						AddGirl(1);
#endif // _DEBUG
					}
				}
				else if (g_aSpider[nCntSpider].nKey == 3)
				{
					if (g_aSpider[nCntSpider].aMotioninfo[SPIDER_STATE_ATTACK].bLoop == true)
					{
						g_aSpider[nCntSpider].nKey = 0;
					}
					else
					{
						g_aSpider[nCntSpider].nKey = 4;
					}
				}
			}
#ifdef _DEBUG
			if (GetKeyboardPress(DIK_L) == true)
			{
				g_aSpider[nCntSpider].aState = SPIDER_STATE_ATTACK;
				g_aSpider[nCntSpider].nKey = 0;
			}
			else if (GetKeyboardPress(DIK_O) == true)
			{
				g_aSpider[nCntSpider].aState = SPIDER_STATE_WALK;
				g_aSpider[nCntSpider].nKey = 0;
			}
			if (GetKeyboardTrigger(DIK_P) == true)
			{
				g_aSpider[nCntSpider].bCllision = g_aSpider[nCntSpider].bCllision ? false : true;
			}
#endif // DEBUG
			SetPointShadow(g_aSpider[nCntSpider].nIdex, D3DXVECTOR3(g_aSpider[nCntSpider].pos.x, 0.0f, g_aSpider[nCntSpider].pos.z), 150.0f, 150.0f);
		}
	}
}

//---------------------------
//�`�揈��
//---------------------------
void DrawSpider(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^

	pDevice = GetDevice();		//�f�o�C�X���擾����

	for (int nCntSpider = 0; nCntSpider < MAX_SPIDER_MODEL; nCntSpider++)
	{
		if (g_aSpider[nCntSpider].bUse == true)
		{
			//-------------------------------
			//�v���C���[(���_)�̃}�g���b�N�X�̐ݒ�
			//-------------------------------
			D3DXMATRIX			mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

			pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

			D3DXMatrixIdentity(&g_aSpider[nCntSpider].mtxWold);	//�}�g���b�N�X������

																//�����̐ݒ�
			D3DXMatrixRotationYawPitchRoll(	&mtxRot,
											g_aSpider[nCntSpider].rot.y,
											g_aSpider[nCntSpider].rot.x,
											g_aSpider[nCntSpider].rot.z);

			D3DXMatrixMultiply(	&g_aSpider[nCntSpider].mtxWold,
								&g_aSpider[nCntSpider].mtxWold,
								&mtxRot);
			//�ʒu
			D3DXMatrixTranslation(	&mtxTrans,
									g_aSpider[nCntSpider].pos.x,
									g_aSpider[nCntSpider].pos.y,
									g_aSpider[nCntSpider].pos.z);

			D3DXMatrixMultiply(	&g_aSpider[nCntSpider].mtxWold,
								&g_aSpider[nCntSpider].mtxWold,
								&mtxTrans);
			//�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(	D3DTS_WORLD,
									&g_aSpider[nCntSpider].mtxWold);
			//---------------------------------
			//���f���p�[�c�̃}�g���b�N�X�̐ݒ�
			//---------------------------------
			for (int nCntParts = 0; nCntParts < g_aSpider[nCntSpider].nNumModel; nCntParts++)
			{
				D3DXMATRIX mtxRotModel, mtxTransModel;	//�v�Z�p�}�g���b�N�X
				D3DXMATRIX mtxParent;					//�e�̃}�g���b�N�X

				D3DXMatrixIdentity(&g_aSpider[nCntSpider].aModel[nCntParts].mtxWold);	//�}�g���b�N�X������

				//�����̐ݒ�
				D3DXMatrixRotationYawPitchRoll(	&mtxRotModel,
												g_aSpider[nCntSpider].aModel[nCntParts].rot.y,
												g_aSpider[nCntSpider].aModel[nCntParts].rot.x,
												g_aSpider[nCntSpider].aModel[nCntParts].rot.z);

				D3DXMatrixMultiply(	&g_aSpider[nCntSpider].aModel[nCntParts].mtxWold,
									&g_aSpider[nCntSpider].aModel[nCntParts].mtxWold,
									&mtxRotModel);
				//�ʒu
				D3DXMatrixTranslation(	&mtxTransModel,
										g_aSpider[nCntSpider].aModel[nCntParts].pos.x,
										g_aSpider[nCntSpider].aModel[nCntParts].pos.y,
										g_aSpider[nCntSpider].aModel[nCntParts].pos.z);

				D3DXMatrixMultiply(	&g_aSpider[nCntSpider].aModel[nCntParts].mtxWold,
									&g_aSpider[nCntSpider].aModel[nCntParts].mtxWold,
									&mtxTransModel);

				//�p�[�c�̐e�̃}�g���b�N�X��ݒ�
				//�����e��������
				if (g_aSpider[nCntSpider].aModel[nCntParts].nIdx != -1)
				{
					mtxParent = g_aSpider[nCntSpider].aModel[g_aSpider[nCntSpider].aModel[nCntParts].nIdx].mtxWold;
				}
				else
				{
					mtxParent = g_aSpider[nCntSpider].mtxWold;
				}

				//�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃��[���h�}�g���b�N�X���|�����킹��
				D3DXMatrixMultiply(	&g_aSpider[nCntSpider].aModel[nCntParts].mtxWold,
									&g_aSpider[nCntSpider].aModel[nCntParts].mtxWold,
									&mtxParent);

				//�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(	D3DTS_WORLD,
										&g_aSpider[nCntSpider].aModel[nCntParts].mtxWold);

				//---------------------------
				//�`�揈��
				//---------------------------
				D3DMATERIAL9 matDef;	//�}�e���A���̈ꎞ�ۑ�
				D3DXMATERIAL *pMat;		//�}�e���A���f�[�^�̃|�C���^

				//���݂̃}�e���A�����擾
				pDevice->GetMaterial(&matDef);

				//�}�e���A���f�[�^�̃|�C���^
				pMat = (D3DXMATERIAL*)g_aSpider[nCntSpider].aModel[nCntParts].pBuffMat->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)g_aSpider[nCntSpider].aModel[nCntParts].pnNumMat; nCntMat++)
				{
					//�}�e���A���̐ݒ�
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					//�e�N�X�`���̐ݒ�
					pDevice->SetTexture(	0,
											g_apTextureEnemy[nCntParts][nCntMat]);

					//���f���p�[�c�̕`��
					g_aSpider[nCntSpider].aModel[nCntParts].pMesh->DrawSubset(nCntMat);
				}
				//�ꎞ�ۑ����Ă�������ǂ�
				pDevice->SetMaterial(&matDef);
			}
		}
	}
}

//---------------------------
//���f���Z�b�g
//---------------------------
void SetSpider(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife, float fMoveSpeed)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	pDevice = GetDevice();		//�f�o�C�X�̎擾

	for (int nCntSpider = 0; nCntSpider < MAX_SPIDER_MODEL; nCntSpider++)
	{
		if (g_aSpider[nCntSpider].bUse == false)
		{
			g_aSpider[nCntSpider].pos = pos;		//�ʒu�̑��
			g_aSpider[nCntSpider].rot = rot;		//�����̑��
			g_aSpider[nCntSpider].nLife = nLife;
			g_aSpider[nCntSpider].fMoveSpeed = fMoveSpeed;

			g_aSpider[nCntSpider].nIdex = SetShadow(D3DXVECTOR3(g_aSpider[nCntSpider].pos.x, 0.0f, g_aSpider[nCntSpider].pos.z), 150.0f, 150.0f);
			g_aSpider[nCntSpider].bUse = true;
			break;
		}
	}
}

void SpiderLooknig(int nCntSpider)
{
	Girl *pGirl;

	pGirl = GetGirl();

	int nSide;
	float fRadius = 10000.0f;
	float fARadius = 50.0f;

	g_aSpider[nCntSpider].posdfrc.x = pGirl->pos.x - g_aSpider[nCntSpider].pos.x; 
	g_aSpider[nCntSpider].posdfrc.z = pGirl->pos.z - g_aSpider[nCntSpider].pos.z;

	g_aSpider[nCntSpider].fAngle = atan2(g_aSpider[nCntSpider].posdfrc.x, g_aSpider[nCntSpider].posdfrc.z);

	g_aSpider[nCntSpider].fLength = sqrtf((g_aSpider[nCntSpider].posdfrc.x * g_aSpider[nCntSpider].posdfrc.x) + (g_aSpider[nCntSpider].posdfrc.z * g_aSpider[nCntSpider].posdfrc.z));

	if (g_aSpider[nCntSpider].fLength < fRadius)
	{
		g_aSpider[nCntSpider].rot.y = g_aSpider[nCntSpider].fAngle + D3DX_PI;

		g_aSpider[nCntSpider].move.x = -sinf(g_aSpider[nCntSpider].rot.y) * g_aSpider[nCntSpider].fMoveSpeed;

		g_aSpider[nCntSpider].move.z = -cosf(g_aSpider[nCntSpider].rot.y) * g_aSpider[nCntSpider].fMoveSpeed;
	}
	else
	{
		g_aSpider[nCntSpider].move.x = 0.0f;
							
		g_aSpider[nCntSpider].move.z = 0.0f;
	}
	
}

bool CollisionSpider(D3DXVECTOR3 *pos, D3DXVECTOR3 *posold, D3DXVECTOR3 *move, float fWidth, float fHeight, CollisionType nType)
{
	bool bCollision = false;
	D3DXVECTOR3 posdfrc;
	D3DXVECTOR3 efectmove;
	float fAngle;
	float fSpeed = 2.5f;
	float nGuysR = 15.0f;
	float fposdfrcX;

	posdfrc = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	for (int nCntSpider = 0; nCntSpider < MAX_SPIDER_MODEL; nCntSpider++)
	{
		if (g_aSpider[nCntSpider].bUse == true)
		{
			posdfrc.x = g_aSpider[nCntSpider].pos.x - pos->x;
			posdfrc.z = g_aSpider[nCntSpider].pos.z - pos->z;

			posdfrc.x = posdfrc.x * posdfrc.x;
			posdfrc.z = posdfrc.z * posdfrc.z;

			fposdfrcX = posdfrc.x + posdfrc.z;

			fposdfrcX = sqrtf(fposdfrcX);

			if (g_aSpider[nCntSpider].pos.y <= pos->y + fHeight / 2 &&
				g_aSpider[nCntSpider].pos.y + g_aSpider[nCntSpider].fHight >= pos->y - fHeight / 2 &&
				fposdfrcX < nGuysR)
			{
				if (nType == COLLISION_PLAYER)
				{

				}
				else if (nType == COLLISION_BULLET)
				{
					g_aSpider[nCntSpider].nLife--;

					//��x�ɏo�����̗�(nDensity)
					for (int nCntDensity = 0; nCntDensity < 19; nCntDensity++)
					{
						fAngle = CIRCLE;
						D3DXVECTOR3 move = D3DXVECTOR3(sinf(fAngle)* fSpeed, cosf(fAngle) * fSpeed, CIRCLE * 1.5f);

						//��юU��G�t�F�N�g
						SetEffect(g_aSpider[nCntSpider].pos,
							D3DXCOLOR(255, 84, 0, 255),
							D3DXCOLOR(0, 3, 0, 0),
							move,
							10.0,
							10.0,
							0.2,
							0.2,
							3,
							19);
					}


					if (g_aSpider[nCntSpider].nLife <= 0)
					{
						g_aSpider[nCntSpider].bUse = false;
						AddScore(100);
						g_nCntDeth++;
					}
				}
				else if (nType == COLLISION_GIRL)
				{
					g_aSpider[nCntSpider].aState = SPIDER_STATE_ATTACK;
				}
				bCollision = true;
			}
			//�e
			SetPointShadow(g_aSpider[nCntSpider].nIdex, g_aSpider[nCntSpider].pos, 30.0f, 30.0f);
		}
	}
	return bCollision;
}

//---------------------------
//�G������
//---------------------------
Spider *GetSpider(void)
{
	return &g_aSpider[0];
}

int DethCount(void)
{
	return g_nCntDeth;
}

void ResetsDeth(void)
{
	g_nCntDeth = 0;
}

int GetSpidertrue(void)
{
	for (int nCntSpider = 0; nCntSpider < MAX_SPIDER_MODEL; nCntSpider++)
	{
		if (g_aSpider[nCntSpider].bUse == true)
		{
			g_nCounttrue += 1;
		}
	}
	return g_nCounttrue;
}