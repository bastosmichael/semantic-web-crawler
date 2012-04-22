
#include <stdio.h>
#include "ThreadWorker.h"
#include "ProcessingUnit.h"


 

ThreadWorker::ThreadWorker()
{
;
}

ThreadWorker::~ThreadWorker(void)
{
;
}

//this is some kind of pointer to memeber function 
//to be able the thread worker to excute member function in the Pu object 
void ThreadWorker::Init(void* p ,std::vector<std::string>* linksVec)
{

     
    m_ProcessingUnit = static_cast<ProcessingUnit*>(p);
    m_LinksVec.swap(*linksVec);
    
}
void ThreadWorker::Init(std::vector<std::string>* linksVec)
{

    m_LinksVec.swap(*linksVec);
    
}

void ThreadWorker::Init(void* p)
{

     
    m_ProcessingUnit = static_cast<ProcessingUnit*>(p);
    
    
}



bool ThreadWorker::execute()
{
	 
	printf("Testing %d\r\n", &m_ts);
	//m_ProcessingUnit->BatchParseLink(m_LinksVec);
	
	ProcessingUnit* processingUnit = new ProcessingUnit();
	processingUnit->Init();
	processingUnit->StartTheProcessingLinks(&m_LinksVec);
	processingUnit->DeInit();
	
	return ThreadJob::execute();
}