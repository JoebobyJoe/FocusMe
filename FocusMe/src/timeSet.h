#pragma once

#include "time.h"

static class TimeSet
{
public:
	TimeSet();
	TimeSet(Time start, Time end);
	TimeSet(int start, int end);// used to set 'null' values
	~TimeSet();
	Time* getTimeSet();
	std::string to_string();

	//overrides
	int operator==(const TimeSet x);

private:
	Time m_time[2];
};

TimeSet::TimeSet()
{
	m_time[0] = Time();
	m_time[1] = Time();
}

TimeSet::TimeSet(Time start, Time end)
{
	m_time[0] = start;
	m_time[1] = end;
}

TimeSet::TimeSet(int start, int end)
{
	m_time[0] = Time(start, start);
	m_time[1] = Time(end, end);
}

TimeSet::~TimeSet()
{
}

Time* TimeSet::getTimeSet()
{
	return m_time;
}

std::string TimeSet::to_string()
{
	return m_time[0].to_string() + " - " + m_time[1].to_string();
}

int TimeSet::operator==(const TimeSet x)
{
	if (m_time[0] == x.m_time[0] && m_time[1] == x.m_time[1])
	{
		return 1;
	}

	return 0;
}
