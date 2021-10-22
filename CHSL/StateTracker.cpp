#include "core.h"

#include "StateTracker.h"
#include <iostream>

cs::StateTracker::StateTracker(float keys[], int keyCount, float start)
	:
	m_time(start),
	m_keys(new float[keyCount]),
	m_keyCount(keyCount),
	m_currentInterval(0),
	m_currentState(StateRunning)
{
	memcpy(m_keys, keys, keyCount * sizeof(float));

	UpdateStates();
}

cs::StateTracker::StateTracker(const StateTracker& lVal)
	:
	m_keys(nullptr)
{
	(*this) = lVal;
}

cs::StateTracker::StateTracker(StateTracker&& rVal)
	:
	m_keys(nullptr)
{
	(*this) = std::move(rVal);
}

cs::StateTracker::~StateTracker()
{
	delete[] m_keys;
}

cs::StateTracker& cs::StateTracker::operator=(const StateTracker& lVal)
{
	if (this == &lVal)
	{
		return *this;
	}

	m_time = lVal.m_time;
	m_currentInterval = lVal.m_currentInterval;
	m_currentState = lVal.m_currentState;

	if (m_keys == nullptr || m_keyCount != lVal.m_keyCount)
	{
		m_keyCount = lVal.m_keyCount;

		delete[] m_keys;
		m_keys = new float[m_keyCount];
	}

	memcpy(m_keys, lVal.m_keys, m_keyCount * sizeof(float));

	return *this;
}

cs::StateTracker& cs::StateTracker::operator=(StateTracker&& rVal)/* noexcept*/
{
	if (this == &rVal)
	{
		return *this;
	}

	delete[] m_keys;

	m_time = rVal.m_time;
	m_keys = rVal.m_keys;
	m_keyCount = rVal.m_keyCount;
	m_currentInterval = rVal.m_currentInterval;
	m_currentState = rVal.m_currentState;

	rVal.m_keys = nullptr;

	return *this;
}

void cs::StateTracker::Reset()
{
	m_time = 0.0f;
	
	UpdateStates();
}

void cs::StateTracker::Lapse(float difference)
{
	m_time += difference;

	while (m_time >= m_keys[m_currentInterval + 1] && m_currentInterval < m_keyCount - 2)
	{
		m_currentInterval++;
	}

	while (m_time < m_keys[m_currentInterval] && m_currentInterval > 1)
	{
		m_currentInterval--;
	}

	if (m_time < m_keys[0])
	{
		m_currentState = StateUnder;
	}
	else if (m_time > m_keys[m_keyCount - 1])
	{
		m_currentState = StateOver;
	}
	else
	{
		m_currentState = StateRunning;
	}
}

void cs::StateTracker::GoToTime(float time)
{
	m_time = time;

	UpdateStates();
}

void cs::StateTracker::GoToInterval(int interval)
{
	if (interval < 0 || interval > m_keyCount - 2)
	{
		return;
	}

	m_time = m_keys[interval];
	m_currentInterval = interval;
	m_currentState = StateRunning;
}

void cs::StateTracker::GoToInterval(int interval, float additionalTime)
{
	if (interval < 0 || interval > m_keyCount - 2)
	{
		return;
	}

	m_time = m_keys[interval] + additionalTime;

	UpdateStates();
}

int cs::StateTracker::GetInterval() const
{
	return m_currentInterval;
}

float cs::StateTracker::GetTime() const
{
	return m_time;
}

float cs::StateTracker::GetTimeC() const
{
	return fclamp(
		m_time, 
		m_keys[0], 
		m_keys[m_keyCount - 1]
	);
}

float cs::StateTracker::GetIntervalTime() const
{
	return m_time - m_keys[m_currentInterval];
}

float cs::StateTracker::GetIntervalTimeC() const
{
	return fclamp(
		m_time - m_keys[m_currentInterval], 
		m_keys[m_currentInterval], 
		m_keys[m_currentInterval + 1]
	);
}

cs::StateTracker::State cs::StateTracker::GetRunState() const
{
	return m_currentState;
}

void cs::StateTracker::UpdateStates()
{
	if (m_time < m_keys[0])
	{
		m_currentState = StateUnder;
		m_currentInterval = 0;
	}
	else if (m_time > m_keys[m_keyCount - 1])
	{
		m_currentState = StateOver;
		m_currentInterval = m_keyCount - 2;
	}
	else
	{
		m_currentState = StateRunning;

		for (int i = 1; i < m_keyCount; ++i)
		{
			if (m_time < m_keys[i])
			{
				m_currentInterval = i - 1;
				return;
			}
		}
	}
}
