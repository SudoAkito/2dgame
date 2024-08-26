//------------------------------------------
//
//        ���C���Q�[������
//       Author:Sudou Akito
//
//------------------------------------------
#ifndef _GAME_H_
#define _GAME_H_

#include "input.h"

//�Q�[���̏��
typedef enum
{
	GAMESTATE_NONE=0,  //�������ĂȂ����
	GAMESTATE_NORMAL,  //�ʏ���(�Q�[���i�s��)
	GAMESTATE_END,     //�I�����(�G�S�ŁA�v���C���[�ŁA�^�C���I�[�o�[�Ȃ�)
	GAMESTATE_MAX     
}GAMESTATE;

//�v���g�^�C�v�錾
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
void SetGameState(GAMESTATE state);
GAMESTATE GetGameState(void);

#endif
