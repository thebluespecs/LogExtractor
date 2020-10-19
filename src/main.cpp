#include <fstream>
#include <limits>

#include <filesystem>
namespace fs = std::filesystem;

#include "Log.h"
#include "cmdParser.h"
#include "spdlog/sinks/rotating_file_sink.h"

std::istream& ignoreline(std::ifstream& in, std::ifstream::pos_type& pos)
{
    pos = in.tellg();
    return in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string getLastLine(std::ifstream& in)
{
    std::ifstream::pos_type pos = in.tellg();

    std::ifstream::pos_type lastPos;
    while (in >> std::ws && ignoreline(in, lastPos))
        pos = lastPos;

    in.clear();
    in.seekg(pos);

    std::string line;
    std::getline(in, line);
    return line;
}

int main(int argc, char const *argv[])
{   
    cmdParser parser(argc, argv);

    if(parser.getStartTime() > parser.getEndTime()){
        std::cerr<<"Error : Start time should be less than End time.\n";
        return 1;
    }

    LE::Log::Init();
    spdlog::set_pattern("%v");

    std::vector<std::string> Files;

    for (const auto& entry : fs::directory_iterator(parser.getDirPath())){
        std::ifstream file(entry.path().string());
        if (file){
            
            std::string sLine;
            std::getline(file, sLine);
            std::string eLine = getLastLine(file);

            if(parser.getStartTime() >= sLine.substr(0, 24) && parser.getEndTime() <= eLine.substr(0, 24)){
                // single file.
                Files.push_back(entry.path().string());
                break;
            }
            else{
                // logs span over multiple files.
                if(parser.getStartTime() >= sLine.substr(0, 24) && parser.getStartTime() <= eLine.substr(0, 24)) Files.push_back(entry.path().string());
                else if(parser.getStartTime() <= sLine.substr(0, 24) && parser.getEndTime() >= eLine.substr(0, 24))Files.push_back(entry.path().string());
                else if(parser.getEndTime() >= sLine.substr(0, 24) && parser.getEndTime() <= eLine.substr(0, 24)){
                    Files.push_back(entry.path().string());
                    break;
                } 
            }
                
        }
    }
    for(auto& file : Files){
        std::ifstream infile(file);
        std::string line;
        while (true) {
            if (!getline(infile, line) || line.substr(0, 24) > parser.getEndTime()) break;
            else if(line.substr(0, 24) >= parser.getStartTime() && line.substr(0, 24) <= parser.getEndTime())
                SL_INFO(line);
        }
    }

    return 0;
}
