#ifndef ThreadJob_H
#define ThreadJob_H

// ThreadJob.h: interface for the ThreadJob class.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#include <time.h>

class ThreadJob  
{
public:
	inline virtual bool execute()
	{
		delete this;
		return true;
	}
	ThreadJob() 
	{
		time(&m_ts);
	}
	virtual ~ThreadJob() {}
protected:
	time_t m_ts;
};
#endif

