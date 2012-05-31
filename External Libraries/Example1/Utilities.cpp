//##############################################################################
//                                                                             #
// Copyright 2011 Meir yanovich,	                                           #
//	   Questions just email me to meiry242@gmail.com / meiryanovich@gmail.com  #
//                                                                             #
//##############################################################################



#include "Utilities.h"
 

void Utilities::GetSystemTime(std::string& sdateStr,std::string& stimeStr)
{
    char dateStr [9];
    char timeStr [9];
    sdateStr = _strdate( dateStr);
    stimeStr = _strtime( timeStr );
    
}


void Utilities::StringSearchAndReplace(std::string& sourceStr,std::string toReplace,std::string withThisStr)
{
    std::string::size_type idx = 0;
    while (true)
    {
        idx = sourceStr.find(toReplace, idx); // find(): another string member
                                      //         see `searching' below
        if (idx == std::string::npos)
            break;

        sourceStr.replace(idx, toReplace.size(), withThisStr);
        idx += withThisStr.length();     // don't change the replacement
    }

}


bool Utilities::Sleep(long lTimeMsecs)
{
 #if defined(WIN32)
  ::Sleep(lTimeMsecs);
  return (true);
#else
  timeval tv;
  tv.tv_sec = lTimeMsecs / 1000;
  tv.tv_usec = (lTimeMsecs % 1000) * 1000;
  if (::select(0, 0, 0, 0, &tv) == -1)
     return (false);
  else
     return (true);
#endif
}


//first version of search and replace 
void Utilities::find_and_replace( std::string &source, const std::string find, std::string replace ) {
      size_t j;
      for ( ; (j = source.find( find )) != std::string::npos ; ) {
          source.replace( j, find.length(), replace );
      }
}

//secound version of search and replace 
std::string Utilities::replaceAll( const std::string& s, const std::string& f, const std::string& r ) {
	
	if ( s.empty() || f.empty() || f == r || s.find(f) == std::string::npos ) {
		return s;
	}
	std::ostringstream build_it;
	size_t i = 0;
	
	for ( size_t pos; ( pos = s.find( f, i ) ) != std::string::npos; ) {
		build_it.write( &s[i], pos - i );
		build_it << r;
		i = pos + f.size();
	}
	
	if ( i != s.size() ) {
		build_it.write( &s[i], s.size() - i );
	}
	
	return build_it.str();
}
