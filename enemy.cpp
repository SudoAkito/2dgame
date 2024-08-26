//------------------------------------------
//
//			   �G����
//         Author:Sudou Akito
//
//------------------------------------------

#include"bullet.h"
#include"enemy.h"
#include"explosion.h"

//�}�N����`
#define NUM_ENEMY (1)                 //�G�̎��

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTextureEnemy[NUM_ENEMY] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;
Enemy g_aEnemy[MAX_ENEMY];      //�G�̏��
int g_nNumEnemy = 0;            //�G�̑���

//------------------------------------------
//�G�̏���������
//------------------------------------------
void InitEnemy(void)
{

	int nCntEN{};

	LPDIRECT3DDEVICE9 pDevice;   //�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\enemy1.png",
		&g_apTextureEnemy[0]);

	//�G�̏�����
	for (nCntEN = 0; nCntEN <MAX_ENEMY ; nCntEN++)
	{
		g_aEnemy[nCntEN].pos= D3DXVECTOR3(0.0f,0.0f,0.0f);
		g_aEnemy[nCntEN].move= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEN].rot= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEN].state = {};
		g_aEnemy[nCntEN].nCounterState=0;
		g_aEnemy[nCntEN].nLife=0;
		g_aEnemy[nCntEN].nunti = 0;
		g_aEnemy[nCntEN].nType=0;
		g_aEnemy[nCntEN].bUse=false;
		g_aEnemy[nCntEN].fLength=0;
		g_aEnemy[nCntEN].fAngle = 0;
	}
	g_nNumEnemy = 0;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4*MAX_ENEMY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy,
		NULL);

	VERTEX_2D* pVtx;        //���_���̃|�C���^

//���_�o�b�t�@�����b�N���Ē��_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEN = 0; nCntEN < MAX_ENEMY; nCntEN++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f); 
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
}

//------------------------------------------
//�G�̏I������
//------------------------------------------
void UninitEnemy(void)
{
	int nCntEN;

	//�e�N�X�`���̔j��
	for (nCntEN = 0; nCntEN < NUM_ENEMY; nCntEN++)
	{
		if (g_apTextureEnemy[nCntEN] != NULL)
		{
			g_apTextureEnemy[nCntEN]->Release();
			g_apTextureEnemy[nCntEN] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
}

//------------------------------------------
// �G�̍X�V����
//------------------------------------------
void UpdateEnemy(void)
{
	int nCntEN{};

	VERTEX_2D* pVtx;        //���_���̃|�C���^


	//�g�p����Ă���G���e��������
	for (nCntEN = 0; nCntEN < MAX_ENEMY; nCntEN++)
	{
		if (g_aEnemy[nCntEN].bUse == true)
		{
			switch (g_aEnemy[nCntEN].state)
			{
			case ENEMYSTATE_NORMAL:
				g_aEnemy[nCntEN].nunti++;
				if (g_aEnemy[nCntEN].nunti >= 30)
				{
					SetBullet(g_aEnemy[nCntEN].pos, D3DXVECTOR3(sinf(g_aEnemy[nCntEN].rot.z + D3DX_PI) * MAX_SPEED, cosf(g_aEnemy[nCntEN].rot.z + D3DX_PI) * MAX_SPEED, 0.0f), g_aEnemy[nCntEN].rot, g_aEnemy[nCntEN].fLength, 150, BULLETTYPE_ENEMY);
					g_aEnemy[nCntEN].nunti = 0;
				}
				break;

			case ENEMYSTATE_DAMAGE:

				//���_�o�b�t�@�����b�N���Ē��_���ւ̃|�C���^���擾
				g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

				g_aEnemy[nCntEN].nCounterState--;
				if (g_aEnemy[nCntEN].nCounterState <= 0)
				{
					g_aEnemy[nCntEN].state = ENEMYSTATE_NORMAL;
					//���_�J���[�̐ݒ�
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				}
				break;
				//���_�o�b�t�@���A�����b�N����
				g_pVtxBuffEnemy->Unlock();
			}
		}
	}
}

//------------------------------------------
// �G�̕`�揈��
//------------------------------------------
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;   //�f�o�C�X�ւ̃|�C���^
	int nCntEN;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�t�H�[�}�b�g�̐ݒ�
	/*pDevice->SetFVF(FVF_VERTEX_2D);*/

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	for (nCntEN = 0; nCntEN < MAX_ENEMY; nCntEN++)
	{
		if (g_aEnemy[nCntEN].bUse == true)
		{
			int nType = g_aEnemy[nCntEN].nType;
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureEnemy[nCntEN]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,nCntEN*4,2);//�v���~�e�B�u�̎��,�v���~�e�B�u�̐�
		}
	}
}

//------------------------------------------
// �G�̃Z�b�g����
//------------------------------------------
void SetEnemy(D3DXVECTOR3 pos, int nType)
{
	int nCntEN;
	VERTEX_2D* pVtx;        //���_���̃|�C���^

	//���_�o�b�t�@�����b�N���Ē��_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEN = 0; nCntEN < MAX_ENEMY; nCntEN++)
	{
		if(g_aEnemy[nCntEN].bUse == false)
		{//�G���g�p����Ă��Ȃ�

			//�G�̏��̐ݒ�
			g_aEnemy[nCntEN].pos= pos;
			g_aEnemy[nCntEN].state =ENEMYSTATE_NORMAL;
			g_aEnemy[nCntEN].nCounterState=0;//��ԊǗ��J�E���^�[
			g_aEnemy[nCntEN].nLife=10;        //�̗�
			g_aEnemy[nCntEN].nType =nType;
		
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEN].pos.x-MAX_WIDTH * 0.5f, g_aEnemy[nCntEN].pos.y - MAX_HEIGHT * 0.5f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEN].pos.x+MAX_WIDTH * 0.5f, g_aEnemy[nCntEN].pos.y - MAX_HEIGHT * 0.5f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEN].pos.x-MAX_WIDTH * 0.5f, g_aEnemy[nCntEN].pos.y + MAX_HEIGHT * 0.5f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEN].pos.x+MAX_WIDTH * 0.5f, g_aEnemy[nCntEN].pos.y + MAX_HEIGHT * 0.5f, 0.0f);
			g_aEnemy[nCntEN].bUse = true;
			g_nNumEnemy++;
			break;
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
}
//------------------------------------------
//�G�̏��
//------------------------------------------
Enemy* GetEnemy(void)
{
	return &g_aEnemy[0];
}

//------------------------------------------
// �G�̓����蔻��̌㏈��
//------------------------------------------
void HitEnemy(int nCntEn, int nDmg)
{
	VERTEX_2D* pVtx;        //���_���̃|�C���^

	g_aEnemy[nCntEn].nLife -= nDmg;

	//���_�o�b�t�@�����b�N���Ē��_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	if (g_aEnemy[nCntEn].nLife<=0)
	{
		SetExplosion(g_aEnemy[nCntEn].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), g_aEnemy[nCntEn].rot, g_aEnemy[nCntEn].fLength);
		g_aEnemy[nCntEn].bUse = false;
		g_nNumEnemy--;                //�G�̑����J�E���g�_�E��
	}
	else
	{
		g_aEnemy[nCntEn].state=ENEMYSTATE_DAMAGE;
		g_aEnemy[nCntEn].nCounterState = 5;

		pVtx += 4 * nCntEn;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0 ,255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0 ,0, 255);
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
}

int GetNumEnemy()
{
	return g_nNumEnemy;
}

