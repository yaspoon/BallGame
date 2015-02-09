#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <pthread.h>
#include "LinkedList.h"

#include <vector>

typedef void *(*ThreadFunction)(void *threadData); /*Function thread should call*/
typedef void (*DataCleanup)(void *data); /*Function used to cleanup data*/

class ThreadPool
{
private:
	static const int DEFAULT_THREAD_COUNT = 4;

struct ThreadJob
{
	ThreadFunction func;
	void *data;
	DataCleanup cleanup;

};

struct ThreadData
{

	int count;
	int number;
	pthread_cond_t *start; //Condition
	pthread_mutex_t dataLock;
	pthread_mutex_t *listLock;
	LinkedList<ThreadJob> *jobList;
	bool quit;
};

int threadCount;
std::vector<pthread_t> threads;
std::vector<ThreadData> threadData;
pthread_mutex_t listLock;
LinkedList<ThreadJob> jobList;
pthread_cond_t start;

public:
ThreadPool();
ThreadPool(int count);
~ThreadPool();

void addJob(ThreadFunction func, void *data, DataCleanup cleanup);
static void *threadRun(void *data); /*Function that every thread runs*/

int getThreadCount();
};

#endif // THREADPOOL_H
