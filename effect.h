//------------------------------------------
//
//          �G�t�F�N�g����
//       Author:Sudou Akito
//
//------------------------------------------
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include"main.h"

//�v���g�^�C�v�錾
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadius, float fAngle,int nLife);   //pos�͔����ʒu,col�͐F��ς����


#endif

