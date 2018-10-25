#include "Timer.h"

//èâä˙âªÇÃÇΩÇﬂÇ…nullptrÇãlÇﬂÇÈ
Timer* Timer::m_Timer = nullptr;

Timer* Timer::GetInstance()
{
	if (!m_Timer)m_Timer = new Timer();

	return m_Timer;
}

void Timer::Relese()
{
	delete m_Timer;
	m_Timer = nullptr;
}

void Timer::Start()
{
	m_StartTime = std::chrono::system_clock::now();
}

void Timer::End()
{
	m_DiffTime = std::chrono::system_clock::now() - m_StartTime;
}

void Timer::Reset()
{
	m_DiffTime = (DebugDiffTime)0;
}

LONGLONG Timer::GetSecond()
{
	return std::chrono::duration_cast<std::chrono::seconds>(m_DiffTime).count();
}

LONGLONG Timer::GetMilliSecond()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(m_DiffTime).count();
}

LONGLONG Timer::GetMicroSecond()
{
	return std::chrono::duration_cast<std::chrono::microseconds>(m_DiffTime).count();
}