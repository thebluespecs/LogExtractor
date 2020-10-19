#pragma once

#include <memory>
#include "spdlog/spdlog.h"

namespace LE{
    
    class Log{
    private:
        static std::shared_ptr<spdlog::logger> s_Logger;
    public:        
        static void Init();

        inline static std::shared_ptr<spdlog::logger>& GetLogger() { return s_Logger; }
    };
    
};

// log macro
#define SL_INFO(...)          ::LE::Log::GetLogger()->info(__VA_ARGS__)

