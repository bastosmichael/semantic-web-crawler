//##############################################################################
//                                                                             #
// Copyright 2011 Meir yanovich,	                                           #
//	   Questions just email me to meiry242@gmail.com / meiryanovich@gmail.com  #
//                                                                             #
//##############################################################################

#include "Log.h"

Log::Log()
{
    m_outStream_main.open("drill.txt",std::ios::app);
    m_outStream_xml.open("drill_eventsetter.xml",std::ios::app);
    //m_outStream_flash_xml.open("drill_dump.xml",std::ios::app);
     
}

void Log::Write(const std::string logline,logType logtype)
{
    if(logtype==logType::LOG_MAIN)
    {
    m_outStream_main << logline <<  std::endl;
    }
    if(logtype==logType::LOG_FLASH_XML)
    {
        m_outStream_xml << logline <<  std::endl;
    }
    if(logtype==logType::LOG_CONSOLE)
    {   
        std::cout << logline <<  std::endl;
    }
}

void Log::DeInit()
{
     m_outStream_main.close();
     m_outStream_xml.close();
}

