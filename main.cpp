//------------------------------------------
//
//       DirectXの基本処理
//       Author:Sudou Akito
//
//------------------------------------------
#include"main.h"
#include"title.h"
#include"game.h"
#include"result.h"
#include"fade.h"
#include"sound.h"

//グローバル変数
LPDIRECT3D9 g_pD3D = NULL;       //DirectXオブジェクトへのポインタ
LPDIRECT3DDEVICE9 g_pD3DDevice;  //DirectXデバイスへのポインタ
MODE g_mode = MODE_TITLE;        //現在のモード
FADE g_fademode;

//------------------------------------------
//メイン関数
//------------------------------------------
int WINAPI WinMain(_In_ HINSTANCE hInstance,_In_opt_ HINSTANCE hInstncePrev,_In_ LPSTR lPpCmdLine,_In_ int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),    //WNDCLASSEXのメモリサイズ
		CS_CLASSDC,            //ウィンドウのスタイル
		WindowProc,            //ウィ ンドウプロシージャ
		0,                     //0にする（通常は使用しない）
		0,                     //0にする（通常は使用しない）
		hInstance,             //インスタンスハンドル
		LoadIcon(NULL,IDI_APPLICATION), //タスクバーのアイコン
		LoadCursor(NULL,IDC_ARROW),  //マウスカーソル
		(HBRUSH)(COLOR_WINDOW + 1),  //クライアント領域の背景色
		NULL,                        //メニューバー
		CLASS_NAME,                  //ウィンドウクラスのアイコン
		LoadIcon(NULL,IDI_APPLICATION), //ファイルのアイコン
	};

	DWORD dwCurrentTime;   //現在時刻
	DWORD dwExecLastTime;  //最後に処理した時刻
	HWND hWnd;  //ウィンドウハンドル（識別子）
	MSG msg;    //メッセージを格納する変数

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };    //画面サイズの構造体

	//ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	//クライアント領域を指定のサイズに調整
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//ウィンドウを生成
	hWnd = CreateWindowEx(0,      //拡張ウィンドウスタイル
		CLASS_NAME,             //ウィンドウクラスの名前
		WINDOW_NAME,            //ウィンドウの名前
		WS_OVERLAPPEDWINDOW,    //ウィンドウスタイル
		CW_USEDEFAULT,          //ウィンドウの左上X座標
		CW_USEDEFAULT,          //〃左上Y座標
		(rect.right-rect.left),//〃幅
		(rect.bottom - rect.top),//〃高さ
		NULL,					//親ウィンドウのハンドル
		NULL,					//メニューハンドルまたは子ウィンドウID
		hInstance,				//インスタンスハンドル
		NULL);                  //ウィンドウ作成データ

	//初期化処理
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}

	g_fademode = FADE_IN;

	//分解能を設定
	timeBeginPeriod(1);
	dwCurrentTime = 0;                //初期化する
	dwExecLastTime = timeGetTime();   //現在時刻を取得（保存）

	ShowWindow(hWnd, nCmdShow);    //ウィンドウの表示状態を設定
	UpdateWindow(hWnd);            //クライアント領域を更新

	//メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//windowの処理
			if (msg.message == WM_QUIT)
			{//WM_QUITメッセを受け取ったらメッセループを抜ける
				break;
			}
			else
			{
				//メッセージの設定
				TranslateMessage(&msg);   //仮想メッセージを文字メッセージへ
				DispatchMessage(&msg);    //ウィンドウプロシージャへメッセージを送出
			}
		}
		else
		{//DirectXの更新

			dwExecLastTime = timeGetTime();   //現在時刻を取得
			if ((dwCurrentTime- dwExecLastTime)>=(1000/60))
			{//60分の1秒経過
				dwExecLastTime = dwCurrentTime;  //処理開始の時刻[現在時刻]を保存
			}
			//更新処理
			Update();

			//描画処理
			Draw();
		}
	}
	//終了処理
	Uninit();

	//分解能を戻す
	timeEndPeriod(1);

	//ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return(int)msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	const RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };  //ウィンドウの領域(矩形)

	switch (uMsg)
	{
	case WM_DESTROY:   //ウィンドウ破棄のメッセージ
		//WM_QUITメッセージを送る
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN: //キー押下のメッセージ
		switch (wParam)
		{
			case VK_ESCAPE: //[ESC]キーが押され
				DestroyWindow(hWnd);
				break;
		}
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);   //既定の処理を返す
}

