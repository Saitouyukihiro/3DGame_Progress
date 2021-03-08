//-----------------------------------------------------------------------------
//メインの処理
//-----------------------------------------------------------------------------
#ifndef _MAIN_H_
#define _MAIN_H_
#define DIRECTINPUT_VERSION (0x0800)  //ビルド時の警告対処用マクロ

//-----------------------------------------------------------------------------
//インクルードファイル
//-----------------------------------------------------------------------------
#include <windows.h>
#include "d3dx9.h"
#include "dinput.h"  //入力処理に必要
#include "xaudio2.h"
#include "xinput.h"
//-----------------------------------------------------------------------------
//ライブラリのリンク
//-----------------------------------------------------------------------------
#pragma comment (lib,"d3d9.lib")		//描画に必要
#pragma comment (lib,"d3dx9.lib")		//[d3d9.lib]の拡張ライブラリ
#pragma comment (lib,"dxguid.lib")		//DirectXコンポーネント(部品)使用に必要
#pragma comment (lib,"dinput8.lib")		//入力処理に必要
#pragma comment (lib,"winmm.lib")  
#pragma comment (lib,"xinput.lib")		//XINPUTのやつ
//-----------------------------------------------------------------------------
//マクロ定義
//-----------------------------------------------------------------------------
#define SCREEN_WIDTH  (1280)           //ウインドウの幅
#define SCREEN_HEIGHT (720)            //ウインドウの高さ
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)
//-----------------------------------------------------------------------------
//構造体定義
//-----------------------------------------------------------------------------
typedef struct
{
	//2D
	D3DVECTOR pos;   //位置
	float  rhw;      //rhw
	D3DCOLOR col;    //色
	D3DXVECTOR2 tex; //テクスチャ

} VERTEX_2D;

typedef struct
{
	//3D
	D3DXVECTOR3 pos;	//頂点座標
	D3DXVECTOR3 nor;	//法線ベクトル
	D3DCOLOR	col;	//頂点カラー
	D3DXVECTOR2 tex;	//テクスチャ座標
} VERTEX_3D;

//画面(モード)の種類
typedef enum
{
	MODE_TITLE = 0,
	MODE_MAX,
}MODE;

//-----------------------------------------------------------------------------
//プロトタイプ宣言
//-----------------------------------------------------------------------------
LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode);
MODE *GetMode(void);
#endif _MAIN_H_