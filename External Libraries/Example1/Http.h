//##############################################################################
//                                                                             #
// Copyright 2011 Meir yanovich,	                                           #
//	   Questions just email me to meiry242@gmail.com / meiryanovich@gmail.com  #
//                                                                             #
//##############################################################################


#ifndef Http_H
#define Http_H
#include "curl/curl.h"
#include "pthread.h"
#include <string>

using namespace std;

class Http {

    public :
        Http();
        ~Http();
        
        
        bool InitCurl();
		bool InitCurl(const std::string& url,std::string& szbuffer);
        bool DeInitCurl();
        void setUrl(const std::string& url);
		string setUrl();
		const string getBuffer();

  
    private:
        static void writer(void *buffer, size_t size, size_t nmemb,void* f);
        int setBuffer(char *buffer, size_t size, size_t nmemb);
        // Our curl objects
         CURL *m_pcurl;         
         // Write any errors in here
         char m_errorBuffer[CURL_ERROR_SIZE];
         // Write all expected data in here
         string m_szbuffer;
         string m_szUrl;
         pthread_mutex_t m_http_mutex;

};
#endif
