/*
 * Crawler.cpp
 *
 *  Created on: May 5, 2012
 *      Author: michael
 */

#include "Crawler.h"

namespace std {

Crawler::Crawler() {
	// TODO Auto-generated constructor stub

}

Crawler::~Crawler() {
	// TODO Auto-generated destructor stub
}

void Crawler::downloadUrl (Crawler *Url){
	std::string command = "cd cache && wget " + Url->url + " --output-document=" + Url->urlhash + " --continue --force-html";
	system(command.c_str());
	cout << "Downloading... " << command << endl;
	//loadPage(path,url,urlhash);
}

} /* namespace std */
