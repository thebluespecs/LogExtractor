#include <fstream>
#include <limits>

// filesystem as a part of c++17 standards. used to iterate input directory.
#include <filesystem>
namespace fs = std::filesystem;

#include "Log.h"
#include "cmdParser.h"

std::istream& ignoreline(std::ifstream& in, std::ifstream::pos_type& pos)
{
    pos = in.tellg();
    return in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
// functions to get the last line of a file without loading it into the physical memory.
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
    // commandline parser
    cmdParser parser(argc, argv);

    // base condition to check if given time are in order.
    if(parser.getStartTime() > parser.getEndTime()){
        std::cerr<<"Error : Start time should be less than End time.\n";
        return 1;
    }

    // logger setup
    LE::Log::Init();

    // vector to contain the target files for logs to be extracted.
    std::vector<std::string> Files;

    for (const auto& entry : fs::directory_iterator(parser.getDirPath())){
        std::ifstream file(entry.path().string());
        if (file){
            // get first logging time.
            std::string sLine;
            std::getline(file, sLine);
            // get last loggin time.
            std::string eLine = getLastLine(file);

            // base condition if the log lie in the same file.
            if(parser.getStartTime() >= sLine.substr(0, 24) && parser.getEndTime() <= eLine.substr(0, 24)){
                // single file.
                Files.push_back(entry.path().string());
                break;
            }
            // condition if target logs span multiple files.
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
    // iterating over target files and start logging the time frames.
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
