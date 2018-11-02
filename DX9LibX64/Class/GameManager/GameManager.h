#pragma once
#include <windows.h>
#include <tchar.h>
#include "Window\Window.h"
#include "DirectX\DirectX.h"
#include "../CustomVertices/CustomVertices.h"
#include "../Draw/Draw.h"
#include "../FileManager/FileManager.h"
#include "Light\Light.h"

class Light;
class CustomVertices;
class Draw;

struct CustomVertex;
struct Custom3DVertex;
struct ObjectData;

class GameManager
{
public:
	static GameManager* GetInstance(HINSTANCE hInst, TCHAR* pAppName, VOID(*pMainFunc)(), D3DXVECTOR2 displaySize, BOOL canWindown);
	static GameManager* CopyInstance();

	VOID Create();
	VOID GetInputData(InputData** pPInputData);
	INT Release();
	LPDIRECT3DDEVICE9 GetDirectX3DDevice();
	VOID GetDisplaySize(D3DXVECTOR2* pDisplaySize);

	/**
	* @fn virtual VOID Render(const FbxRelated* pFBXModel,
	*	const D3DXMATRIX* pMatWorld, const LPDIRECT3DTEXTURE9 texture = NULL)
	* @brief FBXの描画を行う
	* @param (pFBXModel) FBXのクラス モデルを読み込んだ後でないといけない
	* @param (pMatWorld) 拡大回転移動行列をまとめた行列のポインタ
	* @param (pTexture) モデルに張り付けるテクスチャ デフォルトで存在している場合はNULL
	* @return なし
	* @detail pMatWorldをSetTransformを行い,引数のテクスチャを設定した後
	*	pFBXModelのメンバ関数を用い描画する
	*/
	virtual VOID Render(const FbxRelated* pFBXModel,
		const D3DXMATRIX* pMatWorld, const LPDIRECT3DTEXTURE9 pTexture = NULL);

	/**
	* @fn virtual VOID Render(const CustomVertex* pCustomVertices,
	*	const LPDIRECT3DTEXTURE9 pTexture = NULL)
	* @brief 2Dの描画を行う
	* @param (pCustomVertices) 頂点データの先頭ポインタ
	* @param (pTexture) ポリゴンに張り付けるテクスチャ
	* @return なし
	* @detail 引数のテクスチャを設定した後、DrawPrimitiveUpを用い描画する
	*/
	virtual VOID Render(const CustomVertex* pCustomVertices,
		const LPDIRECT3DTEXTURE9 pTexture = NULL);

	/**
	* @fn virtual VOID Render(const CustomVertex* pCustomVertices,
	*	const D3DXMATRIX* pMatWorld, const LPDIRECT3DTEXTURE9 pTexture = NULL)
	* @brief 3Dの描画
	* @param (Custom3DVertex) 3D頂点データの先頭ポインタ
	* @param (pMatWorld) 拡大回転移動行列をまとめた行列のポインタ
	* @return なし
	* @detail pMatWorldをSetTransformを行い、virtual VOID Render(const CustomVertex* pCustomVertices,
	*　	const LPDIRECT3DTEXTURE9 pTexture = NULL)
	*/
	virtual VOID Render(const Custom3DVertex* pCustom3DVertices,
		const D3DXMATRIX* pMatWorld, const LPDIRECT3DTEXTURE9 pTexture = NULL);

	/**
	* @brief テクスチャの作成
	* @param (pTexName) テクスチャにつける名前
	* @param (pTexturePath) 作成するテクスチャのパス
	* @return なし
	*/
	VOID CreateTex(TCHAR* pTexName, TCHAR* pTexturePath);

	/**
	* @brief 作成した全テクスチャの削除
	* @return なし
	*/
	VOID DeleteTex();

	/**
	* @brief テクスチャの取得
	* @param (pTexName) テクスチャの名前
	* @return LPDIRECT3DTEXTURE9 テクスチャのポインタ
	*/
	LPDIRECT3DTEXTURE9 GetTex(TCHAR* pTexName);

