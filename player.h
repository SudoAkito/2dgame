//------------------------------------------
//
//     �@�v���C���[����
//       Author:Sudou Akito
//
//------------------------------------------
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include"main.h"

//�}�N����`
#define MAX_PLAYPATTERN (10)
#define MAX_SIZE (200)        //���ƍ���
#define MAX_MAX (400)
#define MAX_MIN (50)

//�v���C���[�̏��
//typedef enum
//{
//	PLAYERSTATE_NORMAL = 0,  //�ʏ���
//	PLAYERSTATE_DAMAGE,    //�_���[�W���
//	PLAYERSTATE_MAX
//}PLAYERSTATE;

//�v���C���[�̏��
typedef enum
{
	PLAYERSTATE_APPEAR=0,     //�o���n�_(�_��)
	PLAYERSTATE_NORMAL,       //�ʏ���
	PLAYERSTATE_DAMAGE,       //�_���[�W���
	PLAYERSTATE_DEATH,        //���S���
	PLAYERSTATE_MAX
}PLAYERSTATE1;

//�v���C���[�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;     //�ʒu
	D3DXVECTOR3 move;    //�ړ���
	D3DXVECTOR3 rot;     //����
	//PLAYERSTATE state;   //���
	PLAYERSTATE1 state1; //�v���C���[�̏��
	//int nCounterState;   //��ԊǗ��J�E���^�[
	int nCounterState1;  //��ԊǗ��J�E���^�[
	float fLength;       //�Ίp���̒���
	float fAngle;        //�Ίp���̊p�x
	int nLife;           //�̗�
	bool bDisp;          //�\�����邩���Ȃ���
}Player;

//�v���g�^�C�v�錾
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
Player* GetPlayer(void);
void HitPlayer(int nDmg);
void GetKeyPlayer(void);



#endif