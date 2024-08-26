//------------------------------------------
//
//     　プレイヤー処理
//       Author:Sudou Akito
//
//------------------------------------------
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include"main.h"

//マクロ定義
#define MAX_PLAYPATTERN (10)
#define MAX_SIZE (200)        //幅と高さ
#define MAX_MAX (400)
#define MAX_MIN (50)

//プレイヤーの状態
//typedef enum
//{
//	PLAYERSTATE_NORMAL = 0,  //通常状態
//	PLAYERSTATE_DAMAGE,    //ダメージ状態
//	PLAYERSTATE_MAX
//}PLAYERSTATE;

//プレイヤーの状態
typedef enum
{
	PLAYERSTATE_APPEAR=0,     //出現地点(点滅)
	PLAYERSTATE_NORMAL,       //通常状態
	PLAYERSTATE_DAMAGE,       //ダメージ状態
	PLAYERSTATE_DEATH,        //死亡状態
	PLAYERSTATE_MAX
}PLAYERSTATE1;

//プレイヤー構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;     //位置
	D3DXVECTOR3 move;    //移動量
	D3DXVECTOR3 rot;     //向き
	//PLAYERSTATE state;   //状態
	PLAYERSTATE1 state1; //プレイヤーの状態
	//int nCounterState;   //状態管理カウンター
	int nCounterState1;  //状態管理カウンター
	float fLength;       //対角線の長さ
	float fAngle;        //対角線の角度
	int nLife;           //体力
	bool bDisp;          //表示するかしないか
}Player;

//プロトタイプ宣言
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
Player* GetPlayer(void);
void HitPlayer(int nDmg);
void GetKeyPlayer(void);



#endif