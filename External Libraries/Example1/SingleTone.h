//##############################################################################
//                                                                             #
// Copyright 2011 Meir yanovich,	                                           #
//	   Questions just email me to meiry242@gmail.com / meiryanovich@gmail.com  #
//                                                                             #
//##############################################################################


#ifndef SingleTone_H
#define SingleTone_H

#include <string>
#include <list>
#include <map>
#include "HashTable.h"
#include "pthread.h"
#include "Constants.h"
#include "curl/curl.h"



class SingleTone
{
public:
	 static SingleTone* Instance();
	 void push_back(std::string s);
	 void pop_back();
	 int size();
	 std::list<std::string>::reference back();
	 std::list<std::string>::iterator begin();
	 std::list<std::string>::iterator end();
	 void push_front(std::string s);
	 bool empty();
	  
	 unsigned int Get_m_UniqueMap_ForceAdd(const std::string& key,const std::string& url);
	 unsigned int Get_m_UniqueMap_Find(const std::string& key,const std::string& url);
	 HashTable Get_m_UniqueMap(const std::string& key);
     void Set_m_UniqueMap(const std::string& key,HashTable& hash);
     CURL* GetpCurl();

	 
protected:
		  SingleTone();
		  ~SingleTone();
		  pthread_mutex_t m_singleton_mutex;
private:	 
	 static SingleTone* m_pSingleTone;
	 std::list<std::string> m_LinkStack;
	 //std::map<std::string,HashTable*> m_UniqueMap;
	 std::map<std::string,HashTable> m_UniqueMap;
	 CURL *m_pcurl;      
};
#endif