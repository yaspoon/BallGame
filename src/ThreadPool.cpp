#include "ThreadPool.h"

#include <iostream>

ThreadPool::ThreadPool():
threads(DEFAULT_THREAD_COUNT), threadData(DEFAULT_THREAD_COUNT)
{
	threadCount = DEFAULT_THREAD_COUNT;
	start = PTHREAD_COND_INITIALIZER;
	listLock = PTHREAD_MUTEX_INITIALIZER;

	for(int i = 0; i < threadCount; i++)
	{
		threadData[i].count = threadCount;
		threadData[i].dataLock = PTHREAD_MUTEX_INITIALIZER;
		threadData[i].jobList = &jobList;
		threadData[i].listLock = &listLock;
		threadData[i].start = &start;
		threadData[i].quit = false;
		threadData[i].number = i;


		pthread_create(&threads[i], NULL, threadRun, (void *)(&threadData[i]));
	}
}

ThreadPool::ThreadPool(int count):
threads(count), threadData(count)
{
	threadCount = count;
	start = PTHREAD_COND_INITIALIZER;
	listLock = PTHREAD_MUTEX_INITIALIZER;

	for(int i = 0; i < threadCount; i++)
	{
		threadData[i].count = threadCount;
		threadData[i].dataLock = PTHREAD_MUTEX_INITIALIZER;
		threadData[i].jobList = &jobList;
		threadData[i].listLock = &listLock;
		threadData[i].start = &start;
		threadData[i].quit = false;
		threadData[i].number = i;


		pthread_create(&threads[i], NULL, threadRun, (void *)(&threadData[i]));
	}
}

ThreadPool::~ThreadPool()
{
	pthread_mutex_lock(&listLock);
	for(int i = 0; i < threadCount; i++)
	{
		threadData[i].quit = true;
	}
	pthread_cond_broadcast(&start);
	pthread_mutex_unlock(&listLock);

	for(int i = 0; i < threadCount; i++)
	{
		pthread_join(threads[i], NULL);
	}
}

void *ThreadPool::threadRun(void *data)
{
	struct ThreadData *threadData = (struct ThreadData*)data;
	bool reallyQuit = false;

	pthread_mutex_lock(threadData->listLock);

	while(!reallyQuit)
	{

		pthread_mutex_lock(&threadData->dataLock);
		if(!threadData->quit)
		{
			pthread_mutex_unlock(&threadData->dataLock);
			if(threadData->jobList->noElements() > 0)
			{
				ThreadJob job = threadData->jobList->popFront();
				pthread_mutex_unlock(threadData->listLock);

				//std::cout << "Thread " << threadData->number << " running job" << std::endl;
				job.func(job.data);
				if(job.cleanup)
				{
					job.cleanup(job.data);
				}

				pthread_mutex_lock(threadData->listLock);
				//std::cout << "Thread " << threadData->number << " finished job now sleeping" << std::endl;
			}
			else //Sleep till a job arrives
			{
				pthread_cond_wait(threadData->start, threadData->listLock);
			}
		}
		else
		{
			pthread_mutex_unlock(&threadData->dataLock);
			reallyQuit = true;
			pthread_mutex_unlock(threadData->listLock);
		}
	}
}

void ThreadPool::addJob(ThreadFunction func, void *data, DataCleanup cleanup)
{
	ThreadJob job;
	job.func = func;
	job.data = data;
	job.cleanup = cleanup;

	pthread_mutex_lock(&listLock);
	jobList.pushBack(job);
	pthread_cond_broadcast(&start);
	pthread_mutex_unlock(&listLock);
}

int ThreadPool::getThreadCount()
{
	return threadCount;
}
