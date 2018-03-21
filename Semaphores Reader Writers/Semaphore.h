#pragma once
#include <iostream>
#include <thread>
#include <chrono>

struct Semaphore
{

public:
	Semaphore(int i = 1) :m_count(i)
	{

	}

	void P()
	{
		//Locks m_count for changes
		std::unique_lock<decltype(m_mutex)> lock(m_mutex);
		while (m_count <= 0)
		{
			m_condition.wait(lock);
		}
		//Unlocks 
		--m_count;
	}

	void V()
	{
		//Locks m_count for changes
		std::unique_lock<decltype(m_mutex)> lock(m_mutex);

		++m_count;

		m_condition.notify_one();
	}

private:
	int m_count;
	std::mutex m_mutex;
	std::condition_variable m_condition;

};

