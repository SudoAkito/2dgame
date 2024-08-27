//------------------------------------------
//
//     　 スコア処理
//       Author:Sudou Akito
//
//------------------------------------------
#ifndef _SCORE_H_
#define _SCORE_H_

#include"main.h"

//スコア情報の構造体
typedef struct
{
    bool bUse;//使用しているか
    int nCountScoreCounter;//0のカウント
}Score;

//マクロ定義
#define EIGHT (10000000)
#define SEVEN (1000000)
#define MAX_SCORE (8)

//プロトタイプ宣言
void InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
void SetScore(int nScore);
void AddScore(int nValue);
int  ScoreCounter(int nScore);

#endif

