//------------------------------------------
//
//       DirectXの基本処理
//       Author:Sudou Akito
//
//------------------------------------------
#ifndef _MAIN_H_        //マクロ定義がされてなかったら
#define _MAIN_H_        //二重インクルード防止のマクロ定義
 
#include<windows.h>
#include"d3dx9.h"       //描画処理に必要
#define DIRECTINPUT_VERSON (0x0800)    //ビルド時の警告対処用マクロ
#include"dinput.h"                    //入力処理に必要
#include "Xinput.h"     //ジョイパッド処理に必要
#include"xaudio2.h"


//ライブラリのリンク
#pragma comment(lib,"d3d9.lib")  //描画処理に必要
#pragma comment(lib,"d3dx9.lib") //[d3dx9.lib]の拡張ライブラリ
#pragma comment(lib,"dxguid.lib")//DirectXコンポーネント使用に必要
#pragma comment(lib,"winmm.lib") //システム時刻取得に必要
#pragma comment(lib,"dinput8.lib")//入力処理に必要
#pragma comment(lib,"xinput.lib") //ジョイパッド処理に必要

//マクロ定義
#define CLASS_NAME "WindowClass"			//ウィンドウクラスの名前
#define WINDOW_NAME "DirectXの基本処理"	    //ウィンドウの名前（キャプションに表示）
#define SCREEN_WIDTH (1280)					//ウィンドウの幅
#define SCREEN_HEIGHT (720)		            //ウィンドウの高さ
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)

//頂点情報[2D]の構造体を定義
typedef struct
{
	D3DXVECTOR3 pos;    //頂点座標
	float rhw;          //座標変換用係数（１．０ｆで固定）
	D3DCOLOR col;       //座標カラー
	D3DXVECTOR2 tex;    //テクスチャ座標
}VERTEX_2D;

//画面の種類
typedef enum
{
	MODE_TITLE=0,   //タイトル画面
	MODE_GAME,      //ゲーム画面
	MODE_RESULT,    //リザルト画面
	MODE_MAX
}MODE;

//#define ID_BUTTON_FINISH (101)              //終了ボタンのID
//#define ID_BUTTON_COPY (102)                //コピーボタンID
//#define ID_EDIT_INPUT (111)                 //入力ウィンドウID
//#define ID_EDIT_OUTPUT (121)                //出力ウィンドウID
//#define ID_TIMER (122)                      //タイマーID
//#define ID_TIMER_INTERVAL (1000/60)         //タイマーの発生感覚（ミリ秒）

//プロトタイプ宣言
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
void SetMode(MODE mode);
MODE GetMode(void);

LPDIRECT3DDEVICE9 GetDevice(void);

#endif
