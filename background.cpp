//------------------------------------------
//
//			背景処理
//       Author:Sudou Akito
//
//------------------------------------------

#include"player.h"
#include"background.h"

//マクロ定義
#define NUM_BG (3)      //背景の数

//グローバル変数
LPDIRECT3DTEXTURE9 g_apTextureBackground2[NUM_BG] = {};     //テクスチャ(３枚分)へのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBackground = NULL;
float g_aPosTexU[NUM_BG];          //テクスチャ座標の開始位置(U値)

//------------------------------------------
//プレイヤー初期化処理
//------------------------------------------
void InitBackground(void)
{
	LPDIRECT3DDEVICE9 pDevice;   //デバイスへのポインタ
	int nCntBG;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bg100.png",
		&g_apTextureBackground2[0]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bg101.png",
		&g_apTextureBackground2[1]);


	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bg102.png",
		&g_apTextureBackground2[2]);

	//テクスチャ座標の開始位置(U値)の初期化
	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		g_aPosTexU[nCntBG] = 0.0f;
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4*NUM_BG,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBackground,
		NULL);

	VERTEX_2D* pVtx;        //頂点情報のポインタ

	//頂点バッファをロックして頂点情報へのポインタを取得
	g_pVtxBuffBackground->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

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
		pVtx[0].tex = D3DXVECTOR2(g_aPosTexU[nCntBG],0.0f);
		pVtx[1].tex = D3DXVECTOR2(g_aPosTexU[nCntBG]+1.0f,0.0f);
		pVtx[2].tex = D3DXVECTOR2(g_aPosTexU[nCntBG],1.0f);
		pVtx[3].tex = D3DXVECTOR2(g_aPosTexU[nCntBG]+1.0f,1.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffBackground->Unlock();
}

//------------------------------------------
//プレイヤーの終了処理
//------------------------------------------
void UninitBackground(void)
{
	int nCntBG;
	//テクスチャの破棄
	for (nCntBG=0;nCntBG<NUM_BG;nCntBG++)
	{
		if (g_apTextureBackground2[nCntBG] != NULL)
		{
			g_apTextureBackground2[nCntBG]->Release();

			g_apTextureBackground2[nCntBG] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffBackground!= NULL)
	{
		g_pVtxBuffBackground->Release();
		g_pVtxBuffBackground = NULL;
	}
}

//------------------------------------------
//背景の更新処理
//------------------------------------------
void UpdateBackground(void)
{
	int nCntBG;
	VERTEX_2D* pVtx;        //頂点情報のポインタ


	//頂点バッファをロックして頂点情報へのポインタを取得
	g_pVtxBuffBackground->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		//テクスチャ座標の開始位置の更新
		g_aPosTexU[nCntBG]+=0.0001f*(nCntBG+1);
		
		//テクスチャ座標の更新
		pVtx[0].tex = D3DXVECTOR2(g_aPosTexU[nCntBG], 0.0f);
		pVtx[1].tex = D3DXVECTOR2(g_aPosTexU[nCntBG] + 1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(g_aPosTexU[nCntBG], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(g_aPosTexU[nCntBG] + 1.0f, 1.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffBackground->Unlock();
}
	
//------------------------------------------
//プレイヤーの描画処理
//------------------------------------------
void DrawBackground(void)
{
	LPDIRECT3DDEVICE9 pDevice;   //デバイスへのポインタ
	int nCntBG;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBackground, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_apTextureBackground2[nCntBG]);
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,nCntBG*4, 2);//プリミティブの種類,プリミティブの数
	}
}