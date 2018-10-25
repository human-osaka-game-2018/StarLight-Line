#pragma once
#include <Windows.h>
#include <chrono>
#include <crtdbg.h>
#include <cstdio>
#include <cstdlib>
#define _CRTDBG_MAP_ALLOC
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)

/*
*�^�C�}�[�N���X(�V���O���g��)
*�N���X�T�v
*���Ԃ��v��N���X
*/
class Timer
{
public:

	static Timer* GetInstance();	//�C���X�^���X�𐶐�����
	void Relese();					//�C���X�^���X��j������

	void Start();					//�^�C�}�[�J�n
	void End();						//�^�C���J�E���g���I��
	void Reset();					//�^�C�}�[���Z�b�g
	LONGLONG GetSecond();			//�b���擾
	LONGLONG GetMilliSecond();		//�~���b�擾
	LONGLONG GetMicroSecond();		//�}�C�N���b�擾

private:
	Timer() {};
	~Timer() {};

	static Timer* m_Timer;

	typedef std::chrono::duration<
		std::chrono::system_clock::rep,
		std::chrono::system_clock::period> DebugDiffTime;

	std::chrono::system_clock::time_point	m_StartTime;	//!< �v���J�n����.
	DebugDiffTime m_DiffTime;								//!< �v������.
};