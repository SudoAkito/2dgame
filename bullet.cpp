 //------------------------------------------
//
//         弾の出力処理
//       Author:Sudou Akito
//
//------------------------------------------
#include"bullet.h"
#include"player.h"
#include"explosion.h"
#include"enemy.h"
#include"effect.h"

//マクロ定義
#define MAX_BULLET (128)           //弾の最大数
#define BULLET_WIDTH (150)
#define BULLET_HEIGHT (150)

//弾の構造体
typedef struct
{
	D3DXVECTOR3 pos;    //位置
	D3DXVECTOR3 move;   //移動量
	D3DXVECTOR3 rot;    //角度
	int nLife;          //寿命
	BULLETTYPE type;
	float fLengthBullet;
	float fAngleBullet;
	bool bUse;          //使用しているかどうか
}Bullet;

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;
Bullet g_aBullet[MAX_BULLET];

//------------------------------------------
//弾の初期化処理
//------------------------------------------
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bullet000.png",
		&g_pTextureBullet);

	//弾の初期化
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nLife = 150;
		g_aBullet[nCntBullet].bUse = false;   //使用していない状態にする

		//対角線の長さを算出する
		g_aBullet[nCntBullet].fLengthBullet = sqrtf(BULLET_WIDTH * BULLET_WIDTH + BULLET_HEIGHT * BULLET_HEIGHT) / 2.0f;
		//対角線の角度を算出する
		g_aBullet[nCntBullet].fAngleBullet = atan2f(BULLET_WIDTH, BULLET_HEIGHT);
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4*MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	VERTEX_2D* pVtx;

	//頂点バッファをロックして頂点情報へのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//頂点座標の設定
		pVtx[0].pos.x = 0.0f;
		pVtx[0].pos.y = 0.0f;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = 0.0f;
		pVtx[1].pos.y = 0.0f;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = 0.0f;
		pVtx[2].pos.y = 0.0f;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = 0.0f;
		pVtx[3].pos.y = 0.0f;
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

		pVtx += 4;          //頂点データを4つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();
}

