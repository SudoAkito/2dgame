//------------------------------------------
//
//       �v���C���[����
//       Author:Sudou Akito
//
//------------------------------------------
#include"main.h"
#include"player.h"
#include"background.h"
#include"input.h"
#include"bullet.h"
#include "enemy.h"
#include"explosion.h"



//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer= NULL;

int g_nCounterAnimPlayer;    //�A�j���[�V�����J�E���^�[
int g_nPatternAnimPlayer;    //�A�j���[�V�����p�^�[��NO.

Player g_player;

//------------------------------------------
//�v���C���[����������
//------------------------------------------
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;   //�f�o�C�X�ւ̃|�C���^
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\1901.png",
		&g_pTexturePlayer);

	g_player.pos = D3DXVECTOR3(300.0f, 400.0f, 0.0f);  //�ʒu������
	g_player.move = D3DXVECTOR3(0.0f,0.0f,0.0f);	      //�ړ��ʏ�����
	g_player.rot = D3DXVECTOR3(0.0f,0.0f,0.0f);        //�����̏�����
	g_player.nLife = 100;
	g_player.bDisp = true;
	g_player.state1 = {};

	//�Ίp���̒����̎Z�o
	g_player.fLength = sqrtf(MAX_SIZE*MAX_SIZE+MAX_SIZE*MAX_SIZE) / 2.0f;

	//�Ίp���̊p�x���Z�o
	g_player.fAngle = atan2f(MAX_SIZE, MAX_SIZE);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayer,
		NULL);

	VERTEX_2D* pVtx;       //���_���̃|�C���^

	//���_�o�b�t�@�����b�N���Ē��_���ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos.x = g_player.pos.x + sinf(g_player.rot.z - (-D3DX_PI - g_player.fAngle)) * g_player.fLength;
	pVtx[0].pos.y = g_player.pos.y + cosf(g_player.rot.z - (-D3DX_PI - g_player.fAngle)) * g_player.fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_player.pos.x + sinf(g_player.rot.z + (D3DX_PI - g_player.fAngle)) * g_player.fLength;
	pVtx[1].pos.y = g_player.pos.y + cosf(g_player.rot.z + (D3DX_PI - g_player.fAngle)) * g_player.fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_player.pos.x + sinf(g_player.rot.z + (0.0f - g_player.fAngle)) * g_player.fLength;
	pVtx[2].pos.y = g_player.pos.y + cosf(g_player.rot.z + (0.0f - g_player.fAngle)) * g_player.fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_player.pos.x + sinf(g_player.rot.z - (0.0f - g_player.fAngle)) * g_player.fLength;
	pVtx[3].pos.y = g_player.pos.y + cosf(g_player.rot.z - (0.0f - g_player.fAngle)) * g_player.fLength;
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

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayer->Unlock();
}

//------------------------------------------
//�v���C���[�̏I������
//------------------------------------------
void UninitPlayer(void)
{

	//�e�N�X�`���̔j��
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
}

//------------------------------------------
//�v���C���[�̍X�V����
//------------------------------------------
void UpdatePlayer(void)
{
	VERTEX_2D* pVtx;        //���_���̃|�C���^

	GetKeyPlayer();


	switch (g_player.state1)
	{
	case PLAYERSTATE_NORMAL:

		break;

	case PLAYERSTATE_DAMAGE:

		//���_�o�b�t�@�����b�N���Ē��_���ւ̃|�C���^���擾
		g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

		g_player.nCounterState1--;

		if (g_player.nCounterState1 <= 0)
		{
			g_player.state1 = PLAYERSTATE_NORMAL;

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}
		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffPlayer->Unlock();
		break;

	case PLAYERSTATE_DEATH:
		g_player.nCounterState1--;

		if (g_player.nCounterState1 <= 0)
		{
			//���U���g��ʂɈڍs
			SetMode(MODE_RESULT);

			return;
		}
		break;
	}

	//g_nCounterAnimPlayer++;

	//if ((g_nCounterAnimPlayer%10)==0)
	//{
	//	g_nPatternAnimPlayer=(g_nPatternAnimPlayer+1)%MAX_PLAYPATTERN;   //�p�^�[��No.���X�V����

	//	//���_�o�b�t�@�����b�N���Ē��_���ւ̃|�C���^���擾
	//	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
	//	//�e�N�X�`�����W�̐ݒ�
	//	//��
	//	pVtx[0].tex = D3DXVECTOR2(g_nPatternAnimPlayer * 0.2f, (g_nPatternAnimPlayer / 5) * 0.5f);
	//	pVtx[1].tex = D3DXVECTOR2(fData+g_nPatternAnimPlayer * 0.2f, (g_nPatternAnimPlayer / 5) * 0.5f);
	//	pVtx[2].tex = D3DXVECTOR2(g_nPatternAnimPlayer * 0.2f, (g_nPatternAnimPlayer / 5) * 0.5f + 0.5f);
	//	pVtx[3].tex = D3DXVECTOR2(fData+g_nPatternAnimPlayer * 0.2f, (g_nPatternAnimPlayer / 5) * 0.5f + 0.5f);
	//
	//	//���_�o�b�t�@���A�����b�N����
	//	g_pVtxBuffPlayer->Unlock();
	//}

}

