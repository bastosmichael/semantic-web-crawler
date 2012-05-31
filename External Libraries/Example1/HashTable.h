//##############################################################################
//                                                                             #
// Copyright 2011 Meir yanovich,	                                           #
//	   Questions just email me to meiry242@gmail.com / meiryanovich@gmail.com  #
//                                                                             #
//##############################################################################


#ifndef HashTable_H
#define HashTable_H
#include <set>
#include <string>
#include <vector>
 
//typedef unsigned int (*HashFunction)(const std::string&);

class HashTable
{
public:
     HashTable();
    ~HashTable();
    unsigned int ForceAdd(const std::string& str);
    unsigned int Find(const std::string& str);

    
    
    
    unsigned int RSHash  (const std::string& str);
    unsigned int JSHash  (const std::string& str);
    unsigned int PJWHash (const std::string& str);
    unsigned int ELFHash (const std::string& str);
    unsigned int BKDRHash(const std::string& str);
    unsigned int SDBMHash(const std::string& str);
    unsigned int DJBHash (const std::string& str);
    unsigned int DEKHash (const std::string& str);
    unsigned int BPHash  (const std::string& str);
    unsigned int FNVHash (const std::string& str);
    unsigned int APHash  (const std::string& str);
    
    private :
        std::set<unsigned int> HashFunctionResultSet;
        std::vector<unsigned int> hhh;
     
};
#endif

 