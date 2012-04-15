//##############################################################################
//                                                                             #
// Copyright 2011 Meir yanovich,	                                           #
//	   Questions just email me to meiry242@gmail.com / meiryanovich@gmail.com  #
//                                                                             #
//##############################################################################



#ifndef ThreadPool_H
#define ThreadPool_H

// ThreadPool.h: interface for the ThreadPool class.
//
//////////////////////////////////////////////////////////////////////

#pragma once
#include "pthread.h"
#include <deque>
#include <vector>


class Thread;

class ThreadPool  
{
public:
	bool is_stop() { return m_fstop; }

	// Thread Functions
	void start(int nthreads);
	void stop();
	bool wait_thread();
	long get_threadcount() {return m_nthreadcount;}


	// Job Functions
	long get_jobcount();
	void add_job(ThreadJob* pjob);
	ThreadJob* get_next();

	// Thread Pooling Object definition
	 
	inline pthread_cond_t* get_object() { return &m_condition; }
	 

	ThreadPool();
	~ThreadPool();

protected:
	 
	pthread_cond_t m_condition;
	pthread_mutex_t m_mutex;
	std::deque<ThreadJob* > m_jobs;
	std::vector<Thread* > m_threads;
	
	pthread_mutex_t m_cs;
	int m_nthreadcount;
	bool m_fstop;
};
#endif