//------------------------------------------
//�v���C���[�̕`�揈��
//------------------------------------------
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;   //�f�o�C�X�ւ̃|�C���^
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	if (g_player.bDisp == true)
	{
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexturePlayer);

	
		//�v���C���[�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);//�v���~�e�B�u�̎��,�v���~�e�B�u�̐�
	}
}
	
//------------------------------------------
// �v���C���[���̎擾
//------------------------------------------
Player* GetPlayer(void)
{
	return &g_player;
}

//------------------------------------------
// �����蔻���̏���
//------------------------------------------
void HitPlayer(int nDmg)
{
	VERTEX_2D* pVtx;//���_���̃|�C���^

	g_player.nLife -= nDmg;
	//���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
	if (g_player.nLife <= 0)
	{
		SetExplosion(g_player.pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), g_player.rot, g_player.fLength);
		g_player.bDisp = false;
		g_player.state1 = PLAYERSTATE_DEATH;
		g_player.nCounterState1 = 60;
	}
	else
	{
		g_player.state1 = PLAYERSTATE_DAMAGE;
		g_player.nCounterState1 = 5;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);
	}
	//�A�����b�N
	g_pVtxBuffPlayer->Unlock();
}


//------------------------------------------
// �L�[���͂̏���
//------------------------------------------
void GetKeyPlayer(void)
{

	static float fData = 0.2;

	VERTEX_2D* pVtx;        //���_���̃|�C���^

	if (GetKeyboardPress(DIK_A) == true|| GetJoypadPress(JOYKEY_LEFT) == true)
	{//������
		fData = 0.2;

		if (GetKeyboardPress(DIK_W) == true||GetJoypadPress(JOYKEY_UP) == true)
		{//�������
			g_player.move.x += sinf(-D3DX_PI * 0.75f) * 0.3f;
			g_player.move.y += cosf(-D3DX_PI * 0.75f) * 0.3f;
		}
		else if (GetKeyboardPress(DIK_S) == true|| GetJoypadPress(JOYKEY_DOWN) == true)
		{//��������
			g_player.move.x += sinf(-D3DX_PI * 0.25f) * 0.3f;
			g_player.move.y += cosf(-D3DX_PI * 0.25f) * 0.3f;
		}
		else
		{//������
			g_player.move.x -= 0.3f;
		}
	}
	else if (GetKeyboardPress(DIK_W) == true || GetJoypadPress(JOYKEY_UP) == true)
	{
		if (GetKeyboardPress(DIK_D) == true||GetJoypadPress(JOYKEY_RIGHT) == true)
		{//�E�����
			g_player.move.x += sinf(D3DX_PI * 0.75f) * 0.3f;
			g_player.move.y += cosf(-D3DX_PI * 0.75f) * 0.3f;
			fData = -0.2;
		}
		else
		{//�����
			g_player.move.y -= 0.3f;
		}

	}
	else if (GetKeyboardPress(DIK_D) == true||GetJoypadPress(JOYKEY_RIGHT) == true)
	{
		fData = -0.2;
		if (GetKeyboardPress(DIK_S) == true||GetJoypadPress(JOYKEY_DOWN) == true)
		{//�E������
			g_player.move.x += sinf(D3DX_PI * 0.25f) * 0.3f;
			g_player.move.y += cosf(D3DX_PI * 0.25f) * 0.3f;
		}
		else
		{//�E����
			g_player.move.x += 0.3f;
		}
	}
	else if (GetKeyboardPress(DIK_S) == true|| GetJoypadPress(JOYKEY_DOWN) == true)
	{//������
		g_player.move.y += 0.3f;
	}
	else if (GetKeyboardPress(DIK_RIGHT) == true|| GetJoypadPress(JOYKEY_RB) == true)
	{//��]
		g_player.rot.z += 0.1f;
	}
	else if (GetKeyboardPress(DIK_LEFT) == true|| GetJoypadPress(JOYKEY_LB) == true)
	{//��]
		g_player.rot.z -= 0.1f;
	}
	else if (GetKeyboardPress(DIK_UP) == true|| GetJoypadPress(JOYKEY_A) == true|| GetJoypadPress(JOYKEY_Y) == true)
	{//�g��
		if (g_player.fLength <= MAX_MAX)
		{
			g_player.fLength += 0.3f;
		}
		else if (g_player.fLength >= MAX_MAX)
		{
			g_player.fLength += 0.0f;
		}
	}
	else if (GetKeyboardPress(DIK_DOWN) == true|| GetJoypadPress(JOYKEY_B) == true|| GetJoypadPress(JOYKEY_X) == true)
	{//�k��
		if (g_player.fLength <= MAX_MIN)
		{
			g_player.fLength -= 0.0f;
		}
		else if (g_player.fLength >= MAX_MIN)
		{
			g_player.fLength -= 0.3f;
		}
	}
	else if (GetKeyboardPress(DIK_T) == true|| GetJoypadPress(JOYKEY_START) == true|| GetJoypadPress(JOYKEY_BACK) == true)
	{
		InitPlayer();
		InitEnemy();
		SetEnemy(D3DXVECTOR3(800.0f, 350.0f, 0.0f), 0);
	}

	if (KeyboardTrigger(DIK_SPACE) == true|| GetJoypadPress(JOYKEY_R3) == true|| GetJoypadPress(JOYKEY_L3) == true)
	{//SPACE�������ꂽ
		//�e�̐ݒ�
		SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI) * MAX_SPEED, cosf(g_player.rot.z + D3DX_PI) * MAX_SPEED, 0.0f), g_player.rot, g_player.fLength, 150, BULLETTYPE_PLAYER);
		/*SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.75f) * MAX_SPEED, cosf(g_player.rot.z + D3DX_PI * 0.75f) * MAX_SPEED, 0.0f), g_player.rot, g_player.fLength, 150, BULLETTYPE_PLAYER);
		SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + (-D3DX_PI * 0.75f)) * MAX_SPEED, cosf(g_player.rot.z + (-D3DX_PI * 0.75f)) * MAX_SPEED, 0.0f), g_player.rot, g_player.fLength, 150, BULLETTYPE_PLAYER);*/
	}


	//�ʒu���X�V
	g_player.pos.x += g_player.move.x;
	g_player.pos.y += g_player.move.y;

	//�ړ��ʂ��X�V(����������)
	g_player.move.x += (0.0f - g_player.move.x) * 0.03f;
	g_player.move.y += (0.0f - g_player.move.y) * 0.03f;

	//���_�o�b�t�@�����b�N���Ē��_���ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos.x = g_player.pos.x + sinf(g_player.rot.z + (-D3DX_PI + g_player.fAngle)) * g_player.fLength;
	pVtx[0].pos.y = g_player.pos.y + cosf(g_player.rot.z + (-D3DX_PI + g_player.fAngle)) * g_player.fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_player.pos.x + sinf(g_player.rot.z + (D3DX_PI - g_player.fAngle)) * g_player.fLength;
	pVtx[1].pos.y = g_player.pos.y + cosf(g_player.rot.z + (D3DX_PI - g_player.fAngle)) * g_player.fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_player.pos.x + sinf(g_player.rot.z + (0.0f - g_player.fAngle)) * g_player.fLength;
	pVtx[2].pos.y = g_player.pos.y + cosf(g_player.rot.z + (0.0f - g_player.fAngle)) * g_player.fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_player.pos.x + sinf(g_player.rot.z + (0.0f + g_player.fAngle)) * g_player.fLength;
	pVtx[3].pos.y = g_player.pos.y + cosf(g_player.rot.z + (0.0f + g_player.fAngle)) * g_player.fLength;
	pVtx[3].pos.z = 0.0f;

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayer->Unlock();
}