	/**
	* @fn static VOID RotateXYZ(CustomVertex* pCustomVertices, const D3DXVECTOR3* pDegree, const D3DXVECTOR3* pRelativeRotateCenter)
	* @brief XYZ順に回転を行う
	* @param (pCustomVertices) 頂点データ配列の先頭アドレス
	* @param (pDegree) 回転をさせる度数法での角度のポインタ
	* @param (pRelativeRotateCenter) どれほど回転の中心が矩形の中心よりずれているかのポインタ
	* @return なし
	* @detail 回転行列を作成し、矩形の中心を求め回転の中心を原点に移動させ、回転行列を用いて回転を行い原点へ移動させた分元に戻す
	*/
	VOID RotateXYZ(CustomVertex* pCustomVertices, const D3DXVECTOR3* pDegree, const D3DXVECTOR3* pRelativeRotateCenter);

	VOID RotateX(CustomVertex* pCustomVertices, FLOAT degree, const D3DXVECTOR3* pRelativeRotateCenter);

	VOID RotateY(CustomVertex* pCustomVertices, FLOAT degree, const D3DXVECTOR3* pRelativeRotateCenter);

	VOID RotateZ(CustomVertex* pCustomVertices, FLOAT degree, const D3DXVECTOR3* pRelativeRotateCenter);

	VOID RotateXYZ(Custom3DVertex* pCustom3DVertices, const D3DXVECTOR3* pDegree, const D3DXVECTOR3* pRelativeRotateCenter);

	VOID RotateX(Custom3DVertex* pCustom3DVertices, FLOAT degree, const D3DXVECTOR3* pRelativeRotateCenter);

	VOID RotateY(Custom3DVertex* pCustom3DVertices, FLOAT degree, const D3DXVECTOR3* pRelativeRotateCenter);

	VOID RotateZ(Custom3DVertex* pCustom3DVertices, FLOAT degree, const D3DXVECTOR3* pRelativeRotateCenter);

	/**
	* @fn VOID Rescale(CustomVertex* pCustomVertices, const D3DXVECTOR2* pScaleRate)
	* @brief 矩形を拡縮させる
	* @param (pCustomVertices) 頂点データ配列の先頭アドレス
	* @param (pScaleRate) 拡縮率のポインタ
	* @return なし
	* @detail 矩形の中心を求め幅と高さを割り出し、拡縮率を幅と高さに掛け合わせ、矩形の中心点から再構成させる
	*/
	VOID Rescale(CustomVertex* pCustomVertices, const D3DXVECTOR2* pScaleRate);

	VOID Rescale(Custom3DVertex* pCustom3DVertices, const D3DXVECTOR2* pScaleRate);

	/**
	* @fn Move(CustomVertex* pCustomVertices, const D3DXVECTOR3* pMovement)
	* @brief 矩形を移動させる
	* @param (pCustomVertices) 頂点データ配列の先頭アドレス
	* @param (pMovement) 移動量のポインタ
	* @return なし
	*/
	VOID Move(CustomVertex* pCustomVertices, const D3DXVECTOR3* pMovement);

	VOID Move(Custom3DVertex* pCustom3DVertices, const D3DXVECTOR3* pMovement);

	/**
	* @fn Move(CustomVertex* pCustomVertices, const D3DXVECTOR3* pMovement)
	* @brief 矩形を引数の位置に再配置させる
	* @param (pCustomVertices) 頂点データ配列の先頭アドレス
	* @param (pCenter) 矩形を移動させる座標のポインタ
	* @return なし
	*/
	VOID Locale(CustomVertex* pCustomVertices, const D3DXVECTOR3* pPos);

	VOID Locale(Custom3DVertex* pCustom3DVertices, const D3DXVECTOR3* pPos);

