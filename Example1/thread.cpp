// Thread.cpp: implementation of the Thread class.
//
//////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include "thread.h"


//-----------------------------------------------------------------------------
 
void* __thread_proc(void *p) 
{
	((Thread*)p)->run();
	return 0;
}
 //-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
ThreadPool& Thread::get_threadpool()
{
	static ThreadPool m_threads;
	return m_threads;
}

//-----------------------------------------------------------------------------
// On constructor, a thread is created.
//-----------------------------------------------------------------------------
Thread::Thread()
{
	 
	m_threadid = pthread_create(&m_thread, NULL, __thread_proc, this);
	 
}

Thread::~Thread()
{
}
//-----------------------------------------------------------------------------
void Thread::run()
{
	while (true) 
	{
		// wait on wakeup by a signal from the threadpool
		// if this returns false, there is one less active thread.
		// I have not performed any actions to recover for this situation.
		// Usually, this happens when the IO Completion Port is not valid anymore.
		if (!get_threadpool().wait_thread()) { break; }
		
		// if the thread is already closed, then quit without checking for a new job
		bool isStop = get_threadpool().is_stop();
		if (isStop) { break; }
			
		// acquire the next job from the queue and execute it
		ThreadJob* pjob = get_threadpool().get_next();
		 
		while (pjob != NULL) 
		{
			pjob->execute();
			pjob = get_threadpool().get_next();
		}
		 
	}
}
