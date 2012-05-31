//##############################################################################
//                                                                             #
// Copyright 2011 Meir yanovich,	                                           #
//	   Questions just email me to meiry242@gmail.com / meiryanovich@gmail.com  #
//                                                                             #
//##############################################################################


#include "Http.h"
#include "SingleTone.h"
#include "mutex.h"

Http::Http()
{
    
      //m_pcurl = curl_easy_init();   
      m_pcurl = SingleTone::Instance()->GetpCurl();

}
void Http::setUrl(const std::string& url)
{
    Http::m_szUrl = url;
}

string Http::setUrl()
{
	return Http::m_szUrl;
}
// This is the writer call back function used by curl 
//(void *buffer, size_t sz, size_t n, void *f
void Http::writer(void *buffer, size_t size, size_t nmemb,void* f)
{
  // Call non-static member function.
       static_cast<Http*>(f)->setBuffer((char*)buffer,size,nmemb);

}

int Http::setBuffer(char *buffer, size_t size, size_t nmemb)
{
    // What we will return
  int result = 0;
  
  
  // Is there anything in the buffer?
  if (buffer!=NULL)
  {
    // Append the data to the buffer
    m_szbuffer.append(buffer, size * nmemb);

    // How much did we write?
    result = size * nmemb;
  }
  buffer = NULL ;   
  return result;
}

/*
bool Http::InitCurl(const std::string& url,std::string& szbuffer){
	Http::m_szUrl = url;
	if(Http::InitCurl(szbuffer))
    	return true;
   
 
 return false;
}
*/
bool Http::DeInitCurl()
{
    curl_easy_cleanup(m_pcurl);
    curl_global_cleanup();
    m_pcurl = NULL;
     
    return true;
}
bool Http::InitCurl(const std::string& url,std::string& szbuffer)
{
    //PROFILE_FUNC(); // begin profile until end of block    
    // Create our curl handle
    /*
	CURL *pcurl;
    */
    pthread_mutex_init(&m_http_mutex, NULL);
    Http::m_szUrl = url;
    // m_pcurl = curl_easy_init();   
    CURLcode result;
   // pcurl = curl_easy_init();
    
    if (m_pcurl)
    {
      // Now set up all of the curl options
      curl_easy_setopt(m_pcurl, CURLOPT_ERRORBUFFER, Http::m_errorBuffer);
      curl_easy_setopt(m_pcurl, CURLOPT_URL,m_szUrl.c_str());
      curl_easy_setopt(m_pcurl, CURLOPT_HEADER, 0);
      curl_easy_setopt(m_pcurl, CURLOPT_FOLLOWLOCATION, 1);
      curl_easy_setopt(m_pcurl, CURLOPT_WRITEFUNCTION,Http::writer);
      curl_easy_setopt(m_pcurl, CURLOPT_WRITEDATA,this);

      // Attempt to retrieve the remote page
      result = curl_easy_perform(m_pcurl);

      // Always cleanup
      //curl_easy_cleanup(m_pcurl);
    }

	// Did we succeed?
      if (result != CURLE_OK)
		return false;
	   	
	  
	szbuffer = m_szbuffer;
	
	m_szbuffer.clear();
    m_szUrl.clear();
    
    pthread_mutex_destroy(&m_http_mutex);  
	return true;	
}


const string Http::getBuffer()
{
	return m_szbuffer;
}
