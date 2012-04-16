//============================================================================
// Name        : SWC.cpp
// Author      : Michael Bastos
// Version     :
// Copyright   : This is open source software
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <cstdlib>
#include <locale>
#include <sstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <fstream>
using namespace std;
void downloadUrl (string url, string urlhash);
int main(int argc, char *argv[])
{

	locale loc;
	const collate<char>& coll = use_facet<collate<char> >(loc);
	//cout << "There are " << argc << " arguments:" << endl;
	if(mkdir("cache",0777)==-1)//creating a directory
	{
	        cerr<<"Caching..." <<endl;
	}

    // Loop through each argument and print its number and value
    for (int i=0; i < argc; i++){
        std::string inputs = argv[i];
        long inputhash = coll.hash(inputs.data(),inputs.data()+inputs.length());
        std::string hash;
        std::stringstream strstream;
        strstream << inputhash;
        strstream >> hash;
        if(inputs.find("http://") != string::npos){
        	cout << i << " " << inputs << " " << inputhash << endl;

        		downloadUrl(inputs, hash);
        }
    }

    return 0;
}

void downloadUrl (string url, string urlhash){
	std::string command = "cd cache && wget " + url + " --output-document=" + urlhash + " --continue --force-html";
	system(command.c_str());
	//cout << command << endl;
}

void parseUrl(){
	string line;

		    ifstream read ("pathname/file.txt");//reading a file
		    if (read.is_open())
		    {

		        while (! read.eof() )
		        {
		            getline (read,line);
		            cout<<line<<endl;
		        }
		        read.close();
		    }
		    else
		        cout << "Unable to open file";
}
