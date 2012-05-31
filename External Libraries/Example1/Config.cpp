//##############################################################################
//                                                                             #
// Copyright 2011 Meir yanovich,	                                           #
//	   Questions just email me to meiry242@gmail.com / meiryanovich@gmail.com  #
//                                                                             #
//##############################################################################

#include "Config.h"
#include "Constants.h"
 

Config* Config::m_pConfig = NULL;

Config::Config()
{
	; 
}

Config* Config::Instance()
{

	if(m_pConfig == NULL){
		m_pConfig = new Config();
	}
	return(m_pConfig);
}

void Config::Init()
{
    //debug test regexp 
    InfoHolder infoHolder;
    //sholud not be in links
    infoHolder.linksBlackList.insert("profile/view/");
    infoHolder.linksBlackList.insert("#comments");
    infoHolder.linksBlackList.insert("#taf");
    infoHolder.linksBlackList.insert("profile/addfavorite/");
    infoHolder.linksBlackList.insert("users/username/");
    infoHolder.linksBlackList.insert("users/total/");
    infoHolder.linksBlackList.insert("href");
    infoHolder.linksBlackList.insert("javascript");
    infoHolder.linksBlackList.insert("#");
    
    //must to be in links 
	/* here you repace the dummy url with your site you wish to drill down */
    infoHolder.linksMastHaveList.insert("www.xxxxxx.com/xxxx/foo");
    infoHolder.BaseUrl = "http://www.xxxxxx.com/";
    
    
    //set up threads config 
     
    infoHolder.iThreadsToInvoke = 1;
    infoHolder.iThreadPoolSize = 1;
    
	//set the config map with the first part of the configuration.
    m_ConfigMap[LINKS_FILTER]=infoHolder;
    
	/*
	Scraplet are regexp units each unit hold rule . the rule is regexp
	that capture/scrap string from the current web page the drill spider visit
	Scraplet.regExp : is the regexp string 
	Scraplet.IsUnique : look only for one pattern result of the regexp if true 
	if false meny patterns can be capture in the same page
	*/
    Scraplet s1_Date;
    Scraplet s1_Time;
    Scraplet s1_Event;
    Scraplet s1_Host;
    Scraplet s1_Location;
    Scraplet s1_Contact;
    Scraplet s1_Phone;
    Scraplet s1_Email;
    Scraplet s1_Website;
    Scraplet s1_Price;
    Scraplet s1_FullDetails;
     
	/*
		this is the regexp that will be respansible for the links parsing on every page 
		i keep here the regexp example's put i dont provide any link base url link .
		you can see here the regexp can be complex and you have to master them.
	*/
    Scraplet s1_link;
    
    s1_link.regExp = "<a[^>]+href\\s*=\\s*[\"']?([^\"'> ]+)";
    s1_link.IsUnique = true;
    
    //s1_Date.regExp = "<\\s*font\\s*class=[\"']cat_date[\"']>\\s*>?\\s*Date.*<\\s*h5\\s*class=[\"']description_bold[\"']>\\s*>?(.*?)<\\s*br\\s*>";
    s1_Date.regExp = "<\\s*font\\s*class=[\"']cat_date[\"']>\\s*>?\\s*Date.+?\\s*\/font>.+?description_bold[\"']>(.+?)<";
    s1_Date.IsUnique = true;
    
    //s1_Time.regExp = "<\\s*font\\s*class=[\"']cat_date[\"']>\\s*>?\\s*Time.*<\\s*font\\s*class=[\"']description_bold[\"']>\\s*>?(.*?)<\\s*br\\s*>";
    s1_Time.regExp = "<\\s*font\\s*class=[\"']cat_date[\"']>\\s*>?\\s*Time.+?\\s*\/font>.+?description_bold[\"']>(.+?)<";
    s1_Time.IsUnique = true;
    
    s1_Event.regExp = "<\\s*font\\s*class=[\"']cat_date[\"']>\\s*>?\\s*Event.*<\\s*h1\\s*class=[\"']full_title[\"']>\\s*>?(.*?)<\\s*\/\\s*h1\\s*>";
    s1_Event.IsUnique = true;
    
    s1_Host.regExp = "<\\s*font\\s*class=[\"']cat_date[\"']>\\s*>?\\s*Host.*<\\s*h4\\s*class=[\"']full_title[\"']>\\s*>?(.*?)<\\s*\/\\s*h4\\s*>";
    s1_Host.IsUnique = true;
    
    s1_Location.regExp = "<\\s*font\\s*class=[\"']cat_date[\"']>\\s*>?\\s*Location.*<\\s*h4\\s*class=[\"']description_bold[\"']>\\s*>?(.*?)<\\s*\/\\s*h4\\s*>";
    s1_Location.IsUnique = true;
    
    //s1_Contact.regExp = "<\\s*font\\s*class=[\"']cat_date[\"']>\\s*>?\\s*Contact.*<\\s*font\\s*class=[\"']description_bold[\"']>\\s*>?(.*?)<\\s*\/\\s*font\\s*>";
    //s1_Contact.regExp   = "<\\s*font\\s*class=[\"']cat_date[\"']>\\s*>?\\s*Contact.+?\\s*\/font>.+?description_bold[\"']>(.+?)<\/font>";
    s1_Contact.regExp   ="<\\s*font\\s*class=[\"']cat_date[\"']>\\s*>?\\s*Contact.+?\\s*\/font>.+?description_bold[\"']>?([a-zA-Z0-9.\\s-_]+[^\/<])?";
    s1_Contact.IsUnique = true;
    
   // s1_Phone.regExp = "<\\s*font\\s*class=[\"']cat_date[\"']>\\s*>?\\s*Phone.*<\\s*font\\s*class=[\"']description_bold[\"']>\\s*>?(.*?)<\\s*\/\\s*font\\s*>";
    //s1_Phone.regExp ="<\\s*font\\s*class=[\"']cat_date[\"']>\\s*>?\\s*Phone.+?\\s*\/font>.+?description_bold[\"']>(.+?)<\/font>";
    s1_Phone.regExp = "<\\s*font\\s*class=[\"']cat_date[\"']>\\s*>?\\s*Phone.+?\\s*\/font>.+?description_bold[\"']>?([a-zA-Z0-9.\\s-_]+[^\/<])?";
    s1_Phone.IsUnique = true;
    
    s1_Email.regExp ="<\\s*font\\s*class=[\"']cat_date[\"']>\\s*>?\\s*Email.*<\\s*font \\s*class=[\"']description_bold[\"']>\\s*>?.*>\\s*([A-Z0-9._%+-]+@[A-Z0-9.-]+\.[A-Z]{2,10}).*<\\s*\/\\s*font\\s*>";
    s1_Email.IsUnique = true;
    
    
    s1_Website.regExp = "<\\s*font\\s*class=[\"']cat_date[\"']>\\s*>?\\s*Website.*<\\s*h5\\s*class=[\"']description_bold[\"']>\\s*>?.*\\s*<a[^>]+href\\s*=\\s*[\"']?([^\"'> ]+).*<\\s*\/\\s*h5\\s*>";
    s1_Website.IsUnique = true;
    
    s1_Price.regExp = "<\\s*font\\s*class=[\"']cat_date[\"']>\\s*>?\\s*Price.*<\\s*font\\s*class=[\"']description_bold[\"']>\\s*>?(.*?)<\\s*\/\\s*font\\s*>";
    s1_Price.IsUnique = true;
    
    s1_FullDetails.regExp = "<\\s*font\\s*class=[\"']cat_date[\"']>\\s*>?\\s*Full\\sdetails.*<\\s*font\\s*class=[\"']description_details[\"']>\\s*>?(.*?)<\\s*\/\\s*font\\s*>";
    s1_FullDetails.IsUnique = true;
    
    
    
    
    //NOTE the names for the keys will be given from the user 

    m_RegExpMap["Date"]=s1_Date;
    m_RegExpMap["Time"]=s1_Time;
    m_RegExpMap["Event"]=s1_Event;
    m_RegExpMap["Host"]=s1_Host;
    m_RegExpMap["Location"]=s1_Location;
    
    m_RegExpMap["Contact"]=s1_Contact;
    m_RegExpMap["Phone"]=s1_Phone;
    m_RegExpMap["Email"]=s1_Email;
    m_RegExpMap["Website"]=s1_Website;
    m_RegExpMap["Price"]=s1_Price;
    m_RegExpMap["FullDetails"]=s1_FullDetails;
    
    m_RegExpMap["link"]=s1_link;
    
   
}

std::map<std::string,InfoHolder>& Config::Getm_ConfigMap()
{
    return m_ConfigMap;
}

std::map<std::string,Scraplet>& Config::Getm_RegExpMap()
{
    return m_RegExpMap;
}



//DOTO need to move here all the config