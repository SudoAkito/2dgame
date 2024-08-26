//------------------------------------------
//
//         �e�̏o�͏���
//       Author:Sudou Akito
//
//------------------------------------------
#include"bullet.h"
#include"explosion.h"

//�}�N����`
#define MAX_EXPLOSION (128)           //�e�̍ő吔
#define EX_WIDTH (50)
#define EX_HEIGHT (50)


//�e�̍\����
typedef struct
{
	D3DXVECTOR3 pos;    //�ʒu
	D3DXVECTOR3 rot;    //�p�x
	D3DXCOLOR col;   //�ړ���
	int nCounterAnim;
	int nPatternAnim;
	bool bUse;          //�g�p���Ă��邩�ǂ���
	float fLengthExplosion;
	float fAngleExplosion;

}Explosion;

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureExplosion = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;
Explosion g_aExplosion[MAX_EXPLOSION];

//------------------------------------------
//�����̏���������
//------------------------------------------
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntExplosion=NULL;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\explosion000.png",
		&g_pTextureExplosion);

	//�e�̏�����
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

		//�Ίp���̒������Z�o����
		g_aExplosion[nCntExplosion].fLengthExplosion = sqrtf(EX_WIDTH * EX_WIDTH + EX_HEIGHT * EX_HEIGHT) / 2.0f;
		//�Ίp���̊p�x���Z�o����
		g_aExplosion[nCntExplosion].fAngleExplosion = atan2f(EX_WIDTH, EX_HEIGHT);

		g_aExplosion[nCntExplosion].nCounterAnim= 0;
		g_aExplosion[nCntExplosion].nPatternAnim = 0;
		g_aExplosion[nCntExplosion].bUse = false;   //�g�p���Ă��Ȃ���Ԃɂ���

	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4*MAX_EXPLOSION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL);

	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���Ē��_���ւ̃|�C���^���擾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
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
		pVtx[0].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);

		pVtx += 4;          //���_�f�[�^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffExplosion->Unlock();
}

//------------------------------------------
//�����̏I������
//------------------------------------------
void UninitExplosion(void)
{

	//�e�N�X�`���̔j��
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}
}

//------------------------------------------
//�����̍X�V����
//------------------------------------------
void UpdateExplosion(void)
{
	VERTEX_2D* pVtx;
	int nCntExplosion;
	//���_�o�b�t�@�����b�N���Ē��_���ւ̃|�C���^���擾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{ //�e���g�p����Ă���
			g_aExplosion[nCntExplosion].nCounterAnim++;

			if ((g_aExplosion[nCntExplosion].nCounterAnim % 10) == 0)
			{
				g_aExplosion[nCntExplosion].nCounterAnim = 0;
				g_aExplosion[nCntExplosion].nPatternAnim = (g_aExplosion[nCntExplosion].nPatternAnim + 1) % 10;

				if (g_aExplosion[nCntExplosion].nPatternAnim >= 8)    //���p�^�[�������߂����ꍇ
				{
					g_aExplosion[nCntExplosion].bUse=false;  //�g�p���Ă��Ȃ���Ԃɂ���
				}

				//�e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.125f * g_aExplosion[nCntExplosion].nPatternAnim, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.125f + 0.125f * g_aExplosion[nCntExplosion].nPatternAnim, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.125f * g_aExplosion[nCntExplosion].nPatternAnim, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.125f + 0.125f * g_aExplosion[nCntExplosion].nPatternAnim, 1.0f);
			}
		}
		pVtx += 4;          //���_�f�[�^��4���i�߂�
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffExplosion->Unlock();
}

//------------------------------------------
//�����̕`�揈��
//------------------------------------------
void DrawExplosion(void) 
{
	VERTEX_2D* pVtx;
	int nCntExplosion;

	LPDIRECT3DDEVICE9 pDevice;   //�f�o�C�X�ւ̃|�C���^
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		pDevice->SetTexture(0, g_pTextureExplosion);
		if (g_aExplosion[nCntExplosion].bUse == true)
		{
			//�e���g�p����Ă���
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,4*nCntExplosion,2);
		}
	}
}

//------------------------------------------
//�����̐ݒ菈��
//------------------------------------------
void SetExplosion(D3DXVECTOR3 pos,D3DXCOLOR col, D3DXVECTOR3 rot,float fLength)
{
	VERTEX_2D* pVtx;
	int nCntExplosion;


	//���_�o�b�t�@�����b�N���Ē��_���ւ̃|�C���^���擾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == false)
		{

			g_aExplosion[nCntExplosion].pos = pos;
			g_aExplosion[nCntExplosion].rot = rot;

			pVtx[0].pos.x = g_aExplosion[nCntExplosion].pos.x + sinf(g_aExplosion[nCntExplosion].rot.z - (D3DX_PI - g_aExplosion[nCntExplosion].fAngleExplosion)) * (g_aExplosion[nCntExplosion].fLengthExplosion );
			pVtx[0].pos.y = g_aExplosion[nCntExplosion].pos.y + cosf(g_aExplosion[nCntExplosion].rot.z - (D3DX_PI - g_aExplosion[nCntExplosion].fAngleExplosion)) * (g_aExplosion[nCntExplosion].fLengthExplosion );
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = g_aExplosion[nCntExplosion].pos.x + sinf(g_aExplosion[nCntExplosion].rot.z + (D3DX_PI - g_aExplosion[nCntExplosion].fAngleExplosion)) * (g_aExplosion[nCntExplosion].fLengthExplosion );
			pVtx[1].pos.y = g_aExplosion[nCntExplosion].pos.y + cosf(g_aExplosion[nCntExplosion].rot.z + (D3DX_PI - g_aExplosion[nCntExplosion].fAngleExplosion)) * (g_aExplosion[nCntExplosion].fLengthExplosion);
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = g_aExplosion[nCntExplosion].pos.x + sinf(g_aExplosion[nCntExplosion].rot.z + (0.0f - g_aExplosion[nCntExplosion].fAngleExplosion)) * (g_aExplosion[nCntExplosion].fLengthExplosion);
			pVtx[2].pos.y = g_aExplosion[nCntExplosion].pos.y + cosf(g_aExplosion[nCntExplosion].rot.z + (0.0f - g_aExplosion[nCntExplosion].fAngleExplosion)) * (g_aExplosion[nCntExplosion].fLengthExplosion);
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = g_aExplosion[nCntExplosion].pos.x + sinf(g_aExplosion[nCntExplosion].rot.z - (0.0f - g_aExplosion[nCntExplosion].fAngleExplosion)) * (g_aExplosion[nCntExplosion].fLengthExplosion);
			pVtx[3].pos.y = g_aExplosion[nCntExplosion].pos.y + cosf(g_aExplosion[nCntExplosion].rot.z - (0.0f - g_aExplosion[nCntExplosion].fAngleExplosion)) * (g_aExplosion[nCntExplosion].fLengthExplosion);
			pVtx[3].pos.z = 0.0f;

			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			g_aExplosion[nCntExplosion].col = col;
			g_aExplosion[nCntExplosion].bUse = true;//�g�p���Ă��Ԃɂ���
			break;
		}
		pVtx += 4;

	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffExplosion->Unlock();
}