//##############################################################################
//                                                                             #
// Copyright 2011 Meir yanovich,	                                           #
//	   Questions just email me to meiry242@gmail.com / meiryanovich@gmail.com  #
//                                                                             #
//##############################################################################


#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H
#pragma once
#include <string>
#include <set>

struct Scraplet {
    std::string regExp;
    bool IsUnique;
};
// need to implement interface to this so we have all kinds of infos 

 

struct InfoHolder {
 
    std::set<std::string> linksBlackList;
    std::set<std::string> linksMastHaveList;
    
    std::string  BaseUrl;
    //need to move it to the proper struct : ThreadConfigHolder
     
    
    int iThreadsToInvoke;
    int iThreadPoolSize;
     
};

struct ThreadConfigHolder  {
 
    int iInitProduct;
    int iMultiplication;
    int iThreadPoolSize;
};
#endif







