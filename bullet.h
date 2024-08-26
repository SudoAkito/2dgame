//------------------------------------------
//
//         弾の出力処理
//       Author:Sudou Akito
//
//------------------------------------------
#ifndef _BULLET_H_
#define _BULLET_H_

#include"main.h"

//弾の種類
typedef enum
{
	BULLETTYPE_PLAYER=0,  //プレイヤーの弾
	BULLETTYPE_ENEMY,     //敵の弾
	BULLETTYPE_MAX
}BULLETTYPE;


//プロトタイプ宣言
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, float fLength, int nLife, BULLETTYPE type);   //posは発射位置,rotは向いた方向に出させる

//マクロ
#define MAX_SPEED (3)              //スピード

#endif

