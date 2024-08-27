//------------------------------------------
//
//     �@ �X�R�A����
//       Author:Sudou Akito
//
//------------------------------------------
#ifndef _SCORE_H_
#define _SCORE_H_

#include"main.h"

//�X�R�A���̍\����
typedef struct
{
    bool bUse;//�g�p���Ă��邩
    int nCountScoreCounter;//0�̃J�E���g
}Score;

//�}�N����`
#define EIGHT (10000000)
#define SEVEN (1000000)
#define MAX_SCORE (8)

//�v���g�^�C�v�錾
void InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
void SetScore(int nScore);
void AddScore(int nValue);
int  ScoreCounter(int nScore);

#endif

