#pragma once
#include <Windows.h>
#include <chrono>
#include <crtdbg.h>
#include <cstdio>
#include <cstdlib>
#define _CRTDBG_MAP_ALLOC
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)

/*
*タイマークラス(シングルトン)
*クラス概要
*時間を計るクラス
*/
class Timer
{
public:

	static Timer* GetInstance();	//インスタンスを生成する
	void Relese();					//インスタンスを破棄する

	void Start();					//タイマー開始
	void End();						//タイムカウントを終了
	void Reset();					//タイマーリセット
	LONGLONG GetSecond();			//秒を取得
	LONGLONG GetMilliSecond();		//ミリ秒取得
	LONGLONG GetMicroSecond();		//マイクロ秒取得

private:
	Timer() {};
	~Timer() {};

	static Timer* m_Timer;

	typedef std::chrono::duration<
		std::chrono::system_clock::rep,
		std::chrono::system_clock::period> DebugDiffTime;

	std::chrono::system_clock::time_point	m_StartTime;	//!< 計測開始時間.
	DebugDiffTime m_DiffTime;								//!< 計測時間.
};