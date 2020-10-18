#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace LE {

    std::shared_ptr<spdlog::logger> Log::s_Logger;

    void Log::Init() 
    {
        // spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");
        spdlog::set_pattern("%Y-%m-%dT%H:%M:%S.%eZ,%v");

        s_Logger = spdlog::stdout_color_mt("LogExtractor");
        s_Logger->set_level(spdlog::level::info);
    }
}
