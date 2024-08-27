//------------------------------------------
//
//         ポーズ処理
//       Author:Sudou Akito
//
//------------------------------------------

#include"pause.h"
#include"input.h"
#include "fade.h"
#include "game.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexturePause[MAX_UI] = {};       //テクスチャポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;    //頂点バッファポインタ
PAUSE_MENU g_pauseMenu;                            //ポーズメニュー

//------------------------------------------
//ポーズ画面の初期化処理
//------------------------------------------
void InitPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;   //デバイスへのポインタ
	int nCntPu;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\CONTUNUE.png",
		&g_pTexturePause[1]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Retry.png",
		&g_pTexturePause[2]);


	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Quit.png",
		&g_pTexturePause[3]);


	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_UI,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPause,
		NULL);

	VERTEX_2D* pVtx;        //頂点情報のポインタ

	//頂点バッファをロックして頂点情報へのポインタを取得
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	float max_y = 150.0f;
	float max_x = 800.0f;
	float min_y = 50.0f;
	float min_x = 400.0f;

	for (nCntPu = 0; nCntPu < MAX_UI; nCntPu++)
	{
		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		if (nCntPu == 0)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

			//頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(0,0,0,120);
			pVtx[1].col = D3DCOLOR_RGBA(0,0,0,120);
			pVtx[2].col = D3DCOLOR_RGBA(0,0,0,120);
			pVtx[3].col = D3DCOLOR_RGBA(0,0,0,120);
		}
		else if(nCntPu==1)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(min_x, min_y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(max_x, min_y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(min_x, max_y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(max_x, max_y, 0.0f);
		}
		else if (nCntPu == 2)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(min_x, min_y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(max_x, min_y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(min_x, max_y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(max_x, max_y, 0.0f);
		}
		else if (nCntPu == 3)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(min_x, min_y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(max_x, min_y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(min_x, max_y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(max_x, max_y, 0.0f);
		}

		min_y += OFFSET_VALUE;
		max_y += OFFSET_VALUE;

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	
	//頂点バッファをアンロックする
	g_pVtxBuffPause->Unlock();

	g_pauseMenu = PAUSE_MENU_CONTINUE;
}

//------------------------------------------
//ポーズ画面の終了処理
//------------------------------------------
void UninitPause(void)
{
	//テクスチャの破棄
	for (int nCntPu = 0; nCntPu < MAX_UI; nCntPu++)
	{
		if (g_pTexturePause[nCntPu] != NULL)
		{
			g_pTexturePause[nCntPu]->Release();
			g_pTexturePause[nCntPu] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}
}

//------------------------------------------
// ポーズの更新処理
//------------------------------------------
void UpdatePause(void)
{
	//メニューの選択
	switch (g_pauseMenu)
	{
	case PAUSE_MENU_CONTINUE:
		if (KeyboardTrigger(DIK_UP) == true)
		{
			g_pauseMenu = PAUSE_MENU_QUIT;
		}
		else if (KeyboardTrigger(DIK_DOWN) == true)
		{
			g_pauseMenu = PAUSE_MENU_RETRY;
		}
		SelectPause(1);
		break;
	
	case PAUSE_MENU_RETRY:
		if (KeyboardTrigger(DIK_UP) == true)
		{
			g_pauseMenu = PAUSE_MENU_CONTINUE;
		}
		else if (KeyboardTrigger(DIK_DOWN) == true)
		{
			g_pauseMenu = PAUSE_MENU_QUIT;
		}
		SelectPause(2);

		break;

	case PAUSE_MENU_QUIT:
		if (KeyboardTrigger(DIK_UP) == true)
		{
			g_pauseMenu = PAUSE_MENU_QUIT;
		}
		else if (KeyboardTrigger(DIK_DOWN) == true)
		{
			g_pauseMenu = PAUSE_MENU_CONTINUE;
		}
		SelectPause(3);

		break;
	}

	if (KeyboardTrigger(DIK_RETURN) == true)
	{//ENTERが押されたとき
		//メニューに合わせてモードの切り替え
		switch (g_pauseMenu)
		{
		case PAUSE_MENU_CONTINUE:
			SetEnablePause(false);
			break;

		case PAUSE_MENU_RETRY:
			SetFade(MODE_GAME);
			break;

		case PAUSE_MENU_QUIT:
			SetFade(MODE_TITLE);
			break;
		}
	}
}

//------------------------------------------
//ポーズの描画処理
//------------------------------------------
void DrawPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;   //デバイスへのポインタ
	int nCntPu;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntPu = 0; nCntPu < MAX_UI; nCntPu++)
	{
		pDevice->SetTexture(0, g_pTexturePause[nCntPu]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntPu,2);//プリミティブの種類,プリミティブの数

	}
}

//------------------------------------------
//ポーズの選択処理
//------------------------------------------
void SelectPause(int nNumSelect)
{
	VERTEX_2D* pVtx;        //頂点情報のポインタ

		//頂点バッファをロックして頂点情報へのポインタを取得
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntPu = 0; nCntPu < MAX_UI; nCntPu++)
	{
		if (nCntPu == 0)
		{
			//頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(0, 0, 0, 120);
			pVtx[1].col = D3DCOLOR_RGBA(0, 0, 0, 120);
			pVtx[2].col = D3DCOLOR_RGBA(0, 0, 0, 120);
			pVtx[3].col = D3DCOLOR_RGBA(0, 0, 0, 120);
		}
		else if (nCntPu == nNumSelect)
		{
			//頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}
		else
		{
			//頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(150, 150, 150, 255);
			pVtx[1].col = D3DCOLOR_RGBA(150, 150, 150, 255);
			pVtx[2].col = D3DCOLOR_RGBA(150, 150, 150, 255);
			pVtx[3].col = D3DCOLOR_RGBA(150, 150, 150, 255);
		}

		pVtx += 4;
	}
	
	//頂点バッファをアンロックする
	g_pVtxBuffPause->Unlock();
}