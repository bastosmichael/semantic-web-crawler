
//##############################################################################
//                                                                             #
// Copyright 2011 Meir yanovich,	                                           #
//	   Questions just email me to meiry242@gmail.com / meiryanovich@gmail.com  #
//                                                                             #
//##############################################################################



#ifndef Utilities_H
#define Utilities_H

#if defined(WIN32)
 #include <windows.h>
#else
 #include <sys/time.h>
#endif

#include <stdio.h>
#include <time.h>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>


class Utilities {
public:
    static void GetSystemTime(std::string& sdateStr,std::string& stimeStr);
    static void StringSearchAndReplace(std::string& sourceStr,std::string toReplace,std::string withThisStr);
    static bool Sleep(long lTimeMsecs);
    static void find_and_replace( std::string &source, const std::string find, std::string replace );
    static std::string replaceAll( const std::string& s, const std::string& f, const std::string& r );
};
#endif