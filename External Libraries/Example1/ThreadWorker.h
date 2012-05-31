//##############################################################################
//                                                                             #
// Copyright 2011 Meir yanovich,	                                           #
//	   Questions just email me to meiry242@gmail.com / meiryanovich@gmail.com  #
//                                                                             #
//##############################################################################



#ifndef ThreadWorker_H
#define ThreadWorker_H

#pragma once
#include "threadjob.h"
#include <string>
#include <vector>

class ProcessingUnit;
class ThreadWorker : public ThreadJob
{
    
  public:  
    ThreadWorker() ;
    ~ThreadWorker(void);
    void Init(void* p,std::vector<std::string>* linksVec);
    void Init(std::vector<std::string>* linksVec);
    void ThreadWorker::Init(void* p);
    bool execute();
  private :
    ProcessingUnit* m_ProcessingUnit;
    std::vector<std::string> m_LinksVec;
};
#endif

