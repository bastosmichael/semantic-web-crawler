//##############################################################################
//                                                                             #
// Copyright 2011 Meir yanovich,	                                           #
//	   Questions just email me to meiry242@gmail.com / meiryanovich@gmail.com  #
//                                                                             #
//##############################################################################


#include "RegExp.h"
#include "Log.h"
#include <sstream> 

#define OVECCOUNT 30    /* should be a multiple of 3 */

std::ostringstream logprint2;
RegExp::RegExp()
{
   
}
RegExp::~RegExp()
{
}


bool RegExp::DeInit()
{
    return true;
}

bool RegExp::getRegExpResult(const std::string& szdataString,PcreWrapper* preRegExpCompiled,vector<string>* stringVec)
{
	
    int rc=0;
    std::string strMatch;
    std::string temps = preRegExpCompiled->origReg;
 
    while ( preRegExpCompiled->match ( szdataString ) ) {
        strMatch = preRegExpCompiled->GetSubStr(1);
        stringVec->push_back(strMatch);
        rc++;
    }
    if(rc==0) 
        return false;

  return true;
  
}


bool RegExp::AssambleRegExpResults(const std::string& szdataString,vector<string>* stringVec,std::string& regExpName)
{
    bool bFoundMatch=false;
    std::set<std::string>::iterator setIt ;
    map<std::string,PcreWrapper*>::iterator mapIt;

    vector<string> tempVec;
    tempVec.resize(1);
                            
//    for(std::map<std::string,PcreWrapper*>::iterator it=m_RegExpCompiledMap.begin();it!=m_RegExpCompiledMap.end();++it )
//    { 
        //get the compiled regexp by name 
        mapIt = m_RegExpCompiledMap.find(regExpName);
        if(mapIt!= m_RegExpCompiledMap.end())
        {    
            //find in set if allready we had this befor
            setIt=m_RegExpUsed.find(mapIt->first);
            //if we dont first 
            if(setIt==m_RegExpUsed.end())
            {
                //run regexp on string 
                if(getRegExpResult(szdataString,mapIt->second,stringVec))
                {
                    regExpName = mapIt->first;
                    m_RegExpUsed.insert(regExpName);
                    bFoundMatch = true;
                    
                }
            }   
        }
        
        
        /*
        if(getRegExpResult(szdataString,it->second,stringVec))
        {
           setIt=m_RegExpUsed.find(it->first);
           if(setIt!=m_RegExpUsed.end()) 
           { 
              if(it->first.compare(LINK)!=0)
              {     
                  stringVec->clear();  
                  continue;
              } else {
                  regExpName = it->first;
                  m_RegExpUsed.insert(regExpName);
                  bFoundMatch = true;
                  break;
              }
           } else {
             regExpName = it->first;
             m_RegExpUsed.insert(regExpName);
             bFoundMatch = true;
             break;
           }
          
         }
         */
     //}
   return bFoundMatch;
}

bool RegExp::SetRegExpCollection(const std::map<std::string,Scraplet> regexpCollectionMap)
{
    for(std::map<std::string,Scraplet>::const_iterator it=regexpCollectionMap.begin();it!=regexpCollectionMap.end();++it ) {
        //pcre* RegExpCompiled;
        //compileRegExp((const char*)it->second.c_str(),RegExpCompiled);
        std::string tmpStr = it->second.regExp;
        PcreWrapper* re = new PcreWrapper((const std::string)tmpStr, "gi");
        re->origReg = tmpStr;
        if(!re->IsValid())
        {
             logprint2 << "Error: Syntax error in regex, failed to compile ";
             Log::Instance().Write(logprint2.str(),Log::LOG_MAIN);
             logprint2.str("");
        } 
        else
        { 
           m_RegExpCompiledMap[it->first]=re;
        }
        
        //RegExpCompiled = NULL;
    }
  return true;  
}