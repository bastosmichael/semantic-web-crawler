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
#include <string.h>
#include <sys/types.h>
#include <algorithm>   // remove_if()
#include <cctype>      // isspace()
#include <functional>  // ptr_fun <>
using namespace std;

vector<string> page;
vector<string> regex;
vector<string> data;

void downloadUrl (const char *path, string url, string urlhash);
void loadPage(const char *p, string url, string urlhash);
void parsePage(vector<string> page);
void parseLine(string line);
void processArguments(std::string inputs);
void checkForCacheFolder();
void generateUrlHash(std::string inputs);
string delCharacter(string &line, string remove);

int main(int argc, char *argv[]) {
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
	string pattern = "[^tpr]{2,}";
	regex.push_back (pattern);
	
	if(inputs.find("SWC") != string::npos){
		//Check for application argument ./SWC
	} else if(inputs.find("http://") != string::npos || inputs.find("https://") != string::npos){
		generateUrlHash(inputs);
	} else if(inputs.find("block=") != string::npos){
		
	} else if(inputs.find("active=") != string::npos){
		
	} else if(inputs.find(".=") != string::npos){
		string block = delCharacter(inputs, '.=');
		regex.push_back (block);
	} else if(inputs.find("pagination=") != string::npos){
		
	}
	parsePage(page);
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
	//page.clear();
	string line;
	ifstream read (path);//reading a file
	if (read.is_open()) {
		while (! read.eof() ) {
			getline (read,line);
			page.push_back (line);
			//cout<<line<<endl;
	    }
	    read.close();
	    //parsePage(page);
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
		parseLine(*line,regex);
	}

}

void parseLine(string line, vector<string> regex){
	
	for (vector<string>::iterator pattern = regex.begin();pattern != regex.end();++pattern)
	{
	//cout << line << endl;
	delCharacter(line,' ');
	regexLine(line,*pattern);
	}
}

void regexLine(string line, string pattern){
	regex_t reg;
	regmatch_t matches[1];

	regcomp(&reg,pattern.c_str(),REG_EXTENDED|REG_ICASE);

	if (regexec(&reg,line.c_str(),1,matches,0)==0) {
	  //cout << "Match ";
	  cout << line.substr(matches[0].rm_so,matches[0].rm_eo-matches[0].rm_so);
	  //cout << " found starting at: ";
	  //cout << matches[0].rm_so;
	  //cout << " and ending at ";
	  //cout << matches[0].rm_eo;
	  //cout << " - " << line;
	  cout << endl;
	} else {
	  //cout << "Match not found.";
	  //cout << endl;
	}
	regfree(&reg);
}

void saveAsCSV(){
	int mat[3][3] = {{1, 2, 3},
	{4,5,6},{7,8,9}};

	int i, j;
	mat2[3][3];
	/*Write matrix to file*/
	FILE *fp = fopen("matrix.txt", "w");
	for(i=0; i<3; i++)
	for(j=0;j<3; j++)
	fprinf(fp, "%d\n", mat[i][j]);
	fclose(fp);
	/*Read matrix back from file*/
	fp = fopen("matrix.txt", "r");
	for(i=0; i<3; i++)
	for(j=0;j<3; j++)
	fscanf(fp, "%d", &mat2[i][j]);
	fclose(fp);

}

string delCharacter(string &line, string remove)
{
	std::string::iterator end_pos = std::remove(line.begin(), line.end(), remove);
	line.erase(end_pos, line.end());
	return line;
}
