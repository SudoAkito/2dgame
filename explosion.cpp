//------------------------------------------
//
//         弾の出力処理
//       Author:Sudou Akito
//
//------------------------------------------
#include"bullet.h"
#include"explosion.h"

//マクロ定義
#define MAX_EXPLOSION (128)           //弾の最大数
#define EX_WIDTH (50)
#define EX_HEIGHT (50)


//弾の構造体
typedef struct
{
	D3DXVECTOR3 pos;    //位置
	D3DXVECTOR3 rot;    //角度
	D3DXCOLOR col;   //移動量
	int nCounterAnim;
	int nPatternAnim;
	bool bUse;          //使用しているかどうか
	float fLengthExplosion;
	float fAngleExplosion;

}Explosion;

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureExplosion = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;
Explosion g_aExplosion[MAX_EXPLOSION];

//------------------------------------------
//爆発の初期化処理
//------------------------------------------
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntExplosion=NULL;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\explosion000.png",
		&g_pTextureExplosion);

	//弾の初期化
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

		//対角線の長さを算出する
		g_aExplosion[nCntExplosion].fLengthExplosion = sqrtf(EX_WIDTH * EX_WIDTH + EX_HEIGHT * EX_HEIGHT) / 2.0f;
		//対角線の角度を算出する
		g_aExplosion[nCntExplosion].fAngleExplosion = atan2f(EX_WIDTH, EX_HEIGHT);

		g_aExplosion[nCntExplosion].nCounterAnim= 0;
		g_aExplosion[nCntExplosion].nPatternAnim = 0;
		g_aExplosion[nCntExplosion].bUse = false;   //使用していない状態にする

	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4*MAX_EXPLOSION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL);

	VERTEX_2D* pVtx;

	//頂点バッファをロックして頂点情報へのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
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
		pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);

		pVtx += 4;          //頂点データを4つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffExplosion->Unlock();
}

//------------------------------------------
//爆発の終了処理
//------------------------------------------
void UninitExplosion(void)
{

	//テクスチャの破棄
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}
}

//------------------------------------------
//爆発の更新処理
//------------------------------------------
void UpdateExplosion(void)
{
	VERTEX_2D* pVtx;
	int nCntExplosion;
	//頂点バッファをロックして頂点情報へのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{ //弾が使用されている
			g_aExplosion[nCntExplosion].nCounterAnim++;

			if ((g_aExplosion[nCntExplosion].nCounterAnim % 10) == 0)
			{
				g_aExplosion[nCntExplosion].nCounterAnim = 0;
				g_aExplosion[nCntExplosion].nPatternAnim = (g_aExplosion[nCntExplosion].nPatternAnim + 1) % 10;

				if (g_aExplosion[nCntExplosion].nPatternAnim >= 8)    //総パターン数超過した場合
				{
					g_aExplosion[nCntExplosion].bUse=false;  //使用していない状態にする
				}

				//テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2(0.125f * g_aExplosion[nCntExplosion].nPatternAnim, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.125f + 0.125f * g_aExplosion[nCntExplosion].nPatternAnim, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.125f * g_aExplosion[nCntExplosion].nPatternAnim, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.125f + 0.125f * g_aExplosion[nCntExplosion].nPatternAnim, 1.0f);
			}
		}
		pVtx += 4;          //頂点データを4つ分進める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffExplosion->Unlock();
}

//------------------------------------------
//爆発の描画処理
//------------------------------------------
void DrawExplosion(void) 
{
	VERTEX_2D* pVtx;
	int nCntExplosion;

	LPDIRECT3DDEVICE9 pDevice;   //デバイスへのポインタ
	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		pDevice->SetTexture(0, g_pTextureExplosion);
		if (g_aExplosion[nCntExplosion].bUse == true)
		{
			//弾が使用されている
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,4*nCntExplosion,2);
		}
	}
}

//------------------------------------------
//爆発の設定処理
//------------------------------------------
void SetExplosion(D3DXVECTOR3 pos,D3DXCOLOR col, D3DXVECTOR3 rot,float fLength)
{
	VERTEX_2D* pVtx;
	int nCntExplosion;


	//頂点バッファをロックして頂点情報へのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == false)
		{

			g_aExplosion[nCntExplosion].pos = pos;
			g_aExplosion[nCntExplosion].rot = rot;

			pVtx[0].pos.x = g_aExplosion[nCntExplosion].pos.x + sinf(g_aExplosion[nCntExplosion].rot.z - (D3DX_PI - g_aExplosion[nCntExplosion].fAngleExplosion)) * (g_aExplosion[nCntExplosion].fLengthExplosion );
			pVtx[0].pos.y = g_aExplosion[nCntExplosion].pos.y + cosf(g_aExplosion[nCntExplosion].rot.z - (D3DX_PI - g_aExplosion[nCntExplosion].fAngleExplosion)) * (g_aExplosion[nCntExplosion].fLengthExplosion );
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = g_aExplosion[nCntExplosion].pos.x + sinf(g_aExplosion[nCntExplosion].rot.z + (D3DX_PI - g_aExplosion[nCntExplosion].fAngleExplosion)) * (g_aExplosion[nCntExplosion].fLengthExplosion );
			pVtx[1].pos.y = g_aExplosion[nCntExplosion].pos.y + cosf(g_aExplosion[nCntExplosion].rot.z + (D3DX_PI - g_aExplosion[nCntExplosion].fAngleExplosion)) * (g_aExplosion[nCntExplosion].fLengthExplosion);
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = g_aExplosion[nCntExplosion].pos.x + sinf(g_aExplosion[nCntExplosion].rot.z + (0.0f - g_aExplosion[nCntExplosion].fAngleExplosion)) * (g_aExplosion[nCntExplosion].fLengthExplosion);
			pVtx[2].pos.y = g_aExplosion[nCntExplosion].pos.y + cosf(g_aExplosion[nCntExplosion].rot.z + (0.0f - g_aExplosion[nCntExplosion].fAngleExplosion)) * (g_aExplosion[nCntExplosion].fLengthExplosion);
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = g_aExplosion[nCntExplosion].pos.x + sinf(g_aExplosion[nCntExplosion].rot.z - (0.0f - g_aExplosion[nCntExplosion].fAngleExplosion)) * (g_aExplosion[nCntExplosion].fLengthExplosion);
			pVtx[3].pos.y = g_aExplosion[nCntExplosion].pos.y + cosf(g_aExplosion[nCntExplosion].rot.z - (0.0f - g_aExplosion[nCntExplosion].fAngleExplosion)) * (g_aExplosion[nCntExplosion].fLengthExplosion);
			pVtx[3].pos.z = 0.0f;

			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			g_aExplosion[nCntExplosion].col = col;
			g_aExplosion[nCntExplosion].bUse = true;//使用してる状態にする
			break;
		}
		pVtx += 4;

	}
	//頂点バッファをアンロックする
	g_pVtxBuffExplosion->Unlock();
}