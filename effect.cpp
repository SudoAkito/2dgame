//------------------------------------------
//
//         �e�̏o�͏���
//       Author:Sudou Akito
//
//------------------------------------------
#include"Effect.h"
#include"effect.h"

//�}�N����`
#define MAX_EFFECT (4096)  //�G�t�F�N�g�̍ő吔

//�e�̍\����
typedef struct
{
	D3DXVECTOR3 pos; //�ʒu
	D3DXCOLOR col;   //�ړ���
	D3DXVECTOR3 rot;
	float fRadius;   //���a(�傫��)
	float fAngle;
	int nLife;       //����(�\������)
	bool bUse;       //�g�p���Ă��邩�ǂ���
}EFFECT;

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureEffect = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;
EFFECT g_aEffect[MAX_EFFECT];                    //�G�t�F�N�g�̏��

//------------------------------------------
//�G�t�F�N�g�̏���������
//------------------------------------------
void InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEffect = NULL;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\effect000.jpg",
		&g_pTextureEffect);

	//�e�̏�����
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aEffect[nCntEffect].fRadius = 50.0f;
		g_aEffect[nCntEffect].nLife = 50;
		g_aEffect[nCntEffect].bUse = false;   //�g�p���Ă��Ȃ���Ԃɂ���
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL);

	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���Ē��_���ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos.x = 0.0f;
		pVtx[0].pos.y = 0.0f;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = 0.0f;
		pVtx[1].pos.y = 0.0f;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = 0.0f;
		pVtx[2].pos.y = 0.0f;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = 0.0f;
		pVtx[3].pos.y = 0.0f;
		pVtx[3].pos.z = 0.0f;

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;          //���_�f�[�^��4���i�߂�
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();
}

//------------------------------------------
//�G�t�F�N�g�̏I������
//------------------------------------------
void UninitEffect(void)
{

	//�e�N�X�`���̔j��
	if (g_pTextureEffect != NULL)
	{
		g_pTextureEffect->Release();
		g_pTextureEffect = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}

//------------------------------------------
//�G�t�F�N�g�̍X�V����
//------------------------------------------
void UpdateEffect(void)
{
	VERTEX_2D* pVtx;
	int nCntEffect;
	//���_�o�b�t�@�����b�N���Ē��_���ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{

			//���_�J���[�̐ݒ�(�X�V)
			pVtx[0].col = D3DXCOLOR(0.1f, 1.0f, 0.1f, 0.1f);
			pVtx[1].col = D3DXCOLOR(0.1f, 1.0f, 0.1f, 0.1f);
			pVtx[2].col = D3DXCOLOR(0.1f, 1.0f, 0.1f, 0.1f);
			pVtx[3].col = D3DXCOLOR(0.1f, 1.0f, 0.1f, 0.1f);

			////���_���W�̐ݒ�i�X�V�j
			//pVtx[0].pos.x = g_aEffect[nCntEffect].pos.x - g_aEffect[nCntEffect].fRadius;
			//pVtx[0].pos.y = g_aEffect[nCntEffect].pos.y - g_aEffect[nCntEffect].fRadius;
			//pVtx[0].pos.z = 0.0f;

			//pVtx[1].pos.x = g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].fRadius;
			//pVtx[1].pos.y = g_aEffect[nCntEffect].pos.y - g_aEffect[nCntEffect].fRadius;
			//pVtx[1].pos.z = 0.0f;

			//pVtx[2].pos.x = g_aEffect[nCntEffect].pos.x - g_aEffect[nCntEffect].fRadius;
			//pVtx[2].pos.y = g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].fRadius;
			//pVtx[2].pos.z = 0.0f;

			//pVtx[3].pos.x = g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].fRadius;
			//pVtx[3].pos.y = g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].fRadius;
			//pVtx[3].pos.z = 0.0f;
			
			//���_���W�̍X�V
			pVtx[0].pos.x = g_aEffect[nCntEffect].pos.x + sinf(g_aEffect[nCntEffect].rot.z - (D3DX_PI - g_aEffect[nCntEffect].fAngle)) * (g_aEffect[nCntEffect].fRadius);
			pVtx[0].pos.y = g_aEffect[nCntEffect].pos.y + cosf(g_aEffect[nCntEffect].rot.z - (D3DX_PI - g_aEffect[nCntEffect].fAngle)) * (g_aEffect[nCntEffect].fRadius);
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = g_aEffect[nCntEffect].pos.x + sinf(g_aEffect[nCntEffect].rot.z + (D3DX_PI - g_aEffect[nCntEffect].fAngle)) * (g_aEffect[nCntEffect].fRadius);
			pVtx[1].pos.y = g_aEffect[nCntEffect].pos.y + cosf(g_aEffect[nCntEffect].rot.z + (D3DX_PI - g_aEffect[nCntEffect].fAngle)) * (g_aEffect[nCntEffect].fRadius);
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = g_aEffect[nCntEffect].pos.x + sinf(g_aEffect[nCntEffect].rot.z + (0.0f - g_aEffect[nCntEffect].fAngle)) * (g_aEffect[nCntEffect].fRadius);
			pVtx[2].pos.y = g_aEffect[nCntEffect].pos.y + cosf(g_aEffect[nCntEffect].rot.z + (0.0f - g_aEffect[nCntEffect].fAngle)) * (g_aEffect[nCntEffect].fRadius);
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = g_aEffect[nCntEffect].pos.x + sinf(g_aEffect[nCntEffect].rot.z - (0.0f - g_aEffect[nCntEffect].fAngle)) *g_aEffect[nCntEffect].fRadius;
			pVtx[3].pos.y = g_aEffect[nCntEffect].pos.y + cosf(g_aEffect[nCntEffect].rot.z - (0.0f - g_aEffect[nCntEffect].fAngle)) *g_aEffect[nCntEffect].fRadius;
			pVtx[3].pos.z = 0.0f;

			g_aEffect[nCntEffect].nLife--;
			g_aEffect[nCntEffect].fRadius --;

			if(g_aEffect[nCntEffect].nLife <= 0)
			{
				g_aEffect[nCntEffect].bUse=false;
			}
		}
		pVtx += 4;          //���_�f�[�^��4���i�߂�
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();
}

