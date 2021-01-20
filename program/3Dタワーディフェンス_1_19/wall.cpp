//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "wall.h"
#include "camara.h"

//---------------------------
//�O���[�o���ϐ�
//---------------------------
LPDIRECT3DTEXTURE9		g_pTextureWall[MAX_WALL_TEX] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;				//���_�o�b�t�@�ւ̃|�C���^
Wall					g_aWall[MAX_WALL];					//�ǂ̃|�C���^

//---------------------------
//����������
//---------------------------
HRESULT InitWall(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	pDevice = GetDevice();		//�f�o�C�X�̎擾

	//�l�̏�����
	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		g_aWall[nCntWall].pos = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		g_aWall[nCntWall].rot = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		g_aWall[nCntWall].fWidth = WALL_X;
		g_aWall[nCntWall].fHeiht = WALL_Y;
		g_aWall[nCntWall].nType = 0;
		g_aWall[nCntWall].bUse = false;
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/wall_000.jpg",			//�e�N�X�`��
								&g_pTextureWall[0]);
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(	sizeof(VERTEX_3D) * 4 * MAX_WALL,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_3D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffWall,
									NULL);
	//---------------------------
	//���_���
	//---------------------------
	VERTEX_3D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-g_aWall[nCntWall].fWidth, g_aWall[nCntWall].fHeiht, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aWall[nCntWall].fWidth, g_aWall[nCntWall].fHeiht, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-g_aWall[nCntWall].fWidth, -g_aWall[nCntWall].fHeiht, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aWall[nCntWall].fWidth, -g_aWall[nCntWall].fHeiht, 0.0f);

		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;	//���_��i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffWall->Unlock();

	return S_OK;
}

//---------------------------
//�I������
//---------------------------
void UninitWall(void)
{
	//---------------------------
	//�e�N�X�`���j��
	//---------------------------
	for (int nCntWall = 0; nCntWall < MAX_WALL_TEX; nCntWall++)
	{
		if (g_pTextureWall[nCntWall] != NULL)
		{
			g_pTextureWall[nCntWall]->Release();
			g_pTextureWall[nCntWall] = NULL;
		}
	}

	//---------------------------
	//�o�b�t�@�j��
	//---------------------------
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}
}

//---------------------------
//�X�V����
//---------------------------
void UpdateWall(void)
{

}

//---------------------------
//�`�揈��
//---------------------------
void DrawWall(void)
{

	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�̃|�C���^

	pDevice = GetDevice();			//�f�o�C�X���擾����

	//---------------------------
	//�}�g���b�N�X�̐ݒ�
	//---------------------------
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_aWall[nCntWall].bUse == true)
		{
			//�J�����O�L
			pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

			pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

			//�}�g���b�N�X������
			D3DXMatrixIdentity(&g_aWall[nCntWall].mtxWold);

			//�X�P�[��
			g_aWall[nCntWall].mtxWold._11 = g_aWall[nCntWall].fWidth;
			g_aWall[nCntWall].mtxWold._22 = g_aWall[nCntWall].fHeiht;

			//�����̐ݒ�
			D3DXMatrixRotationYawPitchRoll(	&mtxRot,
											g_aWall[nCntWall].rot.y,
											g_aWall[nCntWall].rot.x,
											g_aWall[nCntWall].rot.z);

			D3DXMatrixMultiply(	&g_aWall[nCntWall].mtxWold,
								&g_aWall[nCntWall].mtxWold,
								&mtxRot);
			//�ʒu
			D3DXMatrixTranslation(	&mtxTrans,
									g_aWall[nCntWall].pos.x,
									g_aWall[nCntWall].pos.y,
									g_aWall[nCntWall].pos.z);
													  
			D3DXMatrixMultiply(	&g_aWall[nCntWall].mtxWold,
								&g_aWall[nCntWall].mtxWold,
								&mtxTrans);
			//�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(	D3DTS_WORLD,
									&g_aWall[nCntWall].mtxWold);
			//---------------------------
			//�`�揈��
			//---------------------------
			//�o�b�t�@�̐ݒ���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(	0,
										g_pVtxBuffWall,
										0,
										sizeof(VERTEX_3D));
			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(	0,
									g_pTextureWall[g_aWall[nCntWall].nType]);
			//�|���S���̕`��
			pDevice->DrawPrimitive(	D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
									nCntWall * 4,			//���Ԗڂ���`�悷�邩
									2);						//���̐�
		}
	}
}

