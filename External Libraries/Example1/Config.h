//##############################################################################
//                                                                             #
// Copyright 2011 Meir yanovich,	                                           #
//	   Questions just email me to meiry242@gmail.com / meiryanovich@gmail.com  #
//                                                                             #
//##############################################################################


#ifndef CONFIG_H
#define CONFIG_H
#include <string>
#include "DataStructures.h"
#include <map>
class Config
{
    public :
	 static Config* Instance();
	 void Init();
	 std::map<std::string,InfoHolder>& Getm_ConfigMap();
	 std::map<std::string,Scraplet>& Getm_RegExpMap();
	 
    protected:
		  Config(); 
    private :
      static Config* m_pConfig; 
      std::map<std::string,InfoHolder> m_ConfigMap; 
      std::map<std::string,Scraplet> m_RegExpMap;  
};
#endif