//------------------------------------------
//
//     �@ �X�R�A����
//       Author:Sudou Akito
//
//------------------------------------------

#include "score.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureScore = NULL;      //�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL; //���_�o�b�t�@�|�C���^
D3DXVECTOR3 g_posScore;                         //�X�R�A�̈ʒu
int g_nScore;                                   //�X�R�A�̒l

//�X�R�A�^�̃O���[�o���ϐ�
Score g_aScore[MAX_SCORE];

//------------------------------------------
//�@�X�R�A����������
//------------------------------------------
void InitScore(void)
{
	int nCntscore;
	LPDIRECT3DDEVICE9 pDevice;   //�f�o�C�X�ւ̃|�C���^
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\number000.png",
		&g_pTextureScore);

	g_posScore = D3DXVECTOR3(0.0f,0.0f,0.0f);  //�ʒu������
	g_nScore = 0;                              //�l������

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 *MAX_SCORE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL);

	VERTEX_2D* pVtx;       //���_���̃|�C���^

	//���_�o�b�t�@�����b�N���Ē��_���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntscore = 0; nCntscore < MAX_SCORE; nCntscore++)
	{
		g_aScore[nCntscore].bUse = true;

		//���_���W�ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f + nCntscore * 40.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f + nCntscore * 40.0f + 40.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f + nCntscore * 40.0f, 90.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f + nCntscore * 40.0f + 40.0f, 90.0f, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255,255,255,255);
		pVtx[1].col = D3DCOLOR_RGBA(255,255,255,255);
		pVtx[2].col = D3DCOLOR_RGBA(255,255,255,255);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;
	}
	
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();
}

//------------------------------------------
//  �X�R�A�I������
//------------------------------------------
void UninitScore(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
}

//------------------------------------------
//  �X�R�A�X�V����
//------------------------------------------
void UpdateScore(void)
{
	int nData;  //���[�J���ϐ�

	//�����ۑ�
	nData = ScoreCounter(g_nScore);

	for (int nData1 = 0; nData1 < MAX_SCORE; nData1++)
	{
		if (nData >= MAX_SCORE - nData1)
		{
			//��̏�������L����
			g_aScore[nData1].bUse = true;
		}
		else
		{
			//����ȊO�̏ꍇ
			g_aScore[nData1].bUse = false;
		}
	}

}

//------------------------------------------
//     �X�R�A�`�揈��
//------------------------------------------
void DrawScore(void)
{
	//�K�v�������̕`��
	LPDIRECT3DDEVICE9 pDevice;   //�f�o�C�X�ւ̃|�C���^
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	VERTEX_2D* pVtx;       //���_���̃|�C���^

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);


	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		if (g_aScore[nCnt].bUse == true)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureScore);

			//�X�R�A�̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCnt, 2);//�v���~�e�B�u�̎��,�v���~�e�B�u�̐�
		}
	}

}

//------------------------------------------
//     �X�R�A�ݒ菈��
//------------------------------------------
void SetScore(int nScore)
{
	int aPosTexU[8];    //�e���̐������i�[
	g_nScore = nScore;
	int eight = EIGHT;
	int seven = SEVEN;
	VERTEX_2D* pVtx;       //���_���̃|�C���^

	//���_�o�b�t�@�����b�N���Ē��_���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		if (nCnt == 0)
		{
			aPosTexU[0] = g_nScore / EIGHT;
		}
		else
		{
			aPosTexU[nCnt] = g_nScore % EIGHT / SEVEN;
			eight = EIGHT / 10;
			seven = SEVEN / 10;
		}
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[nCnt]), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCnt]), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[nCnt]), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCnt]), 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();
}

//------------------------------------------
//     �X�R�A���Z����
//------------------------------------------
void AddScore(int nValue)
{
	int aPosTexU[8];   //�e���̐������i�[
	int nCnt{};
	VERTEX_2D* pVtx;       //���_���̃|�C���^
	g_nScore += nValue;

	int eight = EIGHT;
	int seven = SEVEN;

	//���_�o�b�t�@�����b�N���Ē��_���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);


	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		if (nCnt==0)
		{
			aPosTexU[0] = g_nScore / EIGHT;
		}
		else
		{
			aPosTexU[nCnt] = g_nScore % EIGHT / SEVEN;
			eight= EIGHT / 10;
			seven = SEVEN / 10;
		}
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f+(0.1f * aPosTexU[nCnt]), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f+(0.1f * aPosTexU[nCnt]), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f+(0.1f * aPosTexU[nCnt]), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f+(0.1f * aPosTexU[nCnt]), 1.0f);

		pVtx += 4;
	}
	
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();
}

//------------------------------------------
//     �X�R�A0�J�E���g
//------------------------------------------
int  ScoreCounter(int nScore)
{
	int nNum = nScore;//�X�R�A�̂O�̕������J�E���g
	int nNum1 = 0;    //�X�R�A����

	while (nNum != 0)
	{
		nNum / 10;  //10�Ł�
		nNum1++;    //�������Z
	}
	if (nScore == 0)
	{//1���ڂ�0���͂����Ă�Ƃ�
		nNum1 = 1;
	}

	return nNum1;    //�X�R�A������Ԃ�
}

