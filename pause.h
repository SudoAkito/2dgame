//------------------------------------------
//
//         ポーズ処理
//       Author:Sudou Akito
//
//------------------------------------------
#ifndef _PAUSE_H_
#define _PAUSE_H_

#include"main.h"

//ポーズメニュー
typedef enum
{
	PAUSE_MENU_CONTINUE = 0,    //ゲームに戻る
	PAUSE_MENU_RETRY,         //ゲームやり直し
	PAUSE_MENU_QUIT,          //タイトルに戻る
	PAUSE_MENU_MAX
}PAUSE_MENU;

//プロトタイプ宣言
void InitPause(void);
void UninitPause(void);
void UpdatePause(void);
void DrawPause(void);
void SelectPause(int nNumSelect);

//マクロ定義
#define MAX_UI (4)
#define OFFSET_VALUE (120.0f)

#endif
