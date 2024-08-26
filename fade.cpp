//------------------------------------------
//
//          フェード処理
//       Author:Sudou Akito
//
//------------------------------------------

#include"fade.h"

//グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFade = NULL;    //頂点バッファポインタ
FADE g_fade;                                      //フェードの状態
MODE g_modeNext;                                  //次の画面(モード)
D3DXCOLOR g_colorFade;                            //ポリゴン(フェード)の色

//------------------------------------------
//フェード初期化
//------------------------------------------
void InitFade(MODE modeNext)
{
	g_fade = FADE_IN;    //フェードイン状態

	g_modeNext = modeNext;  //次の画面を設定

	LPDIRECT3DDEVICE9 pDevice;   //デバイスへのポインタ
	VERTEX_2D* pVtx;        //頂点情報のポインタ
	pDevice = GetDevice();  //デバイス取得


	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f); //黒ポリゴン（不透明）にしておく

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 ,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFade,
		NULL);

	//頂点バッファをロックして頂点情報へのポインタを取得
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);


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
	pVtx[0].col = D3DXCOLOR(g_colorFade);
	pVtx[1].col = D3DXCOLOR(g_colorFade);
	pVtx[2].col = D3DXCOLOR(g_colorFade);
	pVtx[3].col = D3DXCOLOR(g_colorFade);

	//頂点バッファをアンロックする
	g_pVtxBuffFade->Unlock();

	SetMode(g_modeNext);
}

//------------------------------------------
//フェード終了
//------------------------------------------
void UninitFade(void)
{
	//頂点バッファの破棄
	if (g_pVtxBuffFade != NULL)
	{
		g_pVtxBuffFade->Release();
		g_pVtxBuffFade = NULL;
	}
}

//------------------------------------------
//フェード更新
//------------------------------------------
void UpdateFade(void)
{

	VERTEX_2D* pVtx;        //頂点情報のポインタ

	//頂点バッファをロックして頂点情報へのポインタを取得
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	if (g_fade != FADE_NONE)
	{
		if (g_fade == FADE_IN)
		{//フェードイン状態
			g_colorFade.a -= 0.02f;    //ポリゴンを透明にする

			if (g_colorFade.a <= 0.0f)
			{
				g_colorFade.a = 0.0f;
				g_fade = FADE_NONE;    //何もしていない状態に
			}
		}
		else if (g_fade == FADE_OUT)
		{
			g_colorFade.a += 0.02f;    //ポリゴン不透明化

			if (g_colorFade.a >= 1.0f)
			{
				g_colorFade.a = 1.0f;
				g_fade = FADE_IN;    //フェードイン状態

				SetMode(g_modeNext);
			}
		}
		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(g_colorFade);
		pVtx[1].col = D3DXCOLOR(g_colorFade);
		pVtx[2].col = D3DXCOLOR(g_colorFade);
		pVtx[3].col = D3DXCOLOR(g_colorFade);
	}

	//頂点バッファをアンロックする
	g_pVtxBuffFade->Unlock();
}

//------------------------------------------
//フェード描画
//------------------------------------------
void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDevice;   //デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffFade, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0,NULL);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0, 2);//プリミティブの種類,プリミティブの数
}

//------------------------------------------
// フェードのセット
//------------------------------------------
void SetFade(MODE modeNext)
{
	g_fade = FADE_OUT;      //フェードアウト状態に

	g_modeNext = modeNext;  //次の画面を設定

	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);  //黒ポリゴンにしておく
}

//------------------------------------------
// 情報を取得
//------------------------------------------
FADE GetFade(void)
{
	return g_fade;
}