//------------------------------------------
//
//     　 スコア処理
//       Author:Sudou Akito
//
//------------------------------------------

#include "score.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureScore = NULL;      //テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL; //頂点バッファポインタ
D3DXVECTOR3 g_posScore;                         //スコアの位置
int g_nScore;                                   //スコアの値

//------------------------------------------
//　スコア初期化処理
//------------------------------------------
void InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;   //デバイスへのポインタ
	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\number000.png",
		&g_pTextureScore);

	g_posScore = D3DXVECTOR3(0.0f,0.0f,0.0f);  //位置初期化
	g_nScore = 0;                              //値初期化

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 *MAX_KETA,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL);

	VERTEX_2D* pVtx;       //頂点情報のポインタ

	//頂点バッファをロックして頂点情報へのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_KETA; nCnt++)
	{
		//頂点座標設定
		pVtx[0].pos = D3DXVECTOR3(850.0f + nCnt * 40.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(850.0f + nCnt * 40.0f + 40.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(850.0f + nCnt * 40.0f, 90.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(850.0f + nCnt * 40.0f + 40.0f, 90.0f, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255,255,255,255);
		pVtx[1].col = D3DCOLOR_RGBA(255,255,255,255);
		pVtx[2].col = D3DCOLOR_RGBA(255,255,255,255);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;
	}
	
	//頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();
}

//------------------------------------------
//  スコア終了処理
//------------------------------------------
void UninitScore(void)
{
	//テクスチャの破棄
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
}

//------------------------------------------
//  スコア更新処理
//------------------------------------------
void UpdateScore(void)
{
	//スコアに演出を加える場合書く
}

//------------------------------------------
//     スコア描画処理
//------------------------------------------
void DrawScore(void)
{
	//必要桁数分の描画
	LPDIRECT3DDEVICE9 pDevice;   //デバイスへのポインタ
	//デバイスの取得
	pDevice = GetDevice();

	VERTEX_2D* pVtx;       //頂点情報のポインタ

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);


	//頂点バッファをロックして頂点情報へのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);


	for (int nCnt = 0; nCnt < MAX_KETA; nCnt++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureScore);

		//スコアの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4*nCnt, 2);//プリミティブの種類,プリミティブの数

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f + (nCnt / 10), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (nCnt / 10), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (nCnt / 10), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (nCnt / 10), 1.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();
}

//------------------------------------------
//     スコア設定処理
//------------------------------------------
void SetScore(int nScore)
{
	int aPosTexU[8];    //各桁の数字を格納
	int nCnt{};
	g_nScore = nScore;
	int eight = EIGHT;
	int seven = SEVEN;
	VERTEX_2D* pVtx;       //頂点情報のポインタ

	for (int nCnt = 0; nCnt < 8; nCnt++)
	{
		if (aPosTexU[nCnt] == aPosTexU[0])
		{
			aPosTexU[0] = g_nScore / EIGHT;
		}
		else
		{
			aPosTexU[nCnt] = g_nScore % EIGHT / SEVEN;
			eight = EIGHT / 10;
			seven = SEVEN / 10;
		}
	}

	//頂点バッファをロックして頂点情報へのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt1 = 0; nCnt < MAX_KETA; nCnt++)
	{
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);
	}

	//頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();
}

//------------------------------------------
//     スコア加算処理
//------------------------------------------
void AddScore(int nValue)
{
	int aPosTexU[8];   //各桁の数字を格納
	int nCnt{};
	VERTEX_2D* pVtx;       //頂点情報のポインタ
	g_nScore += nValue;

	int eight = EIGHT;
	int seven = SEVEN;

	for (int nCnt = 0; nCnt < 8; nCnt++)
	{
		if (aPosTexU[nCnt] == aPosTexU[0])
		{
			aPosTexU[0] = g_nScore / EIGHT;
		}
		else
		{
			aPosTexU[nCnt] = g_nScore % EIGHT / SEVEN;
			eight= EIGHT / 10;
			seven = SEVEN / 10;
		}
	}
	//頂点バッファをロックして頂点情報へのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt1 = 0; nCnt < MAX_KETA; nCnt++)
	{
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

	}
	
	//頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();
}

