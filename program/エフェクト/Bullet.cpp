#include "main.h"
#include "bullet.h"
#include "Model.h"
#include "camera.h"
#include "Object.h"
#include "Effect.h"
#include "wall.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureBullet[BULLETTYPE_MAX] = {};//�e�N�X�`���ւ̃|�C���^

//���_�o�b�t�@�̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL; //���_�o�b�t�@�ւ̃|�C���^

Bullet g_aBullet[MAX_BULLET];

//����������
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�̃|�C���^
	int nCntBullet;
	pDevice = GetDevice();//�f�o�C�X�̎擾

	//�e�̏�����
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		g_aBullet[nCntBullet].bUse = false;
		g_aBullet[nCntBullet].nlife = 0;
		g_aBullet[nCntBullet].ntype = 0;
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "date/TEXTURE/�͂�.png", &g_pTextureBullet[BULLETTYPE_PLAYER]);


	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BULLET, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffBullet, NULL);

	VERTEX_3D*pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);


	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//���_�̍��W
		pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - (MAX_BULLET_SIZE_X / 2), g_aBullet[nCntBullet].pos.y + (MAX_BULLET_SIZE_Y / 2), g_aBullet[nCntBullet].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + (MAX_BULLET_SIZE_X / 2), g_aBullet[nCntBullet].pos.y + (MAX_BULLET_SIZE_Y / 2), g_aBullet[nCntBullet].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - (MAX_BULLET_SIZE_X / 2), g_aBullet[nCntBullet].pos.y, g_aBullet[nCntBullet].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + (MAX_BULLET_SIZE_X / 2), g_aBullet[nCntBullet].pos.y, g_aBullet[nCntBullet].pos.z);

		//�x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���_�̐F
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`����UV���W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}


	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBullet->Unlock();
}

//�I������
void UninitBullet(void)
{
	int nCntBullet;
	for (nCntBullet = 0; nCntBullet == BULLETTYPE_MAX; nCntBullet++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureBullet[nCntBullet] != NULL)
		{
			g_pTextureBullet[nCntBullet]->Release();
			g_pTextureBullet[nCntBullet] = NULL;
		}

		//���_�o�b�t�@���j��
		if (g_pVtxBuffBullet != NULL)
		{
			g_pVtxBuffBullet->Release();
			g_pVtxBuffBullet = NULL;
		}
	}
}

//�X�V����
void UpdateBullet(void)
{
	int nCntBullet;
	Object * pObject = GetObject();

	Wall * pWall = GetWall();

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			g_aBullet[nCntBullet].pos.x += sinf(g_aBullet[nCntBullet].rot.y) * 6;
			g_aBullet[nCntBullet].pos.z += cosf(g_aBullet[nCntBullet].rot.y) * 6;
			g_aBullet[nCntBullet].pos.y += tanf(g_aBullet[nCntBullet].rot.x) * 6;

			g_aBullet[nCntBullet].nlife--;

			//�I�u�W�F�N�g�ƒe�̓����蔻��
			for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
			{
				if (pObject[nCntObject].bUse == true)
				{
					if (g_aBullet[nCntBullet].pos.x >= pObject[nCntObject].pos.x + (pObject[nCntObject].VtxMinObject.x) && g_aBullet[nCntBullet].pos.x <= pObject[nCntObject].pos.x + (pObject[nCntObject].VtxMaxObject.x) &&
						g_aBullet[nCntBullet].pos.y >= pObject[nCntObject].pos.y + (pObject[nCntObject].VtxMinObject.y) && g_aBullet[nCntBullet].pos.y <= pObject[nCntObject].pos.y + (pObject[nCntObject].VtxMaxObject.y) &&
						g_aBullet[nCntBullet].pos.z >= pObject[nCntObject].pos.z + (pObject[nCntObject].VtxMinObject.z) && g_aBullet[nCntBullet].pos.z <= pObject[nCntObject].pos.z + (pObject[nCntObject].VtxMaxObject.z))
					{
						g_aBullet[nCntBullet].bUse = false;
					}
				}
			}
			/*for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
			{
				if (pWall[nCntWall].bUse == true)
				{
					if (g_aBullet[nCntBullet].pos.x > pWall[nCntWall].pos.x - (pWall[nCntWall].fWhidth) &&
						g_aBullet[nCntBullet].pos.x < pWall[nCntWall].pos.x + (pWall[nCntWall].fWhidth)&&
						g_aBullet[nCntBullet].pos.y > pWall[nCntWall].pos.y - (pWall[nCntWall].fHight) &&
						g_aBullet[nCntBullet].pos.y < pWall[nCntWall].pos.y + (pWall[nCntWall].fHight))
					{
						
						g_aBullet[nCntBullet].bUse = false;
					}
				}
			}*/

			SetEffect(g_aBullet[nCntBullet].pos, D3DXCOLOR(255, 0, 255, 255), 8, 8, EFFECTTYPE_PLAYER, 7);

			//�˒����O�ɂȂ��������
			if (g_aBullet[nCntBullet].nlife <= 0)
			{
				g_aBullet[nCntBullet].bUse = false;
			}
		}

	}

}

//�`�揈��
void DrawBullet(void)
{
	int nCntBullet;
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxView;
	D3DXMATRIX mtxTrans;
	pDevice = GetDevice();//�f�o�C�X���擾����

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			//Z�e�X�g�֌W
			/*pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);*/

			//�A���t�@�e�X�g�֌W
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

			//�}�g���b�N�X������
			D3DXMatrixIdentity(&g_aBullet[nCntBullet].mtxWorld);
			//�r���[�}�g���b�N�X�̎擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�|���S�����J�����ɑ΂��Đ��ʂ�
			D3DXMatrixInverse(&g_aBullet[nCntBullet].mtxWorld, NULL, &mtxView);

			g_aBullet[nCntBullet].mtxWorld._41 = 0.0f;
			g_aBullet[nCntBullet].mtxWorld._42 = 0.0f;
			g_aBullet[nCntBullet].mtxWorld._43 = 0.0f;

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aBullet[nCntBullet].pos.x, g_aBullet[nCntBullet].pos.y, g_aBullet[nCntBullet].pos.z);
			D3DXMatrixMultiply(&g_aBullet[nCntBullet].mtxWorld, &g_aBullet[nCntBullet].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aBullet[nCntBullet].mtxWorld);

			//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));

			pDevice->SetFVF(FVF_VERTEX_3D);//���_�t�H�[�}�b�g�̐ݒ�

			pDevice->SetTexture(0, g_pTextureBullet[0]);//�e�N�X�`���̐ݒ�

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBullet * 4, 2);

			//Z�e�X�g�֌W
			/*pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);*/

			//�A���t�@�e�X�g�֌W
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);
		}

	}
}

//�e�̐ݒ菈��
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int ntype)
{
	int nCntBullet;


	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{
			g_aBullet[nCntBullet].pos = pos;
			g_aBullet[nCntBullet].ntype = ntype;

			g_aBullet[nCntBullet].rot = rot;
			g_aBullet[nCntBullet].nlife = 100;
			g_aBullet[nCntBullet].bUse = true;

			break;
		}
		
	}
}

Bullet *GetBullet(void)
{
	return &g_aBullet[0];
}