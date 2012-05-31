#ifndef RegExp_H
#define RegExp_H

#include "PcreWrapper.h"
#include <string>
#include <vector>
#include <map>
#include <set>
#include "Constants.h"
#include "DataStructures.h"

 


using namespace std;
class RegExp 
{
public :
	RegExp();
	~RegExp();
	
	bool getRegExpResult(const std::string& szdataString,PcreWrapper* preRegExpCompiled,vector<string>* stringVec);
    bool DeInit();
    bool SetRegExpCollection(std::map<std::string,Scraplet> regexpCollectionMap);
    bool AssambleRegExpResults(const std::string& szdataString,vector<string>* stringVec,std::string& regExpName);
    std::set<std::string> m_RegExpUsed;
private:
    std::map<std::string,PcreWrapper*> m_RegExpCompiledMap;

};
#endif