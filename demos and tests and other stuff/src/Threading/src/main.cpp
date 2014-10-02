#include "Iron.h"

//Timer class used to count... TIME.
class Timer {
private:
	LARGE_INTEGER	s;
	LARGE_INTEGER	f;

public:
	Timer() {
		QueryPerformanceFrequency(&f);
	}

	~Timer() {
	}

	float GetElapsedTime() {
		LARGE_INTEGER c;
		QueryPerformanceCounter(&c);
		return float(c.QuadPart - s.QuadPart) / float(f.QuadPart);
	}

	void Reset() {
		QueryPerformanceCounter(&s);
	}

};

//Threading related.
class Sample : public iron::thread::TaskData {
public:
	int id;
	Sample() {}
	Sample(int i) { id = i; }
	~Sample() {}
};

//Threading related.
void work1(iron::thread::TaskData* d) {
	Sample* data = (Sample*)d;
	printf("Started %d\n", data->id);
	for (int i = 0; i<500000; ++i);
	printf("Finished %d\n", data->id);
}

//Threading related.
void work2(iron::thread::TaskData* d) {
	Sample* data = (Sample*)d;
	printf("Started %d\n", data->id);
	for (int i = 0; i<100000; ++i);
	printf("Finished %d\n", data->id);
}

int main(int argc, char *argv[]) {

	/**************************************************************************************/
	/************************************** Threading *************************************/
	/**************************************************************************************/

	int addTask = 0;
	iron::thread::ThreadPool* pool = iron::thread::ThreadPool::s();

	pool->init(4, 4);
	printf("Thread pool Initialized with %d threads.\n", pool->getActiveThreads());
	system("pause");

	for (int i = 0; i < 20; ++i) {
		Sample* data = new Sample(i);
		if (i % 2 == 0) {
			pool->addTask(work1, data);
		} else {
			pool->addTask(work2, data);
		}
	}

	Timer elapsed;
	pool->start();
	elapsed.Reset();

	while (true) {
		if (pool->getActiveThreads() == pool->getSlackingThreads() && !pool->hasWaitingTasks()) {
			break;
		}
	}

	float imediatefinish = elapsed.GetElapsedTime();

	printf("Thread Pool has finished in %f seconds.\n", imediatefinish);
	printf("CPU Time (ExecutionTime/NumberOfThreads+NumberOfProcessors) is %f seconds\n",
		(imediatefinish / (pool->getActiveThreads() + 4)));

	pool->stop();
	pool->close(); 
	

	for (int i = 0; i < 100; i++) {
		pool->init(8, 8);
		printf("\n\n\n\nThread pool Initialized with %d threads.\n", pool->getActiveThreads());
		system("pause");

		for (int i = 0; i < 20; ++i) {
			Sample* data = new Sample(i);
			if (i % 2 == 0) {
				pool->addTask(work1, data);
			}
			else {
				pool->addTask(work2, data);
			}
		}
		pool->start();
		elapsed.Reset();

		while (true) {
			if (pool->getActiveThreads() == pool->getSlackingThreads() && !pool->hasWaitingTasks()) {
				break;
			}
		}

		imediatefinish = elapsed.GetElapsedTime();

		printf("Thread Pool has finished in %f seconds.\n", imediatefinish);
		printf("CPU Time (ExecutionTime/NumberOfThreads+NumberOfProcessors) is %f seconds\n",
			(imediatefinish / (pool->getActiveThreads() + 4)));

		pool->stop();
		pool->close();
	}

	return 0;
}