//------------------------------------------
//プレイヤーの終了処理
//------------------------------------------
void UninitBullet(void)
{

	//テクスチャの破棄
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//------------------------------------------
//弾の更新処理
//------------------------------------------
void UpdateBullet(void)
{
	VERTEX_2D* pVtx;
	int nCntbullet;
	//頂点バッファをロックして頂点情報へのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntbullet = 0; nCntbullet < MAX_BULLET; nCntbullet++)
	{
		if (g_aBullet[nCntbullet].bUse == true)
		{ 
			SetEffect(g_aBullet[nCntbullet].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),50.0f,g_aBullet[nCntbullet].fAngleBullet ,50);
		
			if (g_aBullet[nCntbullet].type == BULLETTYPE_PLAYER)
			{
				//弾が使用されている
					Enemy * pEnemy = GetEnemy();      //敵のポインタ
					int nCntEn;

				if (pEnemy->bUse == true)
				{

					for (nCntEn = 0; nCntEn < MAX_ENEMY; nCntEn++, pEnemy++)
					{

						//敵が使用されている

						if (g_aBullet[nCntbullet].pos.x <= pEnemy->pos.x + MAX_WIDTH * 0.5f
							&& g_aBullet[nCntbullet].pos.x >= pEnemy->pos.x - MAX_WIDTH * 0.5f
							&& g_aBullet[nCntbullet].pos.y <= pEnemy->pos.y + MAX_HEIGHT * 0.5f
							&& g_aBullet[nCntbullet].pos.y >= pEnemy->pos.y - MAX_HEIGHT * 0.5f)
						{
							//敵のヒット処理
							HitEnemy(nCntEn, 1);
							g_aBullet[nCntbullet].bUse = false;      //使用してない状態
						}

					}
				}
			}
			else if (g_aBullet[nCntbullet].type == BULLETTYPE_ENEMY)
			{  //敵の弾
				//プレイヤーの取得
				Player* pPlayer = GetPlayer();

				if (pPlayer->bDisp == true)
				{
					//プレイヤーとの当たり判定
					if (g_aBullet[nCntbullet].pos.x <= pPlayer->pos.x + MAX_WIDTH * 0.5f
						&& g_aBullet[nCntbullet].pos.x >= pPlayer->pos.x - MAX_WIDTH * 0.5f
						&& g_aBullet[nCntbullet].pos.y <= pPlayer->pos.y + MAX_HEIGHT * 0.5f
						&& g_aBullet[nCntbullet].pos.y >= pPlayer->pos.y - MAX_HEIGHT * 0.5f)
					{
						HitPlayer(1);
						SetExplosion(g_aBullet[nCntbullet].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), g_aBullet[nCntbullet].rot, g_aBullet[nCntbullet].fLengthBullet);
						g_aBullet[nCntbullet].bUse = false;      //使用してない状態
					}
				}

			}

			//位置を更新
			g_aBullet[nCntbullet].pos.x+= g_aBullet[nCntbullet].move.x;
			g_aBullet[nCntbullet].pos.y += g_aBullet[nCntbullet].move.y;


			//頂点座標の更新
			pVtx[0].pos.x = g_aBullet[nCntbullet].pos.x + sinf(g_aBullet[nCntbullet].rot.z - (D3DX_PI - g_aBullet[nCntbullet].fAngleBullet)) * (g_aBullet[nCntbullet].fLengthBullet / 5);
			pVtx[0].pos.y = g_aBullet[nCntbullet].pos.y + cosf(g_aBullet[nCntbullet].rot.z - (D3DX_PI - g_aBullet[nCntbullet].fAngleBullet)) * (g_aBullet[nCntbullet].fLengthBullet / 5);
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = g_aBullet[nCntbullet].pos.x + sinf(g_aBullet[nCntbullet].rot.z + (D3DX_PI - g_aBullet[nCntbullet].fAngleBullet)) * (g_aBullet[nCntbullet].fLengthBullet / 5);
			pVtx[1].pos.y = g_aBullet[nCntbullet].pos.y + cosf(g_aBullet[nCntbullet].rot.z + (D3DX_PI - g_aBullet[nCntbullet].fAngleBullet)) * (g_aBullet[nCntbullet].fLengthBullet / 5);
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = g_aBullet[nCntbullet].pos.x + sinf(g_aBullet[nCntbullet].rot.z + (0.0f - g_aBullet[nCntbullet].fAngleBullet)) * (g_aBullet[nCntbullet].fLengthBullet / 5);
			pVtx[2].pos.y = g_aBullet[nCntbullet].pos.y + cosf(g_aBullet[nCntbullet].rot.z + (0.0f - g_aBullet[nCntbullet].fAngleBullet)) * (g_aBullet[nCntbullet].fLengthBullet / 5);
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = g_aBullet[nCntbullet].pos.x + sinf(g_aBullet[nCntbullet].rot.z - (0.0f - g_aBullet[nCntbullet].fAngleBullet)) * (g_aBullet[nCntbullet].fLengthBullet / 5);
			pVtx[3].pos.y = g_aBullet[nCntbullet].pos.y + cosf(g_aBullet[nCntbullet].rot.z - (0.0f - g_aBullet[nCntbullet].fAngleBullet)) * (g_aBullet[nCntbullet].fLengthBullet / 5);
			pVtx[3].pos.z = 0.0f;

			g_aBullet[nCntbullet].nLife--; 

			//頂点座標の設定
			if (g_aBullet[nCntbullet].pos.x <= 0.0f || g_aBullet[nCntbullet].pos.x >= SCREEN_WIDTH
				|| g_aBullet[nCntbullet].pos.y <= 0.0f || g_aBullet[nCntbullet].pos.y >= SCREEN_HEIGHT)//弾が画面外にでた

			{
				g_aBullet[nCntbullet].bUse = false;   //使用してない状態にする

			}
			if (g_aBullet[nCntbullet].nLife<=0)
			{
				g_aBullet[nCntbullet].bUse = false;   //使用してない状態にする

				//爆発の設定
				SetExplosion(g_aBullet[nCntbullet].pos,D3DXCOLOR(1.0f,1.0f,1.0f,1.0),g_aBullet[nCntbullet].rot,g_aBullet[nCntbullet].fLengthBullet);
				
			}
		}
		
		pVtx += 4;          //頂点データを4つ分進める
	}
	//頂点バッファをロックして頂点情報へのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);
}

