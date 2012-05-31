//##############################################################################
//                                                                             #
// Copyright 2011 Meir yanovich,	                                           #
//	   Questions just email me to meiry242@gmail.com / meiryanovich@gmail.com  #
//                                                                             #
//##############################################################################



// ThreadPool.cpp: implementation of the ThreadPool class.
//
//////////////////////////////////////////////////////////////////////

#include "threadjob.h"
#include "threadpool.h"
#include "thread.h"
#include <algorithm>
#include "mutex.h"

void remove_job(ThreadJob* p) { delete p; }
void delete_thread(Thread* pthread) { delete pthread; }

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ThreadPool::ThreadPool()
{
	m_fstop = false;

	// initialize the mutex
	pthread_mutex_init(&m_cs, NULL);
	 
	pthread_mutex_init(&m_mutex, NULL);
	 
}

ThreadPool::~ThreadPool()
{
	 
	pthread_cond_destroy(&m_condition);
	 
	pthread_mutex_destroy(&m_cs);
}

void ThreadPool::stop() {
	m_fstop = true;
	
	mutex  m(m_cs);

	// delete all queued jobs
	std::for_each(m_jobs.begin(), m_jobs.end(), remove_job);
	m_jobs.erase(m_jobs.begin(), m_jobs.end());
	
	 
	pthread_cond_broadcast(&m_condition);
	 
	
	// destroy all threads and clear the thread list
	std::for_each(m_threads.begin(), m_threads.end(), delete_thread);
	m_threads.erase(m_threads.begin(), m_threads.end());

	// close the IO Completion Port / pthread condition variable
	 
	pthread_mutex_destroy(&m_mutex);
	pthread_cond_destroy(&m_condition);
	 
}


void ThreadPool::start(int nthreads) 
{
	m_nthreadcount = nthreads;

	pthread_cond_init(&m_condition, NULL);

	for (int index = 0; index < nthreads; ++index) 
	{
		m_threads.push_back(new Thread);
	}
}

long ThreadPool::get_jobcount() 
{
	mutex  m(m_cs);
	return m_jobs.size();
}

// add a new job to the thread pool
// all jobs have to be derived from the ThreadJob class
void ThreadPool::add_job(ThreadJob* pjob) 
{
	// Do not queue a new job, if the pool is flagged to be stopped.
	if (m_fstop) { delete pjob; return; }

	{
	mutex  m(m_cs);
	m_jobs.push_back(pjob);
	}
	pthread_cond_signal(&m_condition);
	
}

// gets the next job to be executed from the queue
ThreadJob* ThreadPool::get_next() 
{
	mutex  m(m_cs);
	ThreadJob* p = NULL;
	if (m_jobs.size() > 0) 
	{
		p = m_jobs.front();
		m_jobs.pop_front();
	}
	return p;
}

bool ThreadPool::wait_thread()
{
	// check if there is a new job that is queued
	// ThreadPool signals the pthread condition object or the 
	// IO Completion Port to indicate a pending job
	// The thread waits on this call 
	pthread_cond_wait(Thread::get_threadpool().get_object(), &m_mutex);
	

	return true;
}