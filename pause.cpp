//------------------------------------------
//
//         �|�[�Y����
//       Author:Sudou Akito
//
//------------------------------------------

#include"pause.h"
#include"input.h"
#include "fade.h"
#include "game.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexturePause[MAX_UI] = {};       //�e�N�X�`���|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;    //���_�o�b�t�@�|�C���^
PAUSE_MENU g_pauseMenu;                            //�|�[�Y���j���[

//------------------------------------------
//�|�[�Y��ʂ̏���������
//------------------------------------------
void InitPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;   //�f�o�C�X�ւ̃|�C���^
	int nCntPu;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\CONTUNUE.png",
		&g_pTexturePause[1]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Retry.png",
		&g_pTexturePause[2]);


	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Quit.png",
		&g_pTexturePause[3]);


	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_UI,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPause,
		NULL);

	VERTEX_2D* pVtx;        //���_���̃|�C���^

	//���_�o�b�t�@�����b�N���Ē��_���ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	float max_y = 150.0f;
	float max_x = 800.0f;
	float min_y = 50.0f;
	float min_x = 400.0f;

	for (nCntPu = 0; nCntPu < MAX_UI; nCntPu++)
	{
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		if (nCntPu == 0)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DCOLOR_RGBA(0,0,0,120);
			pVtx[1].col = D3DCOLOR_RGBA(0,0,0,120);
			pVtx[2].col = D3DCOLOR_RGBA(0,0,0,120);
			pVtx[3].col = D3DCOLOR_RGBA(0,0,0,120);
		}
		else if(nCntPu==1)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(min_x, min_y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(max_x, min_y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(min_x, max_y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(max_x, max_y, 0.0f);
		}
		else if (nCntPu == 2)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(min_x, min_y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(max_x, min_y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(min_x, max_y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(max_x, max_y, 0.0f);
		}
		else if (nCntPu == 3)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(min_x, min_y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(max_x, min_y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(min_x, max_y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(max_x, max_y, 0.0f);
		}

		min_y += OFFSET_VALUE;
		max_y += OFFSET_VALUE;

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPause->Unlock();

	g_pauseMenu = PAUSE_MENU_CONTINUE;
}

//------------------------------------------
//�|�[�Y��ʂ̏I������
//------------------------------------------
void UninitPause(void)
{
	//�e�N�X�`���̔j��
	for (int nCntPu = 0; nCntPu < MAX_UI; nCntPu++)
	{
		if (g_pTexturePause[nCntPu] != NULL)
		{
			g_pTexturePause[nCntPu]->Release();
			g_pTexturePause[nCntPu] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}
}

//------------------------------------------
// �|�[�Y�̍X�V����
//------------------------------------------
void UpdatePause(void)
{
	//���j���[�̑I��
	switch (g_pauseMenu)
	{
	case PAUSE_MENU_CONTINUE:
		if (KeyboardTrigger(DIK_UP) == true)
		{
			g_pauseMenu = PAUSE_MENU_QUIT;
		}
		else if (KeyboardTrigger(DIK_DOWN) == true)
		{
			g_pauseMenu = PAUSE_MENU_RETRY;
		}
		SelectPause(1);
		break;
	
	case PAUSE_MENU_RETRY:
		if (KeyboardTrigger(DIK_UP) == true)
		{
			g_pauseMenu = PAUSE_MENU_CONTINUE;
		}
		else if (KeyboardTrigger(DIK_DOWN) == true)
		{
			g_pauseMenu = PAUSE_MENU_QUIT;
		}
		SelectPause(2);

		break;

	case PAUSE_MENU_QUIT:
		if (KeyboardTrigger(DIK_UP) == true)
		{
			g_pauseMenu = PAUSE_MENU_QUIT;
		}
		else if (KeyboardTrigger(DIK_DOWN) == true)
		{
			g_pauseMenu = PAUSE_MENU_CONTINUE;
		}
		SelectPause(3);

		break;
	}

	if (KeyboardTrigger(DIK_RETURN) == true)
	{//ENTER�������ꂽ�Ƃ�
		//���j���[�ɍ��킹�ă��[�h�̐؂�ւ�
		switch (g_pauseMenu)
		{
		case PAUSE_MENU_CONTINUE:
			SetEnablePause(false);
			break;

		case PAUSE_MENU_RETRY:
			SetFade(MODE_GAME);
			break;

		case PAUSE_MENU_QUIT:
			SetFade(MODE_TITLE);
			break;
		}
	}
}

//------------------------------------------
//�|�[�Y�̕`�揈��
//------------------------------------------
void DrawPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;   //�f�o�C�X�ւ̃|�C���^
	int nCntPu;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntPu = 0; nCntPu < MAX_UI; nCntPu++)
	{
		pDevice->SetTexture(0, g_pTexturePause[nCntPu]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntPu,2);//�v���~�e�B�u�̎��,�v���~�e�B�u�̐�

	}
}

//------------------------------------------
//�|�[�Y�̑I������
//------------------------------------------
void SelectPause(int nNumSelect)
{
	VERTEX_2D* pVtx;        //���_���̃|�C���^

		//���_�o�b�t�@�����b�N���Ē��_���ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntPu = 0; nCntPu < MAX_UI; nCntPu++)
	{
		if (nCntPu == 0)
		{
			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DCOLOR_RGBA(0, 0, 0, 120);
			pVtx[1].col = D3DCOLOR_RGBA(0, 0, 0, 120);
			pVtx[2].col = D3DCOLOR_RGBA(0, 0, 0, 120);
			pVtx[3].col = D3DCOLOR_RGBA(0, 0, 0, 120);
		}
		else if (nCntPu == nNumSelect)
		{
			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}
		else
		{
			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DCOLOR_RGBA(150, 150, 150, 255);
			pVtx[1].col = D3DCOLOR_RGBA(150, 150, 150, 255);
			pVtx[2].col = D3DCOLOR_RGBA(150, 150, 150, 255);
			pVtx[3].col = D3DCOLOR_RGBA(150, 150, 150, 255);
		}

		pVtx += 4;
	}
	
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPause->Unlock();
}