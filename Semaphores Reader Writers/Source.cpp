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
bool running = true;

void Reader()
{
	while (running)
	{
		std::cout << "Reader active " << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
		
		m_semaphoreMutex.P();
		//Adds a reader 
		readers++;
		if (readers == 1)
		{
			m_semaphoreMutex.P();
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
	}
}

void Writer()
{
	while (running)
	{
		std::cout << "Writer active" << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
		std::cout << "Writer Locks File" << std::endl;
		m_semaphoreRW.P();
		std::cout << "Writer Using File" << std::endl;
		std::cout << "Writer Unlocking File" << std::endl;
		m_semaphoreRW.V();

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