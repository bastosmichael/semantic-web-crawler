//##############################################################################
//                                                                             #
// Copyright 2011 Meir yanovich,	                                           #
//	   Questions just email me to meiry242@gmail.com / meiryanovich@gmail.com  #
//                                                                             #
//##############################################################################


#pragma once
 
#include "ProcessingUnit.h"
#include "Log.h"
#include "Constants.h"
#include "SingleTone.h"
#include "Config.h"

#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream> 

//std::list<std::string> ProcessingUnit::m_LinkStack; 
std::string linkPassed = "";
std::ostringstream logprint;
//std::list<std::string> m_LinkStack;
int ii=0;
int jj = 0;

ProcessingUnit::ProcessingUnit()
{
    string d;
    string t;
    Utilities::GetSystemTime(t,d);
    logprint << "<list><processing date=\"" << d << "\" time=\"" << t << "\" ></processing>";
    Log::Instance().Write(logprint.str(),Log::LOG_FLASH_XML);
    logprint.str("");
 
}
ProcessingUnit::~ProcessingUnit()
{
    
}
void ProcessingUnit::setBaseUrl(const std::string& szUrl)
{
    m_baseUrl = szUrl;
}
bool ProcessingUnit::DeInit()
{
    m_Http->DeInitCurl();
    std::string d;
    std::string t;
    Utilities::GetSystemTime(t,d);
    std::ostringstream logprint;
    logprint << "<processing date=\"" << d <<"\" time=\""<< t <<"\" ></processing></list >";
    Log::Instance().Write(logprint.str(),Log::LOG_FLASH_XML);
    logprint.str("");

    
    return true;
}
bool ProcessingUnit::Init()
{
    setBaseUrl(Config::Instance()->Getm_ConfigMap()[LINKS_FILTER].BaseUrl);
    
    m_RegExp = new RegExp();
    m_Http = new Http();
   
    
    //compile all regexp in the regexp class   
    m_RegExp->SetRegExpCollection(Config::Instance()->Getm_RegExpMap());
    //set the unique map or any other properties from the scraplts strucs
    //std::map<std::string,Scraplet> rm = Config::Instance()->Getm_RegExpMap();
    
    
    std::map<std::string,Scraplet>::iterator it=Config::Instance()->Getm_RegExpMap().begin();
     
    for(;it!=Config::Instance()->Getm_RegExpMap().end();++it ) {
    
        if(it->second.IsUnique)
        {   
            //m_UniqueMap[it->first] = new HashTable();
            HashTable hst ;//= new HashTable();
           // hst.Find("ddddd");
            
            SingleTone::Instance()->Set_m_UniqueMap(it->first,hst);
        }
    }
     
   return true; 
}


bool ProcessingUnit::StartTheProcessingLinks(vector<string>  *linksHolder)
   
{   
    
  
     
    vector<string>::iterator it = linksHolder->begin();
    string szUrlTmp;
    for (it=linksHolder->begin(); it<linksHolder->end(); it++) {
            szUrlTmp = (*it);
            // here we have to set up the base url hash table this will be done in the secound phase
            PreParseLink((szUrlTmp));
    }
    
    return true;
}
/*
    prepear the first links quota for the thread workes
    i guess it needs to run only in the Dispatcher object init 
    only once per application 
*/ 
bool ProcessingUnit::SetFirstLinksQuotaForThreads(const std::string& url)
{
    std::string tempLinkFromStack;
     
    if(SingleTone::Instance()->Get_m_UniqueMap_Find(LINK,url)==-1)
    {
       SingleTone::Instance()->Get_m_UniqueMap_ForceAdd(LINK,url);
       SingleTone::Instance()->push_back(url);
    } 
    
    while(SingleTone::Instance()->size() <= Config::Instance()->Getm_ConfigMap()[LINKS_FILTER].iThreadsToInvoke)
    {
    
        tempLinkFromStack = SingleTone::Instance()->back();
        SingleTone::Instance()->pop_back();
        ParseLink(tempLinkFromStack);
        
    }
    return true;
}


