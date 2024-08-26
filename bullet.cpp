 //------------------------------------------
//
//         �e�̏o�͏���
//       Author:Sudou Akito
//
//------------------------------------------
#include"bullet.h"
#include"player.h"
#include"explosion.h"
#include"enemy.h"
#include"effect.h"

//�}�N����`
#define MAX_BULLET (128)           //�e�̍ő吔
#define BULLET_WIDTH (150)
#define BULLET_HEIGHT (150)

//�e�̍\����
typedef struct
{
	D3DXVECTOR3 pos;    //�ʒu
	D3DXVECTOR3 move;   //�ړ���
	D3DXVECTOR3 rot;    //�p�x
	int nLife;          //����
	BULLETTYPE type;
	float fLengthBullet;
	float fAngleBullet;
	bool bUse;          //�g�p���Ă��邩�ǂ���
}Bullet;

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;
Bullet g_aBullet[MAX_BULLET];

//------------------------------------------
//�e�̏���������
//------------------------------------------
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bullet000.png",
		&g_pTextureBullet);

	//�e�̏�����
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nLife = 150;
		g_aBullet[nCntBullet].bUse = false;   //�g�p���Ă��Ȃ���Ԃɂ���

		//�Ίp���̒������Z�o����
		g_aBullet[nCntBullet].fLengthBullet = sqrtf(BULLET_WIDTH * BULLET_WIDTH + BULLET_HEIGHT * BULLET_HEIGHT) / 2.0f;
		//�Ίp���̊p�x���Z�o����
		g_aBullet[nCntBullet].fAngleBullet = atan2f(BULLET_WIDTH, BULLET_HEIGHT);
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4*MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���Ē��_���ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
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
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;          //���_�f�[�^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();
}

