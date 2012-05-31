#include "Dispatcher.h"
#include "ProcessingUnit.h"
#include "SingleTone.h"
//##############################################################################
//                                                                             #
// Copyright 2011 Meir yanovich,	                                           #
//	   Questions just email me to meiry242@gmail.com / meiryanovich@gmail.com  #
//                                                                             #
//##############################################################################

#include "Config.h"

Dispatcher::Dispatcher()
{
}

void Dispatcher::Init(vector<string>  *linksHolder)
{   
    //Set all configuration into memory 
    Config::Instance()->Init();
    // start the threads
    int iThreadPoolSize = Config::Instance()->Getm_ConfigMap()[LINKS_FILTER].iThreadPoolSize;
    Thread::get_threadpool().start(iThreadPoolSize);
 
    //first we need some links to scater the threads 
    ProcessingUnit* pu = new ProcessingUnit();
    pu->Init();
    /*
    set the first quota of links to be passed to the worker threads 
    this is only if the thread count is more then 1 
    */
    if(Config::Instance()->Getm_ConfigMap()[LINKS_FILTER].iThreadsToInvoke>1)
    {
        if(pu->SetFirstLinksQuotaForThreads(linksHolder->at(0)))
        {
             SendThreadsToWork();
        }
    }
    else
    {
      pu->StartTheProcessingLinks(linksHolder);  
    }
    
    pu->DeInit();
 

}
/*
    devide the number of links to the number of threads 
    last thread will get the links reminder
*/
void Dispatcher::SendThreadsToWork()
{
    int iLinks=SingleTone::Instance()->size();
    int iNumOfThreads =  Config::Instance()->Getm_ConfigMap()[LINKS_FILTER].iThreadsToInvoke;
    int iResultsPerThread = iLinks / iNumOfThreads;
    int iLeftToLastThread = iLinks % iNumOfThreads;
    
    std::vector<std::string> vv;
    int iThrdCount=1;
    int iResultPerThreadCount=0;
    bool bAddToLastThrd = false;
    list<std::string>::iterator listIt = SingleTone::Instance()->begin();     
    
    for(int i=0;i<iNumOfThreads;i++)
    {
        
         
        while(listIt!=SingleTone::Instance()->end())
        {
            vv.push_back(*listIt);
            listIt++; 
            if((iResultPerThreadCount==iResultsPerThread) && (!bAddToLastThrd))
                break;  
            else if(bAddToLastThrd) 
              vv.push_back(*listIt);
                 
             
        }
        
        
        ThreadWorker* threadWorker = new ThreadWorker();
        threadWorker->Init(&vv);
        Thread::get_threadpool().add_job(threadWorker);  
        
        vv.clear();
        ++iThrdCount;
        if(iThrdCount == iNumOfThreads)
            bAddToLastThrd = true;
        iResultPerThreadCount++;
        
    }
    
}

void Dispatcher::DeInit()
{
    Thread::get_threadpool().stop();
}

    