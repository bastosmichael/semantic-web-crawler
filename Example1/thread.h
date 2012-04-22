//##############################################################################
//                                                                             #
// Copyright 2011 Meir yanovich,	                                           #
//	   Questions just email me to meiry242@gmail.com / meiryanovich@gmail.com  #
//                                                                             #
//##############################################################################


#ifndef Thread_H
#define Thread_H

#include "pthread.h"
#include "threadjob.h"
#include "threadpool.h"	
//class ThreadPool;

class Thread  
{
public:
	static ThreadPool& get_threadpool();
	
	void run();
	
	Thread();
	~Thread();

protected:
	unsigned int m_threadid;
	pthread_t m_thread;
	 
};
#endif

