#pragma once

#include <string>
#include <iostream>
#include <sstream>

class cmdParser
{
private:
    bool help = false;
    int dateFrom = -1;
    int dateTo = -1;
    int directory = -1;
    std::string startT, endT, path;
public:
    cmdParser(const int& argc, char const *argv[]){
        for (int i = 1; i < argc; i++) {
            if ( (strcmp( "-h", argv[i]) == 0) || (strcmp( "-help", argv[i]) == 0)) 
                help = true;
            else if((strcmp( "-f", argv[i]) == 0)) dateFrom = i+1;
            else if((strcmp( "-t", argv[i]) == 0)) dateTo = i+1;
            else if((strcmp( "-i", argv[i]) == 0)) directory = i+1;
        }
        if(argc == 1 || help){
            std::cerr << "Usage: " << argv[0] << " -f \"From Time\" -t \"To Time\" -i \"Log file directory location\""<< std::endl;
        }
        else if(dateFrom == -1 || dateTo == -1 || directory == -1){
            std::cerr << "Program's arguments not set."<<std::endl;
            // return 0;
        }
        
        std::stringstream ss(argv[dateFrom]);
        ss >> startT ;

        ss = std::stringstream(argv[dateTo]);
        ss >> endT;

        ss = std::stringstream(argv[directory]);
        ss >> path;
    }
    ~cmdParser(){}

    inline std::string& getStartTime(){ return startT;}
    inline std::string& getEndTime(){ return endT;}
    inline std::string& getDirPath(){ return path;}
};