//------------------------------------------
//�G�t�F�N�g�̕`�揈��
//------------------------------------------
void DrawEffect(void)
{
	VERTEX_2D* pVtx;
	int nCntEffect;

	LPDIRECT3DDEVICE9 pDevice;   //�f�o�C�X�ւ̃|�C���^
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);  //�u�����h���@
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		pDevice->SetTexture(0, g_pTextureEffect);
		if (g_aEffect[nCntEffect].bUse == true)
		{
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntEffect, 2);
		}
	}

	//���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//------------------------------------------
//�G�t�F�N�g�̐ݒ菈��
//------------------------------------------
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadius,float fAngle, int nLife)
{
	VERTEX_2D* pVtx;
	int nCntEffect;


	//���_�o�b�t�@�����b�N���Ē��_���ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == false)
		{
			g_aEffect[nCntEffect].pos = pos;
			g_aEffect[nCntEffect].col = col;
			g_aEffect[nCntEffect].fRadius = fRadius;
			g_aEffect[nCntEffect].fAngle = fAngle;
			g_aEffect[nCntEffect].nLife = nLife;
			g_aEffect[nCntEffect].bUse = true;//�g�p���Ă��Ԃɂ���


		//���_���W�̐ݒ�i�X�V�j
			pVtx[0].pos.x = g_aEffect[nCntEffect].pos.x + sinf(g_aEffect[nCntEffect].rot.z - (D3DX_PI - g_aEffect[nCntEffect].fAngle)) * (g_aEffect[nCntEffect].fRadius);
			pVtx[0].pos.y = g_aEffect[nCntEffect].pos.y + cosf(g_aEffect[nCntEffect].rot.z - (D3DX_PI - g_aEffect[nCntEffect].fAngle)) * (g_aEffect[nCntEffect].fRadius);
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = g_aEffect[nCntEffect].pos.x + sinf(g_aEffect[nCntEffect].rot.z + (D3DX_PI - g_aEffect[nCntEffect].fAngle)) * (g_aEffect[nCntEffect].fRadius);
			pVtx[1].pos.y = g_aEffect[nCntEffect].pos.y + cosf(g_aEffect[nCntEffect].rot.z + (D3DX_PI - g_aEffect[nCntEffect].fAngle)) * (g_aEffect[nCntEffect].fRadius);
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = g_aEffect[nCntEffect].pos.x + sinf(g_aEffect[nCntEffect].rot.z + (0.0f - g_aEffect[nCntEffect].fAngle)) * (g_aEffect[nCntEffect].fRadius);
			pVtx[2].pos.y = g_aEffect[nCntEffect].pos.y + cosf(g_aEffect[nCntEffect].rot.z + (0.0f - g_aEffect[nCntEffect].fAngle)) * (g_aEffect[nCntEffect].fRadius);
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = g_aEffect[nCntEffect].pos.x + sinf(g_aEffect[nCntEffect].rot.z - (0.0f - g_aEffect[nCntEffect].fAngle)) * (g_aEffect[nCntEffect].fRadius);
			pVtx[3].pos.y = g_aEffect[nCntEffect].pos.y + cosf(g_aEffect[nCntEffect].rot.z - (0.0f - g_aEffect[nCntEffect].fAngle)) * (g_aEffect[nCntEffect].fRadius);
			pVtx[3].pos.z = 0.0f;
			break;
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();
}