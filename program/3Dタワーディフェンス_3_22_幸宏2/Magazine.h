//ーーーーーーーーーーーーーーーーーーーーーーーーー
//スコアのヘッダー
//Author：佐藤秀亮
//ーーーーーーーーーーーーーーーーーーーーーーーーー

#ifndef _MAGAZINE_H_
#define _MAGAZINE_H_

#include "main.h"
#include "Player.h"

//銃のタイプ(必要になったら順次追加してください)
typedef enum
{
	TYPE_ASSULT,
	TYPE_HANDGUN,
	TYPE_MAX,
} GUN_TYPE;

//スコアの構造体
typedef struct
{
	D3DXVECTOR3 pos;//位置
} Magazine;

typedef struct
{
	GUN_TYPE state;//装備タイプ
} Equipment;

void InitMagazine(void);
void UninitMagazine(void);
void UpdateMagazine(void);
void DrawMagazine(void);

Magazine *GetMagazine(void);
Equipment * GetEquipment(void);
#endif


