//============================================================================
// Name        : SWC.cpp
// Author      : Michael Bastos
// Version     :
// Copyright   : This is open source software
// Description : C++ Crawler
//============================================================================

#include <iostream>
#include <sys/stat.h>

#include "Crawler.h"
#include "Database.h"
#include "IO.h"
#include "Parser.h"
#include "Storage.h"
using namespace std;

int main(int argc, char *argv[]) {
	Storage cache;
	cache.checkForCacheFolder();
    for (int i=0; i < argc; i++){
    	//cout << argv[i] << endl;
        IO argument;
        argument.processArguments(argv[i],cache);
    }
    return 0;
}
