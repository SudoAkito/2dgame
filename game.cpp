//------------------------------------------
//
//        メインゲーム処理
//       Author:Sudou Akito
//
//------------------------------------------

#include"game.h"
#include "player.h"
#include"background.h"
#include"bullet.h"
#include"explosion.h"
#include"effect.h"
#include"enemy.h"
#include"fade.h"
#include"score.h"

//グローバル変数
GAMESTATE g_gameState = GAMESTATE_NONE;   //ゲームの状態
int g_nCounterGameState = 0;              //状態管理カウンター

//------------------------------------------
//ゲーム画面の初期化処理
//------------------------------------------
void InitGame(void)
{
	//背景
	InitBackground();

	//プレイヤー
	InitPlayer();

	//スコアの初期化
	InitScore();

	//弾
	InitBullet();

	// 爆発
	InitExplosion();

	//エフェクト
	InitEffect();

	//敵
	InitEnemy();
	SetEnemy(D3DXVECTOR3(800.0f, 350.0f, 0.0f),0);

	g_gameState = GAMESTATE_NORMAL;    //通常状態に設定

	g_nCounterGameState = 0;
}

//------------------------------------------
//ゲーム画面の終了処理
//------------------------------------------
void UninitGame(void)
{
	//背景
	UninitBackground();

	//プレイヤー
	UninitPlayer();

	//スコアの終了
	UninitScore();

	//弾
	UninitBullet();

	//爆発
	UninitExplosion();

	//エフェクト
	UninitEffect();

	//敵
	UninitEnemy();
}

//------------------------------------------
//ゲーム画面の更新処理
//------------------------------------------
void UpdateGame(void)
{

	int nNum;

	//背景
	UpdateBackground();

	//プレイヤー
	UpdatePlayer();

	//スコアの更新
	UpdateScore();

	//弾
	UpdateBullet();

	//爆発
	UpdateExplosion();

	//エフェクト
	UpdateEffect();

	//敵
	UpdateEnemy();

	Player* pPlayer = GetPlayer();  //プレイヤーのポインタ
	nNum=GetNumEnemy();

	if (pPlayer->bDisp==false||nNum<=0)   //いずれタイムオーバーの条件追加
	{
		//モード設定
		g_gameState=GAMESTATE_END;
	}

	switch (g_gameState)
	{
	case GAMESTATE_NORMAL:    //通常状態
		break;

	case GAMESTATE_END:       //終了状態
		g_nCounterGameState++;
		if (g_nCounterGameState >= 60)
		{
			g_gameState = GAMESTATE_NONE;  //何もしていない状態に設定

			//画面の設定
			SetMode(MODE_RESULT);
		}
		break;
	}
}

//------------------------------------------
// ゲームの更新処理
//------------------------------------------
void DrawGame(void)
{
	//背景
	DrawBackground();

	//プレイヤー
	DrawPlayer();

	//スコア
	DrawScore();

	//エフェクト
	DrawEffect();

	//爆発
	DrawExplosion();

	//弾
	DrawBullet();

	//敵
	DrawEnemy();
}

//------------------------------------------
//ゲームの状態の設定
//------------------------------------------
void SetGameState(GAMESTATE state)
{
	g_gameState = state;

	/*g_nCounterGameState = 0;*/
}

//------------------------------------------
//ゲームの状態取得
//------------------------------------------
GAMESTATE GetGameState(void)
{
	return g_gameState;
}