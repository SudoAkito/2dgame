//------------------------------------------
//
//        ���C���Q�[������
//       Author:Sudou Akito
//
//------------------------------------------

#include"game.h"
#include "player.h"
#include"background.h"
#include"bullet.h"
#include"explosion.h"
#include"effect.h"
#include"enemy.h"
#include"fade.h"
#include"score.h"

//�O���[�o���ϐ�
GAMESTATE g_gameState = GAMESTATE_NONE;   //�Q�[���̏��
int g_nCounterGameState = 0;              //��ԊǗ��J�E���^�[

//------------------------------------------
//�Q�[����ʂ̏���������
//------------------------------------------
void InitGame(void)
{
	//�w�i
	InitBackground();

	//�v���C���[
	InitPlayer();

	//�X�R�A�̏�����
	InitScore();

	//�e
	InitBullet();

	// ����
	InitExplosion();

	//�G�t�F�N�g
	InitEffect();

	//�G
	InitEnemy();
	SetEnemy(D3DXVECTOR3(800.0f, 350.0f, 0.0f),0);

	g_gameState = GAMESTATE_NORMAL;    //�ʏ��Ԃɐݒ�

	g_nCounterGameState = 0;
}

//------------------------------------------
//�Q�[����ʂ̏I������
//------------------------------------------
void UninitGame(void)
{
	//�w�i
	UninitBackground();

	//�v���C���[
	UninitPlayer();

	//�X�R�A�̏I��
	UninitScore();

	//�e
	UninitBullet();

	//����
	UninitExplosion();

	//�G�t�F�N�g
	UninitEffect();

	//�G
	UninitEnemy();
}

//------------------------------------------
//�Q�[����ʂ̍X�V����
//------------------------------------------
void UpdateGame(void)
{

	int nNum;

	//�w�i
	UpdateBackground();

	//�v���C���[
	UpdatePlayer();

	//�X�R�A�̍X�V
	UpdateScore();

	//�e
	UpdateBullet();

	//����
	UpdateExplosion();

	//�G�t�F�N�g
	UpdateEffect();

	//�G
	UpdateEnemy();

	Player* pPlayer = GetPlayer();  //�v���C���[�̃|�C���^
	nNum=GetNumEnemy();

	if (pPlayer->bDisp==false||nNum<=0)   //������^�C���I�[�o�[�̏����ǉ�
	{
		//���[�h�ݒ�
		g_gameState=GAMESTATE_END;
	}

	switch (g_gameState)
	{
	case GAMESTATE_NORMAL:    //�ʏ���
		break;

	case GAMESTATE_END:       //�I�����
		g_nCounterGameState++;
		if (g_nCounterGameState >= 60)
		{
			g_gameState = GAMESTATE_NONE;  //�������Ă��Ȃ���Ԃɐݒ�

			//��ʂ̐ݒ�
			SetMode(MODE_RESULT);
		}
		break;
	}
}

//------------------------------------------
// �Q�[���̍X�V����
//------------------------------------------
void DrawGame(void)
{
	//�w�i
	DrawBackground();

	//�v���C���[
	DrawPlayer();

	//�X�R�A
	DrawScore();

	//�G�t�F�N�g
	DrawEffect();

	//����
	DrawExplosion();

	//�e
	DrawBullet();

	//�G
	DrawEnemy();
}

//------------------------------------------
//�Q�[���̏�Ԃ̐ݒ�
//------------------------------------------
void SetGameState(GAMESTATE state)
{
	g_gameState = state;

	/*g_nCounterGameState = 0;*/
}

//------------------------------------------
//�Q�[���̏�Ԏ擾
//------------------------------------------
GAMESTATE GetGameState(void)
{
	return g_gameState;
}