//------------------------------------------
//弾の描画処理
//------------------------------------------
void DrawBullet(void) 
{
	VERTEX_2D* pVtx;
	int nCntBullet;

	LPDIRECT3DDEVICE9 pDevice;   //デバイスへのポインタ
	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			//弾が使用されている
			//ポリゴンの描画
			pDevice->SetTexture(0, g_pTextureBullet);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,4*nCntBullet,2);
		}
	}
}

//------------------------------------------
//弾の設定処理
//------------------------------------------
void SetBullet(D3DXVECTOR3 pos,D3DXVECTOR3 move ,D3DXVECTOR3 rot, float fLength, int nLife, BULLETTYPE type)
{
	VERTEX_2D* pVtx;
	int nCntbullet;


	//頂点バッファをロックして頂点情報へのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntbullet = 0; nCntbullet < MAX_BULLET; nCntbullet++)
	{
		if (g_aBullet[nCntbullet].bUse == false)
		{

			g_aBullet[nCntbullet].pos = pos;
			g_aBullet[nCntbullet].move = move;
			g_aBullet[nCntbullet].rot = rot;
			g_aBullet[nCntbullet].bUse = false;
			g_aBullet[nCntbullet].type = type;

			pVtx[0].pos.x = g_aBullet[nCntbullet].pos.x + sinf(g_aBullet[nCntbullet].rot.z - (D3DX_PI - g_aBullet[nCntbullet].fAngleBullet)) * (g_aBullet[nCntbullet].fLengthBullet / 5);
			pVtx[0].pos.y = g_aBullet[nCntbullet].pos.y + cosf(g_aBullet[nCntbullet].rot.z - (D3DX_PI - g_aBullet[nCntbullet].fAngleBullet)) * (g_aBullet[nCntbullet].fLengthBullet / 5);
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = g_aBullet[nCntbullet].pos.x + sinf(g_aBullet[nCntbullet].rot.z + (D3DX_PI - g_aBullet[nCntbullet].fAngleBullet)) * (g_aBullet[nCntbullet].fLengthBullet / 5);
			pVtx[1].pos.y = g_aBullet[nCntbullet].pos.y + cosf(g_aBullet[nCntbullet].rot.z + (D3DX_PI - g_aBullet[nCntbullet].fAngleBullet)) * (g_aBullet[nCntbullet].fLengthBullet / 5);
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = g_aBullet[nCntbullet].pos.x + sinf(g_aBullet[nCntbullet].rot.z + (0.0f - g_aBullet[nCntbullet].fAngleBullet)) * (g_aBullet[nCntbullet].fLengthBullet / 5);
			pVtx[2].pos.y = g_aBullet[nCntbullet].pos.y + cosf(g_aBullet[nCntbullet].rot.z + (0.0f - g_aBullet[nCntbullet].fAngleBullet)) * (g_aBullet[nCntbullet].fLengthBullet / 5);
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = g_aBullet[nCntbullet].pos.x + sinf(g_aBullet[nCntbullet].rot.z - (0.0f - g_aBullet[nCntbullet].fAngleBullet)) * (g_aBullet[nCntbullet].fLengthBullet / 5);
			pVtx[3].pos.y = g_aBullet[nCntbullet].pos.y + cosf(g_aBullet[nCntbullet].rot.z - (0.0f - g_aBullet[nCntbullet].fAngleBullet)) * (g_aBullet[nCntbullet].fLengthBullet / 5);
			pVtx[3].pos.z = 0.0f;

			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			g_aBullet[nCntbullet].move = move;
			g_aBullet[nCntbullet].nLife = 150;
			g_aBullet[nCntbullet].bUse = true;//使用してる状態にする
			break;
		}
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();
}