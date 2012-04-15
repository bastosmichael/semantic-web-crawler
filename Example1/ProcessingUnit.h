//##############################################################################
//                                                                             #
// Copyright 2011 Meir yanovich,	                                           #
//	   Questions just email me to meiry242@gmail.com / meiryanovich@gmail.com  #
//                                                                             #
//##############################################################################


#ifndef ProcessingUnit_H
#define ProcessingUnit_H

#include <vector>
#include <string>
#include <set>
#include <map>
#include <list>
#include "RegExp.h"
#include "Http.h"
#include "HashTable.h"
#include "Constants.h"
#include "Utilities.h"


using namespace std;


class ProcessingUnit {

 

public:
    ProcessingUnit();
    ~ProcessingUnit();
    bool StartTheProcessingLinks(vector<string> *linksHolder);
    bool Init();
    bool DeInit();
    bool ParseLink(string url);
    void setBaseUrl(const std::string& szUrl);
    std::string HandleRegExpResultVector(vector<std::string> RegExpResultVec);
    bool HandleLinksVector(vector<std::string>& linksVec);
    bool PreDefinedConditions(const std::string& ss,int type);
    bool HandlePageScanResults(std::multimap<std::string,std::string> resultMultiMap);
    void PreParseLink(string url);
    bool GetHtmlFromLink(std::string& szHtmlContent,const std::string& url);
    bool BatchParseLink(vector<std::string> batchLinkVec);
    bool ProcessLinkStack();
    bool SetFirstLinksQuotaForThreads(const std::string& url);
     

   

private:
    
    
    Http*    m_Http;
    Http*    m_Http2;
    RegExp*  m_RegExp;
    set<string> m_LinkContainerSet;
    std::map<std::string,HashTable*> m_UniqueMap;
    //debug : it have to be somekind of hash that holds all the baseurl the application has givven
    // but now i dont have time for that ....
    string m_baseUrl;
    HashTable* m_strTable;
    //static std::list<std::string> m_LinkStack;
    //std::map<std::string,Scraplet> m_RegExpMap;
    //std::map<std::string,InfoHolder> m_ConfigMap;

 
};
#endif