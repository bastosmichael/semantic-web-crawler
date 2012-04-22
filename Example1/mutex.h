//##############################################################################
//                                                                             #
// Copyright 2011 Meir yanovich,	                                           #
//	   Questions just email me to meiry242@gmail.com / meiryanovich@gmail.com  #
//                                                                             #
//##############################################################################


#ifndef mutex_H
#define mutex_H

#pragma once

#include "pthread.h"

class mutex
{
	pthread_mutex_t& m_mutex;
public:
	mutex(pthread_mutex_t& m):m_mutex(m) 
	{
		pthread_mutex_lock(&m_mutex);
	}

	~mutex(void)
	{
		pthread_mutex_unlock(&m_mutex);
	}
};
#endif
