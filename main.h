//------------------------------------------
//
//       DirectX�̊�{����
//       Author:Sudou Akito
//
//------------------------------------------
#ifndef _MAIN_H_        //�}�N����`������ĂȂ�������
#define _MAIN_H_        //��d�C���N���[�h�h�~�̃}�N����`
 
#include<windows.h>
#include"d3dx9.h"       //�`�揈���ɕK�v
#define DIRECTINPUT_VERSON (0x0800)    //�r���h���̌x���Ώ��p�}�N��
#include"dinput.h"                    //���͏����ɕK�v
#include "Xinput.h"     //�W���C�p�b�h�����ɕK�v
#include"xaudio2.h"


//���C�u�����̃����N
#pragma comment(lib,"d3d9.lib")  //�`�揈���ɕK�v
#pragma comment(lib,"d3dx9.lib") //[d3dx9.lib]�̊g�����C�u����
#pragma comment(lib,"dxguid.lib")//DirectX�R���|�[�l���g�g�p�ɕK�v
#pragma comment(lib,"winmm.lib") //�V�X�e�������擾�ɕK�v
#pragma comment(lib,"dinput8.lib")//���͏����ɕK�v
#pragma comment(lib,"xinput.lib") //�W���C�p�b�h�����ɕK�v

//�}�N����`
#define CLASS_NAME "WindowClass"			//�E�B���h�E�N���X�̖��O
#define WINDOW_NAME "DirectX�̊�{����"	    //�E�B���h�E�̖��O�i�L���v�V�����ɕ\���j
#define SCREEN_WIDTH (1280)					//�E�B���h�E�̕�
#define SCREEN_HEIGHT (720)		            //�E�B���h�E�̍���
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)

//���_���[2D]�̍\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;    //���_���W
	float rhw;          //���W�ϊ��p�W���i�P�D�O���ŌŒ�j
	D3DCOLOR col;       //���W�J���[
	D3DXVECTOR2 tex;    //�e�N�X�`�����W
}VERTEX_2D;

//��ʂ̎��
typedef enum
{
	MODE_TITLE=0,   //�^�C�g�����
	MODE_GAME,      //�Q�[�����
	MODE_RESULT,    //���U���g���
	MODE_MAX
}MODE;

//#define ID_BUTTON_FINISH (101)              //�I���{�^����ID
//#define ID_BUTTON_COPY (102)                //�R�s�[�{�^��ID
//#define ID_EDIT_INPUT (111)                 //���̓E�B���h�EID
//#define ID_EDIT_OUTPUT (121)                //�o�̓E�B���h�EID
//#define ID_TIMER (122)                      //�^�C�}�[ID
//#define ID_TIMER_INTERVAL (1000/60)         //�^�C�}�[�̔������o�i�~���b�j

//�v���g�^�C�v�錾
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
void SetMode(MODE mode);
MODE GetMode(void);

LPDIRECT3DDEVICE9 GetDevice(void);

#endif
