//##############################################################################
//                                                                             #
// Copyright 2011 Meir yanovich,	                                           #
//	   Questions just email me to meiry242@gmail.com / meiryanovich@gmail.com  #
//                                                                             #
//##############################################################################


#ifndef Log_H
#define Log_H

#include <string>
#include <fstream> 
#include <iostream>
 

class Log {
public :
 static Log& Instance() {
    static Log theLog;
    return theLog;
 }

 enum logType{
     LOG_MAIN,
     LOG_FLASH_XML,
     LOG_CONSOLE
     
 };

void Write(const std::string logline,logType logtype);
void DeInit();


private:
  Log();          // ctor is hidden
  Log(Log const&);      // copy ctor is hidden
  Log& operator=(Log const&);  // assign op is hidden

  std::ofstream m_outStream_main;
  std::ofstream m_outStream_xml;;
  std::ofstream m_outStream_dump;
};
#endif