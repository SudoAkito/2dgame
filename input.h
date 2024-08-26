//------------------------------------------
//
//         入力処理
//       Author:Sudou Akito
//
//------------------------------------------
#ifndef _INPUT_H_
#define _INPUT_H_

#include"main.h"

//キーの種類
typedef enum
{
	JOYKEY_UP=0,   //十字キー上
	JOYKEY_DOWN=1,
	JOYKEY_LEFT=2,
	JOYKEY_RIGHT=3,
	JOYKEY_START =4,
	JOYKEY_BACK=5,
	JOYKEY_R3=6,
	JOYKEY_L3=7,
	JOYKEY_RB=8,
	JOYKEY_LB=9,
	JOYKEY_RT=10,
	JOYKEY_LT=11,
	JOYKEY_A=12,
	JOYKEY_B=13,
	JOYKEY_X=14,
	JOYKEY_Y=15,
}JOYKEY;


//プロトタイプ宣言
HRESULT InitKeyBoard(HINSTANCE hInstance, HWND hWnd);
void UninitKeyBoard(void);
void UpdateKeyBoard(void);
bool GetKeyboardPress(int nKey);
bool KeyboardTrigger(int nKey);
bool KeyboardRelease(int nKey);
bool KeyboardRepeat(int nKey);

//プロトタイプ宣言
HRESULT InitJoypad(void);
void UninitJoypad(void);
void UpdateJoypad(void);
bool GetJoypadPress(JOYKEY key);
bool JoypadTrigger(JOYKEY key);

#endif

