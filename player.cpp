//------------------------------------------
//
//       プレイヤー処理
//       Author:Sudou Akito
//
//------------------------------------------
#include"main.h"
#include"player.h"
#include"background.h"
#include"input.h"
#include"bullet.h"
#include "enemy.h"
#include"explosion.h"



//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer= NULL;

int g_nCounterAnimPlayer;    //アニメーションカウンター
int g_nPatternAnimPlayer;    //アニメーションパターンNO.

Player g_player;

//------------------------------------------
//プレイヤー初期化処理
//------------------------------------------
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;   //デバイスへのポインタ
	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\1901.png",
		&g_pTexturePlayer);

	g_player.pos = D3DXVECTOR3(300.0f, 400.0f, 0.0f);  //位置初期化
	g_player.move = D3DXVECTOR3(0.0f,0.0f,0.0f);	      //移動量初期化
	g_player.rot = D3DXVECTOR3(0.0f,0.0f,0.0f);        //向きの初期化
	g_player.nLife = 100;
	g_player.bDisp = true;
	g_player.state1 = {};

	//対角線の長さの算出
	g_player.fLength = sqrtf(MAX_SIZE*MAX_SIZE+MAX_SIZE*MAX_SIZE) / 2.0f;

	//対角線の角度を算出
	g_player.fAngle = atan2f(MAX_SIZE, MAX_SIZE);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayer,
		NULL);

	VERTEX_2D* pVtx;       //頂点情報のポインタ

	//頂点バッファをロックして頂点情報へのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos.x = g_player.pos.x + sinf(g_player.rot.z - (-D3DX_PI - g_player.fAngle)) * g_player.fLength;
	pVtx[0].pos.y = g_player.pos.y + cosf(g_player.rot.z - (-D3DX_PI - g_player.fAngle)) * g_player.fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_player.pos.x + sinf(g_player.rot.z + (D3DX_PI - g_player.fAngle)) * g_player.fLength;
	pVtx[1].pos.y = g_player.pos.y + cosf(g_player.rot.z + (D3DX_PI - g_player.fAngle)) * g_player.fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_player.pos.x + sinf(g_player.rot.z + (0.0f - g_player.fAngle)) * g_player.fLength;
	pVtx[2].pos.y = g_player.pos.y + cosf(g_player.rot.z + (0.0f - g_player.fAngle)) * g_player.fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_player.pos.x + sinf(g_player.rot.z - (0.0f - g_player.fAngle)) * g_player.fLength;
	pVtx[3].pos.y = g_player.pos.y + cosf(g_player.rot.z - (0.0f - g_player.fAngle)) * g_player.fLength;
	pVtx[3].pos.z = 0.0f;

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffPlayer->Unlock();
}

//------------------------------------------
//プレイヤーの終了処理
//------------------------------------------
void UninitPlayer(void)
{

	//テクスチャの破棄
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
}

//------------------------------------------
//プレイヤーの更新処理
//------------------------------------------
void UpdatePlayer(void)
{
	VERTEX_2D* pVtx;        //頂点情報のポインタ

	GetKeyPlayer();


	switch (g_player.state1)
	{
	case PLAYERSTATE_NORMAL:

		break;

	case PLAYERSTATE_DAMAGE:

		//頂点バッファをロックして頂点情報へのポインタを取得
		g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

		g_player.nCounterState1--;

		if (g_player.nCounterState1 <= 0)
		{
			g_player.state1 = PLAYERSTATE_NORMAL;

			//頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}
		//頂点バッファをアンロックする
		g_pVtxBuffPlayer->Unlock();
		break;

	case PLAYERSTATE_DEATH:
		g_player.nCounterState1--;

		if (g_player.nCounterState1 <= 0)
		{
			//リザルト画面に移行
			SetMode(MODE_RESULT);

			return;
		}
		break;
	}

	//g_nCounterAnimPlayer++;

	//if ((g_nCounterAnimPlayer%10)==0)
	//{
	//	g_nPatternAnimPlayer=(g_nPatternAnimPlayer+1)%MAX_PLAYPATTERN;   //パターンNo.を更新する

	//	//頂点バッファをロックして頂点情報へのポインタを取得
	//	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
	//	//テクスチャ座標の設定
	//	//左
	//	pVtx[0].tex = D3DXVECTOR2(g_nPatternAnimPlayer * 0.2f, (g_nPatternAnimPlayer / 5) * 0.5f);
	//	pVtx[1].tex = D3DXVECTOR2(fData+g_nPatternAnimPlayer * 0.2f, (g_nPatternAnimPlayer / 5) * 0.5f);
	//	pVtx[2].tex = D3DXVECTOR2(g_nPatternAnimPlayer * 0.2f, (g_nPatternAnimPlayer / 5) * 0.5f + 0.5f);
	//	pVtx[3].tex = D3DXVECTOR2(fData+g_nPatternAnimPlayer * 0.2f, (g_nPatternAnimPlayer / 5) * 0.5f + 0.5f);
	//
	//	//頂点バッファをアンロックする
	//	g_pVtxBuffPlayer->Unlock();
	//}

}

//------------------------------------------
//プレイヤーの描画処理
//------------------------------------------
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;   //デバイスへのポインタ
	//デバイスの取得
	pDevice = GetDevice();

	if (g_player.bDisp == true)
	{
		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTexturePlayer);

	
		//プレイヤーの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);//プリミティブの種類,プリミティブの数
	}
}
	