//---------------------------
//�Z�b�g
//---------------------------
void SetWall(D3DXVECTOR3 rot, D3DXVECTOR3 pos, float fWith, float fHeight, int nType)
{
	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_aWall[nCntWall].bUse == false)
		{
			g_aWall[nCntWall].rot = rot;		//����������
			g_aWall[nCntWall].pos = pos;		//�ʒu������
			g_aWall[nCntWall].fWidth = fWith;	//��������
			g_aWall[nCntWall].fHeiht = fHeight;	//����������
			g_aWall[nCntWall].nType = nType;	//��ނ�����

			g_aWall[nCntWall].bUse = true;		//�g���Ă�
			break;
		}
	}
}

//---------------------------
//�ǂ̓����蔻��
//---------------------------
bool ColisionWall(D3DXVECTOR3 *pos, D3DXVECTOR3 *posold, D3DXVECTOR3 *move, float fWidth, float fHeight, float fDepht, int nType)
{
	bool bLand = false;	//�ǂɂ��Ă邩
	Wall *pWall;
	Camera *pCamera;

	pWall = GetWall();
	pCamera = GetCamera();

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++, pWall++)
	{
		if (pWall->bUse == true)
		{
			if (pos->x <= pWall->pos.x + pWall->fWidth / 2 &&
				pos->x >= pWall->pos.x - pWall->fWidth / 2 &&
				pos->y <= pWall->pos.y + pWall->fHeiht / 2 &&
				pos->y >= pWall->pos.y - pWall->fHeiht / 2)
			{
				if (pWall->rot.y == 0.0f)
				{
					if (posold->z + fDepht <= pWall->pos.z &&
						pos->z + fDepht >= pWall->pos.z)
					{
						pCamera->PosV.z = pWall->pos.z - (fDepht + 0.1f);	//�ǂɍ��킹��
						bLand = true;			//�ǂɂ��Ă�
					}
				}
				else if (pWall->rot.y == -D3DX_PI)
				{
					if (posold->z - fDepht >= pWall->pos.z &&
						pos->z - fDepht <= pWall->pos.z)
					{
						pCamera->PosV.z = pWall->pos.z + (fDepht + 0.1f);	//�ǂɍ��킹��
						bLand = true;			//�ǂɂ��Ă�
					}
				}
			}
			else if (pos->z <= pWall->pos.z + pWall->fWidth / 2 &&
					 pos->z >= pWall->pos.z - pWall->fWidth / 2 &&
					 pos->y <= pWall->pos.y + pWall->fHeiht / 2 &&
					 pos->y >= pWall->pos.y - pWall->fHeiht / 2)
			{
				if (pWall->rot.y == D3DX_PI / 2)
				{
					if (posold->x + fWidth <= pWall->pos.x &&
						pos->x + fWidth >= pWall->pos.x)
					{
						pCamera->PosV.x = pWall->pos.x - (fWidth + 0.1f);	//�ǂɍ��킹��
						bLand = true;			//�ǂɂ��Ă�
					}
				}
				else if (pWall->rot.y == -D3DX_PI)
				{
					if (posold->z - fDepht >= pWall->pos.z &&
						pos->z - fDepht <= pWall->pos.z)
					{
						pCamera->PosV.z = pWall->pos.z + (fDepht + 0.1f);	//�ǂɍ��킹��
						bLand = true;			//�ǂɂ��Ă�
					}
				}
			}
		}
	}
	pWall -= MAX_WALL;

	return bLand;
}

//---------------------------
//�ǂ̏��
//---------------------------
Wall *GetWall(void)
{
	return &g_aWall[0];
}