//------------------------------------------
// 初期化処理
//------------------------------------------
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;           //ディスプレイモード
	D3DPRESENT_PARAMETERS d3dpp;    //プレゼンテーションパラメーター

	//DirectX3Dオブジェの生成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//現在のディスプレイモードを取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//プレゼンテーションパラメーターの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));    //パラメータのゼロクリア

	d3dpp.BackBufferWidth = SCREEN_WIDTH; //ゲーム画面のサイズ（幅）

	d3dpp.BackBufferHeight = SCREEN_HEIGHT;//ゲーム画面のサイズ（高さ）

	d3dpp.BackBufferFormat = d3ddm.Format; //バックバッファの形式
	 
	d3dpp.BackBufferCount = 1;             //バックバッファの数

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD; //ダブルバッファの切り替え（映像信号に同期）

	d3dpp.EnableAutoDepthStencil = TRUE;      //デプスバッファとステンシルバッファを作成

	d3dpp.AutoDepthStencilFormat = D3DFMT_D16; //デプスバッファとして16bitを使う

	d3dpp.Windowed = bWindow;                 //ウィンドウモード

	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;  //リフレッシュレート

	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;   //インターバル

	//DirectX3Dデバイスの生成（描画処理と頂点処理をハードウェアで行う）
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))

	{///DirectX3Dデバイスの生成（描画処理をハードウェア,頂点処理をCPUで行う）
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_HAL,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	//レンダーステートの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//サンプラーステートの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//テクスチャステージステートの設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//キーボード
	if (FAILED(InitKeyBoard(hInstance, hWnd)))
	{
		return E_FAIL;
	}
	
	//ジョイパッドの初期化処理
	if (FAILED(InitJoypad()))
	{
		return E_FAIL;
	}

	//サウンド設定
	InitSound(hWnd);

	//モード設定
	SetMode(g_mode);

	//フェードの設定
	InitFade(g_mode);

	return S_OK;
}

//------------------------------------------
//終了処理
//------------------------------------------
void Uninit(void)
{

	//タイトル終了処理
	UninitTitle();

	//ゲーム画面終了処理
	UninitGame();

	//リザルト画面の終了処理
	UninitResult();

	//サウンド終了処理
	UninitSound();

	//キーボードの終了処理
	UninitKeyBoard();

	//ジョイパッドの終了処理
	UninitJoypad();

	//フェードの終了
	UninitFade();

	

	//Direct3Dデバイスの破棄
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//------------------------------------------
//更新処理
//------------------------------------------
void Update(void)
{

	//キーボード更新処理
	UpdateKeyBoard();

	//ジョイパッド更新処理
	UpdateJoypad();

	switch (g_mode)
	{
	case MODE_TITLE:   //タイトル画面
		UpdateTitle();
		break;

	case MODE_GAME:   //ゲーム画面
		UpdateGame();
		break;

	case MODE_RESULT:  //リザルト画面
		UpdateResult();
		break;
	}

	//フェードの更新
	UpdateFade();

}

//------------------------------------------
//描画処理
//------------------------------------------
void Draw(void)
{
	//画面クリア
	g_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);
	//描画開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{

		switch (g_mode)
		{
		case MODE_TITLE:
			DrawTitle();
			break;

		case MODE_GAME:
			DrawGame();
			break;

		case MODE_RESULT:
			DrawResult();
			break;
		}

		//フェードの更新処理
		DrawFade();

		//描画終了
		g_pD3DDevice->EndScene();
	}
	//バックバッファとフロントバッファを入れ替える
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//------------------------------------------
//モードの設定
//------------------------------------------
void SetMode(MODE mode)
{
	//現在のモードの終了処理
	switch (g_mode)
	{
	case MODE_TITLE:
		//タイトル終了処理
		UninitTitle();
		break;

	case MODE_GAME:
		//ゲーム画面終了処理
		UninitGame();
		break;

	case MODE_RESULT:
		//リザルト画面の終了処理
		UninitResult();
		break;
	}

	//新しいモードの初期化処理
	switch(mode)
	{
	case MODE_TITLE:
		InitTitle();
		break;

	case MODE_GAME:
		InitGame();
		break;

	case MODE_RESULT:
		InitResult();
		break;
	}

	g_mode = mode;    //現在のモードを切り替える
}

//------------------------------------------
//モードの取得
//------------------------------------------
MODE GetMode(void)
{
	return g_mode;
}

LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}