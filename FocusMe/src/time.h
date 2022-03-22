#pragma once

static class Time
{
public:
	Time();
	Time(int hour, int min);
	~Time();
	int* getTime();

private:
	int m_hour, m_min;
};

Time::Time()
{
	m_hour = 0;
	m_min = 0;
}

Time::Time(int hour, int min)
{
	m_hour = hour;
	m_min = min;
}

Time::~Time()
{
}

int* Time::getTime()
{
	int arr[2] = { m_hour, m_min };
	return arr;
}