//------------------------------------------
//�v���C���[�̏I������
//------------------------------------------
void UninitBullet(void)
{

	//�e�N�X�`���̔j��
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//------------------------------------------
//�e�̍X�V����
//------------------------------------------
void UpdateBullet(void)
{
	VERTEX_2D* pVtx;
	int nCntbullet;
	//���_�o�b�t�@�����b�N���Ē��_���ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntbullet = 0; nCntbullet < MAX_BULLET; nCntbullet++)
	{
		if (g_aBullet[nCntbullet].bUse == true)
		{ 
			SetEffect(g_aBullet[nCntbullet].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),50.0f,g_aBullet[nCntbullet].fAngleBullet ,50);
		
			if (g_aBullet[nCntbullet].type == BULLETTYPE_PLAYER)
			{
				//�e���g�p����Ă���
					Enemy * pEnemy = GetEnemy();      //�G�̃|�C���^
					int nCntEn;

				if (pEnemy->bUse == true)
				{

					for (nCntEn = 0; nCntEn < MAX_ENEMY; nCntEn++, pEnemy++)
					{

						//�G���g�p����Ă���

						if (g_aBullet[nCntbullet].pos.x <= pEnemy->pos.x + MAX_WIDTH * 0.5f
							&& g_aBullet[nCntbullet].pos.x >= pEnemy->pos.x - MAX_WIDTH * 0.5f
							&& g_aBullet[nCntbullet].pos.y <= pEnemy->pos.y + MAX_HEIGHT * 0.5f
							&& g_aBullet[nCntbullet].pos.y >= pEnemy->pos.y - MAX_HEIGHT * 0.5f)
						{
							//�G�̃q�b�g����
							HitEnemy(nCntEn, 1);
							g_aBullet[nCntbullet].bUse = false;      //�g�p���ĂȂ����
						}

					}
				}
			}
			else if (g_aBullet[nCntbullet].type == BULLETTYPE_ENEMY)
			{  //�G�̒e
				//�v���C���[�̎擾
				Player* pPlayer = GetPlayer();

				if (pPlayer->bDisp == true)
				{
					//�v���C���[�Ƃ̓����蔻��
					if (g_aBullet[nCntbullet].pos.x <= pPlayer->pos.x + MAX_WIDTH * 0.5f
						&& g_aBullet[nCntbullet].pos.x >= pPlayer->pos.x - MAX_WIDTH * 0.5f
						&& g_aBullet[nCntbullet].pos.y <= pPlayer->pos.y + MAX_HEIGHT * 0.5f
						&& g_aBullet[nCntbullet].pos.y >= pPlayer->pos.y - MAX_HEIGHT * 0.5f)
					{
						HitPlayer(1);
						SetExplosion(g_aBullet[nCntbullet].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), g_aBullet[nCntbullet].rot, g_aBullet[nCntbullet].fLengthBullet);
						g_aBullet[nCntbullet].bUse = false;      //�g�p���ĂȂ����
					}
				}

			}

			//�ʒu���X�V
			g_aBullet[nCntbullet].pos.x+= g_aBullet[nCntbullet].move.x;
			g_aBullet[nCntbullet].pos.y += g_aBullet[nCntbullet].move.y;


			//���_���W�̍X�V
			pVtx[0].pos.x = g_aBullet[nCntbullet].pos.x + sinf(g_aBullet[nCntbullet].rot.z - (D3DX_PI - g_aBullet[nCntbullet].fAngleBullet)) * (g_aBullet[nCntbullet].fLengthBullet / 5);
			pVtx[0].pos.y = g_aBullet[nCntbullet].pos.y + cosf(g_aBullet[nCntbullet].rot.z - (D3DX_PI - g_aBullet[nCntbullet].fAngleBullet)) * (g_aBullet[nCntbullet].fLengthBullet / 5);
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = g_aBullet[nCntbullet].pos.x + sinf(g_aBullet[nCntbullet].rot.z + (D3DX_PI - g_aBullet[nCntbullet].fAngleBullet)) * (g_aBullet[nCntbullet].fLengthBullet / 5);
			pVtx[1].pos.y = g_aBullet[nCntbullet].pos.y + cosf(g_aBullet[nCntbullet].rot.z + (D3DX_PI - g_aBullet[nCntbullet].fAngleBullet)) * (g_aBullet[nCntbullet].fLengthBullet / 5);
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = g_aBullet[nCntbullet].pos.x + sinf(g_aBullet[nCntbullet].rot.z + (0.0f - g_aBullet[nCntbullet].fAngleBullet)) * (g_aBullet[nCntbullet].fLengthBullet / 5);
			pVtx[2].pos.y = g_aBullet[nCntbullet].pos.y + cosf(g_aBullet[nCntbullet].rot.z + (0.0f - g_aBullet[nCntbullet].fAngleBullet)) * (g_aBullet[nCntbullet].fLengthBullet / 5);
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = g_aBullet[nCntbullet].pos.x + sinf(g_aBullet[nCntbullet].rot.z - (0.0f - g_aBullet[nCntbullet].fAngleBullet)) * (g_aBullet[nCntbullet].fLengthBullet / 5);
			pVtx[3].pos.y = g_aBullet[nCntbullet].pos.y + cosf(g_aBullet[nCntbullet].rot.z - (0.0f - g_aBullet[nCntbullet].fAngleBullet)) * (g_aBullet[nCntbullet].fLengthBullet / 5);
			pVtx[3].pos.z = 0.0f;

			g_aBullet[nCntbullet].nLife--; 

			//���_���W�̐ݒ�
			if (g_aBullet[nCntbullet].pos.x <= 0.0f || g_aBullet[nCntbullet].pos.x >= SCREEN_WIDTH
				|| g_aBullet[nCntbullet].pos.y <= 0.0f || g_aBullet[nCntbullet].pos.y >= SCREEN_HEIGHT)//�e����ʊO�ɂł�

			{
				g_aBullet[nCntbullet].bUse = false;   //�g�p���ĂȂ���Ԃɂ���

			}
			if (g_aBullet[nCntbullet].nLife<=0)
			{
				g_aBullet[nCntbullet].bUse = false;   //�g�p���ĂȂ���Ԃɂ���

				//�����̐ݒ�
				SetExplosion(g_aBullet[nCntbullet].pos,D3DXCOLOR(1.0f,1.0f,1.0f,1.0),g_aBullet[nCntbullet].rot,g_aBullet[nCntbullet].fLengthBullet);
				
			}
		}
		
		pVtx += 4;          //���_�f�[�^��4���i�߂�
	}
	//���_�o�b�t�@�����b�N���Ē��_���ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);
}

