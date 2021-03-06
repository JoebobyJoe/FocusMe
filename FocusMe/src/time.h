#pragma once

#include <string>

enum E_TIME
{
	AM,
	PM
};

static class Time
{
public:
	Time();
	Time(int hour, int min);
	~Time();
	int* getTime();
	void setTime(int hour, int min);
	int operator==(const Time x);
	void to_string(std::string &str);
	

private:
	int m_time[2];
};

Time::Time()
{
	m_time[0] = 0;
	m_time[1] = 0;
}

Time::Time(int hour, int min)
{
	m_time[0] = hour;
	m_time[1] = min;
}

Time::~Time()
{
}

int* Time::getTime()
{
	return m_time;
}

void Time::setTime(int hour, int min)
{
	m_time[0] = hour;
	m_time[1] = min;
}

void Time::to_string(std::string &str)
{
	std::string hour = (m_time[0] < 10) ? "0" + std::to_string(m_time[0]) : std::to_string(m_time[0]);
	std::string min = (m_time[1] < 10) ? "0" + std::to_string(m_time[1]) : std::to_string(m_time[1]);
	str =  hour + ":" + min;
}

int Time::operator==(const Time x)
{
	if (m_time[0] == x.m_time[0] && m_time[1] == x.m_time[1])
	{
		return 1;
	}

	return 0;
}