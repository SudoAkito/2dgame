//------------------------------------------
//
//          エフェクト処理
//       Author:Sudou Akito
//
//------------------------------------------
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include"main.h"

//プロトタイプ宣言
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadius, float fAngle,int nLife);   //posは発生位置,colは色を変えれる


#endif