	/**
	* @fn VOID SetTexUV(CustomVertex* pCustomVertices, FLOAT startTU = 0.0f, FLOAT startTV = 0.0f, FLOAT endTU = 1.0f, FLOAT endTV = 1.0f)
	* @brief テクスチャ座標を引数の座標に変更させる
	* @param (pCustomVertices) 頂点データ配列の先頭アドレス
	* @param (startTU) x方向のテクスチャ座標の始まりの値
	* @param (startTV) y方向のテクスチャ座標の始まりの値
	* @param (endTU) x方向のテクスチャ座標の終わりの値
	* @param (endTV) y方向のテクスチャ座標の終わりの値
	* @return なし
	*/
	VOID SetTexUV(CustomVertex* pCustomVertices, FLOAT startTU = 0.0f, FLOAT startTV = 0.0f, FLOAT endTU = 1.0f, FLOAT endTV = 1.0f);

	VOID SetTexUV(Custom3DVertex* pCustom3DVertices, FLOAT startTU = 0.0f, FLOAT startTV = 0.0f, FLOAT endTU = 1.0f, FLOAT endTV = 1.0f);

	/**
	* @fn VOID Create(CustomVertex *pCustomVertices, const D3DXVECTOR3* pCenter, const D3DXVECTOR2* pHalfScale,
	*	DWORD color = 0xFFFFFFFF, FLOAT startTU = 0.0f, FLOAT startTV = 0.0f, FLOAT endTU = 1.0f, FLOAT endTV = 1.0f)
	* @brief 頂点データ構造体に引数の値を代入させる
	* @param (pCustomVertices) 頂点データ配列の先頭アドレス
	* @param (pCenter) 矩形の中心のポインタ
	* @param (pHalfScale) 矩形の高さ幅の半分のポインタ
	* @param (color) 頂点の色カラーコードARGB
	* @param (startTU) x方向のテクスチャ座標の始まりの値
	* @param (startTV) y方向のテクスチャ座標の始まりの値
	* @param (endTU) x方向のテクスチャ座標の終わりの値
	* @param (endTV) y方向のテクスチャ座標の終わりの値
	* @return なし
	*/
	VOID Create(CustomVertex *pCustomVertices, const D3DXVECTOR3* pCenter, const D3DXVECTOR2* pHalfScale,
		DWORD color = 0xFFFFFFFF, FLOAT startTU = 0.0f, FLOAT startTV = 0.0f, FLOAT endTU = 1.0f, FLOAT endTV = 1.0f);

	VOID Create(Custom3DVertex* pCustom3DVertices, const D3DXVECTOR3* pCenter, const D3DXVECTOR2* pHalfScale,
		DWORD color = 0xFFFFFFFF, FLOAT startTU = 0.0f, FLOAT startTV = 0.0f, FLOAT endTU = 1.0f, FLOAT endTV = 1.0f);

	VOID Create(CustomVertex *pCustomVertices, const ObjectData*pObjectData);
	
	/**
	* @brief 頂点データの色設定
	* @param (pCustomVertices) 頂点データの先頭ポインタ
	* @param (color) 設定する色のカラーコードARBG
	* @return なし
	*/
	VOID SetColor(CustomVertex *pCustomVertices, DWORD color);

	VOID SetLight(D3DLIGHT9* pLight, INT lightIndex);

	VOID SetRenderState(D3DRENDERSTATETYPE renderStateType, DWORD value);

private:
	GameManager(HINSTANCE hInst, TCHAR* pAppName, BOOL canWindow);
	~GameManager();

	VOID InitializeWindow();
	VOID InitializeDirectX();
	VOID UpdateInput();
	VOID LoopMainFunc();

	static VOID(*m_pMainFunc)();
	static GameManager* m_pGameManager;
	static D3DXVECTOR2 m_displaySize;
	static InputData* m_pInputData;
	static Window* m_pWindow;
	static DirectX* m_pDirectX;
	static CustomVertices* m_pCustomVertices;
	static Draw* m_pDraw;
	static FileManager* m_pFileManager;
	Light m_light;
};
