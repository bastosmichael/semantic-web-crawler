#include "Log.h"
#include "Dispatcher.h"
#include "Utilities.h"
#include "ProcessingUnit.h"
#include <iostream>
#include <vector>
//##############################################################################
//                                                                             #
// Copyright 2011 Meir yanovich,	                                           #
//	   Questions just email me to meiry242@gmail.com / meiryanovich@gmail.com  #
//                                                                             #
//##############################################################################

#include <sstream> 

using namespace std;
std::ostringstream logprint3;
int main(void) 
{

    vector<string> linkVec;
    string d;
    string t;
    Utilities::GetSystemTime(t,d);
    logprint3 << "Starting drill date=\"" << d << "\" time=\"" << t << "\"";
    Log::Instance().Write(logprint3.str(),Log::LOG_MAIN);
    logprint3.str("");
    // Enter here the uri which you like to drill (spider) down
    linkVec.push_back("http://www.xxxx.com/foo");
	
    Dispatcher* disp = new Dispatcher();
    disp->Init(&linkVec);
    disp->DeInit();
    
    Log::Instance().DeInit();
 
	return 0;
}
