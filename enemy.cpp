//------------------------------------------
//
//			   敵処理
//         Author:Sudou Akito
//
//------------------------------------------

#include"bullet.h"
#include"enemy.h"
#include"explosion.h"

//マクロ定義
#define NUM_ENEMY (1)                 //敵の種類

//グローバル変数
LPDIRECT3DTEXTURE9 g_apTextureEnemy[NUM_ENEMY] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;
Enemy g_aEnemy[MAX_ENEMY];      //敵の情報
int g_nNumEnemy = 0;            //敵の総数

//------------------------------------------
//敵の初期化処理
//------------------------------------------
void InitEnemy(void)
{

	int nCntEN{};

	LPDIRECT3DDEVICE9 pDevice;   //デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\enemy1.png",
		&g_apTextureEnemy[0]);

	//敵の初期化
	for (nCntEN = 0; nCntEN <MAX_ENEMY ; nCntEN++)
	{
		g_aEnemy[nCntEN].pos= D3DXVECTOR3(0.0f,0.0f,0.0f);
		g_aEnemy[nCntEN].move= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEN].rot= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEN].state = {};
		g_aEnemy[nCntEN].nCounterState=0;
		g_aEnemy[nCntEN].nLife=0;
		g_aEnemy[nCntEN].nunti = 0;
		g_aEnemy[nCntEN].nType=0;
		g_aEnemy[nCntEN].bUse=false;
		g_aEnemy[nCntEN].fLength=0;
		g_aEnemy[nCntEN].fAngle = 0;
	}
	g_nNumEnemy = 0;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4*MAX_ENEMY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy,
		NULL);

	VERTEX_2D* pVtx;        //頂点情報のポインタ

//頂点バッファをロックして頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEN = 0; nCntEN < MAX_ENEMY; nCntEN++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f); 
	}
	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
}

//------------------------------------------
//敵の終了処理
//------------------------------------------
void UninitEnemy(void)
{
	int nCntEN;

	//テクスチャの破棄
	for (nCntEN = 0; nCntEN < NUM_ENEMY; nCntEN++)
	{
		if (g_apTextureEnemy[nCntEN] != NULL)
		{
			g_apTextureEnemy[nCntEN]->Release();
			g_apTextureEnemy[nCntEN] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
}

//------------------------------------------
// 敵の更新処理
//------------------------------------------
void UpdateEnemy(void)
{
	int nCntEN{};

	VERTEX_2D* pVtx;        //頂点情報のポインタ


	//使用されている敵が弾を撃つ処理
	for (nCntEN = 0; nCntEN < MAX_ENEMY; nCntEN++)
	{
		if (g_aEnemy[nCntEN].bUse == true)
		{
			switch (g_aEnemy[nCntEN].state)
			{
			case ENEMYSTATE_NORMAL:
				g_aEnemy[nCntEN].nunti++;
				if (g_aEnemy[nCntEN].nunti >= 30)
				{
					SetBullet(g_aEnemy[nCntEN].pos, D3DXVECTOR3(sinf(g_aEnemy[nCntEN].rot.z + D3DX_PI) * MAX_SPEED, cosf(g_aEnemy[nCntEN].rot.z + D3DX_PI) * MAX_SPEED, 0.0f), g_aEnemy[nCntEN].rot, g_aEnemy[nCntEN].fLength, 150, BULLETTYPE_ENEMY);
					g_aEnemy[nCntEN].nunti = 0;
				}
				break;

			case ENEMYSTATE_DAMAGE:

				//頂点バッファをロックして頂点情報へのポインタを取得
				g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

				g_aEnemy[nCntEN].nCounterState--;
				if (g_aEnemy[nCntEN].nCounterState <= 0)
				{
					g_aEnemy[nCntEN].state = ENEMYSTATE_NORMAL;
					//頂点カラーの設定
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				}
				break;
				//頂点バッファをアンロックする
				g_pVtxBuffEnemy->Unlock();
			}
		}
	}
}

//------------------------------------------
// 敵の描画処理
//------------------------------------------
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;   //デバイスへのポインタ
	int nCntEN;
	//デバイスの取得
	pDevice = GetDevice();

	//頂点フォーマットの設定
	/*pDevice->SetFVF(FVF_VERTEX_2D);*/

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	for (nCntEN = 0; nCntEN < MAX_ENEMY; nCntEN++)
	{
		if (g_aEnemy[nCntEN].bUse == true)
		{
			int nType = g_aEnemy[nCntEN].nType;
			//テクスチャの設定
			pDevice->SetTexture(0, g_apTextureEnemy[nCntEN]);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,nCntEN*4,2);//プリミティブの種類,プリミティブの数
		}
	}
}

//------------------------------------------
// 敵のセット処理
//------------------------------------------
void SetEnemy(D3DXVECTOR3 pos, int nType)
{
	int nCntEN;
	VERTEX_2D* pVtx;        //頂点情報のポインタ

	//頂点バッファをロックして頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEN = 0; nCntEN < MAX_ENEMY; nCntEN++)
	{
		if(g_aEnemy[nCntEN].bUse == false)
		{//敵が使用されていない

			//敵の情報の設定
			g_aEnemy[nCntEN].pos= pos;
			g_aEnemy[nCntEN].state =ENEMYSTATE_NORMAL;
			g_aEnemy[nCntEN].nCounterState=0;//状態管理カウンター
			g_aEnemy[nCntEN].nLife=10;        //体力
			g_aEnemy[nCntEN].nType =nType;
		
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEN].pos.x-MAX_WIDTH * 0.5f, g_aEnemy[nCntEN].pos.y - MAX_HEIGHT * 0.5f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEN].pos.x+MAX_WIDTH * 0.5f, g_aEnemy[nCntEN].pos.y - MAX_HEIGHT * 0.5f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEN].pos.x-MAX_WIDTH * 0.5f, g_aEnemy[nCntEN].pos.y + MAX_HEIGHT * 0.5f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEN].pos.x+MAX_WIDTH * 0.5f, g_aEnemy[nCntEN].pos.y + MAX_HEIGHT * 0.5f, 0.0f);
			g_aEnemy[nCntEN].bUse = true;
			g_nNumEnemy++;
			break;
		}
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
}
//------------------------------------------
//敵の情報
//------------------------------------------
Enemy* GetEnemy(void)
{
	return &g_aEnemy[0];
}

//------------------------------------------
// 敵の当たり判定の後処理
//------------------------------------------
void HitEnemy(int nCntEn, int nDmg)
{
	VERTEX_2D* pVtx;        //頂点情報のポインタ

	g_aEnemy[nCntEn].nLife -= nDmg;

	//頂点バッファをロックして頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	if (g_aEnemy[nCntEn].nLife<=0)
	{
		SetExplosion(g_aEnemy[nCntEn].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), g_aEnemy[nCntEn].rot, g_aEnemy[nCntEn].fLength);
		g_aEnemy[nCntEn].bUse = false;
		g_nNumEnemy--;                //敵の総数カウントダウン
	}
	else
	{
		g_aEnemy[nCntEn].state=ENEMYSTATE_DAMAGE;
		g_aEnemy[nCntEn].nCounterState = 5;

		pVtx += 4 * nCntEn;

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0 ,255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0 ,0, 255);
	}
	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
}

int GetNumEnemy()
{
	return g_nNumEnemy;
}

