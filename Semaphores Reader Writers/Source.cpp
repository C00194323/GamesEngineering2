#include <iostream>
#include <mutex>

struct  semaphores
{
public:
	semaphores() {};
	semaphores(int i)
	{
		m_count = i;
	};

	~semaphores() {};

	void p()
	{
		std::unique_lock<std::mutex> lock(m);

		while (m_count == 0)
		{
			m_cv.wait(lock);
		}
		m_count--;
	};
	void v()
	{
		m_count++;
		m_cv.notify_all();
	};

private:
	int m_count;
	std::mutex m;
	std::condition_variable m_cv;
};

int readers = 0;

semaphores ReaderWriter;
semaphores ReaderMutex;

void Reader()
{

}