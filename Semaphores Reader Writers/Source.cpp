#pragma once
#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include "Semaphore.h"

Semaphore m_semaphoreRW;
Semaphore m_semaphoreMutex;
int rw = 1;
int mutexR = 1;
int readers = 0;

void Reader()
{
	while (true)
	{
		std::cout << "Reader active " << std::endl;
		
		
		m_semaphoreMutex.P();
		//Adds a reader 
		readers++;
		if (readers == 1)
		{
			m_semaphoreRW.P();
		}
		// Locks
		m_semaphoreMutex.V();
		std::cout << "Reader Locks File" << std::endl;
		
		m_semaphoreMutex.P();
		readers--;
		if (readers == 0)
		{
			m_semaphoreRW.V();
		}
		//Unlocks
		std::cout << "Reader Unlocks File" << std::endl;
		m_semaphoreMutex.V();
		
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

void Writer()
{
	while (true)
	{
		m_semaphoreRW.P();
		std::cout << "Writer active" << std::endl;
		
		std::cout << "Writer Locks File" << std::endl;

		std::cout << "Writer Unlocking File" << std::endl;
		m_semaphoreRW.V();
		
		std::this_thread::sleep_for(std::chrono::seconds(1));

	}
}

int main()
{

	std::thread m_reader(Reader);
	std::thread m_writer(Writer);

	
	m_writer.join();
	m_reader.join();

	system("PAUSE");
	return 0;

}