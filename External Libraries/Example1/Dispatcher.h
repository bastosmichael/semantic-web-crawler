//##############################################################################
//                                                                             #
// Copyright 2011 Meir yanovich,	                                           #
//	   Questions just email me to meiry242@gmail.com / meiryanovich@gmail.com  #
//                                                                             #
//##############################################################################


#ifndef Dispatcher_H
#define Dispatcher_H
#include "thread.h"
#include "ThreadWorker.h"



class Dispatcher
{   
    public :
        Dispatcher();
        ~Dispatcher();
        void Init(std::vector<std::string>  *linksHolder);
        void DeInit();
        void SendThreadsToWork();

    private:
};
#endif
