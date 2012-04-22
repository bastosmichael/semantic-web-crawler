//##############################################################################
//                                                                             #
// Copyright 2011 Meir yanovich,	                                           #
//	   Questions just email me to meiry242@gmail.com / meiryanovich@gmail.com  #
//                                                                             #
//##############################################################################



#include "SingleTone.h"
#include "mutex.h"


SingleTone* SingleTone::m_pSingleTone = NULL;


SingleTone::SingleTone(){
    
    pthread_mutex_init(&m_singleton_mutex, NULL);
     m_pcurl = curl_easy_init(); 

}

SingleTone::~SingleTone(){
    
    pthread_mutex_destroy(&m_singleton_mutex);

}


SingleTone* SingleTone::Instance(){

	if(m_pSingleTone == NULL){
		m_pSingleTone = new SingleTone();
	}
	return(m_pSingleTone);
}


 void SingleTone::push_back(std::string s)
 {
    mutex  m(m_singleton_mutex);
    return m_LinkStack.push_back(s);
 }
 void SingleTone::pop_back()
 {
    mutex  m(m_singleton_mutex);
    return m_LinkStack.pop_back();
 }
 int SingleTone::size()
 {
    return m_LinkStack.size();
 }
 std::list<std::string>::reference SingleTone::back()
 {
    mutex  m(m_singleton_mutex);
    return m_LinkStack.back();
 }
 std::list<std::string>::iterator SingleTone::begin()
 {
    return m_LinkStack.begin();
 }
 std::list<std::string>::iterator SingleTone::end()
 {
    return m_LinkStack.end();
 }
 void SingleTone::push_front(std::string s)
 {
    mutex  m(m_singleton_mutex);
    return m_LinkStack.push_front(s);
 }
 bool SingleTone::empty()
 {
    return m_LinkStack.empty();
 }
 
unsigned int SingleTone::Get_m_UniqueMap_ForceAdd(const std::string& key,const std::string& url)
{
    mutex  m(m_singleton_mutex);
    return m_UniqueMap[key].ForceAdd(url);
}


unsigned int SingleTone::Get_m_UniqueMap_Find(const std::string& key,const std::string& url)
{
    
    HashTable hss = m_UniqueMap[key];
    unsigned int uiRet =hss.Find(url);
    //unsigned int uiRet = m_UniqueMap[key]->Find(url);
    return uiRet;
}


HashTable SingleTone::Get_m_UniqueMap(const std::string& key)
{
    return m_UniqueMap[key];
}

void SingleTone::Set_m_UniqueMap(const std::string& key,HashTable& hash)
{
      m_UniqueMap[key] = hash;
      
}

CURL* SingleTone::GetpCurl()
{
    return m_pcurl;
}