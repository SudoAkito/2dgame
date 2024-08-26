//------------------------------------------
//
//         敵処理
//       Author:Sudou Akito
//
//------------------------------------------

#ifndef _ENEMY_H_
#define _ENEMY_H_

#include"main.h"

//マクロ
#define MAX_ENEMY (128)
#define MAX_WIDTH (50)
#define MAX_HEIGHT (75)

//敵の状態
typedef enum
{
	ENEMYSTATE_NORMAL=0,  //通常状態
	ENEMYSTATE_DAMAGE,    //ダメージ状態
	ENEMYSTATE_MAX
}ENEMYSTATE;

//敵構造体
typedef struct
{
	D3DXVECTOR3 pos;  //位置
	D3DXVECTOR3 move; //移動量
	D3DXVECTOR3 rot;  //角度
	ENEMYSTATE state; //状態
	int nCounterState;//状態管理カウンター
	int nLife;        //体力
	int nType;        //種類
	int nunti;
	bool bUse;        //使用の有無
	float fLength;
	float fAngle;
}Enemy;

//プロトタイプ宣言
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos,int nType);   //posは発射位置,nTypeは種類
Enemy* GetEnemy(void);
void HitEnemy(int nCntEn, int nDmg);
int GetNumEnemy();

#endif
