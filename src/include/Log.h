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

// Client log macros
#define SL_TRACE(...)         ::LE::Log::GetLogger()->trace(__VA_ARGS__)
#define SL_INFO(...)          ::LE::Log::GetLogger()->info(__VA_ARGS__)
#define SL_WARN(...)          ::LE::Log::GetLogger()->warn(__VA_ARGS__)
#define SL_ERROR(...)         ::LE::Log::GetLogger()->error(__VA_ARGS__)
#define SL_CRITICAL(...)      ::LE::Log::GetLogger()->critical(__VA_ARGS__)
