#include <string>
#include <iostream>
#include <sstream>

#include <boost/filesystem.hpp>

 namespace fs = boost::filesystem;

#include "Log.h"
#include "spdlog/sinks/rotating_file_sink.h"

int main(int argc, char const *argv[])
{
    bool help = false;
    int dateFrom = -1;
    int dateTo = -1;
    int directory = -1;

    for (int i = 1; i < argc; i++) {
        if ( (strcmp( "-h", argv[i]) == 0) || (strcmp( "-help", argv[i]) == 0)) 
            help = true;
        else if((strcmp( "-f", argv[i]) == 0)) dateFrom = i+1;
        else if((strcmp( "-t", argv[i]) == 0)) dateTo = i+1;
        else if((strcmp( "-i", argv[i]) == 0)) directory = i+1;
    }
    if(argc == 1 || help){
        std::cerr << "Usage: " << argv[0] << " -f \"From Time\" -t \"To Time\" -i \"Log file directory location\""<< std::endl;
        return 0;
    }
    else if(dateFrom == -1 || dateTo == -1 || directory == -1){
        std::cerr << "Program's arguments not set."<<std::endl;
        return 0;
    }

    std::stringstream ss(argv[dateFrom]);
    int _numberOfRays = 0;
    ss >> _numberOfRays ;

    double _xPoint, _yPoint, _zPoint;
    ss = std::stringstream(argv[dateTo]);
    ss >> _xPoint;

    ss = std::stringstream(argv[directory]);

    LE::Log::Init();
    spdlog::set_pattern("%v");

    std::string path = "/path/to/directory";
    for (const auto& entry : fs::directory_iterator(path))
        std::cout << entry.path() << std::endl;

    // SL_INFO("Some Field, Other Field, And so on, Till new line");
    return 0;
}
