//------------------------------------------
//
//          爆発処理
//       Author:Sudou Akito
//
//------------------------------------------
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include"main.h"

//プロトタイプ宣言
void InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col, D3DXVECTOR3 rot, float fLength);   //posは発生位置,colは色を変えれる

#endif