//------------------------------------------
// プレイヤー情報の取得
//------------------------------------------
Player* GetPlayer(void)
{
	return &g_player;
}

//------------------------------------------
// 当たり判定後の処理
//------------------------------------------
void HitPlayer(int nDmg)
{
	VERTEX_2D* pVtx;//頂点情報のポインタ

	g_player.nLife -= nDmg;
	//頂点バッファをロックし,頂点情報へのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
	if (g_player.nLife <= 0)
	{
		SetExplosion(g_player.pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), g_player.rot, g_player.fLength);
		g_player.bDisp = false;
		g_player.state1 = PLAYERSTATE_DEATH;
		g_player.nCounterState1 = 60;
	}
	else
	{
		g_player.state1 = PLAYERSTATE_DAMAGE;
		g_player.nCounterState1 = 5;

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);
	}
	//アンロック
	g_pVtxBuffPlayer->Unlock();
}


//------------------------------------------
// キー入力の処理
//------------------------------------------
void GetKeyPlayer(void)
{

	static float fData = 0.2;

	VERTEX_2D* pVtx;        //頂点情報のポインタ

	if (GetKeyboardPress(DIK_A) == true|| GetJoypadPress(JOYKEY_LEFT) == true)
	{//左方向
		fData = 0.2;

		if (GetKeyboardPress(DIK_W) == true||GetJoypadPress(JOYKEY_UP) == true)
		{//左上方向
			g_player.move.x += sinf(-D3DX_PI * 0.75f) * 0.3f;
			g_player.move.y += cosf(-D3DX_PI * 0.75f) * 0.3f;
		}
		else if (GetKeyboardPress(DIK_S) == true|| GetJoypadPress(JOYKEY_DOWN) == true)
		{//左下方向
			g_player.move.x += sinf(-D3DX_PI * 0.25f) * 0.3f;
			g_player.move.y += cosf(-D3DX_PI * 0.25f) * 0.3f;
		}
		else
		{//左方向
			g_player.move.x -= 0.3f;
		}
	}
	else if (GetKeyboardPress(DIK_W) == true || GetJoypadPress(JOYKEY_UP) == true)
	{
		if (GetKeyboardPress(DIK_D) == true||GetJoypadPress(JOYKEY_RIGHT) == true)
		{//右上方向
			g_player.move.x += sinf(D3DX_PI * 0.75f) * 0.3f;
			g_player.move.y += cosf(-D3DX_PI * 0.75f) * 0.3f;
			fData = -0.2;
		}
		else
		{//上方向
			g_player.move.y -= 0.3f;
		}

	}
	else if (GetKeyboardPress(DIK_D) == true||GetJoypadPress(JOYKEY_RIGHT) == true)
	{
		fData = -0.2;
		if (GetKeyboardPress(DIK_S) == true||GetJoypadPress(JOYKEY_DOWN) == true)
		{//右下方向
			g_player.move.x += sinf(D3DX_PI * 0.25f) * 0.3f;
			g_player.move.y += cosf(D3DX_PI * 0.25f) * 0.3f;
		}
		else
		{//右方向
			g_player.move.x += 0.3f;
		}
	}
	else if (GetKeyboardPress(DIK_S) == true|| GetJoypadPress(JOYKEY_DOWN) == true)
	{//下方向
		g_player.move.y += 0.3f;
	}
	else if (GetKeyboardPress(DIK_RIGHT) == true|| GetJoypadPress(JOYKEY_RB) == true)
	{//回転
		g_player.rot.z += 0.1f;
	}
	else if (GetKeyboardPress(DIK_LEFT) == true|| GetJoypadPress(JOYKEY_LB) == true)
	{//回転
		g_player.rot.z -= 0.1f;
	}
	else if (GetKeyboardPress(DIK_UP) == true|| GetJoypadPress(JOYKEY_A) == true|| GetJoypadPress(JOYKEY_Y) == true)
	{//拡大
		if (g_player.fLength <= MAX_MAX)
		{
			g_player.fLength += 0.3f;
		}
		else if (g_player.fLength >= MAX_MAX)
		{
			g_player.fLength += 0.0f;
		}
	}
	else if (GetKeyboardPress(DIK_DOWN) == true|| GetJoypadPress(JOYKEY_B) == true|| GetJoypadPress(JOYKEY_X) == true)
	{//縮小
		if (g_player.fLength <= MAX_MIN)
		{
			g_player.fLength -= 0.0f;
		}
		else if (g_player.fLength >= MAX_MIN)
		{
			g_player.fLength -= 0.3f;
		}
	}
	else if (GetKeyboardPress(DIK_T) == true|| GetJoypadPress(JOYKEY_START) == true|| GetJoypadPress(JOYKEY_BACK) == true)
	{
		InitPlayer();
		InitEnemy();
		SetEnemy(D3DXVECTOR3(800.0f, 350.0f, 0.0f), 0);
	}

	if (KeyboardTrigger(DIK_SPACE) == true|| GetJoypadPress(JOYKEY_R3) == true|| GetJoypadPress(JOYKEY_L3) == true)
	{//SPACEが押された
		//弾の設定
		SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI) * MAX_SPEED, cosf(g_player.rot.z + D3DX_PI) * MAX_SPEED, 0.0f), g_player.rot, g_player.fLength, 150, BULLETTYPE_PLAYER);
		/*SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.75f) * MAX_SPEED, cosf(g_player.rot.z + D3DX_PI * 0.75f) * MAX_SPEED, 0.0f), g_player.rot, g_player.fLength, 150, BULLETTYPE_PLAYER);
		SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + (-D3DX_PI * 0.75f)) * MAX_SPEED, cosf(g_player.rot.z + (-D3DX_PI * 0.75f)) * MAX_SPEED, 0.0f), g_player.rot, g_player.fLength, 150, BULLETTYPE_PLAYER);*/
	}


	//位置を更新
	g_player.pos.x += g_player.move.x;
	g_player.pos.y += g_player.move.y;

	//移動量を更新(減衰させる)
	g_player.move.x += (0.0f - g_player.move.x) * 0.03f;
	g_player.move.y += (0.0f - g_player.move.y) * 0.03f;

	//頂点バッファをロックして頂点情報へのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos.x = g_player.pos.x + sinf(g_player.rot.z + (-D3DX_PI + g_player.fAngle)) * g_player.fLength;
	pVtx[0].pos.y = g_player.pos.y + cosf(g_player.rot.z + (-D3DX_PI + g_player.fAngle)) * g_player.fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_player.pos.x + sinf(g_player.rot.z + (D3DX_PI - g_player.fAngle)) * g_player.fLength;
	pVtx[1].pos.y = g_player.pos.y + cosf(g_player.rot.z + (D3DX_PI - g_player.fAngle)) * g_player.fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_player.pos.x + sinf(g_player.rot.z + (0.0f - g_player.fAngle)) * g_player.fLength;
	pVtx[2].pos.y = g_player.pos.y + cosf(g_player.rot.z + (0.0f - g_player.fAngle)) * g_player.fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_player.pos.x + sinf(g_player.rot.z + (0.0f + g_player.fAngle)) * g_player.fLength;
	pVtx[3].pos.y = g_player.pos.y + cosf(g_player.rot.z + (0.0f + g_player.fAngle)) * g_player.fLength;
	pVtx[3].pos.z = 0.0f;

	//頂点バッファをアンロックする
	g_pVtxBuffPlayer->Unlock();
}