//------------------------------------------
//�e�̕`�揈��
//------------------------------------------
void DrawBullet(void) 
{
	VERTEX_2D* pVtx;
	int nCntBullet;

	LPDIRECT3DDEVICE9 pDevice;   //�f�o�C�X�ւ̃|�C���^
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			//�e���g�p����Ă���
			//�|���S���̕`��
			pDevice->SetTexture(0, g_pTextureBullet);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,4*nCntBullet,2);
		}
	}
}

//------------------------------------------
//�e�̐ݒ菈��
//------------------------------------------
void SetBullet(D3DXVECTOR3 pos,D3DXVECTOR3 move ,D3DXVECTOR3 rot, float fLength, int nLife, BULLETTYPE type)
{
	VERTEX_2D* pVtx;
	int nCntbullet;


	//���_�o�b�t�@�����b�N���Ē��_���ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntbullet = 0; nCntbullet < MAX_BULLET; nCntbullet++)
	{
		if (g_aBullet[nCntbullet].bUse == false)
		{

			g_aBullet[nCntbullet].pos = pos;
			g_aBullet[nCntbullet].move = move;
			g_aBullet[nCntbullet].rot = rot;
			g_aBullet[nCntbullet].bUse = false;
			g_aBullet[nCntbullet].type = type;

			pVtx[0].pos.x = g_aBullet[nCntbullet].pos.x + sinf(g_aBullet[nCntbullet].rot.z - (D3DX_PI - g_aBullet[nCntbullet].fAngleBullet)) * (g_aBullet[nCntbullet].fLengthBullet / 5);
			pVtx[0].pos.y = g_aBullet[nCntbullet].pos.y + cosf(g_aBullet[nCntbullet].rot.z - (D3DX_PI - g_aBullet[nCntbullet].fAngleBullet)) * (g_aBullet[nCntbullet].fLengthBullet / 5);
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = g_aBullet[nCntbullet].pos.x + sinf(g_aBullet[nCntbullet].rot.z + (D3DX_PI - g_aBullet[nCntbullet].fAngleBullet)) * (g_aBullet[nCntbullet].fLengthBullet / 5);
			pVtx[1].pos.y = g_aBullet[nCntbullet].pos.y + cosf(g_aBullet[nCntbullet].rot.z + (D3DX_PI - g_aBullet[nCntbullet].fAngleBullet)) * (g_aBullet[nCntbullet].fLengthBullet / 5);
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = g_aBullet[nCntbullet].pos.x + sinf(g_aBullet[nCntbullet].rot.z + (0.0f - g_aBullet[nCntbullet].fAngleBullet)) * (g_aBullet[nCntbullet].fLengthBullet / 5);
			pVtx[2].pos.y = g_aBullet[nCntbullet].pos.y + cosf(g_aBullet[nCntbullet].rot.z + (0.0f - g_aBullet[nCntbullet].fAngleBullet)) * (g_aBullet[nCntbullet].fLengthBullet / 5);
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = g_aBullet[nCntbullet].pos.x + sinf(g_aBullet[nCntbullet].rot.z - (0.0f - g_aBullet[nCntbullet].fAngleBullet)) * (g_aBullet[nCntbullet].fLengthBullet / 5);
			pVtx[3].pos.y = g_aBullet[nCntbullet].pos.y + cosf(g_aBullet[nCntbullet].rot.z - (0.0f - g_aBullet[nCntbullet].fAngleBullet)) * (g_aBullet[nCntbullet].fLengthBullet / 5);
			pVtx[3].pos.z = 0.0f;

			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			g_aBullet[nCntbullet].move = move;
			g_aBullet[nCntbullet].nLife = 150;
			g_aBullet[nCntbullet].bUse = true;//�g�p���Ă��Ԃɂ���
			break;
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();
}