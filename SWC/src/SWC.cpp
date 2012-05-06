//============================================================================
// Name        : SWC.cpp
// Author      : Michael Bastos
// Version     :
// Copyright   : This is open source software
// Description : C++ Crawler
//============================================================================

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <locale>
#include <sstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
using namespace std;
vector<string> page;
void downloadUrl (const char *path, string url, string urlhash);
void loadPage(const char *p, string url, string urlhash);
void parsePage(vector<string> page);
void parseLine(string line);
void processArguments(std::string inputs);
void checkForCacheFolder();
void generateUrlHash(std::string inputs);

int main(int argc, char *argv[])
{
	checkForCacheFolder();
    // Loop through each argument and print its number and value
    for (int i=0; i < argc; i++){
        processArguments(argv[i]);
    }

    return 0;
}

void checkForCacheFolder(){
	if(mkdir("cache",0777)==-1)//creating a directory
		{
		        //cerr<<"Caching..." <<endl;
		}
}

void processArguments(std::string inputs){
	if(inputs.find("SWC") != string::npos){
		//Check for application argument ./SWC
	} else if(inputs.find("http://") != string::npos){
		generateUrlHash(inputs);
	} else if(inputs.find("https://") != string::npos){

	} else if(inputs.find("=") != string::npos){

	}

}

void generateUrlHash(std::string url){
	locale loc;
	const collate<char>& coll = use_facet<collate<char> >(loc);
	long urlhash = coll.hash(url.data(),url.data()+url.length());
	std::string hash;
	std::stringstream strstream;
	strstream << urlhash;
	strstream >> hash;
	string path = "cache/" + hash;
	const char *p;
	p=path.c_str();
	//cout << p << endl;
	cout << " " << url << " " << hash << endl;
	loadPage(p,url,hash);
}

void loadPage(const char *path, string url, string urlhash){
	page.clear();
	string line;
	ifstream read (path);//reading a file
	if (read.is_open()) {
		while (! read.eof() ) {
			getline (read,line);
			page.push_back (line);
			//cout<<line<<endl;
	    }
	    read.close();
	    parsePage(page);
	} else {
		downloadUrl(path,url,urlhash);
	}
}

void downloadUrl (const char *path, string url, string urlhash){
	std::string command = "cd cache && wget " + url + " --output-document=" + urlhash + " --continue --force-html";
	system(command.c_str());
	//cout << command << endl;
	loadPage(path,url,urlhash);
}

void parsePage(vector<string> page){
	for (vector<string>::iterator line = page.begin();line != page.end();++line)
	{
		parseLine(*line);
	}

}

void parseLine(string line){
	//cout << line << endl;

}