void ProcessingUnit::PreParseLink(string url)
{
    
    int reminderForLastThread=0;
    int reminingLinksForThreads=0;
    int threadsPerVector=0;
   
    
    std::string tempLinkFromStack;
     
     
    if(SingleTone::Instance()->Get_m_UniqueMap_Find(LINK,url)==-1)
    {
       SingleTone::Instance()->Get_m_UniqueMap_ForceAdd(LINK,url);
       SingleTone::Instance()->push_back(url);
    } 
    
     
    while(!SingleTone::Instance()->empty())
    {
    
        tempLinkFromStack = SingleTone::Instance()->back();
        SingleTone::Instance()->pop_back();
        ParseLink(tempLinkFromStack);
        
    }
     
    
}

bool ProcessingUnit::BatchParseLink(vector<std::string> batchLinkVec)
{
    for(int y = 0 ; y < batchLinkVec.size();y++)
    {
        SingleTone::Instance()->push_front(batchLinkVec.at(y)); 
    }

return true;
}




bool ProcessingUnit::ProcessLinkStack()
{
    std::string tempLinkFromStack;
    while(!SingleTone::Instance()->empty())
    {
    
        tempLinkFromStack = SingleTone::Instance()->back();
        SingleTone::Instance()->pop_back();
        ParseLink(tempLinkFromStack);
        
    }
    return true;
}


 bool ProcessingUnit::ParseLink(string url)
 {
  try{
     string szHtmlContent="";  
     if(GetHtmlFromLink(szHtmlContent,url))
     {
          
        logprint << "Parsing "<< ii++ << " :"<<url;
		Log::Instance().Write(logprint.str(),Log::LOG_CONSOLE);
		Log::Instance().Write(logprint.str(),Log::LOG_MAIN);
		logprint.str("");
        //for debug print to log all content of html
        /*		
		logprint << szHtmlContent  <<url;
		Log::Instance().Write(logprint.str(),Log::LOG_MAIN);
		logprint.str("");
        */
         
        string s ;
        string linkTmp;
        std::multimap<std::string,std::string> FinelResultMultiMap;
        std::string cr ="\n";
        std::string empty = "";
        
        Utilities::StringSearchAndReplace(szHtmlContent,"\n","");
        //new regexp loop ,send each line of the page to process it 
        //return which regexp did the job on the line 
           vector<string> stringResultsVec;
           std:string szRegExpName;
           for(map<std::string,Scraplet>::iterator it=Config::Instance()->Getm_RegExpMap().begin();it!=Config::Instance()->Getm_RegExpMap().end();++it)
           {
                stringResultsVec.clear();
                szRegExpName = it->first;
                if(m_RegExp->AssambleRegExpResults(szHtmlContent,&stringResultsVec,szRegExpName))
                {   
                   if(szRegExpName.compare(LINK)!=0) 
                   {
                        for(int i=0;i<stringResultsVec.size();i++) {
                            
                           //set the unique map or any other properties from the scraplts strucs
                            if(it->second.IsUnique)
                            {
                                //convert the scraplet to hash value and check uniquness 
                               int iFind = SingleTone::Instance()->Get_m_UniqueMap_Find(szRegExpName,stringResultsVec.at(i));
                               if( iFind ==-1)
                               {    
                                   // no entry in the the unique map so handle the data 
                                   int hashNum  = SingleTone::Instance()->Get_m_UniqueMap_ForceAdd(szRegExpName,stringResultsVec.at(i));
                                   printf("%d",hashNum);
                                   FinelResultMultiMap.insert(std::pair<std::string,std::string>(szRegExpName,stringResultsVec.at(i)));
                               } 
                               else
                               {
                                    continue;
                               }
                                
                            }
                            else
                            {
                                FinelResultMultiMap.insert(std::pair<std::string,std::string>(szRegExpName,stringResultsVec.at(i)));
                            }
                                
                        }
                        //another system defined info we will save the fatched link
                   }
                    //handle system ops
                    //link handling must be last 
                   if(szRegExpName.compare(LINK)==0) 
                   {   
                         HandleLinksVector(stringResultsVec);                       
                   }
                   
                }
                 
                //stringResultsVec.clear();
           }
       //**** Handle Results per page ******** \\
       
       szHtmlContent.clear();
       m_RegExp->m_RegExpUsed.clear();
       
       if(FinelResultMultiMap.size()>0)
       {
        /*  
        logprint << "Start Handling Html Content from: "<<url;
		Log::Instance().Write(logprint.str(),Log::LOG_CONSOLE);
		Log::Instance().Write(logprint.str(),Log::LOG_MAIN);
		logprint.str("");
		*/
        FinelResultMultiMap.insert(std::pair<std::string,std::string>(PAGE_URL,url));
        HandlePageScanResults(FinelResultMultiMap);
        
        /*
        logprint << "Done Handling New link " << linkPassed;
        Log::Instance().Write(logprint.str(),Log::LOG_CONSOLE);
        Log::Instance().Write(logprint.str(),Log::LOG_MAIN);
        logprint.str("");
        */
       }
       stringResultsVec.clear();
       
     }
             
     } catch (exception& e)
     {
         logprint <<"exception: "<< e.what();
         Log::Instance().Write(logprint.str(),Log::LOG_MAIN);
         logprint.str("");
         cout << "exception: "<< e.what() << endl;
     }
     return true;
 }
 bool ProcessingUnit::HandlePageScanResults(std::multimap<std::string,std::string> resultMultiMap)
 {
    /*
    logprint << "Entering ProcessingUnit::HandlePageScanResults";
    Log::Instance().Write(logprint.str(),Log::LOG_CONSOLE);
    Log::Instance().Write(logprint.str(),Log::LOG_MAIN);
    */
    
   
    //lts build xml result first based on user defined logic , here it will be hard coded
    
    std::string tmpURL = "";
    std::string tmpDate = "";
    std::string tmpTime="";
    std::string tmpEvent="";
    std::string tmpHost="";
    std::string tmpLocation="";
    std::string tmpContact = "";
    std::string tmpPhone="";
    std::string tmpEmail="";
    std::string tmpWebsite="";
    std::string tmpPrice="";
    std::string tmpFullDetails="";

    std::multimap<std::string,std::string>::iterator it;
    it=resultMultiMap.find(PAGE_URL);
    if(it!=resultMultiMap.end())
        tmpURL = resultMultiMap.find(PAGE_URL)->second;
    
    it=resultMultiMap.find("Date");
    if(it!=resultMultiMap.end())
        tmpDate = resultMultiMap.find("Date")->second;

    it=resultMultiMap.find("Time");
    if(it!=resultMultiMap.end())
        tmpTime = resultMultiMap.find("Time")->second;
        
    it=resultMultiMap.find("Event");
    if(it!=resultMultiMap.end())
        tmpEvent = resultMultiMap.find("Event")->second;
    
    it=resultMultiMap.find("Host");
    if(it!=resultMultiMap.end())
        tmpHost = resultMultiMap.find("Host")->second;
        
    
    
    it=resultMultiMap.find("Website");
    if(it!=resultMultiMap.end())
        tmpWebsite = resultMultiMap.find("Website")->second;

    it=resultMultiMap.find("Price");
    if(it!=resultMultiMap.end())
        tmpPrice = resultMultiMap.find("Price")->second;
        
    it=resultMultiMap.find("Phone");
    if(it!=resultMultiMap.end())
        tmpPhone = resultMultiMap.find("Phone")->second;
    
    it=resultMultiMap.find("Email");
    if(it!=resultMultiMap.end())
        tmpEmail = resultMultiMap.find("Email")->second;
        
    
    
    it=resultMultiMap.find("Location");
    if(it!=resultMultiMap.end())
        tmpLocation = resultMultiMap.find("Location")->second;

    it=resultMultiMap.find("Contact");
    if(it!=resultMultiMap.end())
        tmpContact = resultMultiMap.find("Contact")->second;
        
    it=resultMultiMap.find("FullDetails");
    if(it!=resultMultiMap.end())
        tmpFullDetails = resultMultiMap.find("FullDetails")->second;
    
     

    

    
    string d;
    string t;
    Utilities::GetSystemTime(t,d);
    Utilities::StringSearchAndReplace(tmpFullDetails,"&","U+0026"); 
    Utilities::StringSearchAndReplace(tmpFullDetails,"<","&lt;"); 
    Utilities::StringSearchAndReplace(tmpFullDetails,">","&gt;"); 
    Utilities::StringSearchAndReplace(tmpFullDetails,"&nbsp;","&#160;"); 
    Utilities::StringSearchAndReplace(tmpFullDetails,"&ldquo;","U+201C"); 
    Utilities::StringSearchAndReplace(tmpFullDetails,"&rdquo;","U+201D"); 
    Utilities::StringSearchAndReplace(tmpFullDetails,"&rsquo;","U+2019"); 
    Utilities::StringSearchAndReplace(tmpFullDetails,"&lsquo;","U+2018"); 
      
    Utilities::StringSearchAndReplace(tmpLocation,"&","U+0026");  
    Utilities::StringSearchAndReplace(tmpLocation,"<","&lt;"); 
    Utilities::StringSearchAndReplace(tmpLocation,">","&gt;"); 
    Utilities::StringSearchAndReplace(tmpLocation,"&nbsp;","&#160;"); 
    Utilities::StringSearchAndReplace(tmpLocation,"&ldquo;","U+201C"); 
    Utilities::StringSearchAndReplace(tmpLocation,"&rdquo;","U+201D"); 
    Utilities::StringSearchAndReplace(tmpLocation,"&rsquo;","U+2019"); 
    Utilities::StringSearchAndReplace(tmpLocation,"&lsquo;","U+2018"); 
    
    Utilities::StringSearchAndReplace(tmpHost,"&","U+0026");
    Utilities::StringSearchAndReplace(tmpHost,"<","&lt;"); 
    Utilities::StringSearchAndReplace(tmpHost,">","&gt;"); 
    Utilities::StringSearchAndReplace(tmpHost,"&nbsp;","&#160;"); 
    Utilities::StringSearchAndReplace(tmpHost,"&ldquo;","U+201C"); 
    Utilities::StringSearchAndReplace(tmpHost,"&rdquo;","U+201D"); 
    Utilities::StringSearchAndReplace(tmpHost,"&rsquo;","U+2019"); 
    Utilities::StringSearchAndReplace(tmpHost,"&lsquo;","U+2018");
    
    Utilities::StringSearchAndReplace(tmpEvent,"&","U+0026"); 
    Utilities::StringSearchAndReplace(tmpEvent,"<","&lt;"); 
    Utilities::StringSearchAndReplace(tmpEvent,">","&gt;"); 
    Utilities::StringSearchAndReplace(tmpEvent,"&nbsp;","&#160;"); 
    Utilities::StringSearchAndReplace(tmpEvent,"&ldquo;","U+201C"); 
    Utilities::StringSearchAndReplace(tmpEvent,"&rdquo;","U+201D"); 
    Utilities::StringSearchAndReplace(tmpEvent,"&rsquo;","U+2019"); 
    Utilities::StringSearchAndReplace(tmpEvent,"&lsquo;","U+2018");          
    
    
    logprint <<  "  <site_link number=\""<< jj++ << "\" time=\""<< d << "\"  link=\""<< tmpURL << "\">" << 
                    "\n<Date>" << tmpDate << "</Date>" << 
                    "\n<Time>" << tmpTime << "</Time>" <<
                    "\n<Event>" << tmpEvent << "</Event>" <<
                    "\n<Host>"  << tmpHost  << "</Host>" <<
                    "\n<Location>" << tmpLocation << "</Location>" <<
                    "\n<Contact>" << tmpContact << "</Contact>" <<
                    "\n<Phone>" << tmpPhone << "</Phone>" <<
                    "\n<Email>" << tmpEmail << "</Email>" <<
                    "\n<Website>" << tmpWebsite << "</Website>" <<
                    "\n<Price>" << tmpPrice << "</Price>" <<
                     "\n<FullDetails>" << tmpFullDetails << "</FullDetails>" <<
                    "</site_link>";
    Log::Instance().Write(logprint.str(),Log::LOG_FLASH_XML);
    Log::Instance().Write(logprint.str(),Log::LOG_CONSOLE);
    logprint.str("");
    
    
   
    return true;
 }
 std::string ProcessingUnit::HandleRegExpResultVector(vector<std::string> RegExpResultVec)
 {    
    std::string szReturn = "";
    for(int i=1;i<RegExpResultVec.size();i++) {
          szReturn  = RegExpResultVec.at(i);
    }
    return szReturn;
 }
 
 bool ProcessingUnit::HandleLinksVector(vector<std::string>& linksVec)
 {
    std::string linkTmp;
    vector<std::string> tempVec;
    //sort the vector and make the elements in vector unique 
    std::vector<std::string>::iterator new_end_pos;
    std::sort(linksVec.begin(),linksVec.end());
    new_end_pos = std::unique(linksVec.begin(),linksVec.end());
    linksVec.erase( new_end_pos, linksVec.end() );
    
    //print only matchs 
    for(int i=0;i<linksVec.size();i++) {
        //first check if it failed into predefined
         
      if(SingleTone::Instance()->Get_m_UniqueMap_Find(LINK,linksVec.at(i))==-1)
      {  
        if(PreDefinedConditions(linksVec.at(i),1)) 
        {   
            SingleTone::Instance()->Get_m_UniqueMap_ForceAdd(LINK,linksVec.at(i));
            continue;
        } 
        else 
        {
            //constarct ful link out of partaial links using the domain name.
            if(linksVec.at(i).find("http:")==string::npos){
                linkTmp.append(m_baseUrl);
                linkTmp.append(linksVec.at(i));
            } else {                            
                linkTmp.append(linksVec.at(i));
            }
            //all the links must be under one domain we dont what to scan all the net ...
            if(linkTmp.find(m_baseUrl)!=string::npos)
            {
                if(SingleTone::Instance()->Get_m_UniqueMap_Find(LINK,linkTmp)==-1)
                {
                   SingleTone::Instance()->Get_m_UniqueMap_ForceAdd(LINK,linkTmp);
                   tempVec.push_back(linkTmp); 
                   SingleTone::Instance()->push_front(linkTmp); 
                } 
            }
        }
       }
    linkTmp.clear();
    }
    
   
   linksVec.swap(tempVec);
   if(tempVec.size()==0)
   {
       tempVec.clear();
       return false;
   }
   tempVec.clear();
   return true;
 }


 bool ProcessingUnit::PreDefinedConditions(const std::string& ss,int type)
 {
 // later will be loaded from config
    bool bFound = false;
    if(type==1)
    {
        std::string szFilter="";
        std::set<std::string>::const_iterator it;
        //not have 
         
        for (it=Config::Instance()->Getm_ConfigMap()[LINKS_FILTER].linksBlackList.begin(); it!=Config::Instance()->Getm_ConfigMap()[LINKS_FILTER].linksBlackList.end(); it++)
        {
            szFilter = *it;
            if(ss.find(szFilter)!=string::npos)
            {
               bFound = true;
               break; 
            }
          szFilter = "";  
        }
        //must have 
        if(!bFound)
        {
            for (it=Config::Instance()->Getm_ConfigMap()[LINKS_FILTER].linksMastHaveList.begin(); it!=Config::Instance()->Getm_ConfigMap()[LINKS_FILTER].linksMastHaveList.end(); it++)
            {
                szFilter = *it;
                if(ss.find(szFilter)==string::npos)
                {
                   bFound = true;
                   break; 
                }
               szFilter = "";   
            }
        }
    }
 return bFound;
 }
 
 bool ProcessingUnit::GetHtmlFromLink(std::string& szHtmlContent,const std::string& url)
 {
    //fatch url's 
     if(m_Http->InitCurl(url,szHtmlContent))
     {  
        return true;
     }    
     
    return false; 
 } 
 
 
 
