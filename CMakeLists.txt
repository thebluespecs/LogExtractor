cmake_minimum_required(VERSION 3.1...3.14)
project( LogExtractor )

#-------------VENDOR--------------------
set(vspdlog ./vendor/spdlog/include)

#-------------SOURCE--------------------
SET(source ./src/main.cpp ./src/Log.cpp)
include_directories(./src/include ${vspdlog})

# -----------EXECUTION------------------
ADD_EXECUTABLE(LogExtractor ${source})
set_target_properties(LogExtractor PROPERTIES CXX_STANDARD 17 CXX_EXTENSIONS OFF)