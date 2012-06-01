/*
 * Storage.cpp
 *
 *  Created on: May 5, 2012
 *      Author: michael
 */

#include "Storage.h"

namespace std {

Storage::Storage() {
	// TODO Auto-generated constructor stub

}

Storage::~Storage() {
	// TODO Auto-generated destructor stub
}

void Storage::checkForCacheFolder(){
	if(mkdir("cache",0777)==-1)//creating a directory
		{
		        cerr<<"Caching..." <<endl;
		}
}

void Storage::generateUrlHash(std::string url, Storage cache){
	Crawler Url;
	locale loc;
	const collate<char>& coll = use_facet<collate<char> >(loc);
	long hash = coll.hash(url.data(),url.data()+url.length());
	std::stringstream strstream;
	strstream << hash;
	strstream >> Url.urlhash;
	string p = "cache/" + Url.urlhash;
	Url.path=p.c_str();
	cout << "Saving to " << Url.path << " from " << url << " as " << Url.urlhash << endl;
	cache.loadPage(Url);
}

void Storage::loadPage(Crawler Url){
	//page.clear();
	string line;
	ifstream read (Url.path);//reading a file
	if (read.is_open()) {
		while (! read.eof() ) {
			getline (read,line);
			page.push_back (line);
			cout << line << endl;
	    }
	    read.close();
	} else {
		//Url.downloadUrl(*Url);
	}
}

} /* namespace std */
